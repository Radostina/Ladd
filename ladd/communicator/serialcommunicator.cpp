#include "serialcommunicator.h"

#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

const char SerialCommunicator::s_address = 1;
const char SerialCommunicator::s_commandRead = 3;
const char SerialCommunicator::s_commandWrtie = 6;
const char SerialCommunicator::s_check = 255;
const int SerialCommunicator::s_commandReadLength = 3;
const int SerialCommunicator::s_commandWrtieLength = 5;
const int SerialCommunicator::s_readDataPosition1 = 2;
const int SerialCommunicator::s_readDataPosition2 = 3;

SerialCommunicator::SerialCommunicator(QObject *parent)
    : BaseCommunicator(parent)
    , m_isReadingSession(false)
    , m_isWrittingSession(false)
{
    connect(&m_serialPort, SIGNAL(readyRead()),this, SLOT(readData()));
    setCommunicationType(Config::CommunicationType::Serial);
    fillPortsParameters();
}

void SerialCommunicator::initiateCommunication()
{
    qDebug() << currentSettings.name;
    qDebug() << currentSettings.baudRate;
    qDebug() << currentSettings.dataBits;
    qDebug() << currentSettings.parity;
    qDebug() << currentSettings.stopBits;
    qDebug() << currentSettings.flowControl;

    m_serialPort.setPortName(currentSettings.name);
    m_serialPort.setBaudRate(currentSettings.baudRate);
    m_serialPort.setDataBits(currentSettings.dataBits);
    m_serialPort.setParity(currentSettings.parity);
    m_serialPort.setStopBits(currentSettings.stopBits);
    m_serialPort.setFlowControl(currentSettings.flowControl);
    if (!m_serialPort.open(QIODevice::ReadWrite))
    {
        qDebug() << "Could not open port";
    }
}

QMap<int, bool> SerialCommunicator::readInputs()
{
    QByteArray readCommand;
    readCommand.append(s_address);
    readCommand.append(s_commandRead);
    readCommand.append(s_check);

    readCommand.resize(s_commandReadLength);

    m_isReadingSession = true;
    m_serialPort.write(readCommand);

    return QMap<int, bool>();
}

void SerialCommunicator::writeOutputs(QList<Output> outputs)
{
    m_dataToWrite = outputsToChar(outputs);
    writeData();
}

void SerialCommunicator::stopCommunication()
{
    if(m_serialPort.isOpen())
    {
        m_serialPort.close();
    }
}

void SerialCommunicator::writeData()
{
    QByteArray writeCommand;
    writeCommand.append(s_address);
    writeCommand.append(s_commandWrtie);
    writeCommand.append(m_dataToWrite);
    writeCommand.append(m_dataToWrite);
    writeCommand.append(s_check);

    writeCommand.resize(s_commandWrtieLength);

    m_isWrittingSession = true;
    m_serialPort.write(writeCommand);
}



void SerialCommunicator::readData()
{
    if(!m_isReadingSession
        && !m_isWrittingSession)
    {
        return;
    }

    QByteArray data = m_serialPort.readAll();

    int size = data.size();

    if((size % s_commandWrtieLength) != 0)
    {
        //resendLastCommand();
        return;
    }


    if(size > s_commandWrtieLength)
    {
        for(int i = size/s_commandWrtieLength; i > 0; i--)
        {
            QByteArray last = data.right(s_commandWrtieLength);
            handleData(last);
            data.chop(s_commandWrtieLength);
        }
    }
    else
    {
        handleData(data);
    }
}

void SerialCommunicator::handleData(const QByteArray &data)
{
    char dataReceived = data.at(s_readDataPosition1);
    if(dataReceived != data.at(s_readDataPosition2))
    {
        //resendLastCommand();
    }

    if(m_isWrittingSession
            && (dataReceived != m_dataToWrite) )
    {
        //resendLastCommand();
        //return;
    }

    if(m_isReadingSession)
    {
        emit inputsRead(charToInputs(dataReceived));
        m_isReadingSession = false;
        return;
    }

    m_isWrittingSession = false;
}

void SerialCommunicator::fillPortsParameters()
{
    currentSettings.name =
            QSerialPortInfo::availablePorts().first().portName(); // could be another one, not the first
    currentSettings.baudRate = QSerialPort::Baud9600;
    currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);

    currentSettings.dataBits = QSerialPort::Data8;

    currentSettings.parity = QSerialPort::NoParity;

    currentSettings.stopBits = QSerialPort::OneStop;
    currentSettings.flowControl = QSerialPort::NoFlowControl;
    currentSettings.stringFlowControl = "None";

    currentSettings.localEchoEnabled = true;
}

void SerialCommunicator::resendLastCommand()
{
    qDebug() << "resendLastCommand();";
    if(m_isWrittingSession)
    {
        writeData();
    }
    if(m_isReadingSession)
    {
        readInputs();
    }
}

