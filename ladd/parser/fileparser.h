#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QFile>
class FileParser
{
public:
    FileParser();

    static int idToInt(const QString& branchString);

    static const int s_numberPartsTmrId;
    static const int s_numberPartsLaddId;

    static const QString s_idSeparator;
};

//TODO maybe remove

#endif // FILEPARSER_H
