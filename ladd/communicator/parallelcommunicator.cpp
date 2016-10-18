#include "parallelcommunicator.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#include <QDebug>

#define base 0x378
ParallelCommunicator::ParallelCommunicator(QObject *parent)
    : BaseCommunicator(parent)
{
    setCommunicationType(Config::CommunicationType::Parallel);
}


void ParallelCommunicator::initiateCommunication()
{
    if (iopl(3)) //reserve 0x378, 0x379
        fprintf(stderr, "Couldn't get the port at %x\n", base), exit(1);
}

void ParallelCommunicator::stopCommunication()
{
    // TODO release parport
}

QMap<int, bool> ParallelCommunicator::readInputs()
{
    char b   = inb(base+1);
    QMap<int, bool> result = charToInputs(b);
    emit inputsRead(result);
    return result;
}

void ParallelCommunicator::writeOutputs(QList<Output> outputs)
{
    unsigned char x = outputsToChar(outputs);
    outb(x,base);
}
