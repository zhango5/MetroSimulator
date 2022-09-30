#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class FileParser
{
public:
    FileParser();
    ~FileParser();

public:
    void YiPiaoTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                             , const QByteArray& ba);
    void YiKaTongTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                           , const QByteArray& ba);
    void PhoneTicketTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                              , const QByteArray& ba);
    void BankCardTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                           , const QByteArray& ba);
    void QRCodeTradeFile(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                         , const QByteArray& ba);

    QString filePath;

    void output();

    void OpenDB();
    void CloseDB();

    void TestFunc();

private:
    unsigned int YiPiaoTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                      , const QByteArray& ba);
    unsigned int YiPiaoTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);
    unsigned int YiPiaoTongOneWayTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiPiaoTongUnsignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                     , const QByteArray& ba);
    unsigned int YiPiaoTongSignedStoredValueTicket(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                   , const QByteArray& ba);
    unsigned int YiPiaoTongPersonalizedCardApply(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                 , const QByteArray& ba);
    unsigned int YiPiaoTongStoredTicketRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                , const QByteArray& ba);
    unsigned int YiPiaoTongSingleImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                 , const QByteArray& ba);
    unsigned int YiPiaoTongStoredImmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                 , const QByteArray& ba);
    unsigned int YiPiaoTongStoredUnimmediateRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                                   , const QByteArray& ba);
    unsigned int YiPiaoTongStoredPostpone(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                          , const QByteArray& ba);
    unsigned int YiPiaoTongStoredLock(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                             , const QByteArray& ba);
    unsigned int YiPiaoTongStoredUnlock(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiPiaoTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                  , const QByteArray& ba);
    unsigned int YiPiaoTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiPiaoTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);
    unsigned int YiPiaoTongStoredRefund(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiPiaoTongSpecialPurse(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 一卡通
    unsigned int YiKaTongHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                      , const QByteArray& ba);
    unsigned int YiKaTongTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);

    unsigned int YiKaTongSale(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongRecharge(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongLockCard(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int YiKaTongM1MetroApp(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 手机卡交易
    unsigned int PhoneCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                      , const QByteArray& ba);
    unsigned int PhoneCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);
    unsigned int PhoneCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int PhoneCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int PhoneCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int PhoneCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 银行卡交易
    unsigned int BankCardHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                      , const QByteArray& ba);
    unsigned int BankCardTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);
    unsigned int BankCardUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int BankCardEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int BankCardExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int BankCardCutPayment(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                               , const QByteArray& ba);

    // 二维码交易
    unsigned int QRCodeHeaderPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                      , const QByteArray& ba);
    unsigned int QRCodeTxnListPart(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                       , const QByteArray& ba);
    unsigned int QRCodeUpdate(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                  , const QByteArray& ba);
    unsigned int QRCodeEnterStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
                                        , const QByteArray& ba);
    unsigned int QRCodeExitStation(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer
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

    QSqlDatabase db;
    QSqlQuery* query = nullptr;

    const QString txn_sjt_sale = "INSERT INTO txn_sjt_sale (txn_type, transaction_date_time_hi, transaction_data_time_lo"
                                 ", line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type, sub_global_message_id"
                                 ", ticket_family_type, ticket_type, ticket_catalog_id, tiket_phy_id, ticket_logic_id"
                                 ", ticket_status, test_flag, ticket_sn, ticket_remaining_value, card_init_id, InitBatchCode, paymentmeans"
                                 ", language_flag, transaction_value, ticket_price_value, change_value, original_value, transaction_status"
                                 ", valid_start_date, valid_end_date, operator_id, bom_shift_id, tac) "
                                 "VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                 ", :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id"
                                 ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :tiket_phy_id, :ticket_logic_id"
                                 ", :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :card_init_id, :InitBatchCode, :paymentmeans"
                                 ", :language_flag, :transaction_value, :ticket_price_value, :change_value, :original_value, :transaction_status"
                                 ", :valid_start_date, :valid_end_date, :operator_id, :bom_shift_id, :tac)";

    const QString txn_ypt_entry = "INSERT INTO txn_ypt_entry (txn_type, transaction_date_time_hi, transaction_data_time_lo"
                                  ", line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type, sub_global_message_id"
                                  ", ticket_family_type, ticket_type, ticket_catalog_id, tiket_phy_id, ticket_logic_id"
                                  ", ticket_status, test_flag, ticket_sn, ticket_remaining_value, trans_status_before_trans, trans_status_after_trans, remaining_value, tac) "
                                  "VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                  ", :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id"
                                  ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :tiket_phy_id, :ticket_logic_id"
                                  ", :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :trans_status_before_trans, :trans_status_after_trans, :remaining_value, :tac)";

    const QString txn_ypt_exit = "INSERT INTO txn_ypt_exit (txn_type, transaction_date_time_hi, transaction_data_time_lo"
                                 ", line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type, sub_global_message_id"
                                 ", ticket_family_type, ticket_type, ticket_catalog_id, tiket_phy_id, ticket_logic_id"
                                 ", ticket_status, test_flag, ticket_sn, ticket_remaining_value, entry_device_id, entry_time_hi, entry_time_lo, trans_status_before_trans"
                                 ", trans_status_after_trans, transaction_value, original_value, sjt_recycle_flag, deduce_location, terminate_number, sam_sn, join_concession_id"
                                 ", join_concession_type, join_concession_value, join_concession_percentage, pile_concession_id, current_bonus, accumulation_bonus, tac) "
                                 "VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                 ", :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id"
                                 ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :tiket_phy_id, :ticket_logic_id"
                                 ", :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :entry_device_id, :entry_time_hi, :entry_time_lo, :trans_status_before_trans"
                                 ", :trans_status_after_trans, :transaction_value, :original_value, :sjt_recycle_flag, :deduce_location, :terminate_number, :sam_sn, :join_concession_id"
                                 ", :join_concession_type, :join_concession_value, :join_concession_percentage, :pile_concession_id, :current_bonus, :accumulation_bonus, :tac)";
};

#endif // FILEPARSER_H
