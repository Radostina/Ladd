#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include "basecommunicator.h"
#include "QtSerialPort/QSerialPort"

class SerialCommunicator : public BaseCommunicator
{

    Q_OBJECT

public:
    SerialCommunicator(QObject *parent = 0);

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    // BaseCommunicator interface
public:
    void initiateCommunication();
    QMap<int, bool> readInputs();
    void writeOutputs(QList<Output> outputs);
    void stopCommunication();

    void writeData();

public slots:
    void readData();
    void handleData(const QByteArray& data);

private:
    void fillPortsParameters();
    void resendLastCommand();

private:
    Settings currentSettings;
    QSerialPort m_serialPort;
    bool m_isReadingSession;
    bool m_isWrittingSession;

    char m_dataToWrite;

    static const char s_address;
    static const char s_commandWrtie;
    static const char s_commandRead;
    static const char s_check;
    static const int s_commandReadLength;
    static const int s_commandWrtieLength;
    static const int s_readDataPosition1;
    static const int s_readDataPosition2;

};

#endif // SERIALCOMMUNICATOR_H
