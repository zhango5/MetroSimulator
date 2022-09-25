#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QByteArray>
#include <QString>
#include <QDateTime>
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class FileParser
{
public:
    FileParser();

public:
    static void YiPiaoTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                    , const QByteArray& ba);
    static void YiKaTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                  , const QByteArray& ba);
    static void PhoneTicketTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                     , const QByteArray& ba);
    static void BankCardTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                  , const QByteArray& ba);
    static void QRCodeTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                , const QByteArray& ba);

private:
    static unsigned int YiPiaoTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int YiPiaoTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);
    static unsigned int YiPiaoTongOneWayTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiPiaoTongUnsignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                            , const QByteArray& ba);
    static unsigned int YiPiaoTongSignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                          , const QByteArray& ba);
    static unsigned int YiPiaoTongPersonalizedCardApply(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                        , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredTicketRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                       , const QByteArray& ba);
    static unsigned int YiPiaoTongSingleImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                        , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                        , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredUnimmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                          , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredPostpone(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                 , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredLock(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredUnlock(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiPiaoTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                         , const QByteArray& ba);
    static unsigned int YiPiaoTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiPiaoTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);
    static unsigned int YiPiaoTongStoredRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiPiaoTongSpecialPurse(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 一卡通
    static unsigned int YiKaTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int YiKaTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);

    static unsigned int YiKaTongSale(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongLockCard(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int YiKaTongM1MetroApp(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 手机卡交易
    static unsigned int PhoneCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int PhoneCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);
    static unsigned int PhoneCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int PhoneCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int PhoneCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int PhoneCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 银行卡交易
    static unsigned int BankCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int BankCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);
    static unsigned int BankCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int BankCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int BankCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int BankCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 二维码交易
    static unsigned int QRCodeHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    static unsigned int QRCodeTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);
    static unsigned int QRCodeUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                         , const QByteArray& ba);
    static unsigned int QRCodeEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);
    static unsigned int QRCodeExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                              , const QByteArray& ba);

private:
    inline static QString SecsSinceEpoch(uint32_t sec, bool utc = false) {
        QDateTime dt;
        dt.setSecsSinceEpoch(sec);
        if (utc)
            return dt.toUTC().toString("yyyy-MM-dd hh:mm:ss");
        else
            return dt.toLocalTime().toString("yyyy-MM-dd hh:mm:ss");
    };

    inline static QString DaysSinceEpoch(uint32_t day, bool utc = false) {
        QDateTime dt;
        dt.setSecsSinceEpoch(day * 24 * 60 * 60);
        if (utc)
            return dt.toUTC().toString("yyyy-MM-dd hh:mm:ss");
        else
            return dt.toLocalTime().toString("yyyy-MM-dd hh:mm:ss");
    };

    static constexpr char YiPiaoTong[] = "01";
};

#endif // FILEPARSER_H
