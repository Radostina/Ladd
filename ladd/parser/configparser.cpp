#include "configparser.h"

const QString ConfigParser::s_configTag       = "config";
const QString ConfigParser::s_parportTag      = "parport";
const QString ConfigParser::s_serialTag      = "serial";
const QString ConfigParser::s_inputsTag       = "inputs";
const QString ConfigParser::s_inputTag        = "input";
const QString ConfigParser::s_idTag           = "id";
const QString ConfigParser::s_bitNumbTag          = "bitnumb";
const QString ConfigParser::s_initialValueTag = "initialValue";
const QString ConfigParser::s_outputsTag      = "outputs";
const QString ConfigParser::s_outputTag       = "output";
const QString ConfigParser::s_timersTag       = "timers";
const QString ConfigParser::s_timerTag        = "timer";
const QString ConfigParser::s_msecsTag        = "msecs";

ConfigParser::ConfigParser()
{

}

Config ConfigParser::parseConfig(const QString &filePath)
{
    Config& result = Config::getInstance();
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return result;
    }

    QXmlStreamReader* const xmlReader = new QXmlStreamReader(&file);
    QXmlStreamReader::TokenType tokenType;
    while(true){
        tokenType = xmlReader->readNext();
        if (tokenType == QXmlStreamReader::EndDocument
                || tokenType == QXmlStreamReader::Invalid)
        {
            break;
        }

        if (tokenType == QXmlStreamReader::StartElement)
        {
            const QString& tagName = xmlReader->name().toString();
            Config::CommunicationType type = ConfigParser::tagToCommunicationType().value(tagName, Config::CommunicationType::Invalid);
            ConfigParser::parseConfig(xmlReader, result, type);
        }
    }

    return result;

}

void ConfigParser::parseConfig(QXmlStreamReader * const xmlReader, Config &config, Config::CommunicationType type)
{
    if(type == Config::CommunicationType::Invalid)
    {
        return;
    }

    QXmlStreamReader::TokenType tokenType;
    while(true){
        tokenType = xmlReader->readNext();
        if (tokenType == QXmlStreamReader::EndDocument)
        {
            break;
        }

        if (tokenType == QXmlStreamReader::EndElement
                && xmlReader->name() == ConfigParser::tagToCommunicationType().key(type))
        {
            break;
        }

        if (tokenType == QXmlStreamReader::StartElement)
        {
            const QString& tagName = xmlReader->name().toString();
            if (tagName == s_inputsTag)
            {
                config.setInputBitNumberToInputInfo(
                            ConfigParser::parseInputs(xmlReader), type);

            }
            else if (tagName == s_outputsTag)
            {
                config.setOutputIdToBitNumber(
                            ConfigParser::parseOutputs(xmlReader), type);

            }
            else if (tagName == s_timersTag)
            {
                config.setTimerIdToMsecs(
                            ConfigParser::parseTimers(xmlReader), type);
            }
        }
    }
}

QMap<int, int> ConfigParser::parseOutputs(QXmlStreamReader * const xmlReader)
{
    QMap<int, int> result;
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_outputsTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_outputTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            QPair<int,int> output = parseOutput(xmlReader);

            if(output.first != Config::s_invalidInt
                    && output.second != Config::s_invalidInt)
            {
                result.insert(output.first, output.second);
            }
        }

        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_outputsTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}

QPair<int, int> ConfigParser::parseOutput(QXmlStreamReader * const xmlReader)
{
    QPair<int,int> result = qMakePair(Config::s_invalidInt, Config::s_invalidInt);
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_outputTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_idTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            int id = FileParser::idToInt(xmlReader->readElementText());
            result.first = id;
        }

        if(tagName == s_bitNumbTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            bool ok = false;
            int bitnumb = xmlReader->readElementText().toInt(&ok);
            if(ok)
            {
                result.second = bitnumb;
            }
        }


        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_outputTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}

QMap<int, InputInfo> ConfigParser::parseInputs(QXmlStreamReader * const xmlReader)
{
    QMap<int, InputInfo> result;
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_inputsTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_inputTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            QPair<int,InputInfo> input= parseInput(xmlReader);

            if(input.first != Config::s_invalidInt
                    && input.second.isValid())
            {
                result.insert(input.first, input.second);
            }
        }

        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_inputsTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}



QPair<int, InputInfo> ConfigParser::parseInput(QXmlStreamReader * const xmlReader)
{
    QPair<int,InputInfo> result = qMakePair(Config::s_invalidInt, InputInfo());
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_inputTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_idTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            int id = idToInt(xmlReader->readElementText());
            result.second.setId(id);
        }

        if(tagName == s_bitNumbTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            bool ok = false;
            int msecs = xmlReader->readElementText().toInt(&ok);
            if(ok)
            {
                result.first = msecs;
            }
        }

        if(tagName == s_initialValueTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            bool ok = false;
            int initialValue = xmlReader->readElementText().toInt(&ok);
            if(ok)
            {
                result.second.setInitialUnsetValue(initialValue == 1);
            }
        }


        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_inputTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}



QMap<int, int> ConfigParser::parseTimers(QXmlStreamReader * const xmlReader)
{
    QMap<int, int> result;
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_timersTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_timerTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            QPair<int,int> timerInfo = parseTimer(xmlReader);

            if(timerInfo.first != Config::s_invalidInt
                    && timerInfo.second != Config::s_invalidInt)
            {
                result.insert(timerInfo.first, timerInfo.second);
            }
        }

        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_timersTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}

QPair<int, int> ConfigParser::parseTimer(QXmlStreamReader * const xmlReader)
{
    QPair<int,int> result = qMakePair(Config::s_invalidInt, Config::s_invalidInt);
    QString tagName = xmlReader->name().toString();
    QXmlStreamReader::TokenType tokenType = xmlReader->tokenType();
    if(tagName != s_timerTag
            || tokenType != QXmlStreamReader::StartElement)
    {
        return result;
    }

    do
    {
        if(tagName == s_idTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            int id = idToInt(xmlReader->readElementText());
            result.first = id;
        }

        if(tagName == s_msecsTag
                && tokenType == QXmlStreamReader::StartElement)
        {
            bool ok = false;
            int msecs = xmlReader->readElementText().toInt(&ok);
            if(ok)
            {
                result.second = msecs;
            }
        }


        tokenType = xmlReader->readNext();
        tagName = xmlReader->name().toString();
    }

    while(tagName != s_timerTag
          || tokenType != QXmlStreamReader::EndElement);

    return result;
}

QMap<QString, Config::CommunicationType> ConfigParser::tagToCommunicationType()
{
    static QMap<QString, Config::CommunicationType> map =
            QMap<QString, Config::CommunicationType>(
    {
                    {s_parportTag, Config::CommunicationType::Parallel},
                    {s_serialTag, Config::CommunicationType::Serial}});

    return map;
}
