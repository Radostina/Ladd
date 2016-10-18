#ifndef LADDERENTITIES_H
#define LADDERENTITIES_H

#include <limits.h>
#include <QString>

class LadderEntities
{
public:
    LadderEntities();

public:

    static const int s_invalidTime;


    enum Operation
    {
        Read = INT_MIN,
        ReadNot,
        Write,
        WriteNot,
        And,
        AndNot,
        Or,
        OrNot,
        ReadStack,
        ReadNotStack,
        AndStack,
        OrStack,
        Timer,
        Invalid
    };

    static const Operation s_invalidOperation;


};

#endif // LADDERENTITIES_H
