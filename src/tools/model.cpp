#include "model.h"
#include "util.h"
#include <QVariant>

unsigned int DevOpFileHeader::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    FileType = _util.UShort(data + offset, len); offset += len;
    FileCreationTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    FileCreationTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    FileName = _util.UTF8String(data + offset, len); offset += len;
    FileLineID = _util.ByteX2(data + offset, len); offset += len;
    FileStationID = _util.UShortX4(data + offset, len); offset += len;
    FileDeviceID = _util.UIntX8(data + offset, len); offset += len;
    BusinessDay = _util.UShortDayTo19700101(data + offset, len); offset += len;
    FileSN = _util.UInt(data + offset, len); offset += len;
    RecordsInFile = _util.UShort(data + offset, len); offset += len;
    FileHeaderTag = _util.UShort(data + offset, len); offset += len;

    return offset;
}

void DevOpFileHeader::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(FileType)); writer.Uint(this->FileType);
    writer.Key(VAR_NAME(FileCreationTimeHi)); writer.String(this->FileCreationTimeHi.c_str());
    writer.Key(VAR_NAME(FileCreationTimeLo)); writer.String(this->FileCreationTimeLo.c_str());
    writer.Key(VAR_NAME(FileName)); writer.String(this->FileName.c_str());
    writer.Key(VAR_NAME(FileLineID)); writer.String(this->FileLineID.c_str());
    writer.Key(VAR_NAME(FileStationID)); writer.String(this->FileStationID.c_str());
    writer.Key(VAR_NAME(FileDeviceID)); writer.String(this->FileDeviceID.c_str());
    writer.Key(VAR_NAME(BusinessDay)); writer.String(this->BusinessDay.c_str());
    writer.Key(VAR_NAME(FileSN)); writer.Uint(this->FileSN);
    writer.Key(VAR_NAME(RecordsInFile)); writer.Uint(this->RecordsInFile);
    writer.Key(VAR_NAME(FileHeaderTag)); writer.Uint(this->FileHeaderTag);
}

void DevOpFileHeader::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int YiPiaoTongTradePub::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TxnType = _util.UShort(data + offset, len); offset += len;
    TransactionDateTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransactionDateTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LineID = _util.ByteX2(data + offset, len); offset += len;
    StationID = _util.UShortX4(data + offset, len); offset += len;
    DeviceID = _util.UIntX8(data + offset, len); offset += len;
    TACSAMID = _util.UInt(data + offset, len); offset += len;
    ModeCode = _util.Byte(data + offset, len); offset += len;
    UDSN = _util.UInt(data + offset, len); offset += len;
    TransactionType = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void YiPiaoTongTradePub::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TxnType)); writer.Uint(this->TxnType);
    writer.Key(VAR_NAME(TransactionDateTimeHi)); writer.String(this->TransactionDateTimeHi.c_str());
    writer.Key(VAR_NAME(TransactionDateTimeLo)); writer.String(this->TransactionDateTimeLo.c_str());
    writer.Key(VAR_NAME(LineID)); writer.String(this->LineID.c_str());
    writer.Key(VAR_NAME(StationID)); writer.String(this->StationID.c_str());
    writer.Key(VAR_NAME(DeviceID)); writer.String(this->DeviceID.c_str());
    writer.Key(VAR_NAME(TACSAMID)); writer.Uint(this->TACSAMID);
    writer.Key(VAR_NAME(ModeCode)); writer.Int(this->ModeCode);
    writer.Key(VAR_NAME(UDSN)); writer.Uint(this->UDSN);
    writer.Key(VAR_NAME(TransactionType)); writer.Uint(this->TransactionType);
}

void YiPiaoTongTradePub::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":txn_type", QVariant(TxnType));
    query.bindValue(":transaction_date_time_hi", QVariant(TransactionDateTimeHi.c_str()));
    query.bindValue(":transaction_data_time_lo", QVariant(TransactionDateTimeLo.c_str()));
    query.bindValue(":line_id", QVariant(LineID.c_str()));
    query.bindValue(":station_id", QVariant(StationID.c_str()));
    query.bindValue(":device_id", QVariant(DeviceID.c_str()));
    query.bindValue(":tac_sam_id", QVariant(TACSAMID));
    query.bindValue(":mode_code", QVariant(ModeCode));
    query.bindValue(":udsn", QVariant(UDSN));
    query.bindValue(":transaction_type", QVariant(TransactionType));
}

unsigned int TicketComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TicketFamilyType = _util.UShort(data + offset, len); offset += len;
    TicketType = _util.Byte(data + offset, len); offset += len;
    TicketCatalogID = _util.UShort(data + offset, len); offset += len;
    TicketPhyID = _util.TicketPhyID(data + offset, len); offset += len;
    TicketLogicID = _util.UTF8String(data + offset, len); offset += len;
    TicketStatus = _util.Byte(data + offset, len); offset += len;
    TestFlag = _util.Byte(data + offset, len); offset += len;
    TicketSN = _util.UInt(data + offset, len); offset += len;
    TicketRemainingValue = _util.Int(data + offset, len); offset += len;

    return offset;
}

void TicketComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TicketFamilyType)); writer.Uint(this->TicketFamilyType);
    writer.Key(VAR_NAME(TicketType)); writer.Uint(this->TicketType);
    writer.Key(VAR_NAME(TicketCatalogID)); writer.Uint(this->TicketCatalogID);
    writer.Key(VAR_NAME(TicketPhyID)); writer.String(this->TicketPhyID.c_str());
    writer.Key(VAR_NAME(TicketLogicID)); writer.String(this->TicketLogicID.c_str());
    writer.Key(VAR_NAME(TicketStatus)); writer.Uint(this->TicketStatus);
    writer.Key(VAR_NAME(TestFlag)); writer.Uint(this->TestFlag);
    writer.Key(VAR_NAME(TicketSN)); writer.Uint(this->TicketSN);
    writer.Key(VAR_NAME(TicketRemainingValue)); writer.Int(this->TicketRemainingValue);
}

void TicketComm_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":ticket_family_type", QVariant(TicketFamilyType));
    query.bindValue(":ticket_type", QVariant(TicketType));
    query.bindValue(":ticket_catalog_id", QVariant(TicketCatalogID));
    query.bindValue(":tiket_phy_id", QVariant(TicketPhyID.c_str()));
    query.bindValue(":ticket_logic_id", QVariant(TicketLogicID.c_str()));
    query.bindValue(":ticket_status", QVariant(TicketStatus));
    query.bindValue(":test_flag", QVariant(TestFlag));
    query.bindValue(":ticket_sn", QVariant(TicketSN));
    query.bindValue(":ticket_remaining_value", QVariant(TicketRemainingValue));
}

unsigned int TicketEntry_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TransStatusBeforeTrans = _util.Byte(data + offset, len); offset += len;
    TransStatusAfterTrans = _util.Byte(data + offset, len); offset += len;
    RemainingValue = _util.Int(data + offset, len); offset += len;

    return offset;
}

void TicketEntry_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TransStatusBeforeTrans)); writer.Uint(this->TransStatusBeforeTrans);
    writer.Key(VAR_NAME(TransStatusAfterTrans)); writer.Uint(this->TransStatusAfterTrans);
    writer.Key(VAR_NAME(RemainingValue)); writer.Int(this->RemainingValue);
}

void TicketEntry_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":trans_status_before_trans", QVariant(TransStatusBeforeTrans));
    query.bindValue(":trans_status_after_trans", QVariant(TransStatusAfterTrans));
    query.bindValue(":remaining_value", QVariant(RemainingValue));
}

unsigned int SJTInitComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    CardInitDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    InitBatchCode = _util.Byte(data + offset, len); offset += len;

    return offset;
}

void SJTInitComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(CardInitDate)); writer.String(this->CardInitDate.c_str());
    writer.Key(VAR_NAME(InitBatchCode)); writer.Uint(this->InitBatchCode);
}

void SJTInitComm_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":card_init_id", QVariant(CardInitDate.c_str()));
    query.bindValue(":InitBatchCode", QVariant(InitBatchCode));
}

unsigned int SJTSale_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    LanguageFlag = _util.Byte(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    TicketPriceValue = _util.Int(data + offset, len); offset += len;
    ChangeValue = _util.Int(data + offset, len); offset += len;
    OriginalValue = _util.Int(data + offset, len); offset += len;
    TransactionStatus = _util.Byte(data + offset, len); offset += len;
    ValidStartDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    ValidEndDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void SJTSale_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(this->Paymentmeans);
    writer.Key(VAR_NAME(LanguageFlag)); writer.Uint(this->LanguageFlag);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(TicketPriceValue)); writer.Int(this->TicketPriceValue);
    writer.Key(VAR_NAME(ChangeValue)); writer.Int(this->ChangeValue);
    writer.Key(VAR_NAME(OriginalValue)); writer.Int(this->OriginalValue);
    writer.Key(VAR_NAME(TransactionStatus)); writer.Uint(this->TransactionStatus);
    writer.Key(VAR_NAME(ValidStartDate)); writer.String(this->ValidStartDate.c_str());
    writer.Key(VAR_NAME(ValidEndDate)); writer.String(this->ValidEndDate.c_str());
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void SJTSale_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":paymentmeans", QVariant(Paymentmeans));
    query.bindValue(":language_flag", QVariant(LanguageFlag));
    query.bindValue(":transaction_value", QVariant(TransactionValue));
    query.bindValue(":ticket_price_value", QVariant(TicketPriceValue));
    query.bindValue(":change_value", QVariant(ChangeValue));
    query.bindValue(":original_value", QVariant(OriginalValue));
    query.bindValue(":transaction_status", QVariant(TransactionStatus));
    query.bindValue(":valid_start_date", QVariant(ValidStartDate.c_str()));
    query.bindValue(":valid_end_date", QVariant(ValidEndDate.c_str()));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
}

unsigned int CPUInitComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    IssuerCode = _util.UInt(data + offset, len); offset += len;
    CardIssueDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    AppSN = _util.UTF8String(data + offset, len); offset += len;

    return offset;
}

void CPUInitComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(IssuerCode)); writer.Uint(this->IssuerCode);
    writer.Key(VAR_NAME(CardIssueDate)); writer.String(this->CardIssueDate.c_str());
    writer.Key(VAR_NAME(AppSN)); writer.String(this->AppSN.c_str());
}

void CPUInitComm_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":issuer_code", QVariant(IssuerCode));
    query.bindValue(":card_issue_date", QVariant(CardIssueDate.c_str()));
    query.bindValue(":app_sn", QVariant(AppSN.c_str()));
}

unsigned int CPUCardSale_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    LanguageFlag = _util.Byte(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    TransactionStatus = _util.Byte(data + offset, len); offset += len;
    ValidStartDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    ValidEndDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    SectionID = _util.Byte(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardSale_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(this->Paymentmeans);
    writer.Key(VAR_NAME(LanguageFlag)); writer.Uint(this->LanguageFlag);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(TransactionStatus)); writer.Uint(this->TransactionStatus);
    writer.Key(VAR_NAME(ValidStartDate)); writer.String(this->ValidStartDate.c_str());
    writer.Key(VAR_NAME(ValidEndDate)); writer.String(this->ValidEndDate.c_str());
    writer.Key(VAR_NAME(SectionID)); writer.Uint(this->SectionID);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardSale_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int TicketPassengerComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    PassengerTypeID = _util.Byte(data + offset, len); offset += len;
    PassengerStaffFlag = _util.Byte(data + offset, len); offset += len;
    PassengerCNName = _util.UTF8String(data + offset, len); offset += len;
    IdentificationType = _util.Byte(data + offset, len); offset += len;
    IdentificationCode = _util.UTF8String(data + offset, len); offset += len;

    return offset;
}

void TicketPassengerComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(PassengerTypeID)); writer.Uint(this->PassengerTypeID);
    writer.Key(VAR_NAME(PassengerStaffFlag)); writer.Uint(this->PassengerStaffFlag);
    writer.Key(VAR_NAME(PassengerCNName)); writer.String(this->PassengerCNName.c_str());
    writer.Key(VAR_NAME(IdentificationType)); writer.Uint(this->IdentificationType);
    writer.Key(VAR_NAME(IdentificationCode)); writer.String(this->IdentificationCode.c_str());
}

void TicketPassengerComm_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CPUCardMemberRegister_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TicketFamilyType = _util.UShort(data + offset, len); offset += len;
    TicketType = _util.Byte(data + offset, len); offset += len;
    ApplyBillNo = _util.UTF8String(data + offset, len); offset += len;
    CardDepositValue = _util.Int(data + offset, len); offset += len;
    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    PassengerName = _util.UTF8String(data + offset, len); offset += len;
    Gender = _util.Byte(data + offset, len); offset += len;
    TelephoneCode = _util.UTF8String(data + offset, len); offset += len;
    Address = _util.UTF8String(data + offset, len); offset += len;
    IdentificationType = _util.Byte(data + offset, len); offset += len;
    IdentificationCode = _util.UTF8String(data + offset, len); offset += len;
    ValidDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardMemberRegister_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TicketFamilyType)); writer.Uint(this->TicketFamilyType);
    writer.Key(VAR_NAME(TicketType)); writer.Uint(this->TicketType);
    writer.Key(VAR_NAME(ApplyBillNo)); writer.String(this->ApplyBillNo.c_str());
    writer.Key(VAR_NAME(CardDepositValue)); writer.Int(this->CardDepositValue);
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(this->Paymentmeans);
    writer.Key(VAR_NAME(PassengerName)); writer.String(this->PassengerName.c_str());
    writer.Key(VAR_NAME(Gender)); writer.Uint(this->Gender);
    writer.Key(VAR_NAME(TelephoneCode)); writer.String(this->TelephoneCode.c_str());
    writer.Key(VAR_NAME(Address)); writer.String(this->Address.c_str());
    writer.Key(VAR_NAME(IdentificationType)); writer.Uint(this->IdentificationType);
    writer.Key(VAR_NAME(IdentificationCode)); writer.String(this->IdentificationCode.c_str());
    writer.Key(VAR_NAME(ValidDate)); writer.String(this->ValidDate.c_str());
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardMemberRegister_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int BankCardPayment_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    BankCode = _util.UTF8String(data + offset, len); offset += len;
    BIZCode = _util.UTF8String(data + offset, len); offset += len;
    PosNo = _util.UTF8String(data + offset, len); offset += len;
    BankCardCode = _util.UTF8String(data + offset, len); offset += len;
    BankTransSN = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardPayment_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(BankCode)); writer.String(this->BankCode.c_str());
    writer.Key(VAR_NAME(BIZCode)); writer.String(this->BIZCode.c_str());
    writer.Key(VAR_NAME(PosNo)); writer.String(this->PosNo.c_str());
    writer.Key(VAR_NAME(BankCardCode)); writer.String(this->BankCardCode.c_str());
    writer.Key(VAR_NAME(BankTransSN)); writer.Uint(this->BankTransSN);
}

void BankCardPayment_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":bank_code", QVariant(BankCode.c_str()));
    query.bindValue(":biz_code", QVariant(BIZCode.c_str()));
    query.bindValue(":pos_no", QVariant(PosNo.c_str()));
    query.bindValue(":bank_card_code", QVariant(BankCardCode.c_str()));
    query.bindValue(":bank_trans_sn", QVariant(BankTransSN));
}

unsigned int CPUCardAddValue_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    ValidDateBeforeAddValue = _util.UShortDayTo19700101(data + offset, len); offset += len;
    ValidDateAfterAddValue = _util.UShortDayTo19700101(data + offset, len); offset += len;
    NewRemainingValue = _util.Int(data + offset, len); offset += len;
    offset += bcp.parse(data + offset);
    LastAddTransactionValue = _util.Int(data + offset, len); offset += len;
    LastAddValueTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LastAddValueTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LastAddValueUDSN = _util.UInt(data + offset, len); offset += len;
    LastAddValueSAMID = _util.UTF8String(data + offset, len); offset += len;
    LastAddValueDeviceID = _util.UIntX8(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;
    ChargeTerminateNumber = _util.TerminateNumber(data + offset, len); offset += len;
    HostTransactionTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    HostTransactionTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    RealTransactionValue = _util.Int(data + offset, len); offset += len;

    return offset;
}

void CPUCardAddValue_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(Paymentmeans);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(TransactionValue);
    writer.Key(VAR_NAME(ValidDateBeforeAddValue)); writer.String(this->ValidDateBeforeAddValue.c_str());
    writer.Key(VAR_NAME(ValidDateAfterAddValue)); writer.String(this->ValidDateAfterAddValue.c_str());
    writer.Key(VAR_NAME(NewRemainingValue)); writer.Int(this->NewRemainingValue);
    bcp.output(writer);
    writer.Key(VAR_NAME(LastAddTransactionValue)); writer.Int(this->LastAddTransactionValue);
    writer.Key(VAR_NAME(LastAddValueTimeHi)); writer.String(this->LastAddValueTimeHi.c_str());
    writer.Key(VAR_NAME(LastAddValueTimeLo)); writer.String(this->LastAddValueTimeLo.c_str());
    writer.Key(VAR_NAME(LastAddValueUDSN)); writer.Uint(LastAddValueUDSN);
    writer.Key(VAR_NAME(LastAddValueSAMID)); writer.String(this->LastAddValueSAMID.c_str());
    writer.Key(VAR_NAME(LastAddValueDeviceID)); writer.String(this->LastAddValueDeviceID.c_str());
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
    writer.Key(VAR_NAME(ChargeTerminateNumber)); writer.String(this->ChargeTerminateNumber.c_str());
    writer.Key(VAR_NAME(HostTransactionTimeHi)); writer.String(this->HostTransactionTimeHi.c_str());
    writer.Key(VAR_NAME(HostTransactionTimeLo)); writer.String(this->HostTransactionTimeLo.c_str());
    writer.Key(VAR_NAME(RealTransactionValue)); writer.Int(this->RealTransactionValue);
}

void CPUCardAddValue_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":paymentmeans", QVariant(Paymentmeans));
    query.bindValue(":transaction_value", QVariant(TransactionValue));
    query.bindValue(":valid_date_before_add_value", QVariant(ValidDateBeforeAddValue.c_str()));
    query.bindValue(":valid_date_after_add_value", QVariant(ValidDateAfterAddValue.c_str()));
    query.bindValue(":new_remaining_value", QVariant(NewRemainingValue));
    bcp.sqltransaction(query);
    query.bindValue(":last_add_transaction_value", QVariant(LastAddTransactionValue));
    query.bindValue(":last_add_value_time_hi", QVariant(LastAddValueTimeHi.c_str()));
    query.bindValue(":last_add_value_time_lo", QVariant(LastAddValueTimeLo.c_str()));
    query.bindValue(":last_add_value_udsn", QVariant(LastAddValueUDSN));
    query.bindValue(":last_add_value_sam_id", QVariant(LastAddValueSAMID.c_str()));
    query.bindValue(":last_add_value_device_id", QVariant(LastAddValueDeviceID.c_str()));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
    query.bindValue(":charge_terminate_number", QVariant(ChargeTerminateNumber.c_str()));
    query.bindValue(":host_transaction_time_hi", QVariant(HostTransactionTimeHi.c_str()));
    query.bindValue(":host_transaction_time_lo", QVariant(HostTransactionTimeLo.c_str()));
    query.bindValue(":real_transaction_value", QVariant(RealTransactionValue));
}

unsigned int SJTRefund_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    PriceValue = _util.Int(data + offset, len); offset += len;
    RefundReason = _util.Byte(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void SJTRefund_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(PriceValue)); writer.Int(this->PriceValue);
    writer.Key(VAR_NAME(RefundReason)); writer.Int(this->RefundReason);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void SJTRefund_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":price_value", QVariant(PriceValue));
    query.bindValue(":refund_reason", QVariant(RefundReason));
    query.bindValue(":transaction_status", QVariant(TransactionValue));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
}

unsigned int CPUCardImmediateRefund_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    ValidDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    RemainingValue = _util.Int(data + offset, len); offset += len;
    CardDepositValue = _util.Int(data + offset, len); offset += len;
    AccTicketStatus = _util.Byte(data + offset, len); offset += len;
    ValidDateAtACC = _util.UShortDayTo19700101(data + offset, len); offset += len;
    RemainingValueAtACC = _util.Int(data + offset, len); offset += len;
    CardDepositValueAtACC = _util.Int(data + offset, len); offset += len;
    RefundReason = _util.Byte(data + offset, len); offset += len;
    CardDepreciationValue = _util.Int(data + offset, len); offset += len;
    ChargeValue = _util.Int(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardImmediateRefund_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(ValidDate)); writer.String(this->ValidDate.c_str());
    writer.Key(VAR_NAME(RemainingValue)); writer.Int(this->RemainingValue);
    writer.Key(VAR_NAME(CardDepositValue)); writer.Int(this->CardDepositValue);
    writer.Key(VAR_NAME(AccTicketStatus)); writer.Uint(this->AccTicketStatus);
    writer.Key(VAR_NAME(ValidDateAtACC)); writer.String(this->ValidDateAtACC.c_str());
    writer.Key(VAR_NAME(RemainingValueAtACC)); writer.Int(this->RemainingValueAtACC);
    writer.Key(VAR_NAME(CardDepositValueAtACC)); writer.Int(this->CardDepositValueAtACC);
    writer.Key(VAR_NAME(RefundReason)); writer.Uint(this->RefundReason);
    writer.Key(VAR_NAME(CardDepreciationValue)); writer.Int(this->CardDepreciationValue);
    writer.Key(VAR_NAME(ChargeValue)); writer.Int(this->ChargeValue);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardImmediateRefund_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CPUCardNonImmediateRefund_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    ConfirmTimeAtAccHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    ConfirmTimeAtAccLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    OperatorIDAtAcc = _util.UIntX6(data + offset, len); offset += len;
    ApplyBillNo = _util.UTF8String(data + offset, len); offset += len;
    PassengerCNName = _util.UTF8String(data + offset, len); offset += len;
    Gender = _util.Byte(data + offset, len); offset += len;
    IdentificationType = _util.Byte(data + offset, len); offset += len;
    IdentificationCode = _util.UTF8String(data + offset, len); offset += len;
    TelephoneCode = _util.UTF8String(data + offset, len); offset += len;
    Address = _util.UTF8String(data + offset, len); offset += len;
    AccTicketStatus = _util.Byte(data + offset, len); offset += len;
    ValidDateAtACC = _util.UShortDayTo19700101(data + offset, len); offset += len;
    RemainingValueAtACC = _util.Int(data + offset, len); offset += len;
    CardDepositValueAtACC = _util.Int(data + offset, len); offset += len;
    RefundReason = _util.Byte(data + offset, len); offset += len;
    CardDepreciationValue = _util.Int(data + offset, len); offset += len;
    ChargeValue = _util.Int(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardNonImmediateRefund_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(ConfirmTimeAtAccHi)); writer.String(this->ConfirmTimeAtAccHi.c_str());
    writer.Key(VAR_NAME(ConfirmTimeAtAccLo)); writer.String(this->ConfirmTimeAtAccLo.c_str());
    writer.Key(VAR_NAME(OperatorIDAtAcc)); writer.String(this->OperatorIDAtAcc.c_str());
    writer.Key(VAR_NAME(ApplyBillNo)); writer.String(this->ApplyBillNo.c_str());
    writer.Key(VAR_NAME(PassengerCNName)); writer.String(this->PassengerCNName.c_str());
    writer.Key(VAR_NAME(Gender)); writer.Uint(this->Gender);
    writer.Key(VAR_NAME(IdentificationType)); writer.Uint(this->IdentificationType);
    writer.Key(VAR_NAME(IdentificationCode)); writer.String(this->IdentificationCode.c_str());
    writer.Key(VAR_NAME(TelephoneCode)); writer.String(this->TelephoneCode.c_str());
    writer.Key(VAR_NAME(Address)); writer.String(this->Address.c_str());
    writer.Key(VAR_NAME(AccTicketStatus)); writer.Uint(this->AccTicketStatus);
    writer.Key(VAR_NAME(ValidDateAtACC)); writer.String(this->ValidDateAtACC.c_str());
    writer.Key(VAR_NAME(RemainingValueAtACC)); writer.Int(this->RemainingValueAtACC);
    writer.Key(VAR_NAME(CardDepositValueAtACC)); writer.Int(this->CardDepositValueAtACC);
    writer.Key(VAR_NAME(RefundReason)); writer.Uint(this->RefundReason);
    writer.Key(VAR_NAME(CardDepreciationValue)); writer.Int(this->CardDepreciationValue);
    writer.Key(VAR_NAME(ChargeValue)); writer.Int(this->ChargeValue);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardNonImmediateRefund_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CPUCardValidityPeriod_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    OldValidDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    NewValidDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardValidityPeriod_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(OldValidDate)); writer.String(this->OldValidDate.c_str());
    writer.Key(VAR_NAME(NewValidDate)); writer.String(this->NewValidDate.c_str());
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardValidityPeriod_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CPUCardBlock_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    BlockReasonCode = _util.Byte(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardBlock_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(BlockReasonCode)); writer.Uint(this->BlockReasonCode);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardBlock_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":block_reason_code", QVariant(BlockReasonCode));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
}

unsigned int CPUCardUnblock_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    UnblockReasonCode = _util.Byte(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardUnblock_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(UnblockReasonCode)); writer.Uint(this->UnblockReasonCode);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardUnblock_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":unblock_reason_code", QVariant(UnblockReasonCode));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
}

unsigned int TicketSurcharge_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    SurchargeCode = _util.Byte(data + offset, len); offset += len;
    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    TransStatusBeforeTrans = _util.Byte(data + offset, len); offset += len;
    TransStatusAfterTrans = _util.Byte(data + offset, len); offset += len;
    SaleDeviceID = _util.UIntX8(data + offset, len); offset += len;
    TicketSaleValue = _util.Int(data + offset, len); offset += len;
    SurchargeArea = _util.Byte(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void TicketSurcharge_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(SurchargeCode)); writer.Uint(this->SurchargeCode);
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(this->Paymentmeans);
    writer.Key(VAR_NAME(TransStatusBeforeTrans)); writer.Uint(this->TransStatusBeforeTrans);
    writer.Key(VAR_NAME(TransStatusAfterTrans)); writer.Uint(this->TransStatusAfterTrans);
    writer.Key(VAR_NAME(SaleDeviceID)); writer.String(this->SaleDeviceID.c_str());
    writer.Key(VAR_NAME(TicketSaleValue)); writer.Int(this->TicketSaleValue);
    writer.Key(VAR_NAME(SurchargeArea)); writer.Uint(this->SurchargeArea);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void TicketSurcharge_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":surcharge_code", QVariant(SurchargeCode));
    query.bindValue(":paymentmeans", QVariant(Paymentmeans));
    query.bindValue(":trans_status_before_trans", QVariant(TransStatusBeforeTrans));
    query.bindValue(":trans_status_after_trans", QVariant(TransStatusAfterTrans));
    query.bindValue(":sale_device_id", QVariant(SaleDeviceID.c_str()));
    query.bindValue(":ticket_sale_value", QVariant(TicketSaleValue));
    query.bindValue(":surcharge_area", QVariant(SurchargeArea));
    query.bindValue(":transaction_value", QVariant(TransactionValue));
    query.bindValue(":operator_id", QVariant(OperatorID.c_str()));
    query.bindValue(":bom_shift_id", QVariant(BOMShiftID.c_str()));
}

unsigned int TicketExit_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    EntryDeviceID = _util.UIntX8(data + offset, len); offset += len;
    EntryTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    EntryTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransStatusBeforeTrans = _util.Byte(data + offset, len); offset += len;
    TransStatusAfterTrans = _util.Byte(data + offset, len); offset += len;
    RemainingValueBeforeTrans = _util.Int(data + offset, len); offset += len;
    RemainingValueAfterTrans = _util.Int(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OriginalValue = _util.Int(data + offset, len); offset += len;
    SJTRecycleFlag = _util.Byte(data + offset, len); offset += len;
    DeduceLocation = _util.Byte(data + offset, len); offset += len;
    TerminateNumber = _util.TerminateNumber(data + offset, len); offset += len;
    SAMSN = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void TicketExit_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(EntryDeviceID)); writer.String(this->EntryDeviceID.c_str());
    writer.Key(VAR_NAME(EntryTimeHi)); writer.String(this->EntryTimeHi.c_str());
    writer.Key(VAR_NAME(EntryTimeLo)); writer.String(this->EntryTimeLo.c_str());
    writer.Key(VAR_NAME(TransStatusBeforeTrans)); writer.Uint(this->TransStatusBeforeTrans);
    writer.Key(VAR_NAME(TransStatusAfterTrans)); writer.Uint(this->TransStatusAfterTrans);
    writer.Key(VAR_NAME(RemainingValueBeforeTrans)); writer.Int(this->RemainingValueBeforeTrans);
    writer.Key(VAR_NAME(RemainingValueAfterTrans)); writer.Int(this->RemainingValueAfterTrans);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OriginalValue)); writer.Int(this->OriginalValue);
    writer.Key(VAR_NAME(SJTRecycleFlag)); writer.Uint(this->SJTRecycleFlag);
    writer.Key(VAR_NAME(DeduceLocation)); writer.Uint(this->DeduceLocation);
    writer.Key(VAR_NAME(TerminateNumber)); writer.String(this->TerminateNumber.c_str());
    writer.Key(VAR_NAME(SAMSN)); writer.Uint(this->SAMSN);
}

void TicketExit_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":entry_device_id", QVariant(EntryDeviceID.c_str()));
    query.bindValue(":entry_time_hi", QVariant(EntryTimeHi.c_str()));
    query.bindValue(":entry_time_lo", QVariant(EntryTimeLo.c_str()));
    query.bindValue(":trans_status_before_trans", QVariant(TransStatusBeforeTrans));
    query.bindValue(":trans_status_after_trans", QVariant(TransStatusAfterTrans));
    query.bindValue(":remaining_value_before_trans", QVariant(RemainingValueBeforeTrans));
    query.bindValue(":remaining_value_after_trans", QVariant(RemainingValueAfterTrans));
    query.bindValue(":transaction_value", QVariant(TransactionValue));
    query.bindValue(":original_value", QVariant(OriginalValue));
    query.bindValue(":sjt_recycle_flag", QVariant(SJTRecycleFlag));
    query.bindValue(":deduce_location", QVariant(DeduceLocation));
    query.bindValue(":terminate_number", QVariant(TerminateNumber.c_str()));
    query.bindValue(":sam_sn", QVariant(SAMSN));
}

unsigned int RebateScheme_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    JoinConcessionID = _util.Byte(data + offset, len); offset += len;
    JoinConcessionType = _util.Byte(data + offset, len); offset += len;
    JoinConcessionValue = _util.Int(data + offset, len); offset += len;
    JoinConcessionPercentage = _util.Byte(data + offset, len); offset += len;
    PileConcessionID = _util.UInt(data + offset, len); offset += len;
    CurrentBonus = _util.Int(data + offset, len); offset += len;
    AccumulationBonus = _util.Int(data + offset, len); offset += len;

    return offset;
}

void RebateScheme_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(JoinConcessionID)); writer.Uint(this->JoinConcessionID);
    writer.Key(VAR_NAME(JoinConcessionType)); writer.Uint(this->JoinConcessionType);
    writer.Key(VAR_NAME(JoinConcessionValue)); writer.Int(this->JoinConcessionValue);
    writer.Key(VAR_NAME(JoinConcessionPercentage)); writer.Uint(this->JoinConcessionPercentage);
    writer.Key(VAR_NAME(PileConcessionID)); writer.Uint(this->PileConcessionID);
    writer.Key(VAR_NAME(CurrentBonus)); writer.Int(this->CurrentBonus);
    writer.Key(VAR_NAME(AccumulationBonus)); writer.Int(this->AccumulationBonus);
}

void RebateScheme_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":join_concession_id", QVariant(JoinConcessionID));
    query.bindValue(":join_concession_type", QVariant(JoinConcessionType));
    query.bindValue(":join_concession_value", QVariant(JoinConcessionValue));
    query.bindValue(":join_concession_percentage", QVariant(JoinConcessionPercentage));
    query.bindValue(":pile_concession_id", QVariant(PileConcessionID));
    query.bindValue(":current_bonus", QVariant(CurrentBonus));
    query.bindValue(":accumulation_bonus", QVariant(AccumulationBonus));
}

unsigned int CPUCardDeduction_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TransactionValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardDeduction_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void CPUCardDeduction_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CPUCardSpecialPurseSale_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    SalePaymentmeans = _util.Byte(data + offset, len); offset += len;
    SaleTransactionValue = _util.Int(data + offset, len); offset += len;
    SaleTransactionStatus = _util.Byte(data + offset, len); offset += len;
    SalePurseType = _util.Byte(data + offset, len); offset += len;
    SaleStageID = _util.Byte(data + offset, len); offset += len;
    SaleValidStartDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    SaleValidEndDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    SaleSectionID = _util.Byte(data + offset, len); offset += len;
    SaleOperatorID = _util.UIntX6(data + offset, len); offset += len;
    SaleBOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void CPUCardSpecialPurseSale_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(SalePaymentmeans)); writer.Uint(this->SalePaymentmeans);
    writer.Key(VAR_NAME(SaleTransactionValue)); writer.Int(this->SaleTransactionValue);
    writer.Key(VAR_NAME(SaleTransactionStatus)); writer.Uint(this->SaleTransactionStatus);
    writer.Key(VAR_NAME(SalePurseType)); writer.Uint(this->SalePurseType);
    writer.Key(VAR_NAME(SaleStageID)); writer.Uint(this->SaleStageID);
    writer.Key(VAR_NAME(SaleValidStartDate)); writer.String(this->SaleValidStartDate.c_str());
    writer.Key(VAR_NAME(SaleValidEndDate)); writer.String(this->SaleValidEndDate.c_str());
    writer.Key(VAR_NAME(SaleSectionID)); writer.Uint(this->SaleSectionID);
    writer.Key(VAR_NAME(SaleOperatorID)); writer.String(this->SaleOperatorID.c_str());
    writer.Key(VAR_NAME(SaleBOMShiftID)); writer.String(this->SaleBOMShiftID.c_str());
}

void CPUCardSpecialPurseSale_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int YiKaTongTradePub::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TxnType = _util.UShort(data + offset, len); offset += len;
    TransactionDateTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransactionDateTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LineID = _util.ByteX2(data + offset, len); offset += len;
    StationID = _util.UShortX4(data + offset, len); offset += len;
    DeviceID = _util.UIntX8(data + offset, len); offset += len;
    ModeCode = _util.Byte(data + offset, len); offset += len;
    UDSN = _util.UInt(data + offset, len); offset += len;
    ePurseTransactionType = _util.UShort(data + offset, len); offset += len;
    CityCode_TransLocation = _util.UShort(data + offset, len); offset += len;
    CityCode_BelongLocation = _util.UShort(data + offset, len); offset += len;
    TACSAMID = _util.UTF8String(data + offset, len); offset += len;
    TerminateNumber = _util.TerminateNumber(data + offset, len); offset += len;
    SAMSN = _util.UInt(data + offset, len); offset += len;
    SAK = _util.Byte(data + offset, len); offset += len;
    MainCardType = _util.Byte(data + offset, len); offset += len;
    SubCardType = _util.Byte(data + offset, len); offset += len;
    CardVer = _util.Byte(data + offset, len); offset += len;
    RechargeSN = _util.UInt(data + offset, len); offset += len;
    AddValueDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    SaleDate = _util.UShortDayTo19700101(data + offset, len); offset += len;
    SystemTraceSN = _util.UInt(data + offset, len); offset += len;
    TransactionType = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void YiKaTongTradePub::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TxnType)); writer.Uint(this->TxnType);
    writer.Key(VAR_NAME(TransactionDateTimeHi)); writer.String(this->TransactionDateTimeHi.c_str());
    writer.Key(VAR_NAME(TransactionDateTimeLo)); writer.String(this->TransactionDateTimeLo.c_str());
    writer.Key(VAR_NAME(LineID)); writer.String(this->LineID.c_str());
    writer.Key(VAR_NAME(StationID)); writer.String(this->StationID.c_str());
    writer.Key(VAR_NAME(DeviceID)); writer.String(this->DeviceID.c_str());
    writer.Key(VAR_NAME(ModeCode)); writer.Int(this->ModeCode);
    writer.Key(VAR_NAME(UDSN)); writer.Uint(this->UDSN);
    writer.Key(VAR_NAME(ePurseTransactionType)); writer.Uint(this->ePurseTransactionType);
    writer.Key(VAR_NAME(CityCode_TransLocation)); writer.Uint(this->CityCode_TransLocation);
    writer.Key(VAR_NAME(CityCode_BelongLocation)); writer.Uint(this->CityCode_BelongLocation);
    writer.Key(VAR_NAME(TACSAMID)); writer.String(this->TACSAMID.c_str());
    writer.Key(VAR_NAME(TerminateNumber)); writer.String(this->TerminateNumber.c_str());
    writer.Key(VAR_NAME(SAMSN)); writer.Uint(this->SAMSN);
    writer.Key(VAR_NAME(SAK)); writer.Uint(this->SAK);
    writer.Key(VAR_NAME(MainCardType)); writer.Uint(this->MainCardType);
    writer.Key(VAR_NAME(SubCardType)); writer.Uint(this->SubCardType);
    writer.Key(VAR_NAME(CardVer)); writer.Uint(this->CardVer);
    writer.Key(VAR_NAME(RechargeSN)); writer.Uint(this->RechargeSN);
    writer.Key(VAR_NAME(AddValueDate)); writer.String(this->AddValueDate.c_str());
    writer.Key(VAR_NAME(SaleDate)); writer.String(this->SaleDate.c_str());
    writer.Key(VAR_NAME(SystemTraceSN)); writer.Uint(this->SystemTraceSN);
    writer.Key(VAR_NAME(TransactionType)); writer.Uint(this->TransactionType);
}

void YiKaTongTradePub::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":txn_type", QVariant(TxnType));
    query.bindValue(":transaction_date_time_hi", QVariant(TransactionDateTimeHi.c_str()));
    query.bindValue(":transaction_data_time_lo", QVariant(TransactionDateTimeLo.c_str()));
    query.bindValue(":line_id", QVariant(LineID.c_str()));
    query.bindValue(":station_id", QVariant(StationID.c_str()));
    query.bindValue(":device_id", QVariant(DeviceID.c_str()));
    query.bindValue(":mode_code", QVariant(ModeCode));
    query.bindValue(":udsn", QVariant(UDSN));
    query.bindValue(":e_purse_transaction_type", QVariant(ePurseTransactionType));
    query.bindValue(":city_code_trans_location", QVariant(CityCode_TransLocation));
    query.bindValue(":city_code_belong_location", QVariant(CityCode_BelongLocation));
    query.bindValue(":tac_sam_id", QVariant(TACSAMID.c_str()));
    query.bindValue(":terminate_number", QVariant(TerminateNumber.c_str()));
    query.bindValue(":sam_sn", QVariant(SAMSN));
    query.bindValue(":sak", QVariant(SAK));
    query.bindValue(":main_card_type", QVariant(MainCardType));
    query.bindValue(":sub_card_type", QVariant(SubCardType));
    query.bindValue(":card_ver", QVariant(CardVer));
    query.bindValue(":recharge_sn", QVariant(RechargeSN));
    query.bindValue(":add_value_date", QVariant(AddValueDate.c_str()));
    query.bindValue(":sale_date", QVariant(SaleDate.c_str()));
    query.bindValue(":system_trace_sn", QVariant(SystemTraceSN));
    query.bindValue(":transaction_type", QVariant(TransactionType));
}

unsigned int YKTTicketPassengerComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    PassengerCNName = _util.UTF8String(data + offset, len); offset += len;
    IdentificationType = _util.Byte(data + offset, len); offset += len;
    IdentificationCode = _util.UTF8String(data + offset, len); offset += len;
    TelephoneCode = _util.UTF8String(data + offset, len); offset += len;
    Address = _util.UTF8String(data + offset, len); offset += len;
    CompanyName = _util.UTF8String(data + offset, len); offset += len;

    return offset;
}

void YKTTicketPassengerComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(PassengerCNName)); writer.String(this->PassengerCNName.c_str());
    writer.Key(VAR_NAME(IdentificationType)); writer.Uint(this->IdentificationType);
    writer.Key(VAR_NAME(IdentificationCode)); writer.String(this->IdentificationCode.c_str());
    writer.Key(VAR_NAME(TelephoneCode)); writer.String(this->TelephoneCode.c_str());
    writer.Key(VAR_NAME(Address)); writer.String(this->Address.c_str());
    writer.Key(VAR_NAME(CompanyName)); writer.String(this->CompanyName.c_str());
}

void YKTTicketPassengerComm_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int YKTTicketExit_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    EntryDeviceID = _util.UIntX8(data + offset, len); offset += len;
    EntryTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    EntryTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransStatusBeforeTrans = _util.Byte(data + offset, len); offset += len;
    TransStatusAfterTrans = _util.Byte(data + offset, len); offset += len;
    RemainingValueBeforeTrans = _util.Int(data + offset, len); offset += len;
    RemainingValueAfterTrans = _util.Int(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    OriginalValue = _util.Int(data + offset, len); offset += len;

    return offset;
}

void YKTTicketExit_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(EntryDeviceID)); writer.String(this->EntryDeviceID.c_str());
    writer.Key(VAR_NAME(EntryTimeHi)); writer.String(this->EntryTimeHi.c_str());
    writer.Key(VAR_NAME(EntryTimeLo)); writer.String(this->EntryTimeLo.c_str());
    writer.Key(VAR_NAME(TransStatusBeforeTrans)); writer.Uint(this->TransStatusBeforeTrans);
    writer.Key(VAR_NAME(TransStatusAfterTrans)); writer.Uint(this->TransStatusAfterTrans);
    writer.Key(VAR_NAME(RemainingValueBeforeTrans)); writer.Int(this->RemainingValueBeforeTrans);
    writer.Key(VAR_NAME(RemainingValueAfterTrans)); writer.Int(this->RemainingValueAfterTrans);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(OriginalValue)); writer.Int(this->OriginalValue);
}

void YKTTicketExit_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":entry_device_id", QVariant(EntryDeviceID.c_str()));
    query.bindValue(":entry_time_hi", QVariant(EntryTimeHi.c_str()));
    query.bindValue(":entry_time_lo", QVariant(EntryTimeLo.c_str()));
    query.bindValue(":trans_status_before_trans", QVariant(TransStatusBeforeTrans));
    query.bindValue(":trans_status_after_trans", QVariant(TransStatusAfterTrans));
    query.bindValue(":remaining_value_befor_trans", QVariant(RemainingValueBeforeTrans));
    query.bindValue(":remaining_value_after_trans", QVariant(RemainingValueAfterTrans));
    query.bindValue(":transaction_value", QVariant(TransactionValue));
    query.bindValue(":original_value", QVariant(OriginalValue));
}

unsigned int YKTMetroStart_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    SurchargeArea = _util.Byte(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void YKTMetroStart_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(SurchargeArea)); writer.Uint(this->SurchargeArea);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void YKTMetroStart_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int CellPhoneTradePub::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TxnType = _util.UShort(data + offset, len); offset += len;
    TransactionDateTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransactionDateTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LineID = _util.ByteX2(data + offset, len); offset += len;
    StationID = _util.UShortX4(data + offset, len); offset += len;
    DeviceID = _util.UIntX8(data + offset, len); offset += len;
    TACSAMID = _util.UInt(data + offset, len); offset += len;
    ModeCode = _util.Byte(data + offset, len); offset += len;
    UDSN = _util.UInt(data + offset, len); offset += len;
    TransactionType = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void CellPhoneTradePub::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TxnType)); writer.Uint(this->TxnType);
    writer.Key(VAR_NAME(TransactionDateTimeHi)); writer.String(this->TransactionDateTimeHi.c_str());
    writer.Key(VAR_NAME(TransactionDateTimeLo)); writer.String(this->TransactionDateTimeLo.c_str());
    writer.Key(VAR_NAME(LineID)); writer.String(this->LineID.c_str());
    writer.Key(VAR_NAME(StationID)); writer.String(this->StationID.c_str());
    writer.Key(VAR_NAME(DeviceID)); writer.String(this->DeviceID.c_str());
    writer.Key(VAR_NAME(TACSAMID)); writer.Uint(this->TACSAMID);
    writer.Key(VAR_NAME(ModeCode)); writer.Int(this->ModeCode);
    writer.Key(VAR_NAME(UDSN)); writer.Uint(this->UDSN);
    writer.Key(VAR_NAME(TransactionType)); writer.Uint(this->TransactionType);
}

void CellPhoneTradePub::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":txn_type", QVariant(TxnType));
    query.bindValue(":transaction_date_time_hi", QVariant(TransactionDateTimeHi.c_str()));
    query.bindValue(":transaction_data_time_lo", QVariant(TransactionDateTimeLo.c_str()));
    query.bindValue(":line_id", QVariant(LineID.c_str()));
    query.bindValue(":station_id", QVariant(StationID.c_str()));
    query.bindValue(":device_id", QVariant(DeviceID.c_str()));
    query.bindValue(":tac_sam_id", QVariant(TACSAMID));
    query.bindValue(":mode_code", QVariant(ModeCode));
    query.bindValue(":udsn", QVariant(UDSN));
    query.bindValue(":transaction_type", QVariant(TransactionType));
}

unsigned int MobileDeduction_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TicketFamilyType = _util.UShort(data + offset, len); offset += len;
    TicketType = _util.Byte(data + offset, len); offset += len;
    TestFlag = _util.Byte(data + offset, len); offset += len;
    IssuerCode = _util.UInt(data + offset, len); offset += len;
    IssuerSN = _util.UInt(data + offset, len); offset += len;
    CityCode = _util.UShort(data + offset, len); offset += len;
    SIMType = _util.Byte(data + offset, len); offset += len;
    SIMStatus = _util.Byte(data + offset, len); offset += len;
    SIMID = _util.UTF8String(data + offset, len); offset += len;
    MobileNo = _util.UTF8String(data + offset, len); offset += len;
    SIMTransSN = _util.UInt(data + offset, len); offset += len;
    TransactionValue = _util.Int(data + offset, len); offset += len;
    SIMStatusAfterTrans = _util.Byte(data + offset, len); offset += len;
    RemainingValueAfterTrans = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void MobileDeduction_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TicketFamilyType)); writer.Uint(this->TicketFamilyType);
    writer.Key(VAR_NAME(TicketType)); writer.Uint(this->TicketType);
    writer.Key(VAR_NAME(TestFlag)); writer.Uint(this->TestFlag);
    writer.Key(VAR_NAME(IssuerCode)); writer.Uint(this->IssuerCode);
    writer.Key(VAR_NAME(IssuerSN)); writer.Uint(this->IssuerSN);
    writer.Key(VAR_NAME(CityCode)); writer.Uint(this->CityCode);
    writer.Key(VAR_NAME(SIMType)); writer.Uint(this->SIMType);
    writer.Key(VAR_NAME(SIMStatus)); writer.Uint(this->SIMStatus);
    writer.Key(VAR_NAME(SIMID)); writer.String(this->SIMID.c_str());
    writer.Key(VAR_NAME(MobileNo)); writer.String(this->MobileNo.c_str());
    writer.Key(VAR_NAME(SIMTransSN)); writer.Uint(this->SIMTransSN);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(SIMStatusAfterTrans)); writer.Uint(this->SIMStatusAfterTrans);
    writer.Key(VAR_NAME(RemainingValueAfterTrans)); writer.Int(this->RemainingValueAfterTrans);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void MobileDeduction_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int BankCardTradePub::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TxnType = _util.UShort(data + offset, len); offset += len;
    TransactionDateTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransactionDateTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LineID = _util.ByteX2(data + offset, len); offset += len;
    StationID = _util.UShortX4(data + offset, len); offset += len;
    DeviceID = _util.UIntX8(data + offset, len); offset += len;
    TACSAMID = _util.UInt(data + offset, len); offset += len;
    ModeCode = _util.Byte(data + offset, len); offset += len;
    UDSN = _util.UInt(data + offset, len); offset += len;
    TransactionType = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardTradePub::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TxnType)); writer.Uint(this->TxnType);
    writer.Key(VAR_NAME(TransactionDateTimeHi)); writer.String(this->TransactionDateTimeHi.c_str());
    writer.Key(VAR_NAME(TransactionDateTimeLo)); writer.String(this->TransactionDateTimeLo.c_str());
    writer.Key(VAR_NAME(LineID)); writer.String(this->LineID.c_str());
    writer.Key(VAR_NAME(StationID)); writer.String(this->StationID.c_str());
    writer.Key(VAR_NAME(DeviceID)); writer.String(this->DeviceID.c_str());
    writer.Key(VAR_NAME(TACSAMID)); writer.Uint(this->TACSAMID);
    writer.Key(VAR_NAME(ModeCode)); writer.Int(this->ModeCode);
    writer.Key(VAR_NAME(UDSN)); writer.Uint(this->UDSN);
    writer.Key(VAR_NAME(TransactionType)); writer.Uint(this->TransactionType);
}

void BankCardTradePub::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":txn_type", QVariant(TxnType));
    query.bindValue(":transaction_date_time_hi", QVariant(TransactionDateTimeHi.c_str()));
    query.bindValue(":transaction_data_time_lo", QVariant(TransactionDateTimeLo.c_str()));
    query.bindValue(":line_id", QVariant(LineID.c_str()));
    query.bindValue(":station_id", QVariant(StationID.c_str()));
    query.bindValue(":device_id", QVariant(DeviceID.c_str()));
    query.bindValue(":tac_sam_id", QVariant(TACSAMID));
    query.bindValue(":mode_code", QVariant(ModeCode));
    query.bindValue(":udsn", QVariant(UDSN));
    query.bindValue(":transaction_type", QVariant(TransactionType));
}

unsigned int BankCardTicketComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TicketFamilyType = _util.UShort(data + offset, len); offset += len;
    TicketType = _util.Byte(data + offset, len); offset += len;
    TicketCatalogID = _util.Byte(data + offset, len); offset += len;
    PrimaryAccount = _util.UTF8String(data + offset, len); offset += len;
    BankCode = _util.UTF8String(data + offset, len); offset += len;
    PosNo = _util.UTF8String(data + offset, len); offset += len;
    TerminNo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardTicketComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TicketFamilyType)); writer.Uint(this->TicketFamilyType);
    writer.Key(VAR_NAME(TicketType)); writer.Uint(this->TicketType);
    writer.Key(VAR_NAME(TicketCatalogID)); writer.Uint(this->TicketCatalogID);
    writer.Key(VAR_NAME(PrimaryAccount)); writer.String(this->PrimaryAccount.c_str());
    writer.Key(VAR_NAME(BankCode)); writer.String(this->BankCode.c_str());
    writer.Key(VAR_NAME(PosNo)); writer.String(this->PosNo.c_str());
    writer.Key(VAR_NAME(TerminNo)); writer.Uint(this->TerminNo);
}

void BankCardTicketComm_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":ticket_family_type", QVariant(TicketFamilyType));
    query.bindValue(":ticket_type", QVariant(TicketType));
    query.bindValue(":ticket_catalog_id", QVariant(TicketCatalogID));
    query.bindValue(":primary_account", QVariant(PrimaryAccount.c_str()));
    query.bindValue(":bank_code", QVariant(BankCode.c_str()));
    query.bindValue(":pos_no", QVariant(PosNo.c_str()));
    query.bindValue(":termin_no", QVariant(TerminNo));
}

unsigned int BankCardSurcharge_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    PreAuthValue = _util.Int(data + offset, len); offset += len;
    AuthCode = _util.UTF8String(data + offset, len); offset += len;
    SurchargeCode = _util.Byte(data + offset, len); offset += len;
    Paymentmeans = _util.Byte(data + offset, len); offset += len;
    SaleDeviceID = _util.UIntX8(data + offset, len); offset += len;
    TicketSaleValue = _util.Int(data + offset, len); offset += len;
    SurchargeArea = _util.Byte(data + offset, len); offset += len;
    SurchargeValue = _util.Int(data + offset, len); offset += len;
    DisSurchargeValue = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;
    ReserveOne = _util.UInt(data + offset, len); offset += len;
    ReserveTwo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardSurcharge_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(PreAuthValue)); writer.Int(this->PreAuthValue);
    writer.Key(VAR_NAME(AuthCode)); writer.String(this->AuthCode.c_str());
    writer.Key(VAR_NAME(SurchargeCode)); writer.Uint(this->SurchargeCode);
    writer.Key(VAR_NAME(Paymentmeans)); writer.Uint(this->Paymentmeans);
    writer.Key(VAR_NAME(SaleDeviceID)); writer.String(this->SaleDeviceID.c_str());
    writer.Key(VAR_NAME(TicketSaleValue)); writer.Int(this->TicketSaleValue);
    writer.Key(VAR_NAME(SurchargeArea)); writer.Uint(this->SurchargeArea);
    writer.Key(VAR_NAME(SurchargeValue)); writer.Int(this->SurchargeValue);
    writer.Key(VAR_NAME(DisSurchargeValue)); writer.Int(this->SurchargeValue);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
    writer.Key(VAR_NAME(ReserveOne)); writer.Uint(this->ReserveOne);
    writer.Key(VAR_NAME(ReserveTwo)); writer.Uint(this->ReserveTwo);
}

void BankCardSurcharge_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int BankCardEntry_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    PreAuthValue = _util.Int(data + offset, len); offset += len;
    AuthCode = _util.UTF8String(data + offset, len); offset += len;
    ReserveOne = _util.UInt(data + offset, len); offset += len;
    ReserveTwo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardEntry_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(PreAuthValue)); writer.Int(this->PreAuthValue);
    writer.Key(VAR_NAME(AuthCode)); writer.String(this->AuthCode.c_str());
    writer.Key(VAR_NAME(ReserveOne)); writer.Uint(this->ReserveOne);
    writer.Key(VAR_NAME(ReserveTwo)); writer.Uint(this->ReserveTwo);
}

void BankCardEntry_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":pre_auth_value", QVariant(PreAuthValue));
    query.bindValue(":auth_code", QVariant(AuthCode.c_str()));
    query.bindValue(":reserve_one", QVariant(ReserveOne));
    query.bindValue(":reserve_two", QVariant(ReserveTwo));
}

unsigned int BankCardExit_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TransValue = _util.Int(data + offset, len); offset += len;
    DisTransValue = _util.Int(data + offset, len); offset += len;
    StartDevice = _util.UIntX8(data + offset, len); offset += len;
    StartTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    StartTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    ReserveOne = _util.UInt(data + offset, len); offset += len;
    ReserveTwo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void BankCardExit_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TransValue)); writer.Int(this->TransValue);
    writer.Key(VAR_NAME(DisTransValue)); writer.Int(this->DisTransValue);
    writer.Key(VAR_NAME(StartDevice)); writer.String(this->StartDevice.c_str());
    writer.Key(VAR_NAME(StartTimeHi)); writer.String(this->StartTimeHi.c_str());
    writer.Key(VAR_NAME(StartTimeLo)); writer.String(this->StartTimeLo.c_str());
    writer.Key(VAR_NAME(ReserveOne)); writer.Uint(this->ReserveOne);
    writer.Key(VAR_NAME(ReserveTwo)); writer.Uint(this->ReserveTwo);
}

void BankCardExit_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":trans_value", QVariant(TransValue));
    query.bindValue(":dis_trans_value", QVariant(DisTransValue));
    query.bindValue(":start_device", QVariant(StartDevice.c_str()));
    query.bindValue(":start_time_hi", QVariant(StartTimeHi.c_str()));
    query.bindValue(":start_time_lo", QVariant(StartTimeLo.c_str()));
    query.bindValue(":reserve_one", QVariant(ReserveOne));
    query.bindValue(":reserve_two", QVariant(ReserveTwo));
}

unsigned int BankCardDeduction_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TestFlag = _util.Byte(data + offset, len); offset += len;
    offset += bcp.parse(data + offset);
    TransactionValue = _util.Int(data + offset, len); offset += len;
    RemainingValueAfterTrans = _util.Int(data + offset, len); offset += len;
    OperatorID = _util.UIntX6(data + offset, len); offset += len;
    BOMShiftID = _util.UIntX8(data + offset, len); offset += len;

    return offset;
}

void BankCardDeduction_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TestFlag)); writer.Uint(TestFlag);
    bcp.output(writer);
    writer.Key(VAR_NAME(TransactionValue)); writer.Int(this->TransactionValue);
    writer.Key(VAR_NAME(RemainingValueAfterTrans)); writer.Int(this->RemainingValueAfterTrans);
    writer.Key(VAR_NAME(OperatorID)); writer.String(this->OperatorID.c_str());
    writer.Key(VAR_NAME(BOMShiftID)); writer.String(this->BOMShiftID.c_str());
}

void BankCardDeduction_t::sqltransaction(QSqlQuery& query)
{
    Q_UNUSED(query);
}

unsigned int QRCodeTradePub::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TxnType = _util.UShort(data + offset, len); offset += len;
    TransactionDateTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    TransactionDateTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    LineID = _util.ByteX2(data + offset, len); offset += len;
    StationID = _util.UShortX4(data + offset, len); offset += len;
    DeviceID = _util.UIntX8(data + offset, len); offset += len;
    TACSAMID = _util.UInt(data + offset, len); offset += len;
    ModeCode = _util.Byte(data + offset, len); offset += len;
    UDSN = _util.UInt(data + offset, len); offset += len;
    TransactionType = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void QRCodeTradePub::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TxnType)); writer.Uint(this->TxnType);
    writer.Key(VAR_NAME(TransactionDateTimeHi)); writer.String(this->TransactionDateTimeHi.c_str());
    writer.Key(VAR_NAME(TransactionDateTimeLo)); writer.String(this->TransactionDateTimeLo.c_str());
    writer.Key(VAR_NAME(LineID)); writer.String(this->LineID.c_str());
    writer.Key(VAR_NAME(StationID)); writer.String(this->StationID.c_str());
    writer.Key(VAR_NAME(DeviceID)); writer.String(this->DeviceID.c_str());
    writer.Key(VAR_NAME(TACSAMID)); writer.Uint(this->TACSAMID);
    writer.Key(VAR_NAME(ModeCode)); writer.Int(this->ModeCode);
    writer.Key(VAR_NAME(UDSN)); writer.Uint(this->UDSN);
    writer.Key(VAR_NAME(TransactionType)); writer.Uint(this->TransactionType);
}

void QRCodeTradePub::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":txn_type", QVariant(TxnType));
    query.bindValue(":transaction_date_time_hi", QVariant(TransactionDateTimeHi.c_str()));
    query.bindValue(":transaction_data_time_lo", QVariant(TransactionDateTimeLo.c_str()));
    query.bindValue(":line_id", QVariant(LineID.c_str()));
    query.bindValue(":station_id", QVariant(StationID.c_str()));
    query.bindValue(":device_id", QVariant(DeviceID.c_str()));
    query.bindValue(":tac_sam_id", QVariant(TACSAMID));
    query.bindValue(":mode_code", QVariant(ModeCode));
    query.bindValue(":udsn", QVariant(UDSN));
    query.bindValue(":transaction_type", QVariant(TransactionType));
}

unsigned int QRCodeTicketComm_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TicketFamilyType = _util.UShort(data + offset, len); offset += len;
    TicketType = _util.Byte(data + offset, len); offset += len;
    TicketCatalogID = _util.UShort(data + offset, len); offset += len;
    Uid = _util.UTF8String(data + offset, len); offset += len;
    QRCodeID = _util.UTF8String(data + offset, len); offset += len;

    return offset;
}

void QRCodeTicketComm_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TicketFamilyType)); writer.Uint(this->TicketFamilyType);
    writer.Key(VAR_NAME(TicketType)); writer.Uint(this->TicketType);
    writer.Key(VAR_NAME(TicketCatalogID)); writer.Uint(this->TicketCatalogID);
    writer.Key(VAR_NAME(Uid)); writer.String(this->Uid.c_str());
    writer.Key(VAR_NAME(QRCodeID)); writer.String(this->QRCodeID.c_str());
}

void QRCodeTicketComm_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":ticket_family_type", QVariant(TicketFamilyType));
    query.bindValue(":ticket_type", QVariant(TicketType));
    query.bindValue(":ticket_catalog_id", QVariant(TicketCatalogID));
    query.bindValue(":uid", QVariant(Uid.c_str()));
    query.bindValue(":qr_code_id", QVariant(QRCodeID.c_str()));
}

unsigned int QRCodeUnnamed::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    ReserveOne = _util.UInt(data + offset, len); offset += len;
    ReserveTwo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void QRCodeUnnamed::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(ReserveOne)); writer.Uint(this->ReserveOne);
    writer.Key(VAR_NAME(ReserveTwo)); writer.Uint(this->ReserveTwo);
}

void QRCodeUnnamed::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":reserve_one", QVariant(ReserveOne));
    query.bindValue(":reserve_two", QVariant(ReserveTwo));
}

unsigned int QRCodeExit_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    TransValue = _util.Int(data + offset, len); offset += len;
    StartDevice = _util.UIntX8(data + offset, len); offset += len;
    StartTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    StartTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    ReserveOne = _util.UInt(data + offset, len); offset += len;
    ReserveTwo = _util.UInt(data + offset, len); offset += len;

    return offset;
}

void QRCodeExit_t::output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
    writer.Key(VAR_NAME(TransValue)); writer.Int(this->TransValue);
    writer.Key(VAR_NAME(StartDevice)); writer.String(this->StartDevice.c_str());
    writer.Key(VAR_NAME(StartTimeHi)); writer.String(this->StartTimeHi.c_str());
    writer.Key(VAR_NAME(StartTimeLo)); writer.String(this->StartTimeLo.c_str());
    writer.Key(VAR_NAME(ReserveOne)); writer.Uint(this->ReserveOne);
    writer.Key(VAR_NAME(ReserveTwo)); writer.Uint(this->ReserveTwo);
}

void QRCodeExit_t::sqltransaction(QSqlQuery& query)
{
    query.bindValue(":trans_value", QVariant(TransValue));
    query.bindValue(":start_device", QVariant(StartDevice.c_str()));
    query.bindValue(":start_time_hi", QVariant(StartTimeHi.c_str()));
    query.bindValue(":start_time_lo", QVariant(StartTimeLo.c_str()));
    query.bindValue(":reserve_one", QVariant(ReserveOne));
    query.bindValue(":reserve_two", QVariant(ReserveTwo));
}
