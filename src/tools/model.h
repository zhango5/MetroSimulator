#ifndef MODEL_H
#define MODEL_H

#include "iparser.h"
#include <string>
#include "util.h"

#define VAR_NAME(_X_)    #_X_

class DevOpFileHeader : public IParser
{
public:
    DevOpFileHeader();
    ~DevOpFileHeader();

public:
    virtual unsigned int parse(const char* data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) override;

private:
    unsigned short FileType;
    std::string    FileCreationTimeHi;
    std::string    FileCreationTimeLo;
    std::string    FileName;
    std::string    FileLineID;
    std::string    FileStationID;
    std::string    FileDeviceID;
    std::string    BusinessDay;
    unsigned int   FileSN;
    unsigned short RecordsInFile;
    unsigned short FileHeaderTag;
};

class YiPiaoTongTradePub : public IParser
{
public:
    YiPiaoTongTradePub();
    ~YiPiaoTongTradePub();

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned short TxnType;
    std::string    TransactionDateTimeHi;
    std::string    TransactionDateTimeLo;
    std::string    LineID;
    std::string    StationID;
    std::string    DeviceID;
    unsigned int   TACSAMID;
    unsigned char  ModeCode;
    unsigned int   UDSN;
    unsigned int   TransactionType;
};

class TicketComm_t : public IParser
{
public:
    TicketComm_t();
    ~TicketComm_t();

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned short TicketFamilyType;
    unsigned char  TicketType;
    unsigned short TicketCatalogID;
    std::string    TicketPhyID;
    std::string    TicketLogicID;
    unsigned char  TicketStatus;
    unsigned char  TestFlag;
    unsigned int   TicketSN;
    int            TicketRemainingValue;
};

class TicketEntry_t : public IParser
{
public:
    TicketEntry_t();
    ~TicketEntry_t();

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  TransStatusBeforeTrans;
    unsigned char  TransStatusAfterTrans;
    int            RemainingValue;
};

class SJTInitComm_t : public IParser
{
public:
    SJTInitComm_t() {}
    ~SJTInitComm_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    std::string   CardInitDate;
    unsigned char InitBatchCode = 0;
};

class SJTSale_t : public IParser
{
public:
    SJTSale_t() {}
    ~SJTSale_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char Paymentmeans = 0;
    unsigned char LanguageFlag = 0;
    int           TransactionValue = 0;
    int           TicketPriceValue = 0;
    int           ChangeValue = 0;
    int           OriginalValue = 0;
    unsigned char TransactionStatus = 0;
    std::string   ValidStartDate;
    std::string   ValidEndDate;
    std::string   OperatorID;
    std::string   BOMShiftID;
};

class CPUInitComm_t : public IParser
{
public:
    CPUInitComm_t() {}
    ~CPUInitComm_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned int  IssuerCode = 0;
    std::string   CardIssueDate;
    std::string   AppSN;
};

class CPUCardSale_t : public IParser
{
public:
    CPUCardSale_t() {}
    ~CPUCardSale_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char Paymentmeans = 0;
    unsigned char LanguageFlag = 0;
    int           TransactionValue = 0;
    unsigned char TransactionStatus = 0;
    std::string   ValidStartDate;
    std::string   ValidEndDate;
    unsigned char SectionID = 0;
    std::string   OperatorID;
    std::string   BOMShiftID;
};

class TicketPassengerComm_t : public IParser
{
public:
    TicketPassengerComm_t() {}
    ~TicketPassengerComm_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char PassengerTypeID = 0;
    unsigned char PassengerStaffFlag = 0;
    std::string   PassengerCNName;
    unsigned char IdentificationType = 0;
    std::string   IdentificationCode;
};

class CPUCardMemberRegister_t : public IParser
{
public:
    CPUCardMemberRegister_t() {}
    ~CPUCardMemberRegister_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned short TicketFamilyType;
    unsigned char  TicketType;
    std::string    ApplyBillNo;
    int            CardDepositValue;
    unsigned char  Paymentmeans;
    std::string    PassengerName;
    unsigned char  Gender;
    std::string    TelephoneCode;
    std::string    Address;
    unsigned char  IdentificationType;
    std::string    IdentificationCode;
    std::string    ValidDate;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class BankCardPayment_t : public IParser
{
public:
    BankCardPayment_t() {}
    ~BankCardPayment_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    std::string   BankCode;
    std::string   BIZCode;
    std::string   PosNo;
    std::string   BankCardCode;
    unsigned int  BankTransSN = 0;
};

class CPUCardAddValue_t : public IParser
{
public:
    CPUCardAddValue_t() {}
    ~CPUCardAddValue_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  Paymentmeans;
    int            TransactionValue;
    std::string    ValidDateBeforeAddValue;
    std::string    ValidDateAfterAddValue;
    int            NewRemainingValue;
    BankCardPayment_t bcp;
    int            LastAddTransactionValue;
    std::string    LastAddValueTimeHi;
    std::string    LastAddValueTimeLo;
    unsigned int   LastAddValueUDSN;
    std::string    LastAddValueSAMID;
    std::string    LastAddValueDeviceID;
    std::string    OperatorID;
    std::string    BOMShiftID;
    std::string    ChargeTerminateNumber;
    std::string    HostTransactionTimeHi;
    std::string    HostTransactionTimeLo;
    int            RealTransactionValue;
};

class SJTRefund_t : public IParser
{
public:
    SJTRefund_t() {}
    ~SJTRefund_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    int            PriceValue = 0;
    unsigned char  RefundReason = 0;
    int            TransactionValue = 0;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardImmediateRefund_t : public IParser
{
public:
    CPUCardImmediateRefund_t() {}
    ~CPUCardImmediateRefund_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    std::string    ValidDate;
    int            RemainingValue;
    int            CardDepositValue;
    unsigned char  AccTicketStatus;
    std::string    ValidDateAtACC;
    int            RemainingValueAtACC;
    int            CardDepositValueAtACC;
    unsigned char  RefundReason;
    int            CardDepreciationValue;
    int            ChargeValue;
    int            TransactionValue;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardNonImmediateRefund_t : public IParser
{
public:
    CPUCardNonImmediateRefund_t() {}
    ~CPUCardNonImmediateRefund_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    std::string    ConfirmTimeAtAccHi;
    std::string    ConfirmTimeAtAccLo;
    std::string    OperatorIDAtAcc;
    std::string    ApplyBillNo;
    std::string    PassengerCNName;
    unsigned char  Gender;
    unsigned char  IdentificationType;
    std::string    IdentificationCode;
    std::string    TelephoneCode;
    std::string    Address;
    unsigned char  AccTicketStatus;
    std::string    ValidDateAtACC;
    int            RemainingValueAtACC;
    int            CardDepositValueAtACC;
    unsigned char  RefundReason;
    int            CardDepreciationValue;
    int            ChargeValue;
    int            TransactionValue;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardValidityPeriod_t : public IParser
{
public:
    CPUCardValidityPeriod_t() {}
    ~CPUCardValidityPeriod_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    std::string    OldValidDate;
    std::string    NewValidDate;
    int            TransactionValue;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardBlock_t : public IParser
{
public:
    CPUCardBlock_t() {}
    ~CPUCardBlock_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  BlockReasonCode;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardUnblock_t : public IParser
{
public:
    CPUCardUnblock_t() {}
    ~CPUCardUnblock_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  UnblockReasonCode;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class TicketSurcharge_t : public IParser
{
public:
    TicketSurcharge_t() {}
    ~TicketSurcharge_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  SurchargeCode;
    unsigned char  Paymentmeans;
    unsigned char  TransStatusBeforeTrans;
    unsigned char  TransStatusAfterTrans;
    std::string    SaleDeviceID;
    int            TicketSaleValue;
    unsigned char  SurchargeArea;
    int            TransactionValue;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class TicketExit_t : public IParser
{
public:
    TicketExit_t() {}
    ~TicketExit_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned int   EntryDeviceID;
    std::string    EntryTimeHi;
    std::string    EntryTimeLo;
    unsigned char  TransStatusBeforeTrans;
    unsigned char  TransStatusAfterTrans;
    int            RemainingValueBeforeTrans;
    int            RemainingValueAfterTrans;
    int            TransactionValue;
    int            OriginalValue;
    unsigned char  SJTRecycleFlag;
    unsigned char  DeduceLocation;
    std::string    TerminateNumber;
    unsigned int   SAMSN;
};

class RebateScheme_t : public IParser
{
public:
    RebateScheme_t() {}
    ~RebateScheme_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  JoinConcessionID;
    unsigned char  JoinConcessionType;
    int            JoinConcessionValue;
    unsigned char  JoinConcessionPercentage;
    unsigned int   PileConcessionID;
    int            CurrentBonus;
    int            AccumulationBonus;
};

class CPUCardDeduction_t : public IParser
{
public:
    CPUCardDeduction_t() {}
    ~CPUCardDeduction_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    int            TransactionValue;
    std::string    OperatorID;
    std::string    BOMShiftID;
};

class CPUCardSpecialPurseSale_t : public IParser
{
public:
    CPUCardSpecialPurseSale_t() {}
    ~CPUCardSpecialPurseSale_t() {}

public:
    virtual unsigned int parse(const char *data) override;
    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) override;

private:
    unsigned char  SalePaymentmeans;
    int            SaleTransactionValue;
    unsigned char  SaleTransactionStatus;
    unsigned char  SalePurseType;
    unsigned char  SaleStageID;
    std::string    SaleValidStartDate;
    std::string    SaleValidEndDate;
    unsigned char  SaleSectionID;
    std::string    SaleOperatorID;
    std::string    SaleBOMShiftID;
};

#endif // MODEL_H
