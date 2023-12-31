#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QString>
//#include <winsock2.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <ws2tcpip.h>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>

// структура для конфігурації сирени
typedef struct
{
    QString name;
    QString fatherName;
    sockaddr_in ipAddress;
    QString macAddress;
    int id;
} alarmConfig_t;

// структура для конфігурації регіонів
typedef struct
{
    QString name;
    QString fatherName;
    int id;
} regionConfig_t;


//зробити щоб при створені регіонів або сирен створювався файл в який я б їх записува, потім з цим ж файлом працював
  //  назви обєктів мають бути унікальними, треба перевірити чи унікальні назви, якщо назва повторюється, то сповіщати про це користувача
    // ну і зробити щоб у діалогі з сиреною, вискакувало одне спільне месендж бокс при пустих полях

class ConfigManager
{
public:
    ConfigManager();
    ~ConfigManager();

    bool addAlarmConfig(const alarmConfig_t& alarmConfig); // додати конфігурацію сирени
    bool addRegionConfig(const regionConfig_t& regionConfig); // додати конфігурацію регіону
    bool isNameUnique(const QString& name); // перевірити чи унікальна назва обєкта
    void saveToFile(const alarmConfig_t& alarmConfig);  // зберегти конфігурацію сирени в файл
    void saveToFile(const regionConfig_t& regionConfig); // зберегти конфігурацію регіону в файл
    void readFromAlarmConfigFile(); // прочитати конфігурацію сирени з файлу
    void readFromRegionConfigFile(); // прочитати конфігурацію сирени з файлу
    QList<alarmConfig_t> getAlarmConfigList(); // отримати список конфігурацій сирен
    QList<regionConfig_t> getRegionConfigList(); // отримати список конфігурацій регіонів
    bool deleteAlarmConfigFromFile(const QString& name); // видалити конфігурацію сирени
    bool deleteRegionConfigFromFile(const QString& name); // видалити конфігурацію сирени




private:
    QList<alarmConfig_t> alarmConfigList; // список конфігурацій сирен
    QList<regionConfig_t> regionConfigList; // список конфігурацій регіонів
    QFile alarmFile; // файл для збереження конфігурацій сирен
    QFile regionFile; // файл для збереження конфігурацій регіонів
    void overwriteRegionFile(); // переписати дані з списку в файл

};

#endif // CONFIGMANAGER_H
