#ifndef BRANCH_H
#define BRANCH_H

#include <QList>
#include <QMap>

#include "data/input.h"
#include "data/output.h"
#include "data/pendingoutput.h"

class Branch
{
public:
    Branch();

    bool isEmpty();
    QList<PendingOutput> treatInputs(QMap<int, bool>& inputs) const;

    QList<int> getLadderSequence() const;
    void setLadderSequence(const QList<int> &value);
    void addLadderSequence(int value);

private:
    QList<int> m_ladderSequence;

private:
    static const bool s_defaultInputValue;
};

#endif // BRANCH_H
