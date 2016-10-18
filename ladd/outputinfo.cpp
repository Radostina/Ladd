#include "outputinfo.h"

OutputInfo::OutputInfo()
{

}

int OutputInfo::getId() const
{
    return id;
}

void OutputInfo::setId(int value)
{
    id = value;
}

int OutputInfo::getBitNumber() const
{
    return bitNumber;
}

void OutputInfo::setBitNumber(int value)
{
    bitNumber = value;
}
