#ifndef PARALLELCOMMUNICATOR_H
#define PARALLELCOMMUNICATOR_H

#include "basecommunicator.h"

class ParallelCommunicator : public BaseCommunicator
{

    Q_OBJECT

public:
    ParallelCommunicator(QObject *parent = 0);

    void initiateCommunication() Q_DECL_OVERRIDE;
    void stopCommunication() Q_DECL_OVERRIDE;
    QMap<int,bool> readInputs() Q_DECL_OVERRIDE;
    void writeOutputs(QList<Output> outputs) Q_DECL_OVERRIDE;

};

#endif // PARALLELCOMMUNICATOR_H
