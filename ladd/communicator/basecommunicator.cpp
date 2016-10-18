#include "basecommunicator.h"
#include <QMap>

BaseCommunicator::BaseCommunicator(QObject *parent)
    : QObject(parent)
{

}

bool BaseCommunicator::isBitSet(unsigned char x, int bitNumber)
{
    switch (bitNumber) {
    case 0:
        return (x & 0x01) != 0;
    case 1:
        return (x & 0x02) != 0;
    case 2:
        return (x & 0x04) != 0;
    case 3:
        return (x & 0x08) != 0;
    case 4:
        return (x & 0x10) != 0;
    case 5:
        return (x & 0x20) != 0;
    case 6:
        return (x & 0x40) != 0;
    case 7:
        return (x & 0x80) != 0;
    default:
        return false;
    }
}

void BaseCommunicator::setBitHigh(unsigned char& x, int bitNumber)
{
    switch (bitNumber) {
    case 0:
        x|=0x01;
        break;
    case 1:
        x|=0x02;
        break;
    case 2:
        x|=0x04;
        break;
    case 3:
        x|=0x08;
        break;
    case 4:
        x|=0x10;
        break;
    case 5:
        x|=0x20;
        break;
    case 6:
        x|=0x40;
        break;
    case 7:
        x|=0x80;
        break;
    default:
        break;
    }
}

void BaseCommunicator::setBitLow(unsigned char& x, int bitNumber)
{
    switch (bitNumber) {
    case 0:
        x&=0xFE;
        break;
    case 1:
        x&=0xFD;
        break;
    case 2:
        x&=0xFB;
        break;
    case 3:
        x&=0xF7;
        break;
    case 4:
        x&=0xEF;
        break;
    case 5:
        x&=0xDF;
        break;
    case 6:
        x&=0xBF;
        break;
    case 7:
        x&=0x7F;
        break;
    default:
        break;
    }
}

QMap<int, bool> BaseCommunicator::charToInputs(char x)
{
    QMap<int, bool> result;
    QMap<int, InputInfo> bitnumToInputInfos =
            Config::getInstance().inputBitNumberToInputInfo(m_communicationType);

    QMap<int, InputInfo>::iterator iter = bitnumToInputInfos.begin();
    for(;iter != bitnumToInputInfos.end(); iter++)
    {
        bool value = isBitSet(x,iter.key());
        InputInfo info = iter.value();
        result.insert(info.getId(), (value != info.getInitialUnsetValue()));
    }

    return result;
}

unsigned char BaseCommunicator::outputsToChar(QList<Output> outputs)
{
    unsigned char x = 0x0; // TODO are all low if no other info aailable?

    const QMap<int,int>& outputIdToBitNumber =  Config::getInstance().outputIdToBitNumber(m_communicationType);
    for( Output& output : outputs )
    {
        if(output.isActive())
        {
            setBitHigh(x,outputIdToBitNumber.value(output.id()));
        }
        else
        {
            setBitLow(x,outputIdToBitNumber.value(output.id()));
        }
    }

    return x;
}

Config::CommunicationType BaseCommunicator::getCommunicationType() const
{
    return m_communicationType;
}

void BaseCommunicator::setCommunicationType(const Config::CommunicationType &communicationType)
{
    m_communicationType = communicationType;
}
