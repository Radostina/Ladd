#include "ladderparser.h"

#include "../data/config.h"
#include "../ladder/ladderentities.h"

#include <QFile>
#include <QTextStream>



const QString LadderParser::s_readTag = "RD";
const QString LadderParser::s_readNotTag = "RD.NOT";
const QString LadderParser::s_writeTag = "WRT";
const QString LadderParser::s_writeNotTag = "WRT.NOT";
const QString LadderParser::s_andTag = "AND";
const QString LadderParser::s_andNotTag = "AND.NOT";
const QString LadderParser::s_orTag = "OR";
const QString LadderParser::s_orNotTag = "OR.NOT";
const QString LadderParser::s_readStackTag = "RD.STK";
const QString LadderParser::s_readNotStackTag = "RD.NOT.STK";
const QString LadderParser::s_andStackTag = "AND.STK";
const QString LadderParser::s_orStackTag = "OR.STK";
const QString LadderParser::s_timerTag = "TMR";

const QString LadderParser::s_commentSymbol = ";";


LadderParser::LadderParser()
{

}

Ladder LadderParser::parseLadder(const QString &filePath)
{
    Ladder ladder;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return ladder;
    }


    while(!file.atEnd())
    {

        Branch branch = readBranch(file);
        if(!branch.isEmpty())
        {
            ladder.addBranch(branch);
        }

        // TODO description display (alarm, overload, etc)
    }

    return ladder;
}

Branch LadderParser::readBranch(QFile &file)
{
    Branch branch;
    bool isBranchFinished = false;
    while(!file.atEnd())
    {
        QByteArray forwardpeek = file.peek(2);
        if(isBranchFinished
                && ( (QString(forwardpeek) == LadderParser::s_readTag)
                     || (QString(forwardpeek) == LadderParser::s_readNotTag) ))
        {
            return branch;
        }

        QString line(file.readLine());
        QString itemString = line.split(LadderParser::s_commentSymbol).takeFirst();
        if(itemString.isEmpty())
        {
            continue;
        }

        QStringList items = itemString.split(QRegExp("\\s"), QString::SkipEmptyParts);
        QMap<QString, LadderEntities::Operation> operationsTagMap = LadderParser::operationsMap();

        QStringList::iterator iter = items.begin();
        while(iter != items.end())
        {
            int value = operationsTagMap.value(*iter, LadderEntities::s_invalidOperation);
            if(value != LadderEntities::s_invalidOperation)
            {
                // operation Value
                if(value != LadderEntities::Operation::AndStack
                        && value != LadderEntities::Operation::OrStack)
                {
                    if(value == LadderEntities::Operation::Write
                            || value == LadderEntities::Operation::WriteNot
                            || value == LadderEntities::Operation::Timer)
                    {
                        isBranchFinished = true;
                        branch.addLadderSequence(value);
                    }

                    ++iter;
                    if(iter != items.end())
                    {
                        QString operandString = *iter;
                        int operand = FileParser::idToInt(operandString);
                        if (operand == Config::s_invalidInt)
                        {
                            ++iter;
                            continue;
                        }

                        branch.addLadderSequence(operand);
                    }
                    else
                    {
                        continue;
                    }
                }

                if (!isBranchFinished)
                {
                    branch.addLadderSequence(value);
                }

            }
            else
            {
                // operand Value
                value = FileParser::idToInt(*iter);
                if(value != Config::s_invalidInt)
                {
                    branch.addLadderSequence(value);
                }
            }

            ++iter;
        }
    }

    return branch;
}

QMap<QString, LadderEntities::Operation> LadderParser::operationsMap()
{
    QMap<QString, LadderEntities::Operation> result;
    result.insert(s_writeTag,        LadderEntities::Operation::Write );
    result.insert(s_writeNotTag,     LadderEntities::Operation::WriteNot);
    result.insert(s_andTag,          LadderEntities::Operation::And);
    result.insert(s_andNotTag,       LadderEntities::Operation::AndNot);
    result.insert(s_orTag,           LadderEntities::Operation::Or);
    result.insert(s_orNotTag,        LadderEntities::Operation::OrNot);
    result.insert(s_readNotStackTag, LadderEntities::Operation::ReadNotStack);
    result.insert(s_andStackTag,     LadderEntities::Operation::AndStack);
    result.insert(s_orStackTag,      LadderEntities::Operation::OrStack);
    result.insert(s_timerTag,        LadderEntities::Operation::Timer);
    return result;
//    result.insert(LadderEntities::s_readTag,         Operation::Read);
//    result.insert(LadderEntities::s_readNotTag,      Operation::ReadNot);
//    result.insert(LadderEntities::s_readStackTag,    Operation::ReadStack);
}


