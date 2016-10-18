#ifndef BASECOMMUNICATOR_H
#define BASECOMMUNICATOR_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QString>
#include <QTimer>

#include "data/config.h"
#include "data/input.h"
#include "data/output.h"
#include "ladder/ladder.h"

class BaseCommunicator : public QObject
{
    Q_OBJECT

public:
    BaseCommunicator(QObject *parent = 0);

    virtual void initiateCommunication() = 0;
    virtual void stopCommunication() = 0;
    virtual QMap<int, bool> readInputs() = 0;
    virtual void writeOutputs(QList<Output> outputs) = 0;

    static bool isBitSet(unsigned char x, int bitNumber);
    static void setBitHigh(unsigned char &x, int bitNumber);
    static void setBitLow(unsigned char &x, int bitNumber);

    QMap<int,bool> charToInputs(char x);
    unsigned char outputsToChar(QList<Output> outputs);

    Config::CommunicationType getCommunicationType() const;
    void setCommunicationType(const Config::CommunicationType &communicationType);

signals:
    void inputsRead(QMap<int, bool> inputs);

protected:
    Config::CommunicationType m_communicationType;
};

#endif // BASECOMMUNICATOR_H
