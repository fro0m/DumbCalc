#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QObject>
#include <QSettings>
#include <QScreen>
#include <QGuiApplication>

class SettingsManager : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(float windowX READ windowX WRITE setWindowX NOTIFY windowXChanged)
    //Q_PROPERTY(float windowY READ windowY WRITE setWindowY NOTIFY windowYChanged)
    Q_PROPERTY(QRect windowRect READ windowRect WRITE setWindowRect)
public:
    static SettingsManager *instance();
public:
    QRect windowRect() const;
    Q_INVOKABLE void clearSettings() const {
        QSettings settings;
        settings.clear();
    }

private:
    explicit SettingsManager(QObject *parent = nullptr);

signals:

//void windowRectChanged(QRect windowRect);


public slots:
void setWindowRect(QRect windowRect)
{
    QSettings settings;
    settings.setValue("x", QVariant(windowRect.x()));
    settings.setValue("y", QVariant(windowRect.y()));
    settings.setValue("width", QVariant(windowRect.width()));
    settings.setValue("height", QVariant(windowRect.height()));
    //emit windowRectChanged(m_windowRect);
}
};

#endif // SETTINGSMANAGER_H
