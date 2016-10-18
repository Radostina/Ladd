#ifndef COMMUNICATIONCONTROLLER_H
#define COMMUNICATIONCONTROLLER_H

#include <QMap>
#include <QTimer>

#include "communicator/basecommunicator.h"
#include "data/config.h"
#include "data/pendingoutput.h"
#include "ladder/ladder.h"


class CommunicationController : public QObject
{
    Q_OBJECT

public:
    CommunicationController(QObject *parent = 0);
    ~CommunicationController();


    void readInputs();


    Ladder ladder() const;
    void setLadder(const Ladder &ladder);

    static int getInterruptInterval();
    static void setInterruptInterval(int value);

    QList<PendingOutput> getPendingOutputs() const;
    void setPendingOutputs(const QList<PendingOutput> &pendingOutputs);
    void addPendingOutputs(const QList<PendingOutput> &pendingOutputs);

public slots:
    void onInputsRead(QMap<int, bool> inputs);
    void setupCommunication(Config::CommunicationType type);
    void startCommunication();

private:
    void setupTimerInterval();
    void sendPendingOutputs();

    void stopCommunication();
    void stopAndDeleteTimer();
    void stopAndDeleteCommunicator();

private slots:
    void  onInterrupt();

private:
    static int s_interruptInterval;

    QList<PendingOutput> m_pendingOutputs;
    QTimer* m_timer;
    Ladder m_ladder;
    BaseCommunicator* m_baseCommunicator;

};

#endif // COMMUNICATIONCONTROLLER_H
