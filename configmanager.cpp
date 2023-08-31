#include "configmanager.h"

// виклик конструктора
ConfigManager::ConfigManager(): alarmFile("alarmConfig.dat"), regionFile("regionConfig.dat"), // ініціалізація файлів для збереження конфігурацій сирен та регіонів
    alarmConfigList(), regionConfigList() // ініціалізація списків конфігурацій сирен та регіонів
{
    readFromAlarmConfigFile(); // прочитати конфігурацію сирени з файлу
    readFromRegionConfigFile(); // прочитати конфігурацію регіонів з файлу

}
ConfigManager::~ConfigManager()
{

}

bool ConfigManager::addAlarmConfig(const alarmConfig_t &alarmConfig)
{
    if(isNameUnique(alarmConfig.name))
    {
        alarmConfigList.append(alarmConfig);
        return true;
    }

    QMessageBox::warning(nullptr, "Warning", "Сирена з таким іменне вже існує");
    return false;

}

bool ConfigManager::addRegionConfig(const regionConfig_t &regionConfig)
{
    if(isNameUnique(regionConfig.name))
    {
        regionConfigList.append(regionConfig);
        return true;
    }

    QMessageBox::warning(nullptr, "Warning", "Регіон з таким іменне вже існує");
    return false;

}

bool ConfigManager::isNameUnique(const QString& name)
{
    for (const auto& alarmConfig : alarmConfigList)
    {
        if (alarmConfig.name == name)
        {
            qDebug() << "Alarm name is not unique";
            return false;
        }
    }
    for (const auto& regionConfig : regionConfigList)
    {
        if (regionConfig.name == name)
        {
            qDebug() << "Region name is not unique";
            return false;
        }
    }
    return true;
}

void ConfigManager::saveToFile(const alarmConfig_t &alarmConfig /* дописати по прикладу saveToFile регіону*/)
{
    if(!alarmFile.open(QIODevice::Append))// зробити аналогічну команду  Append і для регіонів
    {
        qDebug() << "Failed to open alarmConfig.dat file";
        return;
    }
    QDataStream out(&alarmFile); // створення потоку для запису в файл
    out.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність
    QString ipAddressString = QString::fromLatin1(reinterpret_cast<const char*>(&alarmConfig.ipAddress),
                                                  sizeof(alarmConfig.ipAddress)); // перетворення ip адреси з структури в строку для запису SOCKADDR_IN у потік
    //qint64 bytesWritten;
    //bytesWritten = out.writeRawData(reinterpret_cast<const char*>(&alarmConfig), sizeof(alarmConfig_t)); // запис в файл конфігурації сирени

    out << alarmConfig.name << ipAddressString << alarmConfig.macAddress << alarmConfig.id; // запис в файл конфігурації сирени
    alarmFile.close();

    if(out.status() != QDataStream::Ok)
    {
        qDebug() << "Error writing to alarmFile.";
    }
    else
    {
        qDebug() <<  "Data was successfully written to alarmFile.";
    }
}

void ConfigManager::saveToFile(const regionConfig_t& regionConfig)
{

    if(!regionFile.open(QIODevice::Append))
    {
        qDebug() << "Failed to open regionConfig.dat file";
        return;
    }

    QDataStream out(&regionFile); // створення потоку для запису в файл
    out.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність
    //qint64 bytesWritten;
    //bytesWritten = out.writeRawData(reinterpret_cast<const char*>(&regionConfig), sizeof(regionConfig_t)); // запис в файл конфігурації сирени
    out << regionConfig.name << regionConfig.fatherName <<regionConfig.id;
    regionFile.close();

    if(out.status() != QDataStream::Ok)
    {
        qDebug() << "Error writing to regionFile.";
    }
    else
    {
        qDebug() <<  "Data was successfully written to regionFile.";
    }
}


void ConfigManager::readFromAlarmConfigFile()
{
    if(!alarmFile.exists())
    {
        qDebug() << "File does not exist";
        return;
    }
    if(!alarmFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open alarmConfig.dat file";
        return ;
    }
    QDataStream in(&alarmFile); // створення потоку для запису в файл
    in.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність
    qint64 bytesRead;
    alarmConfig_t alarmConfig;
    QString ipAdressString;
    alarmConfigList.clear(); // очистка списку конфігурацій сирен перед зчитування з файлу
    while(!in.atEnd()){
        in >> alarmConfig.name;
        in >> ipAdressString;
        if(ipAdressString.size() == sizeof(SOCKADDR_IN))
        {
            memcpy(&alarmConfig.ipAddress, ipAdressString.constData(), sizeof(SOCKADDR_IN)); // копіювання ip адреси з строки в структуру
        }
        else
        {
            qDebug() << "Wrong ip address size";
        }
        in >> alarmConfig.macAddress;
        in >> alarmConfig.id;
        if(in.status() != QDataStream::Ok)
        {
            qDebug() << "Error reading from file.";
            regionFile.close();
            return;
        }
        alarmConfigList.append(alarmConfig);

    }

    alarmFile.close();

}

void ConfigManager::readFromRegionConfigFile()
{
    if(!regionFile.exists())
    {
        qDebug() << "File does not exist";
        return;
    }
    if(!regionFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open regionConfig.dat file";
        return;
    }
    QDataStream in(&regionFile); // створення потоку для запису в файл
    in.setVersion(QDataStream::Qt_5_0);
    regionConfig_t regionConfig;
    regionConfigList.clear(); // очистка списку конфігурацій сирен перед зчитування з файлу
    while(!in.atEnd())
    {
        in >> regionConfig.name;
        in >> regionConfig.fatherName;
        in >> regionConfig.id;
        if(in.status() != QDataStream::Ok)
        {
            qDebug() << "Error reading from file.";
            regionFile.close();
            return;
        }
        regionConfigList.append(regionConfig);
    }
    regionFile.close();
}

QList<alarmConfig_t> ConfigManager::getAlarmConfigList()
{
    if(alarmConfigList.isEmpty())
    {
        readFromAlarmConfigFile(); // якщо список конфігурацій сирен пустий, то зчитати з файлу
        if(alarmConfigList.isEmpty()){
            return QList<alarmConfig_t>(); // якщо файл пустий (топто список все ще пустий), то повернути пустий список
        }
    }
    return alarmConfigList;
}

QList<regionConfig_t> ConfigManager::getRegionConfigList()
{
    if(regionConfigList.isEmpty())
    {

        readFromRegionConfigFile(); // якщо список конфігурацій регіонів пустий, то зчитати з файлу
        if(regionConfigList.isEmpty()){
            return QList<regionConfig_t>(); // якщо файл пустий (топто список все ще пустий), то повернути пустий список
        }
    }
    return regionConfigList;
}

bool ConfigManager::deleteAlarmConfigFromFile(const QString &name){
   //треба видалити обєкт з списку і також видалити обєкт з файлу
    return false;
}

// метод для видалення обєктів регіонів з списку та з файлу
bool ConfigManager::deleteRegionConfigFromFile(const QString &name)
{
    int indextToDelete = -1;
    for(int i = 0; i < regionConfigList.size(); i ++ )
    {
        if(regionConfigList[i].name == name)
        {
            indextToDelete = i;
            break;
        }
    }
    if(indextToDelete != -1)
    {
        regionConfigList.removeAt(indextToDelete);
        overwriteRegionFile();
        return true;
    }
    return false;
}

void ConfigManager::overwriteRegionFile()
{
    if(!regionFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open regionConfig.dat file";
        return;
    }

    QDataStream out(&regionFile); // створення потоку для запису в файл
    out.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність

    for(auto it = regionConfigList.constBegin(); it!= regionConfigList.constEnd(); it++)
    {
        const auto& regionConfig = *it;
        out << regionConfig.name << regionConfig.fatherName <<regionConfig.id;
        if(out.status() != QDataStream::Ok)
        {
            qDebug() << "Error writing to regionFile.";
            QMessageBox::warning(nullptr, "Warning", "Error writing to regionFile.");
            break;
        }
    }

    regionFile.close();
}

