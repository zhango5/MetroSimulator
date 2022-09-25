﻿#include "model.h"

DevOpFileHeader::DevOpFileHeader()
    : FileType(0)
    , FileSN(0)
    , RecordsInFile(0)
    , FileHeaderTag(0)
{

}

DevOpFileHeader::~DevOpFileHeader()
{

}

unsigned int DevOpFileHeader::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    FileType = _util.UShort(data + offset, len); offset += len;
    FileCreationTimeHi = _util.IntSecondTo19700101(data + offset, len); offset += len;
    FileCreationTimeLo = _util.IntSecondTo19700101(data + offset, len); offset += len;
    FileName = _util.FileName(data + offset, len); offset += len;
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

YiPiaoTongTradePub::YiPiaoTongTradePub()
    : TxnType(0)
    , TACSAMID(0)
    , ModeCode(0)
    , UDSN(0)
    , TransactionType(0)
{

}

YiPiaoTongTradePub::~YiPiaoTongTradePub()
{

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

TicketComm_t::TicketComm_t()
{

}

TicketComm_t::~TicketComm_t()
{

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

TicketEntry_t::TicketEntry_t()
{

}

TicketEntry_t::~TicketEntry_t()
{

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
    writer.Key(VAR_NAME(LastAddValueTimeHi)); writer.String(this->ValidDateBeforeAddValue.c_str());
    writer.Key(VAR_NAME(LastAddValueTimeLo)); writer.String(this->ValidDateAfterAddValue.c_str());
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

unsigned int TicketExit_t::parse(const char* data)
{
    if (nullptr == data) return 0;

    unsigned int len = 0;
    unsigned int offset = 0;

    Util _util;

    EntryDeviceID = _util.UInt(data + offset, len); offset += len;
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
    writer.Key(VAR_NAME(EntryDeviceID)); writer.Uint(this->EntryDeviceID);
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