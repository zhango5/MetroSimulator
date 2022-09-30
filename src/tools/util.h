#ifndef UTIL_H
#define UTIL_H

#include <QByteArray>
#include <QString>
#include <QDateTime>


class Util
{
public:
    unsigned short UShort(const char* data, unsigned int& len);

    std::string IntSecondTo19700101(const char* data, unsigned int& len);

    std::string FileName(const char* data, unsigned int& len);

    std::string UTF8String(const char* data, unsigned int& len);

    unsigned char Byte(const char* data, unsigned int& len);

    unsigned int UInt(const char* data, unsigned int& len);

    int Int(const char* data, unsigned int& len);

    std::string UShortDayTo19700101(const char* data, unsigned int& len);

    std::string HEX(const char* data, unsigned int& len);

    std::string TicketPhyID(const char* data, unsigned int& len);

    std::string ByteX2(const char* data, unsigned int& len);

    std::string UShortX4(const char* data, unsigned int& len);

    std::string UIntX6(const char* data, unsigned int& len);

    std::string UIntX8(const char* data, unsigned int& len);

    std::string TerminateNumber(const char* data, unsigned int& len);

public:
    Util();
    ~Util();
};

#endif // UTIL_H
