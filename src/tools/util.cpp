#include "util.h"
#include <QtEndian>

template<class T>
T big_endian(const char* ptr)
{
    return static_cast<T>(qFromBigEndian<T>(ptr));
}

Util::Util()
{

}

Util::~Util()
{

}

unsigned short Util::UShort(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    return static_cast<uint16_t>(big_endian<uint32_t>(data));
}

std::string Util::IntSecondTo19700101(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t sec = big_endian<uint32_t>(data);
    QDateTime dt;
    dt.setSecsSinceEpoch(sec);
    return dt.toLocalTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
}

std::string Util::FileName(const char* data, unsigned int& len)
{
    len = big_endian<uint32_t>(data);
    std::string res("");
    if (len != 0) {
        char str[256] = "\0";
        memset(str, 0x00, 256);
        snprintf(str, len + 1, "%s", data + sizeof(uint32_t));
        res = std::string(str);
    }

    len = 40;
    return res;
}

std::string Util::UTF8String(const char* data, unsigned int& len)
{
    len = big_endian<uint32_t>(data);
    std::string res("");
    if (len != 0) {
        char str[256] = "\0";
        memset(str, 0x00, 256);
        snprintf(str, len + 1, "%s", data + sizeof(uint32_t));
        res = std::string(str);
    }

    len += sizeof(uint32_t);
    return res;
}

unsigned char Util::Byte(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    return static_cast<uint8_t>(big_endian<uint32_t>(data));
}

unsigned int Util::UInt(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    return big_endian<uint32_t>(data);
}

int Util::Int(const char* data, unsigned int& len)
{
    len = sizeof(int32_t);
    return big_endian<int32_t>(data);
}

std::string Util::UShortDayTo19700101(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t day = big_endian<uint32_t>(data);
    QDateTime dt;
    dt.setSecsSinceEpoch(day * 24 * 60 * 60);
    return dt.toUTC().toString("yyyy-MM-dd hh:mm:ss").toStdString();
}

std::string Util::HEX(const char* data, unsigned int& len)
{
    char str[48] = "\0";
    snprintf(str, 48, "%08x%08x%08x%08x"
             , big_endian<uint32_t>(data)
             , big_endian<uint32_t>(data + 4)
             , big_endian<uint32_t>(data + 8)
             , big_endian<uint32_t>(data + 12));
    len = 16;
    return std::string(str);
}

std::string Util::TicketPhyID(const char* data, unsigned int& len)
{
    char str[32] = "\0";
    snprintf(str, 32, "%08X%08X"
             , big_endian<uint32_t>(data + 4)
             , big_endian<uint32_t>(data));
    len = 8;
    return std::string(str);
}

std::string Util::ByteX2(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t val = big_endian<uint32_t>(data);
    char str[16] = "\0";
    snprintf(str, 16, "%02x", val);
    return std::string(str);
}

std::string Util::UShortX4(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t val = big_endian<uint32_t>(data);
    char str[16] = "\0";
    snprintf(str, 16, "%04x", val);
    return std::string(str);
}

std::string Util::UIntX6(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t val = big_endian<uint32_t>(data);
    char str[16] = "\0";
    snprintf(str, 16, "%06x", val);
    return std::string(str);
}

std::string Util::UIntX8(const char* data, unsigned int& len)
{
    len = sizeof(uint32_t);
    uint32_t val = big_endian<uint32_t>(data);
    char str[16] = "\0";
    snprintf(str, 16, "%08x", val);
    return std::string(str);
}

std::string Util::TerminateNumber(const char* data, unsigned int& len)
{
    len = sizeof(uint64_t);
    char str[48] = "\0";
    snprintf(str, 48, "%02X%02X%02X%02X%02X%02X"
        , big_endian<uint8_t>(data + 7)
        , big_endian<uint8_t>(data + 6)
        , big_endian<uint8_t>(data + 5)
        , big_endian<uint8_t>(data + 4)
        , big_endian<uint8_t>(data + 3)
        , big_endian<uint8_t>(data + 2));
    return std::string(str);
}
