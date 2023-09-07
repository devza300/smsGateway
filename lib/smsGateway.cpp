#include "smsGateway.h"

#include <QDebug>
#include <QRandomGenerator>
#include <random>

using namespace smsGateway;

#define THREAD_DEBUG qDebug() << "[" << std::hash<std::thread::id> {} (std::this_thread::get_id())  << "] "

Manager::Manager(QObject *parent) : QObject(parent)
{
    mm_isRunning = true;
}

Manager::~Manager()
{
    mm_isRunning = false;

    // очистка очереди сообщений
    std::unique_lock queueLock(mm_mutextQueue);
    mm_queueSend.clear();
    mm_queueNotEmpty.notify_all();
}

void Manager::sendMessage(const QString &phone, const QString &message)
{
    // помещаем отправку СМС в очередь
    std::unique_lock queueLock(mm_mutextQueue);
    mm_queueSend.enqueue({phone, message});

    // оповещене потоков о появлении данных для отправки
    mm_queueNotEmpty.notify_all();
}

void Manager::addGatewayDevice(const QString &ip)
{
    // безопасный доступ к списку шлюзов на чтение
    std::shared_lock lock(mm_mutextDeviceList);

    if (mm_deviceList.contains(ip))
    {
        qDebug() << "already using the device by IP: " << ip;
        return;
    }

    // создание нового потока для устройства
    std::thread deviceThread(&Manager::createDeviceLoop, std::ref(*this), ip);
    deviceThread.detach();
}

void Manager::releaseGateway(const QString &ip)
{
    // доступ к списку шлюзов на запись
    std::unique_lock lock(mm_mutextDeviceList);
    mm_deviceList.remove(ip);
}

void smsGateway::Manager::initializeDevice(const QString &ip)
{
    // доступ к списку шлюзов на запись
    std::unique_lock lock(mm_mutextDeviceList);

    // TODO XMLHttpRequest to initialize devce
    // demo - sleep
    std::uniform_int_distribution dist(1, 2);
    int seconds = dist(*QRandomGenerator::global());
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    mm_deviceList.insert(ip);
}

bool Manager::isDeviceActive(const QString &ip)
{
    // безопасный доступ к списку шлюзов на чтение
    std::shared_lock lock(mm_mutextDeviceList);

    // завершить выполнение, если шлюз был отключен
    return mm_deviceList.contains(ip);
}

void smsGateway::Manager::dequeueMessage(const QString &reason)
{
    std::pair<QString, QString> data;
    // удаление блокировки после получения данных, т.к. она будет выполняться на время сна потока
    {
        std::unique_lock queueLock(mm_mutextQueue);
        data = mm_queueSend.dequeue();
    }

    // TODO XMLHttpRequest to sendMsg
    // demo - sleep
    std::uniform_int_distribution dist(0, 1);
    int seconds = dist(*QRandomGenerator::global());
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    THREAD_DEBUG << reason << " : " << data.first << " <- " << data.second;
}

bool Manager::isQueueEmpty()
{
    std::unique_lock queueLock(mm_mutextQueue);
    return mm_queueSend.isEmpty();
}

void Manager::waitAndSend()
{
    // разблокировать mutex после сигнала для отправки сообщений
    {
        THREAD_DEBUG << "wait notify_all()";
        std::unique_lock queueLock(mm_mutextQueue);
        mm_queueNotEmpty.wait(queueLock, [&] () { return !mm_queueSend.isEmpty() || !mm_isRunning; });
    }

    if (!mm_isRunning)
        return;

    // получено оповещение о появлении в очереди сообщений - вополнить обработку
    dequeueMessage("sending data by notify");
}

void Manager::createDeviceLoop(const QString &ip)
{
    THREAD_DEBUG << "initialize the device by IP: " << ip;

    initializeDevice(ip);
    THREAD_DEBUG << "new smsGateway ready by IP: " << ip;

    while (mm_isRunning && isDeviceActive(ip))
    {
        // если в очереди есть данные - выполнить обработку
        if (!isQueueEmpty())
        {
            // в очереди есть данные для отправки
            dequeueMessage("sending data by queue");
            continue;
        }

        // ожидание сигнала появления данных для отправки
        waitAndSend();
    }

    THREAD_DEBUG << "smsGateway released by IP: " << ip;
}
