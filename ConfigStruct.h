#ifndef CONFIGSTRUCT_H
#define CONFIGSTRUCT_H

#include <QString>
#include <winsock2.h>
#include <ws2tcpip.h>


// структура для конфігурації сирени
typedef struct
{
    QString name;
    SOCKADDR_IN ipAddress;
    QString macAddress;
    int id;
} alarmConfig_t;

// структура для конфігурації регіонів
typedef struct
{
    QString name;
    int id;
} regionConfig_t;


#endif // CONFIGSTRUCT_H
