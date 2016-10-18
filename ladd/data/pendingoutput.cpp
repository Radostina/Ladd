#include "pendingoutput.h"

#include <QDebug>
#include <QTime>

#include "../ladder/ladderentities.h"

PendingOutput::PendingOutput()
{

}

bool PendingOutput::isPending() const
{
    qDebug() << m_timeToWait;
    return m_timeToWait > 0;
}

int PendingOutput::timeToWait() const
{
    return m_timeToWait;
}

void PendingOutput::setTimeToWait(int timeToWait)
{
    m_timeToWait = timeToWait;
}

void PendingOutput::reduceTimeToWait(int timeWaited)
{
    m_timeToWait -= timeWaited;
}

