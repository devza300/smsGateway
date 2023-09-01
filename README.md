![Alt text](task.jpg?raw=true "Задание")

# Инсрукция по использованию

Запустить юнит-тест.

## Результаты тестирования:

```
********* Start testing of ManagerTest *********
Config: Using QtTest library 6.4.2, Qt 6.4.2 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 10.3.1 20210422 (Red Hat 10.3.1-1)), debian 12
PASS   : ManagerTest::initTestCase()
PASS   : ManagerTest::test_createQueue()
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  initialize the device by IP:  "192.168.1.3"
QDEBUG : ManagerTest::test_appendDevice() [ 13792372909686658424 ]  initialize the device by IP:  "192.168.1.1"
QDEBUG : ManagerTest::test_appendDevice() [ 470092387249008095 ]  initialize the device by IP:  "192.168.1.2"
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  new smsGateway ready by IP:  "192.168.1.3"
QDEBUG : ManagerTest::test_appendDevice() [ 13792372909686658424 ]  new smsGateway ready by IP:  "192.168.1.1"
QDEBUG : ManagerTest::test_appendDevice() [ 470092387249008095 ]  new smsGateway ready by IP:  "192.168.1.2"
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  "sending data by queue"  :  "+375293453452"  <-  "11111111"
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  "sending data by queue"  :  "+375291231234"  <-  "22222222"
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  "sending data by queue"  :  "+375293243253"  <-  "33333333"
QDEBUG : ManagerTest::test_appendDevice() [ 7231786545424928180 ]  "sending data by queue"  :  "+375295555557"  <-  "44444444"
PASS   : ManagerTest::test_appendDevice()
QDEBUG : ManagerTest::test_sendMessage() [ 7231786545424928180 ]  "sending data by queue"  :  "+375297878778"  <-  "55555555"
QDEBUG : ManagerTest::test_sendMessage() [ 7231786545424928180 ]  "sending data by queue"  :  "+375294454555"  <-  "66666666"
QDEBUG : ManagerTest::test_sendMessage() [ 7231786545424928180 ]  "sending data by queue"  :  "+375292232333"  <-  "77777777"
QDEBUG : ManagerTest::test_sendMessage() [ 7231786545424928180 ]  "sending data by queue"  :  "+375296456555"  <-  "88888888"
QDEBUG : ManagerTest::test_sendMessage() [ 7231786545424928180 ]  "sending data by queue"  :  "+375291123546"  <-  "99999999"
PASS   : ManagerTest::test_sendMessage()
PASS   : ManagerTest::cleanupTestCase()
Totals: 5 passed, 0 failed, 0 skipped, 0 blacklisted, 28004ms
********* Finished testing of ManagerTest *********
[ 7231786545424928180 ]  "sending data by notify"  :  "+375291111111"  <-  "ASDASDASDASDASDASDASDASD"
[ 7231786545424928180 ]  smsGateway released by IP:  "192.168.1.3"
[ 470092387249008095 ]  "sending data by queue"  :  "+375293333333"  <-  "ячсячсячсячсячсячсячсячс"
[ 470092387249008095 ]  smsGateway released by IP:  "192.168.1.2"
[ 13792372909686658424 ]  "sending data by queue"  :  "+375294444444"  <-  "123123123123123123123123"
[ 13792372909686658424 ]  smsGateway released by IP:  "192.168.1.1"
```
