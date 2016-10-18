#ifndef LADDERPARSER_H
#define LADDERPARSER_H

#include "../ladder/branch.h"
#include "../ladder/ladder.h"
#include "../ladder/ladderentities.h"

#include "fileparser.h"

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>
class LadderParser : public FileParser
{
public:
    LadderParser();

    static const QString s_readTag;
    static const QString s_readNotTag;
    static const QString s_writeTag;
    static const QString s_writeNotTag;
    static const QString s_andTag;
    static const QString s_andNotTag;
    static const QString s_orTag;
    static const QString s_orNotTag;
    static const QString s_readStackTag;
    static const QString s_readNotStackTag;
    static const QString s_andStackTag;
    static const QString s_orStackTag;
    static const QString s_timerTag;

    static const QString s_commentSymbol;

public:
    static Ladder parseLadder(const QString& filePath);
    static Branch readBranch(QFile &file);

private:
    static QMap<QString, LadderEntities::Operation> operationsMap();
};

#endif // LADDERPARSER_H
