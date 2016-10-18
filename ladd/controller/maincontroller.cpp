#include "maincontroller.h"

#include "parser/ladderparser.h"
#include "parser/configparser.h"

#include <QDebug>

MainController::MainController(QObject* parent)
    : QObject( parent )
    , m_settingsPage(nullptr)
{
    m_settingsPage = new SettingsPage();

    m_communicationController = new CommunicationController();
    connect(m_settingsPage,SIGNAL(fileLoaded(QString,SettingsPage::FileType)),this,SLOT(onFileLoaded(QString,SettingsPage::FileType)));
    connect(m_settingsPage,SIGNAL(communicationChanged(Config::CommunicationType)),m_communicationController,SLOT(setupCommunication(Config::CommunicationType)));
    connect(m_settingsPage,SIGNAL(startCommunication()),m_communicationController,SLOT(startCommunication()));
}

MainController::~MainController()
{

}

void MainController::init()
{
    m_settingsPage->show();
}


SettingsPage* MainController::settingsPage() const
{
    return m_settingsPage;
}

void MainController::setSettingsPage(SettingsPage* settingsPage)
{
    m_settingsPage = settingsPage;
}

void MainController::onFileLoaded(const QString filePath, SettingsPage::FileType fileType)
{
    if(fileType == SettingsPage::FileLadder)
    {
        Ladder ladder = LadderParser::parseLadder(filePath);
        m_communicationController->setLadder(ladder);
    }
    else if(fileType == SettingsPage::FileConfig)
    {
        ConfigParser::parseConfig(filePath);
    }
}
