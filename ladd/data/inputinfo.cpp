#include "inputinfo.h"

#include "config.h"

InputInfo::InputInfo()
    : id(Config::s_invalidInt)
    , bitNumber(Config::s_invalidInt)
    , initialUnsetValue(false)
{

}

bool InputInfo::isValid() const
{
    return (id != Config::s_invalidInt)
            /*&& (bitNumber != Config::s_invalidInt)*/;
}

int InputInfo::getId() const
{
    return id;
}

void InputInfo::setId(int value)
{
    id = value;
}

int InputInfo::getBitNumber() const
{
    return bitNumber;
}

void InputInfo::setBitNumber(int value)
{
    bitNumber = value;
}

bool InputInfo::getInitialUnsetValue() const
{
    return initialUnsetValue;
}

void InputInfo::setInitialUnsetValue(bool value)
{
    initialUnsetValue = value;
}
