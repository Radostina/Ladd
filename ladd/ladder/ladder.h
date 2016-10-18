#ifndef LADDER_H
#define LADDER_H

#include <QList>
#include <QPair>
#include <QString>

#include "branch.h"
#include "data/input.h"
#include "data/output.h"
#include "data/pendingoutput.h"

class Ladder
{
public:
    Ladder();

    bool isEmpty();

    QList<PendingOutput> treatInputs(QMap<int, bool>& inputs);

    QList<Branch> branches() const;
    void setBranches(const QList<Branch> &branches);
    void addBranch(const Branch branch);

private:
    QList<Branch> m_branches;
};

#endif // LADDER_H
