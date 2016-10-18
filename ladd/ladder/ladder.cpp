#include "ladder.h"

Ladder::Ladder()
{

}

bool Ladder::isEmpty()
{
    return m_branches.isEmpty();
}

QList<PendingOutput> Ladder::treatInputs(QMap<int, bool> &inputs)
{
    QList<PendingOutput> result;
    for(const Branch& branch : m_branches)
    {
        result.append(branch.treatInputs(inputs));
    }

    return result;
}

QList<Branch> Ladder::branches() const
{
    return m_branches;
}

void Ladder::setBranches(const QList<Branch> &branches)
{
    m_branches = branches;
}

void Ladder::addBranch(const Branch branch)
{
    m_branches.append(branch);
}
