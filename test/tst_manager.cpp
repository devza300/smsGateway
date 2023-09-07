#include <QtTest>

// add necessary includes here
#include "smsGateway.h"

class ManagerTest : public QObject
{
    Q_OBJECT

public:
    ManagerTest();
    ~ManagerTest();

private slots:
    /// наполнение очереди на отправку
    void test_createQueue();

    /// подключение шлюзов
    void test_appendDevice();

    /// добавит сообщения
    void test_sendMessage();

private:
    smsGateway::Manager mm_manager;

};

ManagerTest::ManagerTest() :
    mm_manager(nullptr)
{

}

ManagerTest::~ManagerTest()
{

}

void ManagerTest::test_createQueue()
{
    mm_manager.sendMessage("+375293453452", "11111111");
    mm_manager.sendMessage("+375291231234", "22222222");
    mm_manager.sendMessage("+375293243253", "33333333");
    mm_manager.sendMessage("+375295555557", "44444444");
    mm_manager.sendMessage("+375297878778", "55555555");
    mm_manager.sendMessage("+375294454555", "66666666");
    mm_manager.sendMessage("+375292232333", "77777777");
    mm_manager.sendMessage("+375296456555", "88888888");
    mm_manager.sendMessage("+375291123546", "99999999");
}

void ManagerTest::test_appendDevice()
{
    mm_manager.addGatewayDevice("192.168.1.1");
    mm_manager.addGatewayDevice("192.168.1.2");
    mm_manager.addGatewayDevice("192.168.1.3");

    // whait release queue
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void ManagerTest::test_sendMessage()
{
    mm_manager.sendMessage("+375291111111", "ASDASDASDASDASDASDASDASD");
    mm_manager.sendMessage("+375293333333", "ячсячсячсячсячсячсячсячс");
    mm_manager.sendMessage("+375294444444", "123123123123123123123123");

    // whait send
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

QTEST_APPLESS_MAIN(ManagerTest)

#include "tst_manager.moc"
