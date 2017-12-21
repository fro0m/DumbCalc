#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include "calclib/calclib.h"
#include "core/settingsmanager.h"
#include "Workers/calculatingthread.h"
#include "DataModels/journalmodel.h"
#include "DataTypes/task.h"
#include "DataTypes/result.h"
#include <QDebug>

inline void registerTypes();
inline void configureAndInjectProperties(QQmlApplicationEngine & engine);
inline void setUpAppInfo();

// metatypes
Q_DECLARE_METATYPE(CalcLib::TypeWork)
Q_DECLARE_METATYPE(CalcLib::ErrorCode)


int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    QGuiApplication::setFont(font);

    QQmlApplicationEngine engine;
    qDebug() << "GUI thread is " << QCoreApplication::instance()->thread();
    ::registerTypes();
    ::configureAndInjectProperties(engine);
    ::setUpAppInfo();
    CalculatingThread calculatingThread;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Q_ASSERT(!engine.rootObjects().isEmpty());
    return app.exec();
}

inline void registerTypes() {
    qRegisterMetaType<Result>("Result");
    qRegisterMetaType<Task>("Task");
    qRegisterMetaType<CalcLib::TypeWork>();
}

#define inject(context, var) context->setContextProperty(#var, var)
inline void configureAndInjectProperties(QQmlApplicationEngine & engine) {
    auto * root = engine.rootContext();
    root->setContextProperty("settingsManager", SettingsManager::instance());
    root->setContextProperty("journalModel", new JournalModel);
}
#undef inject

inline void setUpAppInfo() {
    //application's description
    QCoreApplication::setOrganizationName(QStringLiteral("STC"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("www.stc-spb.ru"));
    QCoreApplication::setApplicationName(QStringLiteral("DumbCalc"));
    QCoreApplication::setApplicationVersion(QStringLiteral("1.0.0"));
    /* app versioning
     * major.minor.fixes
     * major
     * 0 - pre MVP
     * 1 - stable conceptual 1
     * minor
     * 0 : inf - features
     * fixes
     * 0 : inf
     */
    //----------------------------------------
}
