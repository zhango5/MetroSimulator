#ifndef IPARSER_H
#define IPARSER_H

#include "rapidjson/prettywriter.h"
#include <QSqlQuery>
#include <QObject>

class IParser
{
public:
    virtual unsigned int parse(const char* data) = 0;

    virtual void output(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) = 0;

    virtual void sqltransaction(QSqlQuery& query) = 0;
};

#endif // IPARSER_H
