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

    void OpenDB(const QString& host, const QString& database, int port, const QString& usr, const QString& pwd);

private:
    void CloseDB();

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
