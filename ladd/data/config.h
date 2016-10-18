#ifndef CONFIG_H
#define CONFIG_H

#include <QList>
#include <QMap>

#include "inputinfo.h"
#include "outputinfo.h"
class Config
{

public:

    static const int s_invalidInt;
    enum CommunicationType
    {
        Serial,
        Parallel,
        Invalid
    };

public:
    static Config &getInstance();

    QMap<int, int> timerIdToMsecs(CommunicationType type) const;
    void setTimerIdToMsecs(const QMap<int, int> &timerIdToMsecs, CommunicationType type);
    int timerIntervalForId(const int timerId, CommunicationType type) const;

    QMap<int, InputInfo> inputBitNumberToInputInfo(CommunicationType type) const;
    void setInputBitNumberToInputInfo(const QMap<int, InputInfo> &inputBitNumberToInputInfo, CommunicationType type);

    QMap<int, int> outputIdToBitNumber(CommunicationType type) const;
    void setOutputIdToBitNumber(const QMap<int, int> &outputIdToBitNumber, CommunicationType type);
// TODO private:
    Config();
private:
    //    QList<InputInfo> m_inputs;
    //    QList<OutputInfo> m_outpust;
    QMap<int, int>       m_parallelTimerIdToMsecs;
    QMap<int, InputInfo> m_parallelInputBitNumberToInputInfo;
    QMap<int, int>       m_parallelOutputIdToBitNumber;

    QMap<int, int>       m_serialTimerIdToMsecs;
    QMap<int, InputInfo> m_serialInputBitNumberToInputInfo;
    QMap<int, int>       m_serialOutputIdToBitNumber;

    static Config s_instance;
};

#endif // CONFIG_H
