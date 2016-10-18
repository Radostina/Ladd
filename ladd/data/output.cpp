#include "output.h"

#include "config.h"

Output::Output()
    : m_id(Config::s_invalidInt)
    , m_isActive(false)
{

}

bool Output::isActive() const
{
    return m_isActive;
}

void Output::setIsActive(bool isActive)
{
    m_isActive = isActive;
}

int Output::id() const
{
    return m_id;
}

void Output::setId(int id)
{
    m_id = id;
}
