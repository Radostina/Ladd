#include "settingspage.h"

#include <QFileDialog>
#include <QHBoxLayout>

#include "parser/ladderparser.h"
#include "parser/configparser.h"

SettingsPage::SettingsPage(QWidget* parent)
    : QWidget( parent )
    , m_loadConfigButton(nullptr)
    , m_loadLadderButton(nullptr)
    , m_configFilePathLabel(nullptr)
    , m_laddFilePathLabel(nullptr)
    , m_communicationTypeSelector(nullptr)
    , m_startCommunicationButton(nullptr)
    , m_errorLabel(nullptr)
{
    m_loadConfigButton = new QPushButton();
    m_loadConfigButton->setText("Select config file");
    connect(m_loadConfigButton, SIGNAL(clicked()), this, SLOT(loadNewConfigurationFile()));

    m_configFilePathLabel = new QLabel();
    m_laddFilePathLabel = new QLabel();

    m_loadLadderButton = new QPushButton();
    m_loadLadderButton->setText("Select ladder file");
    connect(m_loadLadderButton, SIGNAL(clicked()), this, SLOT(loadNewLadderFile()));

    m_communicationTypeSelector = new QComboBox();
    m_communicationTypeSelector->addItem("");
    m_communicationTypeSelector->addItem("Parallel Communication");
    m_communicationTypeSelector->addItem("Serial Communication");
    connect(m_communicationTypeSelector, SIGNAL(currentIndexChanged(int)),this,SLOT(onCommunicationTypeChanged(int)));

    m_startCommunicationButton = new QPushButton();
    m_startCommunicationButton->setText("Start");
    connect(m_startCommunicationButton, SIGNAL(clicked()), this, SLOT(onCommunicationStartRequested()));

    m_errorLabel = new QLabel();

    QVBoxLayout* const ladLayout = new QVBoxLayout();
    ladLayout->addWidget(m_loadLadderButton,1, Qt::AlignBottom);
    ladLayout->addWidget(m_laddFilePathLabel,1, Qt::AlignBottom);

    QVBoxLayout* const configLayout = new QVBoxLayout();
    configLayout->addWidget(m_loadConfigButton,1, Qt::AlignBottom);
    configLayout->addWidget(m_configFilePathLabel,1, Qt::AlignBottom);

    QHBoxLayout* const buttonsLayout = new QHBoxLayout();
    buttonsLayout->addLayout(ladLayout);
    buttonsLayout->addLayout(configLayout);

    QVBoxLayout* const mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(m_communicationTypeSelector,1, Qt::AlignBottom);
    mainLayout->addWidget(m_startCommunicationButton,1, Qt::AlignBottom);
    mainLayout->addWidget(m_errorLabel,1, Qt::AlignBottom);


}

void SettingsPage::loadNewFile(SettingsPage::FileType fileType)
{
    const QString filePath = QFileDialog::getOpenFileName(this,"Open");
    if(fileType == FileLadder)
    {
        m_laddFilePathLabel->setText(filePath);
    }
    else if(fileType == FileConfig)
    {
        m_configFilePathLabel->setText(filePath);
    }

    emit fileLoaded(filePath, fileType);
}

QComboBox *SettingsPage::cmmunicationTypeSelector() const
{

    return m_communicationTypeSelector;
}


void SettingsPage::setCmmunicationTypeSelector(QComboBox *cmmunicationTypeSelector)
{
    m_communicationTypeSelector = cmmunicationTypeSelector;
}

void SettingsPage::setConfFilePathText(const QString &filePath)
{
    m_configFilePathLabel->setText(filePath);
}

void SettingsPage::setLaddFilePathText(const QString &filePath)
{
    m_laddFilePathLabel->setText(filePath);
}

void SettingsPage::setErrorLabelText(const QString &errorText)
{
    m_errorLabel->setText(errorText);
    // TODO set Color red
}

void SettingsPage::showEvent(QShowEvent *)
{
    emit communicationChanged(Config::CommunicationType::Serial);
    emit fileLoaded("/home/radostina/Downloads/myLad.LAD", FileType::FileLadder);
    emit fileLoaded("/home/radostina/Downloads/config", FileType::FileConfig);
}

void SettingsPage::loadNewConfigurationFile()
{
    loadNewFile(SettingsPage::FileType::FileConfig);
}

void SettingsPage::loadNewLadderFile()
{
    loadNewFile(SettingsPage::FileType::FileLadder);
}

void SettingsPage::onCommunicationTypeChanged(int index)
{
    if(index == 1)
    {
        emit communicationChanged(Config::CommunicationType::Parallel);
    }
    else if(index == 2)
    {
        emit communicationChanged(Config::CommunicationType::Serial);
    }
}

void SettingsPage::onCommunicationStartRequested()
{
//    if(m_laddFilePathLabel->text().isEmpty()
//            || m_configFilePathLabel->text().isEmpty()
//            || m_communicationTypeSelector->currentIndex() == 0)
//    {
//        setErrorLabelText("Please select configuration and ladder file and a communication mode before starting");
//        return;
//    }

    setErrorLabelText(QString());
    emit startCommunication();
}
