#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
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
//    int err = CalcLib::Ok;
//    double x = DoIt(CalcLib::Addition, 2, 3, err);
    QGuiApplication app(argc, argv);
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
//	qmlRegisterType<SortedQuestsModel>("ubego.models", 1, 0, "SortedQuestsModel");
//    qmlRegisterType<CouponService>("ubego.services", 1, 0, "CouponService");

//    qmlRegisterUncreatableType<UGlobal>("ubego.global", 1, 0, "UGlobal", "Not creatable");
//    qmlRegisterUncreatableType<QuestTasksModelRoles>("ubego.questTasksModelRoles", 1, 0, "QuestTasksModelRoles", "Not creatable");
//    qmlRegisterUncreatableType<QuestRoles>("ubego.questRoles", 1, 0, "QuestRoles", "Not creatable");
//    qmlRegisterUncreatableType<TinkoffPurchaseService>("ubego.errorCodes", 1, 0, "ErrorCodes", "Not creatable"); // we need this to access to error codes
//    qmlRegisterUncreatableType<ImageCacher>("ubego.imageProviderUtils", 1, 0, "ImageCacher", "Not creatable");

//    qRegisterMetaType<UGlobal::States>("States"); // Quest's Stats
//    qRegisterMetaType<CalcLib::TypeWork>("CalcLib::TypeWork");
//    qRegisterMetaType<CalcLib::ErrorCode>("CalcLib::ErrorCode");
//    qRegisterMetaType<CalcLib::TypeWork>("TypeWork");
//    qRegisterMetaType<CalcLib::ErrorCode>("ErrorCode");
    qRegisterMetaType<Result>("Result");
    qRegisterMetaType<Task>("Task");

}

#define inject(context, var) context->setContextProperty(#var, var)
inline void configureAndInjectProperties(QQmlApplicationEngine & engine) {
    auto * root = engine.rootContext();
    root->setContextProperty("settingsManager", SettingsManager::instance());
    root->setContextProperty("journalModel", new JournalModel);
//    QImageProvider * imageProvider = new QImageProvider();
//    engine.addImageProvider(QStringLiteral("imageProvider"), imageProvider);

//    // worker is a independant operational unit with internal state
//    // service is a worker without internal state for remote tasks

//    //ReportSender * reportSender = new ReportSender(root);

//    //auto * authRemoteWorker = AuthRemoteWorker::instance();//new AuthRemoteWorker(root);
//    auto * authService = new AuthService(root);
//    authService->setToken(StorageWorker::instance()->getToken());
//    QObject::connect(authService, &AuthService::tokenChanged, StorageWorker::instance(), &StorageWorker::setToken);

//	auto * questsModel = new QuestsModel(root);
//    auto * profileModel = new ProfileModel(imageProvider, root);
//    auto * profileService = new ProfileService(profileModel, root); //TODO Incapsulate into profileModel


//    auto * questsService = new QuestsService(questsModel, root);
//    //auto * purchaseService = new FakePurchaseService(authauthRemoteWorker, socketWorker, root);//new TinkoffPurchaseService(profileModel, authauthRemoteWorker, socketWorker, root);
//    auto * purchaseService = new TinkoffPurchaseService(profileModel, root);//new TinkoffPurchaseService(profileModel, authauthRemoteWorker, socketWorker, root);

//    //auto * sessionWorker = new SessionWorker(root); //

//    //auto * gameService = new SimpleGameService(sessionWorker, root);
//    auto * gameEngine = new GameEngine(questsService, /*purchaseService,*/ root);
//    //inject(root, reportSender);
//    root->setContextProperty("sm", UStateMachine::instance());
//    root->setContextProperty("authRemoteWorker", AuthRemoteWorker::instance());
//    //inject(root, AuthRemoteWorker::instance()); // it is needed to find if worker is busy. Need to move it to separate Helper which designates if app is busy.
//	inject(root, questsModel);
//	inject(root, profileModel);
//    inject(root, profileService);
//	inject(root, authService);
//	inject(root, questsService);
//	inject(root, purchaseService);
//    inject(root, gameEngine);

//    root->setContextProperty("uhelper", QVariant::fromValue(new UHelper()));
//    root->setContextProperty("viewConfig", QVariant::fromValue(ViewConfig())); // Careful. it is QGadged and when requested in QML is copied
//    root->setContextProperty("permissionManager", QVariant::fromValue(SystemPermissionManager())); // Careful. it is QGadged and when requested in QML is copied
//    //root->setContextProperty("dbpath", QVariant::fromValue(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)));
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
