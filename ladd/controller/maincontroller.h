#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H


#include <QHash>
#include <QList>
#include <QObject>
#include <QString>

#include "settingspage.h"
#include "communicationcontroller.h"

class MainController : public QObject
{

    Q_OBJECT

public:
    MainController(QObject *parent = 0);

    ~MainController();

    void init();

    SettingsPage *settingsPage() const;
    void setSettingsPage(SettingsPage* mainPage);

public slots:
    void onFileLoaded(const QString filePath, SettingsPage::FileType fileType);

private:
    SettingsPage* m_settingsPage;
    CommunicationController* m_communicationController;
};

#endif // MAINCONTROLLER_H
