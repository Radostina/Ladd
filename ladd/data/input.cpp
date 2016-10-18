#include "input.h"

#include "config.h"

Input::Input()
    : m_id(Config::s_invalidInt)
    , m_isActive(false)
{

}

int Input::id() const
{
    return m_id;
}

void Input::setId(int id)
{
    m_id = id;
}

bool Input::isActive() const
{
    return m_isActive;
}

void Input::setIsActive(bool isActive)
{
    m_isActive = isActive;
}
