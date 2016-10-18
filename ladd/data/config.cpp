#include "config.h"

#include "ladder/ladderentities.h"

Config Config::s_instance = Config();
const int Config::s_invalidInt = -1;

Config::Config()
{
}

Config &Config::getInstance()
{
    return s_instance;
}

QMap<int, int> Config::timerIdToMsecs(CommunicationType type) const
{
    return type == CommunicationType::Parallel
            ? m_parallelTimerIdToMsecs
            : m_serialTimerIdToMsecs;
}

void Config::setTimerIdToMsecs(const QMap<int, int> &timerIdToMsecs, CommunicationType type)
{
    if(type == CommunicationType::Parallel)
    {
        m_parallelTimerIdToMsecs = timerIdToMsecs;
    }
    else
    {
        m_serialTimerIdToMsecs = timerIdToMsecs;
    }
}

int Config::timerIntervalForId(const int timerId, CommunicationType type) const
{
    return type == CommunicationType::Parallel
            ? m_parallelTimerIdToMsecs.value(timerId, LadderEntities::s_invalidTime)
            : m_serialTimerIdToMsecs.value(timerId, LadderEntities::s_invalidTime);
}

QMap<int, InputInfo> Config::inputBitNumberToInputInfo(Config::CommunicationType type) const
{
    return type == CommunicationType::Parallel
            ? m_parallelInputBitNumberToInputInfo
            : m_serialInputBitNumberToInputInfo;
}

void Config::setInputBitNumberToInputInfo(const QMap<int, InputInfo> &inputBitNumberToInputInfo, CommunicationType type)
{
    if(type == CommunicationType::Parallel)
    {
        m_parallelInputBitNumberToInputInfo = inputBitNumberToInputInfo;
    }
    else
    {
        m_serialInputBitNumberToInputInfo = inputBitNumberToInputInfo;
    }
}

QMap<int, int> Config::outputIdToBitNumber(Config::CommunicationType type) const
{
    return type == CommunicationType::Parallel
            ? m_parallelOutputIdToBitNumber
            : m_serialOutputIdToBitNumber;
}

void Config::setOutputIdToBitNumber(const QMap<int, int> &outputIdToBitNumber, CommunicationType type)
{
    if(type == CommunicationType::Parallel)
    {
        m_parallelOutputIdToBitNumber = outputIdToBitNumber;
    }
    else
    {
        m_serialOutputIdToBitNumber = outputIdToBitNumber;
    }
}
