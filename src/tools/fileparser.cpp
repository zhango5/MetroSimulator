#include "fileparser.h"
#include "model.h"
#include "util.h"
#include <QtEndian>
#include <QSqlDriver>
#include <QDebug>

#define TABLE_FMT    "yyyyMM"

FileParser::FileParser()
{
    //qDebug() << QSqlDatabase::drivers();
}

FileParser::~FileParser()
{
    CloseDB();
}

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
    TicketEntry_t tentry;
    TicketExit_t texit;
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

    QString date = QDate::currentDate().toString(TABLE_FMT);
    bool exec = false;

    db.transaction();
    QSqlQuery query(db);

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 1:
            writer.Key("SubGlobalMessageId"); writer.String("01_1");
            offset += tc.parse(ba.data() + offset);
            offset += sjtic.parse(ba.data() + offset);
            offset += sjts.parse(ba.data() + offset);

            tc.output(writer);
            sjtic.output(writer);
            sjts.output(writer);

            query.prepare(txn_sjt_sale.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_1");
            tc.sqltransaction(query);
            sjtic.sqltransaction(query);
            sjts.sqltransaction(query);

            exec = true;
            break;
        case 2:
            writer.Key("SubGlobalMessageId"); writer.String("01_2");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucs.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucs.output(writer);
            break;
        case 3:
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
            writer.Key("SubGlobalMessageId"); writer.String("01_4");
            offset += cpucmr.parse(ba.data() + offset);

            cpucmr.output(writer);
            break;
        case 5:
            writer.Key("SubGlobalMessageId"); writer.String("01_5");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucav.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucav.output(writer);

            query.prepare(txn_svc_charge.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_5");
            tc.sqltransaction(query);
            cpuit.sqltransaction(query);
            cpucav.sqltransaction(query);

            exec = true;
            break;
        case 6:
            writer.Key("SubGlobalMessageId"); writer.String("01_6");
            offset += tc.parse(ba.data() + offset);
            offset += sjtic.parse(ba.data() + offset);
            offset += sjtr.parse(ba.data() + offset);

            tc.output(writer);
            sjtic.output(writer);
            sjtr.output(writer);

            query.prepare(txn_sjt_refund.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_6");
            tc.sqltransaction(query);
            sjtic.sqltransaction(query);
            sjtr.sqltransaction(query);

            exec = true;
            break;
        case 7:
            writer.Key("SubGlobalMessageId"); writer.String("01_7");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucir.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucir.output(writer);
            break;
        case 8:
            writer.Key("SubGlobalMessageId"); writer.String("01_8");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucnir.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucnir.output(writer);
            break;
        case 9:
            writer.Key("SubGlobalMessageId"); writer.String("01_9");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucvp.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucvp.output(writer);
            break;
        case 10:
            writer.Key("SubGlobalMessageId"); writer.String("01_10");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucb.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucb.output(writer);
            break;
        case 11:
            writer.Key("SubGlobalMessageId"); writer.String("01_11");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucu.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucu.output(writer);
            break;
        case 12:
            writer.Key("SubGlobalMessageId"); writer.String("01_12");
            offset += tc.parse(ba.data() + offset);
            offset += ts.parse(ba.data() + offset);

            tc.output(writer);
            ts.output(writer);

            query.prepare(txn_ypt_update.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_12");
            tc.sqltransaction(query);
            ts.sqltransaction(query);

            exec = true;
            break;
        case 13:
            writer.Key("SubGlobalMessageId"); writer.String("01_13");
            offset += tc.parse(ba.data() + offset);
            offset += tentry.parse(ba.data() + offset);

            tc.output(writer);
            tentry.output(writer);

            query.prepare(txn_ypt_entry.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_13");
            tc.sqltransaction(query);
            tentry.sqltransaction(query);

            exec = true;
            break;
        case 14:
            writer.Key("SubGlobalMessageId"); writer.String("01_14");
            offset += tc.parse(ba.data() + offset);
            offset += texit.parse(ba.data() + offset);
            offset += rs.parse(ba.data() + offset);

            tc.output(writer);
            texit.output(writer);
            rs.output(writer);

            query.prepare(txn_ypt_exit.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "01_14");
            tc.sqltransaction(query);
            texit.sqltransaction(query);
            rs.sqltransaction(query);

            exec = true;
            break;
        case 16:
            writer.Key("SubGlobalMessageId"); writer.String("01_16");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucd.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucd.output(writer);
            break;
        case 19:
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

        query.bindValue(":tac", TAC);
        if (!query.exec())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    if (exec)
    {
        if (!db.commit())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
}

void FileParser::YiKaTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    unsigned int len = 0;
    Util _util;

    DevOpFileHeader header;
    offset += header.parse(ba.data());

    writer.StartObject();

    writer.Key("GlobalMessageId"); writer.String("02");
    header.output(writer);

    writer.Key("TxnList");
    writer.StartArray();

    unsigned int TxnType = 0;
    unsigned int TAC = 0;
    std::string MD5;
    unsigned int cnt = _util.UInt(ba.data() + offset, len);
    offset += len;
    YiKaTongTradePub traPub;
    TicketComm_t tc;
    CPUCardSale_t cpucs;
    YKTTicketPassengerComm_t ykttpc;
    CPUInitComm_t cpuit;
    CPUCardAddValue_t cpucav;
    CPUCardBlock_t cpucb;
    TicketSurcharge_t ts;
    TicketEntry_t tentry;
    YKTTicketExit_t yktte;
    RebateScheme_t rs;
    YKTMetroStart_t yktms;

    QString date = QDate::currentDate().toString(TABLE_FMT);
    bool exec = false;

    db.transaction();
    QSqlQuery query(db);

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 34:
            writer.Key("SubGlobalMessageId"); writer.String("02_34");
            offset += tc.parse(ba.data() + offset);
            offset += cpucs.parse(ba.data() + offset);
            offset += ykttpc.parse(ba.data() + offset);

            tc.output(writer);
            cpucs.output(writer);
            ykttpc.output(writer);
            break;
        case 37:
            writer.Key("SubGlobalMessageId"); writer.String("02_37");
            offset += tc.parse(ba.data() + offset);
            offset += cpuit.parse(ba.data() + offset);
            offset += cpucav.parse(ba.data() + offset);

            tc.output(writer);
            cpuit.output(writer);
            cpucav.output(writer);

            query.prepare(txn_ykt_charge.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "02_37");
            tc.sqltransaction(query);
            cpuit.sqltransaction(query);
            cpucav.sqltransaction(query);

            exec = true;
            break;
        case 42:
            writer.Key("SubGlobalMessageId"); writer.String("02_42");
            offset += tc.parse(ba.data() + offset);
            offset += cpucb.parse(ba.data() + offset);

            tc.output(writer);
            cpucb.output(writer);

            query.prepare(txn_ykt_block.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "02_42");
            tc.sqltransaction(query);
            cpucb.sqltransaction(query);

            exec = true;
            break;
        case 44:
            writer.Key("SubGlobalMessageId"); writer.String("02_44");
            offset += tc.parse(ba.data() + offset);
            offset += ts.parse(ba.data() + offset);

            tc.output(writer);
            ts.output(writer);

            query.prepare(txn_ykt_update.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "02_44");
            tc.sqltransaction(query);
            ts.sqltransaction(query);

            exec = true;
            break;
        case 45:
            writer.Key("SubGlobalMessageId"); writer.String("02_45");
            offset += tc.parse(ba.data() + offset);
            offset += tentry.parse(ba.data() + offset);

            tc.output(writer);
            tentry.output(writer);

            query.prepare(txn_ykt_entry.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "02_45");
            tc.sqltransaction(query);
            tentry.sqltransaction(query);

            exec = true;
            break;
        case 46:
            writer.Key("SubGlobalMessageId"); writer.String("02_46");
            offset += tc.parse(ba.data() + offset);
            offset += yktte.parse(ba.data() + offset);
            offset += rs.parse(ba.data() + offset);

            tc.output(writer);
            yktte.output(writer);
            rs.output(writer);

            query.prepare(txn_ykt_exit.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "02_46");
            tc.sqltransaction(query);
            yktte.sqltransaction(query);
            rs.sqltransaction(query);

            exec = true;
            break;
        case 49:
            writer.Key("SubGlobalMessageId"); writer.String("02_49");
            offset += tc.parse(ba.data() + offset);
            offset += yktms.parse(ba.data() + offset);

            tc.output(writer);
            yktms.output(writer);
            break;
        default:
            break;
        }

        TAC = _util.UInt(ba.data() + offset, len);
        offset += len;
        writer.Key("TAC"); writer.Uint(TAC);

        query.bindValue(":tac", TAC);
        if (!query.exec())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    if (exec)
    {
        if (!db.commit())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
}

void FileParser::PhoneTicketTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    unsigned int len = 0;
    Util _util;

    DevOpFileHeader header;
    offset += header.parse(ba.data());

    writer.StartObject();

    writer.Key("GlobalMessageId"); writer.String("03");
    header.output(writer);

    writer.Key("TxnList");
    writer.StartArray();

    unsigned int TxnType = 0;
    unsigned int TAC = 0;
    std::string MD5;
    unsigned int cnt = _util.UInt(ba.data() + offset, len);
    offset += len;
    CellPhoneTradePub traPub;
    TicketComm_t tc;
    CPUCardSale_t cpucs;
    YKTTicketPassengerComm_t ykttpc;
    CPUInitComm_t cpuit;
    CPUCardAddValue_t cpucav;
    CPUCardBlock_t cpucb;
    TicketSurcharge_t ts;
    TicketEntry_t tentry;
    TicketExit_t texit;
    YKTTicketExit_t yktte;
    RebateScheme_t rs;
    YKTMetroStart_t yktms;
    MobileDeduction_t md;

    QString date = QDate::currentDate().toString(TABLE_FMT);
    bool exec = false;

    db.transaction();
    QSqlQuery query(db);

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 76:
            writer.Key("SubGlobalMessageId"); writer.String("03_76");
            offset += tc.parse(ba.data() + offset);
            offset += ts.parse(ba.data() + offset);

            tc.output(writer);
            ts.output(writer);

            query.prepare(txn_ypt_update.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "03_76");
            tc.sqltransaction(query);
            ts.sqltransaction(query);

            exec = true;
            break;
        case 77:
            writer.Key("SubGlobalMessageId"); writer.String("03_77");
            offset += tc.parse(ba.data() + offset);
            offset += tentry.parse(ba.data() + offset);

            tc.output(writer);
            tentry.output(writer);

            query.prepare(txn_ypt_entry.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "03_77");
            tc.sqltransaction(query);
            tentry.sqltransaction(query);

            exec = true;
            break;
        case 78:
            writer.Key("SubGlobalMessageId"); writer.String("03_78");
            offset += tc.parse(ba.data() + offset);
            offset += texit.parse(ba.data() + offset);
            offset += rs.parse(ba.data() + offset);

            tc.output(writer);
            tentry.output(writer);
            rs.output(writer);

            query.prepare(txn_ypt_exit.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "03_78");
            tc.sqltransaction(query);
            texit.sqltransaction(query);
            rs.sqltransaction(query);

            exec = true;
            break;
        case 80:
            writer.Key("SubGlobalMessageId"); writer.String("03_80");
            offset += md.parse(ba.data() + offset);

            md.output(writer);
            break;
        default:
            break;
        }

        TAC = _util.UInt(ba.data() + offset, len);
        offset += len;
        writer.Key("TAC"); writer.Uint(TAC);

        query.bindValue(":tac", TAC);
        if (!query.exec())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    if (exec)
    {
        if (!db.commit())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
}

void FileParser::BankCardTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    unsigned int len = 0;
    Util _util;

    DevOpFileHeader header;
    offset += header.parse(ba.data());

    writer.StartObject();

    writer.Key("GlobalMessageId"); writer.String("04");
    header.output(writer);

    writer.Key("TxnList");
    writer.StartArray();

    unsigned int TxnType = 0;
    unsigned int TAC = 0;
    std::string MD5;
    unsigned int cnt = _util.UInt(ba.data() + offset, len);
    offset += len;
    BankCardTradePub traPub;
    BankCardTicketComm_t bctc;
    BankCardSurcharge_t bcs;
    BankCardEntry_t bcen;
    BankCardExit_t bcex;
    BankCardDeduction_t bcd;

    QString date = QDate::currentDate().toString(TABLE_FMT);
    bool exec = false;

    db.transaction();
    QSqlQuery query(db);

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 108:
            writer.Key("SubGlobalMessageId"); writer.String("04_108");
            offset += bctc.parse(ba.data() + offset);
            offset += bcs.parse(ba.data() + offset);

            bctc.output(writer);
            bcs.output(writer);
            break;
        case 109:
            writer.Key("SubGlobalMessageId"); writer.String("04_109");
            offset += bctc.parse(ba.data() + offset);
            offset += bcen.parse(ba.data() + offset);

            bctc.output(writer);
            bcen.output(writer);

            query.prepare(txn_bank_entry.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "04_109");
            bctc.sqltransaction(query);
            bcen.sqltransaction(query);

            exec = true;
            break;
        case 110:
            writer.Key("SubGlobalMessageId"); writer.String("04_110");
            offset += bctc.parse(ba.data() + offset);
            offset += bcex.parse(ba.data() + offset);

            bctc.output(writer);
            bcex.output(writer);

            query.prepare(txn_bank_exit.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "04_110");
            bctc.sqltransaction(query);
            bcex.sqltransaction(query);

            exec = true;
            break;
        case 112:
            writer.Key("SubGlobalMessageId"); writer.String("04_112");
            offset += bcd.parse(ba.data() + offset);

            bcd.output(writer);
            break;
        default:
            break;
        }

        TAC = _util.UInt(ba.data() + offset, len);
        offset += len;
        writer.Key("TAC"); writer.Uint(TAC);

        query.bindValue(":tac", TAC);
        if (!query.exec())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    if (exec)
    {
        if (!db.commit())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
}

void FileParser::QRCodeTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, const QByteArray &ba)
{
    unsigned int offset = 0;
    unsigned int len = 0;
    Util _util;

    DevOpFileHeader header;
    offset += header.parse(ba.data());

    writer.StartObject();

    writer.Key("GlobalMessageId"); writer.String("70");
    header.output(writer);

    writer.Key("TxnList");
    writer.StartArray();

    unsigned int TxnType = 0;
    unsigned int TAC = 0;
    std::string MD5;
    unsigned int cnt = _util.UInt(ba.data() + offset, len);
    offset += len;
    QRCodeTradePub traPub;
    QRCodeTicketComm_t tc;
    TicketSurcharge_t ts;
    QRCodeUnnamed unnamed;
    QRCodeExit_t exit;

    QString date = QDate::currentDate().toString(TABLE_FMT);
    bool exec = false;

    db.transaction();
    QSqlQuery query(db);

    for (unsigned int i = 0; i < cnt; ++i)
    {
        writer.StartObject();

        TxnType = _util.UInt(ba.data() + offset, len);

        offset += traPub.parse(ba.data() + offset);

        traPub.output(writer);

        switch (TxnType)
        {
        case 144:
            writer.Key("SubGlobalMessageId"); writer.String("70_144");
            offset += tc.parse(ba.data() + offset);
            offset += ts.parse(ba.data() + offset);
            offset += unnamed.parse(ba.data() + offset);

            tc.output(writer);
            ts.output(writer);
            unnamed.output(writer);

            query.prepare(txn_qr_code_update.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "70_144");
            tc.sqltransaction(query);
            ts.sqltransaction(query);
            unnamed.sqltransaction(query);

            exec = true;
            break;
        case 145:
            writer.Key("SubGlobalMessageId"); writer.String("70_145");
            offset += tc.parse(ba.data() + offset);
            offset += unnamed.parse(ba.data() + offset);

            tc.output(writer);
            unnamed.output(writer);

            query.prepare(txn_qr_code_entry.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "70_145");
            tc.sqltransaction(query);
            unnamed.sqltransaction(query);

            exec = true;
            break;
        case 146:
            writer.Key("SubGlobalMessageId"); writer.String("70_146");
            offset += tc.parse(ba.data() + offset);
            offset += exit.parse(ba.data() + offset);

            tc.output(writer);
            exit.output(writer);

            query.prepare(txn_qr_code_exit.arg(date));
            traPub.sqltransaction(query);
            query.bindValue(":sub_global_message_id", "70_146");
            tc.sqltransaction(query);
            exit.sqltransaction(query);

            exec = true;
            break;
        default:
            break;
        }

        TAC = _util.UInt(ba.data() + offset, len);
        offset += len;
        writer.Key("TAC"); writer.Uint(TAC);

        query.bindValue(":tac", TAC);
        if (!query.exec())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }

        writer.EndObject();
    }

    writer.EndArray();

    MD5 = _util.HEX(ba.data() + offset, len);
    offset += len;
    writer.Key("MD5"); writer.String(MD5.c_str());

    writer.EndObject();

    if (exec)
    {
        if (!db.commit())
        {
            qDebug() << query.lastError();
            qDebug() << query.lastQuery();
        }
    }
}

void FileParser::OpenDB(const QString& host, const QString& database, int port, const QString& usr, const QString& pwd)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(usr);
    db.setPassword(pwd);
    db.setPort(port);

    if (!db.open())
    {
        qDebug() << "open database error: " << db.lastError();
        return;
    }
    else
    {
        qDebug() << "open database successful!";
    }

    if (!db.driver()->hasFeature(QSqlDriver::Transactions))
    {
        qDebug() << "database not support transaction.";
    }
}

void FileParser::CloseDB()
{
    if (db.isOpen())
    {
        db.close();
    }
}
