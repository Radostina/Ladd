#ifndef INPUT_H
#define INPUT_H

#include "inputinfo.h"

class Input
{
public:
    Input();

    int id() const;
    void setId(int id);

    bool isActive() const;
    void setIsActive(bool isActive);

private:
    int  m_id;
    bool m_isActive;
};

#endif // INPUT_H
