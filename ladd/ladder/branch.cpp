#include "branch.h"

#include <QTime>

#include "ladderentities.h"
#include "../data/config.h"

const bool Branch::s_defaultInputValue = false;

Branch::Branch()
{

}

bool Branch::isEmpty()
{
    return m_ladderSequence.isEmpty();
}

QList<PendingOutput> Branch::treatInputs(QMap<int, bool> &inputs) const
{
    QList<PendingOutput> result;
    QList<bool> passedValues;

    PendingOutput finalOutput;

    QList<int>::const_iterator iter;
    for(iter = m_ladderSequence.constBegin();
        iter != m_ladderSequence.end();
        iter++)
    {
        if(*iter >= 0)
        {
            if(!inputs.contains(*iter))
            {
                return result;
            }

            passedValues.append(inputs.value(*iter, s_defaultInputValue));
            continue;
        }


        switch (*iter)
        {
        case LadderEntities::Operation::Write :
        case LadderEntities::Operation::WriteNot:
        {
            bool outputValue;
            if(passedValues.size() != 1)
            {
                return result;
            }

            outputValue = passedValues.first();
            if(*iter == LadderEntities::Operation::WriteNot)
            {
                outputValue = !outputValue;
            }

            finalOutput.setIsActive(outputValue);
            iter++;
            if(iter != m_ladderSequence.end())
            {
                finalOutput.setId(*iter);
            }

            result.append(finalOutput);
            break;
        }
        case LadderEntities::Operation::ReadNotStack:
        {
            int size = passedValues.size();
            int lastValuePos = size-1;
            passedValues[lastValuePos] = !passedValues.last();
            break;
        }
        case LadderEntities::Operation::Timer:
        {
            iter++;

            if(iter != m_ladderSequence.end())
            {
                // TODO communication type
                int milisecsToWait = Config::getInstance().timerIntervalForId(*iter, Config::Parallel);
                if(milisecsToWait == LadderEntities::s_invalidTime)
                {
                    continue;
                }

                finalOutput.setTimeToWait(milisecsToWait);
            }

            break;
        }
        case LadderEntities::Operation::And:
        case LadderEntities::Operation::AndStack:
        case LadderEntities::Operation::AndNot:
        {
            if(passedValues.size() < 2)
            {
                return result;
            }

            bool lastValue = (*iter == LadderEntities::Operation::AndNot)
                    ? ! passedValues.takeLast()
                    : passedValues.takeLast();
            bool beforeLastValue = passedValues.takeLast();

            bool resultValue = (lastValue && beforeLastValue);
            passedValues.append(resultValue);
            break;
        }
        case LadderEntities::Operation::Or:
        case LadderEntities::Operation::OrNot:
        case LadderEntities::Operation::OrStack:
        {
            if(passedValues.size() < 2)
            {
                return result;
            }

            bool lastValue = (*iter == LadderEntities::Operation::OrNot)
                    ? ! passedValues.takeLast()
                    : passedValues.takeLast();
            bool beforeLastValue = passedValues.takeLast();

            bool resultValue = (lastValue || beforeLastValue);
            passedValues.append(resultValue);
            break;
        }
        default:
            break;
        }
    }

    return result;
}

QList<int> Branch::getLadderSequence() const
{
    return m_ladderSequence;
}

void Branch::setLadderSequence(const QList<int> &value)
{
    m_ladderSequence = value;
}

void Branch::addLadderSequence(int value)
{
    m_ladderSequence.append(value);
}

