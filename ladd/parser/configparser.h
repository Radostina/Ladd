#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QXmlStreamReader>
#include <QMap>
#include <QPair>

#include "fileparser.h"
#include "../data/config.h"

class ConfigParser : public FileParser
{
public:
    static const QString s_configTag;
    static const QString s_parportTag;
    static const QString s_serialTag;
    static const QString s_inputsTag;
    static const QString s_inputTag;
    static const QString s_idTag;
    static const QString s_bitNumbTag;
    static const QString s_initialValueTag;
    static const QString s_outputsTag;
    static const QString s_outputTag;
    static const QString s_timersTag;
    static const QString s_timerTag;
    static const QString s_msecsTag;
public:
    ConfigParser();
    static Config parseConfig(const QString& filePath);
private:
    static void parseConfig(QXmlStreamReader* const xmlReader,Config& config, Config::CommunicationType type);
    static QMap<int, int>       parseOutputs(QXmlStreamReader* const xmlReader);
    static QMap<int, InputInfo> parseInputs(QXmlStreamReader* const xmlReader);
    static QMap<int, int>       parseTimers(QXmlStreamReader* const xmlReader);
    static QPair<int, int>       parseOutput(QXmlStreamReader* const xmlReader);
    static QPair<int, InputInfo> parseInput(QXmlStreamReader* const xmlReader);
    static QPair<int, int>       parseTimer(QXmlStreamReader* const xmlReader);
    static QMap<QString, Config::CommunicationType> tagToCommunicationType();
};

#endif // CONFIGPARSER_H
