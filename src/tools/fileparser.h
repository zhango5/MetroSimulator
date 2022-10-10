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

    const QString txn_sjt_sale = "INSERT INTO txn_sjt_sale%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo"
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

    const QString txn_ypt_entry = "INSERT INTO txn_ypt_entry%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo"
                                  ", line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type, sub_global_message_id"
                                  ", ticket_family_type, ticket_type, ticket_catalog_id, tiket_phy_id, ticket_logic_id"
                                  ", ticket_status, test_flag, ticket_sn, ticket_remaining_value, trans_status_before_trans, trans_status_after_trans, remaining_value, tac) "
                                  "VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                  ", :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id"
                                  ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :tiket_phy_id, :ticket_logic_id"
                                  ", :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :trans_status_before_trans, :trans_status_after_trans, :remaining_value, :tac)";

    const QString txn_ypt_exit = "INSERT INTO txn_ypt_exit%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo"
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

    const QString txn_ypt_update = "INSERT INTO txn_ypt_update%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, mode_code, udsn, e_purse_transaction_type"
                                   ", city_code_trans_location, city_code_belong_location, tac_sam_id, terminate_number, sam_sn, sak, main_card_type, sub_card_type, card_ver, recharge_sn, add_value_date"
                                   ", sale_date, system_trace_sn, transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, ticket_phy_id, ticket_logic_id"
                                   ", ticket_status, test_flag, ticket_sn, ticket_remaining_value, surcharge_code, paymentmeans, trans_status_befor_trans, trans_status_after_trans, sale_device_id"
                                   ", ticket_sale_value, surcharge_area, transaction_value, operator_id, bom_shift, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                   ", :line_id, :station_id, :device_id, :mode_code, :udsn, :e_purse_transaction_type, :city_code_trans_location, :city_code_belong_location, :tac_sam_id"
                                   ", :terminate_number, :sam_sn, :sak, :main_card_type, :sub_card_type, :card_ver, :recharge_sn, :add_value_date, :sale_date, :system_trace_sn, :transaction_type"
                                   ", :sub_global_message_id, :ticket_family_type, :ticket_type, :ticket_catalog_id, :ticket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn"
                                   ", :ticket_remaining_value, :surcharge_code, :paymentmeans, :trans_status_befor_trans, :trans_status_after_trans, :sale_device_id, :ticket_sale_value, :surcharge_area"
                                   ", :transaction_value, :operator_id, :bom_shift, :tac)";

    const QString txn_bank_entry = "INSERT INTO txn_bank_entry%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn"
                                   ", transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, primary_account, bank_code, pos_no, termin_no, pre_auth_value"
                                   ", auth_code, reserve_one, reserve_two, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo, :line_id, :station_id, :device_id"
                                   ", :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id, :ticket_family_type, :ticket_type, :ticket_catalog_id, :primary_account"
                                   ", :bank_code, :pos_no, :termin_no, :pre_auth_value, :auth_code, :reserve_one, :reserve_two, :tac)";

    const QString txn_bank_exit = "INSERT INTO txn_bank_exit%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type"
                                  ", sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, primary_account, bank_code, pos_no, termin_no, trans_value, dis_trans_value"
                                  ", start_device, start_time_hi, start_time_lo, reserve_one, reserve_two, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo, :line_id"
                                  ", :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id, :ticket_family_type, :ticket_type, :ticket_catalog_id"
                                  ", :primary_account, :bank_code, :pos_no, :termin_no, :trans_value, :dis_trans_value, :start_device, :start_time_hi, :start_time_lo, :reserve_one, :reserve_two, :tac)";

    const QString txn_qr_code_entry = "INSERT INTO txn_qr_code_entry%1 (txn_type, transaction_date_time_hi, transaction_date_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn"
                                      ", transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, uid, qr_code_id, reserve_one, reserve_two, tac) VALUES (:txn_type"
                                      ", :transaction_date_time_hi, :transaction_date_time_lo, :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id"
                                      ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :uid, :qr_code_id, :reserve_one, :reserve_two, :tac)";

    const QString txn_qr_code_exit = "INSERT INTO txn_qr_code_exit%1 (txn_type, transaction_date_time_hi, transaction_date_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn"
                                     ", transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, uid, qr_code_id, trans_value, start_device, start_time_hi"
                                     ", start_time_lo, reserve_one, reserve_two, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_date_time_lo, :line_id, :station_id, :device_id"
                                     ", :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id, :ticket_family_type, :ticket_type, :ticket_catalog_id, :uid, :qr_code_id"
                                     ", :trans_value, :start_device, :start_time_hi, :start_time_lo, :reserve_one, :reserve_two, :tac)";

    const QString txn_qr_code_update = "INSERT INTO txn_qr_code_update%1 (txn_type, transaction_date_time_hi, transaction_date_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn"
                                       ", transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, uid, qr_code_id, surcharge_code, paymentmeans, trans_status_before_trans"
                                       ", trans_status_after_trans, sale_device_id, ticket_sale_value, surcharge_area, transaction_value, operator_id, bom_shift_id, reserve_one, reserve_two"
                                       ", tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_date_time_lo, :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type"
                                       ", :sub_global_message_id, :ticket_family_type, :ticket_type, :ticket_catalog_id, :uid, :qr_code_id, :surcharge_code, :paymentmeans, :trans_status_before_trans"
                                       ", :trans_status_after_trans, :sale_device_id, :ticket_sale_value, :surcharge_area, :transaction_value, :operator_id, :bom_shift_id, :reserve_one, :reserve_two, :tac)";

    const QString txn_sjt_refund = "INSERT INTO txn_sjt_refund%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, tac_sam_id, mode_code, udsn, transaction_type"
                                   ", sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, tiket_phy_id, ticket_logic_id, ticket_status, test_flag, ticket_sn, ticket_remaining_value"
                                   ", card_init_date, InitBatchCode, price_value, refund_reason, transaction_status, operator_id, bom_shift_id, tac) VALUES (:txn_type, :transaction_date_time_hi"
                                   ", :transaction_data_time_lo, :line_id, :station_id, :device_id, :tac_sam_id, :mode_code, :udsn, :transaction_type, :sub_global_message_id, :ticket_family_type"
                                   ", :ticket_type, :ticket_catalog_id, :tiket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :card_init_date, :InitBatchCode"
                                   ", :price_value, :refund_reason, :transaction_status, :operator_id, :bom_shift_id, :tac)";

    const QString txn_svc_charge = "INSERT INTO txn_svc_charge%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, mode_code, udsn, e_purse_transaction_type"
                                   ", city_code_trans_location, city_code_belong_location, tac_sam_id, terminate_number, sam_sn, sak, main_card_type, sub_card_type, card_ver, recharge_sn, add_value_date"
                                   ", sale_date, system_trace_sn, transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, ticket_phy_id, ticket_logic_id, ticket_status"
                                   ", test_flag, ticket_sn, ticket_remaining_value, issuer_code, card_issue_date, app_sn, payment_means, transcation_value, valid_date_before_add_value"
                                   ", valid_date_after_add_value, new_remaining_value, bank_code, biz_code, pos_no, bank_card_code, bank_trans_sn, last_add_transaction_value, last_add_value_time_hi"
                                   ", last_add_value_time_lo, last_add_value_udsn, last_add_value_sam_id, last_add_value_device_id, operator_id, bom_shift_id, charge_terminate_number, host_transaction_time_hi"
                                   ", host_transaction_time_lo, real_transaction_value, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo, :line_id, :station_id, :device_id"
                                   ", :mode_code, :udsn, :e_purse_transaction_type, :city_code_trans_location, :city_code_belong_location, :tac_sam_id, :terminate_number, :sam_sn, :sak, :main_card_type"
                                   ", :sub_card_type, :card_ver, :recharge_sn, :add_value_date, :sale_date, :system_trace_sn, :transaction_type, :sub_global_message_id, :ticket_family_type, :ticket_type"
                                   ", :ticket_catalog_id, :ticket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :issuer_code, :card_issue_date, :app_sn"
                                   ", :payment_means, :transcation_value, :valid_date_before_add_value, :valid_date_after_add_value, :new_remaining_value, :bank_code, :biz_code, :pos_no, :bank_card_code"
                                   ", :bank_trans_sn, :last_add_transaction_value, :last_add_value_time_hi, :last_add_value_time_lo, :last_add_value_udsn, :last_add_value_sam_id, :last_add_value_device_id"
                                   ", :operator_id, :bom_shift_id, :charge_terminate_number, :host_transaction_time_hi, :host_transaction_time_lo, :real_transaction_value, :tac)";

    const QString txn_ykt_block = "INSERT INTO txn_ykt_block%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, mode_code, udsn, e_purse_transaction_type"
                                  ", city_code_trans_location, city_code_belong_location, tac_sam_id, terminate_number, sam_sn, sak, main_card_type, sub_card_type, card_ver, recharge_sn, add_value_date"
                                  ", sale_date, system_trace_sn, transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, ticket_phy_id, ticket_logic_id, ticket_status"
                                  ", test_flag, ticket_sn, ticket_remaining_value, block_reason_code, operator_id, bom_shift_id, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo"
                                  ", :line_id, :station_id, :device_id, :mode_code, :udsn, :e_purse_transaction_type, :city_code_trans_location, :city_code_belong_location, :tac_sam_id, :terminate_number"
                                  ", :sam_sn, :sak, :main_card_type, :sub_card_type, :card_ver, :recharge_sn, :add_value_date, :sale_date, :system_trace_sn, :transaction_type, :sub_global_message_id"
                                  ", :ticket_family_type, :ticket_type, :ticket_catalog_id, :ticket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :block_reason_code"
                                  ", :operator_id, :bom_shift_id, :tac)";

    const QString txn_ykt_charge = "INSERT INTO txn_ykt_charge%1 (add_value_date, app_sn, bank_card_code, bank_code, bank_trans_sn, bizion_id, device_id, mode_code, udsn, e_purse_transaction_type"
                                   ", city_code_trans_location, city_code_belong_location, tac_sam_id, terminate_number, sam_sn, sak, main_card__code, bom_shift_id, card_issue_date, card_ver, charge_terminate_number"
                                   ", city_code_belong_location, cite, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, ticket_phy_id, ticket_logic_id, ticket_status, test_flag"
                                   ", ticket_sn, ticket_remaining_valuy_code_trans_location, device_id, e_purse_transaction_type, host_transaction_time_hi, host_transaction_cket_sale_value, surcharge_area"
                                   ", transaction_value, operator_id, bom_shift, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo, :line_id, :statime_lo, issuer_code"
                                   ", last_add_transaction_value, last_add_value_device_id, last_add_value_sam_id, laste_belong_location, :tac_sam_id, :terminate_number, :sam_sn, :sak, :main_card_type"
                                   ", :sub_card_type, :card_ver, :recharge_sn, :add_value_date, :sale_date, :system_trace_s_add_value_time_hi, last_add_value_time_lo, last_add_value_udsn, line_id, main_card_type"
                                   ", mode_code, neicket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :surcharge_code, :paymentmeans, :trans_status_befor_trans"
                                   ", :trans_statuw_remaining_value, operator_id, payment_means, pos_no, real_transaction_value, recharge_sn, sak, sale_d:bom_shift, :tac)ate, sam_sn, station_id, sub_card_type"
                                   ", sub_global_message_id, system_trace_sn, tac, tac_sam_id, terminate_number, test_flag, ticket_catalog_id, ticket_family_type, ticket_logic_id, ticket_phy_id"
                                   ", ticket_remaining_value, ticket_sn, ticket_status, ticket_type, transaction_data_time_lo, transaction_date_time_hi, transaction_type, transcation_value, txn_type, udsn"
                                   ", valid_date_after_add_value, valid_date_before_add_value) VALUES (:add_value_date, :app_sn, :bank_card_code, :bank_code, :bank_trans_sn, :biz_code, :bom_shift_id"
                                   ", :card_issue_date, :card_ver, :charge_terminate_number, :city_code_belong_location, :city_code_trans_location, :device_id, :e_purse_transaction_type, :host_transaction_time_hi"
                                   ", :host_transaction_time_lo, :issuer_code, :last_add_transaction_value, :last_add_value_device_id, :last_add_value_sam_id, :last_add_value_time_hi, :last_add_value_time_lo"
                                   ", :last_add_value_udsn, :line_id, :main_card_type, :mode_code, :new_remaining_value, :operator_id, :payment_means, :pos_no, :real_transaction_value, :recharge_sn, :sak, :sale_date"
                                   ", :sam_sn, :station_id, :sub_card_type, :sub_global_message_id, :system_trace_sn, :tac, :tac_sam_id, :terminate_number, :test_flag, :ticket_catalog_id, :ticket_family_type"
                                   ", :ticket_logic_id, :ticket_phy_id, :ticket_remaining_value, :ticket_sn, :ticket_status, :ticket_type, :transaction_data_time_lo, :transaction_date_time_hi, :transaction_type"
                                   ", :transcation_value, :txn_type, :udsn, :valid_date_after_add_value, :valid_date_before_add_value)";

    const QString txn_ykt_exit = "INSERT INTO txn_ykt_exit%1 (txn_type, transaction_date_time_hi, transaction_data_time_lo, line_id, station_id, device_id, mode_code, udsn, e_purse_transaction_type"
                                 ", city_code_trans_location, city_code_belong_location, tac_sam_id, terminate_number, sam_sn, sak, main_card_type, sub_card_type, card_ver, recharge_sn, add_value_date"
                                 ", sale_date, system_trace_sn, transaction_type, sub_global_message_id, ticket_family_type, ticket_type, ticket_catalog_id, ticket_phy_id, ticket_logic_id, ticket_status"
                                 ", test_flag, ticket_sn, ticket_remaining_value, entry_device_id, entry_time_hi, entry_time_lo, trans_status_before_trans, trans_status_after_trans, remaining_value_befor_trans"
                                 ", remaining_value_after_trans, transaction_value, original_value, join_concession_id, join_concession_type, join_concession_value, join_concession_percentage"
                                 ", pile_concession_id, current_bonus, accumulation_bonus, tac) VALUES (:txn_type, :transaction_date_time_hi, :transaction_data_time_lo, :line_id, :station_id, :device_id"
                                 ", :mode_code, :udsn, :e_purse_transaction_type, :city_code_trans_location, :city_code_belong_location, :tac_sam_id, :terminate_number, :sam_sn, :sak, :main_card_type"
                                 ", :sub_card_type, :card_ver, :recharge_sn, :add_value_date, :sale_date, :system_trace_sn, :transaction_type, :sub_global_message_id, :ticket_family_type, :ticket_type"
                                 ", :ticket_catalog_id, :ticket_phy_id, :ticket_logic_id, :ticket_status, :test_flag, :ticket_sn, :ticket_remaining_value, :entry_device_id, :entry_time_hi, :entry_time_lo"
                                 ", :trans_status_before_trans, :trans_status_after_trans, :remaining_value_befor_trans, :remaining_value_after_trans, :transaction_value, :original_value, :join_concession_id"
                                 ", :join_concession_type, :join_concession_value, :join_concession_percentage, :pile_concession_id, :current_bonus, :accumulation_bonus, :tac)";
};

#endif // FILEPARSER_H
