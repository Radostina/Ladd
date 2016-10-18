#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "data/config.h"

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    enum FileType
    {
        FileConfig,
        FileLadder
    };

public:
    explicit SettingsPage(QWidget* parent = nullptr);

    QComboBox *cmmunicationTypeSelector() const;
    void setCmmunicationTypeSelector(QComboBox *cmmunicationTypeSelector);

    void setConfFilePathText(const QString& filePath);
    void setLaddFilePathText(const QString& filePath);
    void setErrorLabelText(const QString& errorText);

signals:
    void fileLoaded(const QString filePath, SettingsPage::FileType fileType);
    void communicationChanged(Config::CommunicationType);
    void startCommunication();
protected:
    void showEvent(QShowEvent *);
private slots:
    void loadNewConfigurationFile();
    void loadNewLadderFile();
    void onCommunicationTypeChanged(int index);
    void onCommunicationStartRequested();

private:
    void loadNewFile(FileType fileType);

private:
    QPushButton* m_loadConfigButton;
    QPushButton* m_loadLadderButton;

    QLabel* m_configFilePathLabel;
    QLabel* m_laddFilePathLabel;


    QComboBox* m_communicationTypeSelector;
    QPushButton* m_startCommunicationButton;

    QLabel* m_errorLabel;
};

#endif // SETTINGSPAGE_H
