#include "fileparser.h"

#include "../data/config.h"

const int FileParser::s_numberPartsTmrId = 1;
const int FileParser::s_numberPartsLaddId = 2;

const QString FileParser::s_idSeparator = ".";


FileParser::FileParser()
{

}


int FileParser::idToInt(const QString &branchString)
{
    int result;
    QStringList idParts = branchString.split(FileParser::s_idSeparator);
    const int size = idParts.size();
    QString firstPart = idParts.takeAt(0);
    bool ok = false;
    result = firstPart.toInt(&ok);
    if(!ok)
    {
        return Config::s_invalidInt;
    }

    if(size == s_numberPartsTmrId)
    {
        return result;
    }

    if(size == s_numberPartsLaddId)
    {
        result *= 8;
        QString secondPart = idParts.takeAt(0);
        int secondInt = secondPart.toInt(&ok);
        if(!ok)
        {
            return Config::s_invalidInt;
        }

        result += secondInt;

        return result;
    }

    return Config::s_invalidInt;
}
