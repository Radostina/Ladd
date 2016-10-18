#include "communicationcontroller.h"

#include <QMutableListIterator>

#include "communicator/parallelcommunicator.h"
#include "communicator/serialcommunicator.h"

int CommunicationController::s_interruptInterval = 50; // msecs

CommunicationController::CommunicationController(QObject *parent)
    : QObject(parent)
    , m_timer(nullptr)
    , m_baseCommunicator(nullptr)
{

}

CommunicationController::~CommunicationController()
{
    m_timer->stop();
    m_timer->deleteLater();
}

void CommunicationController::startCommunication()
{
    if(m_baseCommunicator == nullptr)
    {
        return;
    }

    m_baseCommunicator->initiateCommunication();
    connect(m_baseCommunicator,SIGNAL(inputsRead(QMap<int,bool>)),this,SLOT(onInputsRead(QMap<int,bool>)));

    if(m_timer != nullptr)
    {
        stopAndDeleteTimer();
    }

    m_timer = new QTimer();
    m_timer->setSingleShot(false);
    setupTimerInterval();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onInterrupt()));
    m_timer->start();
}

void CommunicationController::readInputs()
{
    m_baseCommunicator->readInputs();
}


int CommunicationController::getInterruptInterval()
{
    return s_interruptInterval;
}

void CommunicationController::setInterruptInterval(int value)
{
    s_interruptInterval = value;
}

void CommunicationController::onInterrupt()
{
    readInputs();
}

QList<PendingOutput> CommunicationController::getPendingOutputs() const
{
    return m_pendingOutputs;
}

void CommunicationController::setPendingOutputs(const QList<PendingOutput> &pendingOutputs)
{
    m_pendingOutputs = pendingOutputs;
}

void CommunicationController::addPendingOutputs(const QList<PendingOutput> &pendingOutputs)
{
    m_pendingOutputs.append(pendingOutputs);
}

void CommunicationController::onInputsRead(QMap<int, bool> inputs)
{
    QList<PendingOutput> outputs = ladder().treatInputs(inputs);
    m_pendingOutputs.append(outputs);
    sendPendingOutputs();
}

void CommunicationController::setupTimerInterval()
{
    if(m_timer != nullptr)
    {
        m_timer->setInterval(s_interruptInterval);
    }
}

void CommunicationController::sendPendingOutputs()
{
    QList<Output> outputsToSend;

    QMutableListIterator<PendingOutput> iter(m_pendingOutputs);
    while (iter.hasNext())
    {
        PendingOutput& value = iter.next();

        if (!value.isPending())
        {
            outputsToSend.append(value);
            iter.remove();
        }
        else
        {
            value.reduceTimeToWait(s_interruptInterval);
        }
    }

    m_baseCommunicator->writeOutputs(outputsToSend);
}

void CommunicationController::stopCommunication()
{
    stopAndDeleteTimer();
    stopAndDeleteCommunicator();
}

void CommunicationController::stopAndDeleteTimer()
{
    if(m_timer != nullptr)
    {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = nullptr;
    }
}

void CommunicationController::stopAndDeleteCommunicator()
{
    if(m_baseCommunicator != nullptr)
    {
        m_baseCommunicator->stopCommunication();
        m_baseCommunicator->deleteLater();
        m_baseCommunicator = nullptr;
    }
}

Ladder CommunicationController::ladder() const
{
    return m_ladder;
}

void CommunicationController::setLadder(const Ladder &ladder)
{
    m_ladder = ladder;
}

void CommunicationController::setupCommunication(Config::CommunicationType type)
{
    stopCommunication();

    if(type == Config::CommunicationType::Parallel)
    {
        m_baseCommunicator = new ParallelCommunicator();
    }
    else if(type == Config::CommunicationType::Serial)
    {
        m_baseCommunicator = new SerialCommunicator();
    }
}
