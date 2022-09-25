#include "fileparser.h"
#include <QtEndian>
#include <QDebug>

template<class T>
T big_endian(const char *ptr)
{
    return static_cast<T>(qFromBigEndian<T>(ptr));
}

template<class T>
T little_endian(const char *ptr)
{
    return static_cast<T>(qFromLittleEndian<T>(ptr));
}

template<class T>
std::string hex2stringX2(T t)
{
    char str[16] = "\0";
    snprintf(str, 16, "%02x", t);
    return std::string(str);
}
template<class T>
std::string hex2stringX4(T t)
{
    char str[16] = "\0";
    snprintf(str, 16, "%04x", t);
    return std::string(str);
}
template<class T>
std::string hex2stringX6(T t)
{
    char str[16] = "\0";
    snprintf(str, 16, "%06x", t);
    return std::string(str);
}
template<class T>
std::string hex2stringX8(T t)
{
    char str[16] = "\0";
    snprintf(str, 16, "%08x", t);
    return std::string(str);
}

std::string disp_string(const char *ptr, int len)
{
    if (0 == len)
    {
        return std::string("");
    }

    char str[256] = "\0";
    memset(str, 0x00, 256);
    snprintf(str, len + 1, "%s", ptr);
    return std::string(str);
}

std::string uint64_string(const char *ptr)
{
    char str[32] = "\0";
    snprintf(str, 32, "%08X%08X"
        , big_endian<uint32_t>(ptr + 4)
        , big_endian<uint32_t>(ptr));
    return std::string(str);
}

std::string TerminateNumber(const char *ptr)
{
    char str[48] = "\0";
    snprintf(str, 48, "%02X%02X%02X%02X%02X%02X"
        , big_endian<uint8_t>(ptr + 7)
        , big_endian<uint8_t>(ptr + 6)
        , big_endian<uint8_t>(ptr + 5)
        , big_endian<uint8_t>(ptr + 4)
        , big_endian<uint8_t>(ptr + 3)
        , big_endian<uint8_t>(ptr + 2));
    return std::string(str);
}

std::string md5_string(const char *ptr)
{
    char str[48] = "\0";
    snprintf(str, 48, "%08x%08x%08x%08x"
        , big_endian<uint32_t>(ptr)
        , big_endian<uint32_t>(ptr + 4)
        , big_endian<uint32_t>(ptr + 8)
        , big_endian<uint32_t>(ptr + 12));
    return std::string(str);
}

FileParser::FileParser()
{

}
#include "model.h"
void FileParser::YiPiaoTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer
    , const QByteArray &ba)
{
    unsigned int offset = 0;
    unsigned int len = 0;
    Util _util;

    DevOpFileHeader header;
    offset += header.parse(ba.data());

    writer.StartObject();

    writer.Key("GlobalMessageId"); writer.String("01");
    header.output(writer);

    writer.Key("TxnList");
    writer.StartArray();

    unsigned int TxnType = 0;
    unsigned int TAC = 0;
    std::string MD5;
    unsigned int cnt = _util.UInt(ba.data() + offset, len);
    offset += len;
    YiPiaoTongTradePub traPub;
    TicketComm_t tc;
    TicketEntry_t te;
    SJTInitComm_t sjtic;
    SJTSale_t sjts;
    CPUInitComm_t cpuit;
    CPUCardSale_t cpucs;
    TicketPassengerComm_t tpc;
    CPUCardMemberRegister_t cpucmr;
    CPUCardAddValue_t cpucav;
    SJTRefund_t sjtr;
    CPUCardImmediateRefund_t cpucir;
    CPUCardNonImmediateRefund_t cpucnir;
    CPUCardValidityPeriod_t cpucvp;
    CPUCardBlock_t cpucb;
    CPUCardUnblock_t cpucu;
    TicketSurcharge_t ts;
    RebateScheme_t rs;
    CPUCardDeduction_t cpucd;
    CPUCardSpecialPurseSale_t cpucsp;

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 1:
//            offset += YiPiaoTongOneWayTicket(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_1");
            offset += tc.parse(ba.data() + offset);
            offset += sjtic.parse(ba.data() + offset);
            offset += sjts.parse(ba.data() + offset);

            tc.output(writer);
            sjtic.output(writer);
            sjts.output(writer);
            break;
        case 2:
//            offset += YiPiaoTongUnsignedStoredValueTicket(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_2");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucs.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucs.output(writer);
            break;
        case 3:
//            offset += YiPiaoTongSignedStoredValueTicket(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_3");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucs.parse(ba.data() + offset);
            offset += tpc.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucs.output(writer);
            tpc.output(writer);
            break;
        case 4:
//            offset += YiPiaoTongPersonalizedCardApply(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_4");
            offset += cpucmr.parse(ba.data() + offset);

            cpucmr.output(writer);
            break;
        case 5:
//            offset += YiPiaoTongStoredTicketRecharge(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_5");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucav.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucav.output(writer);
            break;
        case 6:
//            offset += YiPiaoTongSingleImmediateRefund(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_6");
            offset += tc.parse(ba.data() + offset);
            offset += sjtic.parse(ba.data() + offset);
            offset += sjtr.parse(ba.data() + offset);

            tc.output(writer);
            sjtic.output(writer);
            sjtr.output(writer);
            break;
        case 7:
//            offset += YiPiaoTongStoredImmediateRefund(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_7");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucir.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucir.output(writer);
            break;
        case 8:
//            offset += YiPiaoTongStoredUnimmediateRefund(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_8");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucnir.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucnir.output(writer);
            break;
        case 9:
//            offset += YiPiaoTongStoredPostpone(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_9");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucvp.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucvp.output(writer);
            break;
        case 10:
//            offset += YiPiaoTongStoredLock(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_10");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucb.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucb.output(writer);
            break;
        case 11:
//            offset += YiPiaoTongStoredUnlock(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_11");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucu.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucu.output(writer);
            break;
        case 12:
//            offset += YiPiaoTongUpdate(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_12");
            offset += tc.parse(ba.data() + offset);
            offset += ts.parse(ba.data() + offset);

            tc.output(writer);
            ts.output(writer);
            break;
        case 13:
            writer.Key("SubGlobalMessageId"); writer.String("01_13");
            offset += tc.parse(ba.data() + offset);
            offset += te.parse(ba.data() + offset);

            tc.output(writer);
            te.output(writer);
            break;
        case 14:
//            offset += YiPiaoTongExitStation(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_14");
            offset += tc.parse(ba.data() + offset);
            offset += te.parse(ba.data() + offset);
            offset += rs.parse(ba.data() + offset);

            tc.output(writer);
            te.output(writer);
            rs.output(writer);
            break;
        case 16:
//            offset += YiPiaoTongStoredRefund(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_16");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucd.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucd.output(writer);
            break;
        case 19:
//            offset += YiPiaoTongSpecialPurse(writer, ba.mid(offset));
            writer.Key("SubGlobalMessageId"); writer.String("01_19");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucsp.parse(ba.data() + offset);
            offset += cpucav.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucsp.output(writer);
            cpucav.output(writer);
            break;
        default:
            break;
        }

        TAC = _util.UInt(ba.data() + offset, len);
        offset += len;
        writer.Key("TAC"); writer.Uint(TAC);

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    //unsigned int bytes = 0;

    //writer.StartObject();

    //bytes += YiPiaoTongHeaderPart(writer, ba);
    //bytes += YiPiaoTongTxnListPart(writer, ba.mid(bytes));

    //// MD5
    //writer.Key("MD5"); writer.String(md5_string(ba.data() + bytes).c_str());

    //writer.EndObject();
}

void FileParser::YiKaTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int bytes = 0;

    writer.StartObject();

    bytes += YiKaTongHeaderPart(writer, ba);
    bytes += YiKaTongTxnListPart(writer, ba.mid(bytes));

    // MD5
    writer.Key("MD5"); writer.String(md5_string(ba.data() + bytes).c_str());

    writer.EndObject();
}

void FileParser::PhoneTicketTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int bytes = 0;

    writer.StartObject();

    bytes += PhoneCardHeaderPart(writer, ba);
    bytes += PhoneCardTxnListPart(writer, ba.mid(bytes));

    // MD5
    writer.Key("MD5"); writer.String(md5_string(ba.data() + bytes).c_str());

    writer.EndObject();
}

void FileParser::BankCardTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int bytes = 0;

    writer.StartObject();

    bytes += BankCardHeaderPart(writer, ba);
    bytes += BankCardTxnListPart(writer, ba.mid(bytes));

    // MD5
    writer.Key("MD5"); writer.String(md5_string(ba.data() + bytes).c_str());

    writer.EndObject();
}

void FileParser::QRCodeTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int bytes = 0;

    writer.StartObject();

    bytes += QRCodeHeaderPart(writer, ba);
    bytes += QRCodeTxnListPart(writer, ba.mid(bytes));

    // MD5
    writer.Key("MD5"); writer.String(md5_string(ba.data() + bytes).c_str());

    writer.EndObject();
}

unsigned int FileParser::YiPiaoTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    const unsigned int FILE_NAME_LEN = 40;

    writer.Key("GlobalMessageId"); writer.String(YiPiaoTong);
    writer.Key("FileType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileName"); writer.String(disp_string(ptr + offset + 4, FILE_NAME_LEN - 4).c_str()); offset += FILE_NAME_LEN; // 4包含三个0和一个#
    writer.Key("FileLineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileStationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BusinessDay"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RecordsInFile"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileHeaderTag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    unsigned int cnt = big_endian<uint32_t>(ptr + offset);
    offset += sizeof(uint32_t);
    unsigned int TxnType = 0;

    writer.Key("TxnList");
    writer.StartArray();

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = big_endian<uint32_t>(ptr + offset);

        writer.Key("TxnType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("LineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("StationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("DeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("TACSAMID"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("ModeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("UDSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        switch (TxnType)
        {
        case 1:
            offset += YiPiaoTongOneWayTicket(writer, ba.mid(offset));
            break;
        case 2:
            offset += YiPiaoTongUnsignedStoredValueTicket(writer, ba.mid(offset));
            break;
        case 3:
            offset += YiPiaoTongSignedStoredValueTicket(writer, ba.mid(offset));
            break;
        case 4:
            offset += YiPiaoTongPersonalizedCardApply(writer, ba.mid(offset));
            break;
        case 5:
            offset += YiPiaoTongStoredTicketRecharge(writer, ba.mid(offset));
            break;
        case 6:
            offset += YiPiaoTongSingleImmediateRefund(writer, ba.mid(offset));
            break;
        case 7:
            offset += YiPiaoTongStoredImmediateRefund(writer, ba.mid(offset));
            break;
        case 8:
            offset += YiPiaoTongStoredUnimmediateRefund(writer, ba.mid(offset));
            break;
        case 9:
            offset += YiPiaoTongStoredPostpone(writer, ba.mid(offset));
            break;
        case 10:
            offset += YiPiaoTongStoredLock(writer, ba.mid(offset));
            break;
        case 11:
            offset += YiPiaoTongStoredUnlock(writer, ba.mid(offset));
            break;
        case 12:
            offset += YiPiaoTongUpdate(writer, ba.mid(offset));
            break;
        case 13:
            offset += YiPiaoTongEnterStation(writer, ba.mid(offset));
            break;
        case 14:
            offset += YiPiaoTongExitStation(writer, ba.mid(offset));
            break;
        case 16:
            offset += YiPiaoTongStoredRefund(writer, ba.mid(offset));
            break;
        case 19:
            offset += YiPiaoTongSpecialPurse(writer, ba.mid(offset));
            break;
        default:
            break;
        }

        writer.Key("TAC"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.EndObject();
    }

    writer.EndArray();

    return offset;
}

unsigned int FileParser::YiPiaoTongOneWayTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_1");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardInitDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("InitBatchCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LanguageFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPriceValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ChangeValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OriginalValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidStartDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidEndDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongUnsignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_2");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LanguageFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidStartDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidEndDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("SectionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongSignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_3");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LanguageFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidStartDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidEndDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("SectionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    writer.Key("PassengerTypeID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PassengerStaffFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PassengerCNName"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("IdentificationType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("IdentificationCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;

    return offset;
}

unsigned int FileParser::YiPiaoTongPersonalizedCardApply(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_4");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("ApplyBillNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("CardDepositValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PassengerName"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Gender"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("TelephoneCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Address"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("IdentificationType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("IdentificationCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("ValidDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredTicketRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_5");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidDateBeforeAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidDateAfterAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("NewRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BIZCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCardCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("BankTransSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LastAddTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueUDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("LastAddValueSAMID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("LastAddValueDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("ChargeTerminateNumber"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    writer.Key("HostTransactionTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("HostTransactionTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RealTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongSingleImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_6");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardInitDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("InitBatchCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PriceValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RefundReason"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_7");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("ValidDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardDepositValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("AccTicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidDateAtACC"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAtACC"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardDepositValueAtACC"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RefundReason"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardDepreciationValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ChargeValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredUnimmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_8");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("ConfirmTimeAtAccHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ConfirmTimeAtAccLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorIDAtAcc"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("ApplyBillNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PassengerCNName"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Gender"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IdentificationType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("IdentificationCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("TelephoneCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Address"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("AccTicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidDateAtACC"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAtACC"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardDepositValueAtACC"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RefundReason"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardDepreciationValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ChargeValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredPostpone(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_9");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("OldValidDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("NewValidDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredLock(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_10");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("BlockReasonCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredUnlock(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_11");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("UnblockReasonCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_12");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("TicketSaleValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_13");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_14");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("EntryDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OriginalValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SJTRecycleFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("DeduceLocation"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TerminateNumber"); writer.String(TerminateNumber(ptr + offset).c_str()); offset += sizeof(uint64_t);
    writer.Key("SAMSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionPercentage"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PileConcessionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CurrentBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("AccumulationBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongStoredRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_16");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiPiaoTongSpecialPurse(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("01_19");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("SalePaymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleTransactionStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SalePurseType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleStageID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleValidStartDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("SaleValidEndDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("SaleSectionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleOperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("SaleBOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidDateBeforeAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidDateAfterAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("NewRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BIZCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCardCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("BankTransSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("LastAddTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueUDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("LastAddValueSAMID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("LastAddValueDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("ChargeTerminateNumber"); writer.String(TerminateNumber(ptr + offset).c_str()); offset += sizeof(uint64_t);
    writer.Key("HostTransactionTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("HostTransactionTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RealTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    const unsigned int FILE_NAME_LEN = 40;

    writer.Key("GlobalMessageId"); writer.String("02");
    writer.Key("FileType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileName"); writer.String(disp_string(ptr + offset + 4, FILE_NAME_LEN - 4).c_str()); offset += FILE_NAME_LEN; // 4包含三个0和一个#
    writer.Key("FileLineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileStationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BusinessDay"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RecordsInFile"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileHeaderTag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    unsigned int cnt = big_endian<uint32_t>(ptr + offset);
    offset += sizeof(uint32_t);
    unsigned int TxnType = 0;
    int len = 0;

    writer.Key("TxnList");
    writer.StartArray();

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = big_endian<uint32_t>(ptr + offset);

        writer.Key("TxnType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("LineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("StationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("DeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("ModeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("UDSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("ePurseTransactionType"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("CityCode_TransLocation"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("CityCode_BelongLocation"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
        writer.Key("TACSAMID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
        writer.Key("TerminateNumber"); writer.String(TerminateNumber(ptr + offset).c_str()); offset += sizeof(uint64_t);
        writer.Key("SAMSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("SAK"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.Key("MainCardType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("SubCardType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("CardVer"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("RechargeSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("AddValueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("SaleDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("SystemTraceSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        switch (TxnType)
        {
        case 34:
            offset += YiKaTongSale(writer, ba.mid(offset));
            break;
        case 37:
            offset += YiKaTongRecharge(writer, ba.mid(offset));
            break;
        case 42:
            offset += YiKaTongLockCard(writer, ba.mid(offset));
            break;
        case 44:
            offset += YiKaTongUpdate(writer, ba.mid(offset));
            break;
        case 45:
            offset += YiKaTongEnterStation(writer, ba.mid(offset));
            break;
        case 46:
            offset += YiKaTongExitStation(writer, ba.mid(offset));
            break;
        case 49:
            offset += YiKaTongM1MetroApp(writer, ba.mid(offset));
            break;
        default:
            break;
        }

        writer.Key("TAC"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.EndObject();
    }

    writer.EndArray();

    return offset;
}

unsigned int FileParser::YiKaTongSale(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_34");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LanguageFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidStartDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidEndDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("SectionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PassengerCNName"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("IdentificationType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("IdentificationCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("TelephoneCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Address"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("CompanyName"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;

    return offset;
}

unsigned int FileParser::YiKaTongRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_37");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CardIssueDate"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AppSN"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ValidDateBeforeAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ValidDateAfterAddValue"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("NewRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BIZCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCardCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("BankTransSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LastAddTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("LastAddValueUDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("LastAddValueSAMID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("LastAddValueDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("ChargeTerminateNumber"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    writer.Key("HostTransactionTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("HostTransactionTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("RealTransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongLockCard(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_42");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("BlockReasonCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_44");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("TicketSaleValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_45");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_46");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("EntryDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OriginalValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    writer.Key("JoinConcessionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionPercentage"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PileConcessionID"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CurrentBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("AccumulationBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::YiKaTongM1MetroApp(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("02_49");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::PhoneCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    const unsigned int FILE_NAME_LEN = 40;

    writer.Key("GlobalMessageId"); writer.String("03");
    writer.Key("FileType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileName"); writer.String(disp_string(ptr + offset + 4, FILE_NAME_LEN - 4).c_str()); offset += FILE_NAME_LEN; // 4包含三个0和一个#
    writer.Key("FileLineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileStationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BusinessDay"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RecordsInFile"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileHeaderTag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::PhoneCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    unsigned int cnt = big_endian<uint32_t>(ptr + offset);
    offset += sizeof(uint32_t);
    unsigned int TxnType = 0;

    writer.Key("TxnList");
    writer.StartArray();

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = big_endian<uint32_t>(ptr + offset);

        writer.Key("TxnType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("LineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("StationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("DeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("TACSAMID"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("ModeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("UDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        switch (TxnType)
        {
        case 76:
            offset += PhoneCardUpdate(writer, ba.mid(offset));
            break;
        case 77:
            offset += PhoneCardEnterStation(writer, ba.mid(offset));
            break;
        case 78:
            offset += PhoneCardExitStation(writer, ba.mid(offset));
            break;
        case 80:
            offset += PhoneCardCutPayment(writer, ba.mid(offset));
            break;
        default:
            break;
        }

        writer.Key("TAC"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.EndObject();
    }

    writer.EndArray();

    return offset;
}

unsigned int FileParser::PhoneCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("03_76");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("TicketSaleValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::PhoneCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("03_77");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::PhoneCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("03_78");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketPhyID"); writer.String(uint64_string(ptr + offset).c_str()); offset += sizeof(uint64_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);    // logic ID length
    writer.Key("TicketLogicID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TicketStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketRemainingValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("EntryDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("EntryTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OriginalValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SJTRecycleFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("DeduceLocation"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TerminateNumber"); writer.String(TerminateNumber(ptr + offset).c_str()); offset += sizeof(uint64_t);
    writer.Key("SAMSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("JoinConcessionPercentage"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PileConcessionID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CurrentBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("AccumulationBonus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::PhoneCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("03_78");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("IssuerSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("CityCode"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SIMType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SIMStatus"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("SIMID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("MobileNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("SIMTransSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SIMStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::BankCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    const unsigned int FILE_NAME_LEN = 40;

    writer.Key("GlobalMessageId"); writer.String("04");
    writer.Key("FileType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileName"); writer.String(disp_string(ptr + offset + 4, FILE_NAME_LEN - 4).c_str()); offset += FILE_NAME_LEN; // 4包含三个0和一个#
    writer.Key("FileLineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileStationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BusinessDay"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RecordsInFile"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileHeaderTag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::BankCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    unsigned int cnt = big_endian<uint32_t>(ptr + offset);
    offset += sizeof(uint32_t);
    unsigned int TxnType = 0;

    writer.Key("TxnList");
    writer.StartArray();

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = big_endian<uint32_t>(ptr + offset);

        writer.Key("TxnType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("LineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("StationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("DeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("TACSAMID"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("ModeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("UDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionType"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        switch (TxnType)
        {
        case 108:
            offset += BankCardUpdate(writer, ba.mid(offset));
            break;
        case 109:
            offset += BankCardEnterStation(writer, ba.mid(offset));
            break;
        case 110:
            offset += BankCardExitStation(writer, ba.mid(offset));
            break;
        case 112:
            offset += BankCardCutPayment(writer, ba.mid(offset));
            break;
        default:
            break;
        }

        writer.Key("TAC"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.EndObject();
    }

    writer.EndArray();

    return offset;
}

unsigned int FileParser::BankCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("04_108");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PrimaryAccount"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset);
    if (0 == len)
    {
        if (0x0c == big_endian<uint32_t>(ptr + offset + 1))
        {
            offset += 1;
            len = 0x0c;
        }
    }
    offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TerminNo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PreAuthValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AuthCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("SurchargeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("TicketSaleValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("DisSurchargeValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::BankCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("04_109");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PrimaryAccount"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len; // +1;
    len = big_endian<uint32_t>(ptr + offset);
    if (0 == len)
    {
        if (0x0c == big_endian<uint32_t>(ptr + offset + 1))
        {
            offset += 1;
            len = 0x0c;
        }
    }
    offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TerminNo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("PreAuthValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("AuthCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len; // +2;
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t) + 1;
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t) + 1;

    return offset;
}

unsigned int FileParser::BankCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("04_110");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PrimaryAccount"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset);
    if (0 == len)
    {
        if (0x0c == big_endian<uint32_t>(ptr + offset + 1))
        {
            offset += 1;
            len = 0x0c;
        }
    }
    offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TerminNo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("DisTransValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("StartDevice"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("StartTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("StartTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::BankCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("04_112");
    writer.Key("TestFlag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BIZCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("PosNo"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("BankCardCode"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("BankTransSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RemainingValueAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::QRCodeHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    const unsigned int FILE_NAME_LEN = 40;

    writer.Key("GlobalMessageId"); writer.String("70");
    writer.Key("FileType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileCreationTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileName"); writer.String(disp_string(ptr + offset + 4, FILE_NAME_LEN - 4).c_str()); offset += FILE_NAME_LEN; // 4包含三个0和一个#
    writer.Key("FileLineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileStationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("FileDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BusinessDay"); writer.String(DaysSinceEpoch(big_endian<uint32_t>(ptr + offset), true).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("FileSN"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("RecordsInFile"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("FileHeaderTag"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::QRCodeTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();
    unsigned int cnt = big_endian<uint32_t>(ptr + offset);
    offset += sizeof(uint32_t);
    unsigned int TxnType = 0;

    writer.Key("TxnList");
    writer.StartArray();

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = big_endian<uint32_t>(ptr + offset);

        writer.Key("TxnType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("TransactionDateTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
        writer.Key("LineID"); writer.String(hex2stringX2(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("StationID"); writer.String(hex2stringX4(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("DeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
        writer.Key("TACSAMID"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("ModeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("UDSN"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
        writer.Key("TransactionType"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        switch (TxnType)
        {
        case 144:
            offset += QRCodeUpdate(writer, ba.mid(offset));
            break;
        case 145:
            offset += QRCodeEnterStation(writer, ba.mid(offset));
            break;
        case 146:
            offset += QRCodeExitStation(writer, ba.mid(offset));
            break;
        default:
            break;
        }

        writer.Key("TAC"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

        writer.EndObject();
    }

    writer.EndArray();

    return offset;
}

unsigned int FileParser::QRCodeUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("70_144");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Uid"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("QRCodeID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;

    writer.Key("SurchargeCode"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("Paymentmeans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusBeforeTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransStatusAfterTrans"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SaleDeviceID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("TicketSaleValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("SurchargeArea"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TransactionValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("OperatorID"); writer.String(hex2stringX6(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("BOMShiftID"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::QRCodeEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("70_145");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Uid"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("QRCodeID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

unsigned int FileParser::QRCodeExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    const char *ptr = ba.data();

    writer.Key("SubGlobalMessageId"); writer.String("70_146");
    writer.Key("TicketFamilyType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketType"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("TicketCatalogID"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    int len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("Uid"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    len = big_endian<uint32_t>(ptr + offset); offset += sizeof(uint32_t);
    writer.Key("QRCodeID"); writer.String(disp_string(ptr + offset, len).c_str()); offset += len;
    writer.Key("TransValue"); writer.Int(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("StartDevice"); writer.String(hex2stringX8(big_endian<uint32_t>(ptr + offset)).c_str()); offset += sizeof(uint32_t);
    writer.Key("StartTimeHi"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("StartTimeLo"); writer.String(SecsSinceEpoch(big_endian<uint32_t>(ptr + offset)).toStdString().c_str()); offset += sizeof(uint32_t);
    writer.Key("ReserveOne"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);
    writer.Key("ReserveTwo"); writer.Uint(big_endian<uint32_t>(ptr + offset)); offset += sizeof(uint32_t);

    return offset;
}

