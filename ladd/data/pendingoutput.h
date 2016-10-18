#ifndef PENDINGOUTPUT_H
#define PENDINGOUTPUT_H

#include <QTime>

#include "output.h"
class PendingOutput : public Output
{
public:
    PendingOutput();

    bool isPending() const;

    int m_timeToWait; //msecs

    int timeToWait() const;
    void setTimeToWait(int timeToWait);
    void reduceTimeToWait(int timeWaited);
};

#endif // PENDINGOUTPUT_H
