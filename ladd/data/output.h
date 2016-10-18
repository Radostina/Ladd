#ifndef OUTPUT_H
#define OUTPUT_H

#include <QString>

#include "outputinfo.h"

class Output
{
public:
    Output();

    bool isActive() const;
    void setIsActive(bool isActive);

    int id() const;
    void setId(int id);

private:
    int m_id;
    bool m_isActive;
};

#endif // OUTPUT_H
