#include "settingsmanager.h"

SettingsManager *SettingsManager::instance() {
    static SettingsManager sm;
    return &sm;
}

QRect SettingsManager::windowRect() const
{
    QSettings settings;
    int x = settings.value("x", 0).toDouble();
    int y = settings.value("y", 0).toDouble();
    int width = settings.value("width", 0).toDouble();
    int height = settings.value("height", 0).toDouble();
    if (width == 0 || height == 0) {
        width = 600;
        height = 400; // make default
        //x = QGuiApplication::primaryScreen()->geometry().width() / 2 - width / 2;
    }
    return {x, y, width, height};
}

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{

}
