#include "configmanager.h"


ConfigManager::ConfigManager(): alarmFile("alarmConfig.dat"), regionFile("regionConfig.dat") // виклик конструктора класу QFile
{

}

void ConfigManager::addAlarmConfig(const alarmConfig_t &alarmConfig)
{
    if(isNameUnique(alarmConfig.name))
    {
        alarmConfigList.append(alarmConfig);
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "Сирена з таким іменне вже існує");
    }
}

void ConfigManager::addRegionConfig(const regionConfig_t &regionConfig)
{
    if(isNameUnique(regionConfig.name))
    {
        regionConfigList.append(regionConfig);
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "Регіон з таким іменне вже існує");
    }
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

void ConfigManager::saveToFile(const alarmConfig_t &alarmConfig)
{
//    if(!alarmFile.exists())
//    {
//        qDebug() << "File does not exist";
//        return;
//    }
    if(!alarmFile.open(QIODevice::Append)) зробити аналогічну команду  Append і для регіонів
    {
        qDebug() << "Failed to open alarmConfig.dat file";
        return;
    }
    QDataStream out(&alarmFile); // створення потоку для запису в файл
    out.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність
    qint64 bytesWritten;
    bytesWritten = out.writeRawData(reinterpret_cast<const char*>(&alarmConfig), sizeof(alarmConfig_t)); // запис в файл конфігурації сирени

    if(bytesWritten != sizeof(alarmConfig_t)){
        qDebug() << "Error writing to file.";
        return;
    }

    alarmFile.close();
}

void ConfigManager::saveToFile(const regionConfig_t& regionConfig)
{
    if(!regionFile.exists())
    {
        qDebug() << "File does not exist";
        return;
    }
    if(!regionFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open alarmConfig.dat file";
        return;
    }
    QDataStream out(&regionFile); // створення потоку для запису в файл
     out.setVersion(QDataStream::Qt_5_0); // встановлення версії потоку, версія потоку встановлюється для того щоб забезпечити кросплатформенність
    qint64 bytesWritten;
    bytesWritten = out.writeRawData(reinterpret_cast<const char*>(&regionConfig), sizeof(regionConfig_t)); // запис в файл конфігурації сирени

    if(bytesWritten != sizeof(regionConfig_t)){
        qDebug() << "Error writing to file.";
        return;
    }

    alarmFile.close();
}

void ConfigManager::readFromAlarmConfigFrile()
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
    alarmConfigList.clear(); // очистка списку конфігурацій сирен перед зчитування з файлу
    while(!in.atEnd()){
        bytesRead = in.readRawData(reinterpret_cast<char *>(&alarmConfig),sizeof(alarmConfig_t));
        if(bytesRead == sizeof(alarmConfig_t))
        {
            alarmConfigList.append(alarmConfig);
        }
        else
        {
            qDebug() << "Error reading from file.";
            alarmFile.close();
            return;
        }
    }
    alarmFile.close();

}
