#ifndef SMSGATEWAY_H
#define SMSGATEWAY_H

#include <QObject>
#include <QQueue>
#include <QSet>
#include <condition_variable>
#include <shared_mutex>
#include <thread>

namespace smsGateway {

/*!
 * \brief The Manager class - класс управления SMS-шлюзами
 */
class Manager : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Manager - инициализация класса
     * \param parent - родительский объект
     */
    Manager(QObject *parent);

    /// оставнов потоков устройств, очистка данных
    ~Manager();

    /*!
     * \brief sendMessage - отправить SMS
     * \param phone - номер телефона
     * \param message - текст сообщения
     */
    void sendMessage(const QString &phone, const QString &message);

    /*!
     * \brief addGatewayDevice - добавить устройстов
     * \param ip - адрес страницы управления
     */
    void addGatewayDevice(const QString &ip);

    /*!
     * \brief releaseGateway - удалить устройство
     * \param ip - адрес страницы управления
     */
    void releaseGateway(const QString &ip);

private:
    /*!
     * \brief initializeDevice - инициализация устройства в потоке
     * \param ip - адрес страницы управления
     */
    void initializeDevice(const QString &ip);

    /*!
     * \brief isDeviceActive - проверка выключения шлюза
     * \param ip - адрес страницы управления
     * \return - признак выключения
     */
    bool isDeviceActive(const QString &ip);

    /*!
     * \brief dequeueMessage - отправка сообщения из очереди
     * \param reason - причина отправки (из очереди или по сигналу)
     */
    void dequeueMessage(const QString &reason);

    /*!
     * \brief isQueueEmpty - проверка наличия сообщений в очереди на отправку
     * \return - признак окончания очереди
     */
    bool isQueueEmpty();

    /*!
     * \brief waitAndSend - ожидание данных для отправки
     */
    void waitAndSend();

    /*!
     * \brief createDeviceLoop - создание отдельного потока для взаимодействия со шлюзом
     * \param ip - адрес страницы управления
     */
    void createDeviceLoop(const QString &ip);

private:
    std::atomic<bool> mm_isRunning;                 //!< флаг выполнения потоков шлюзов

    std::shared_mutex mm_mutextDeviceList;          //!< безопасный доступ к управлению шлюзами
    QSet<QString> mm_deviceList;                    //!< список шлюзов для управления потоками устройств

    std::mutex mm_mutextQueue;                      //!< безопасный доступ к очереди сообщений
    std::condition_variable mm_queueNotEmpty;       //!< оповещение потоков о пявении данных для отправки
    QQueue<QPair<QString, QString>> mm_queueSend;   //!< очередь сообщений

};

} // namespace smsGateway

#endif // SMSGATEWAY_H
