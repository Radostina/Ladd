#include "ladderentities.h"
#include "sys/io.h"
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QMap>

const int LadderEntities::s_invalidTime = -1;

LadderEntities::LadderEntities()
{

}


const LadderEntities::Operation LadderEntities::s_invalidOperation = LadderEntities::Operation::Invalid;

