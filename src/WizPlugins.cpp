#include "WizPlugins.h"
#include "sync/WizToken.h"
#include "WizMainWindow.h"
#include "share/WizGlobal.h"
#include "utils/WizPathResolve.h"
#include "widgets/WizLocalProgressWebView.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QToolBar>
#include <QAction>
#include <QStyle>
#include <QDir>
#include <QMovie>
#include <QVBoxLayout>
#include <QStyleFactory>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QNetworkReply>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include "share/WizSettings.h"
#include "share/WizWebEngineView.h"
#include "share/WizMisc.h"

struct LOCAL_LCID_DATA
{
    const char* name;
    int lcid;
};

static const LOCAL_LCID_DATA g_lcid[] =
{
    {"af_ZA", 1078},
    {"am_ET", 1118},
    {"ar_AE", 14337},
    {"ar_BH", 15361},
    {"ar_DZ", 5121},
    {"ar_EG", 3073},
    {"ar_IQ", 2049},
    {"ar_JO", 11265},
    {"ar_KW", 13313},
    {"ar_LB", 12289},
    {"ar_LY", 4097},
    {"ar_MA", 6145},
    {"ar_OM", 8193},
    {"ar_QA", 16385},
    {"ar_SA", 1025},
    {"ar_SY", 10241},
    {"ar_TN", 7169},
    {"ar_YE", 9217},
    {"arn_CL", 1146},
    {"as_IN", 1101},
    {"az_AZ", 2092},
    {"ba_RU", 1133},
    {"be_BY", 1059},
    {"bg_BG", 1026},
    {"bn_IN", 1093},
    {"bo_BT", 2129},
    {"bo_CN", 1105},
    {"br_FR", 1150},
    {"bs_BA", 8218},
    {"ca_ES", 1027},
    {"co_FR", 1155},
    {"cs_CZ", 1029},
    {"cy_GB", 1106},
    {"da_DK", 1030},
    {"de_AT", 3079},
    {"de_CH", 2055},
    {"de_DE", 1031},
    {"de_LI", 5127},
    {"de_LU", 4103},
    {"div_MV", 1125},
    {"dsb_DE", 2094},
    {"el_GR", 1032},
    {"en_AU", 3081},
    {"en_BZ", 10249},
    {"en_CA", 4105},
    {"en_CB", 9225},
    {"en_GB", 2057},
    {"en_IE", 6153},
    {"en_IN", 18441},
    {"en_JA", 8201},
    {"en_MY", 17417},
    {"en_NZ", 5129},
    {"en_PH", 13321},
    {"en_TT", 11273},
    {"en_US", 1033},
    {"en_ZA", 7177},
    {"en_ZW", 12297},
    {"es_AR", 11274},
    {"es_BO", 16394},
    {"es_CL", 13322},
    {"es_CO", 9226},
    {"es_CR", 5130},
    {"es_DO", 7178},
    {"es_EC", 12298},
    {"es_ES", 3082},
    {"es_GT", 4106},
    {"es_HN", 18442},
    {"es_MX", 2058},
    {"es_NI", 19466},
    {"es_PA", 6154},
    {"es_PE", 10250},
    {"es_PR", 20490},
    {"es_PY", 15370},
    {"es_SV", 17418},
    {"es_UR", 14346},
    {"es_US", 21514},
    {"es_VE", 8202},
    {"et_EE", 1061},
    {"eu_ES", 1069},
    {"fa_IR", 1065},
    {"fi_FI", 1035},
    {"fil_PH", 1124},
    {"fo_FO", 1080},
    {"fr_BE", 2060},
    {"fr_CA", 3084},
    {"fr_CH", 4108},
    {"fr_FR", 1036},
    {"fr_LU", 5132},
    {"fr_MC", 6156},
    {"fy_NL", 1122},
    {"ga_IE", 2108},
    {"gbz_AF", 1164},
    {"gl_ES", 1110},
    {"gsw_FR", 1156},
    {"gu_IN", 1095},
    {"ha_NG", 1128},
    {"he_IL", 1037},
    {"hi_IN", 1081},
    {"hr_BA", 4122},
    {"hr_HR", 1050},
    {"hu_HU", 1038},
    {"hy_AM", 1067},
    {"id_ID", 1057},
    {"ii_CN", 1144},
    {"is_IS", 1039},
    {"it_CH", 2064},
    {"it_IT", 1040},
    {"iu_CA", 2141},
    {"ja_JP", 1041},
    {"ka_GE", 1079},
    {"kh_KH", 1107},
    {"kk_KZ", 1087},
    {"kl_GL", 1135},
    {"kn_IN", 1099},
    {"ko_KR", 1042},
    {"kok_IN", 1111},
    {"ky_KG", 1088},
    {"lb_LU", 1134},
    {"lo_LA", 1108},
    {"lt_LT", 1063},
    {"lv_LV", 1062},
    {"mi_NZ", 1153},
    {"mk_MK", 1071},
    {"ml_IN", 1100},
    {"mn_CN", 2128},
    {"mn_MN", 1104},
    {"moh_CA", 1148},
    {"mr_IN", 1102},
    {"ms_BN", 2110},
    {"ms_MY", 1086},
    {"mt_MT", 1082},
    {"my_MM", 1109},
    {"nb_NO", 1044},
    {"ne_NP", 1121},
    {"nl_BE", 2067},
    {"nl_NL", 1043},
    {"nn_NO", 2068},
    {"ns_ZA", 1132},
    {"oc_FR", 1154},
    {"or_IN", 1096},
    {"pa_IN", 1094},
    {"pl_PL", 1045},
    {"ps_AF", 1123},
    {"pt_BR", 1046},
    {"pt_PT", 2070},
    {"qut_GT", 1158},
    {"quz_BO", 1131},
    {"quz_EC", 2155},
    {"quz_PE", 3179},
    {"rm_CH", 1047},
    {"ro_RO", 1048},
    {"ru_RU", 1049},
    {"rw_RW", 1159},
    {"sa_IN", 1103},
    {"sah_RU", 1157},
    {"se_FI", 3131},
    {"se_NO", 1083},
    {"se_SE", 2107},
    {"si_LK", 1115},
    {"sk_SK", 1051},
    {"sl_SI", 1060},
    {"sma_NO", 6203},
    {"sma_SE", 7227},
    {"smj_NO", 4155},
    {"smj_SE", 5179},
    {"smn_FI", 9275},
    {"sms_FI", 8251},
    {"sq_AL", 1052},
    {"sr_BA", 7194},
    {"sr_SP", 3098},
    {"sv_FI", 2077},
    {"sv_SE", 1053},
    {"sw_KE", 1089},
    {"syr_SY", 1114},
    {"ta_IN", 1097},
    {"te_IN", 1098},
    {"tg_TJ", 1064},
    {"th_TH", 1054},
    {"tk_TM", 1090},
    {"tmz_DZ", 2143},
    {"tn_ZA", 1074},
    {"tr_TR", 1055},
    {"tt_RU", 1092},
    {"ug_CN", 1152},
    {"uk_UA", 1058},
    {"ur_IN", 2080},
    {"ur_PK", 1056},
    {"uz_UZ", 2115},
    {"vi_VN", 1066},
    {"wen_DE", 1070},
    {"wo_SN", 1160},
    {"xh_ZA", 1076},
    {"yo_NG", 1130},
    {"zh_CHS", 4},
    {"zh_CHT", 31748},
    {"zh_CN", 2052},
    {"zh_HK", 3076},
    {"zh_MO", 5124},
    {"zh_SG", 4100},
    {"zh_TW", 1028},
    {"zu_ZA", 1077},
    {nullptr, 0},
};

int localNameToLcid(QString name) {
    for (const LOCAL_LCID_DATA* pData = g_lcid; ;pData++) {
        if (!pData->name)
            break;
        //
        if (0 == name.compare(pData->name, Qt::CaseInsensitive)) {
            return pData->lcid;
        }
    }
    return 0;
}

void splitStringKey(QString key, QString& name, int& lcid)
{
    int index = key.lastIndexOf("_");
    if (index != -1) {
        QString testName = key.left(index);
        QString lcidStr = key.mid(index + 1);
        int testLcid = lcidStr.toInt();
        if (WizIntToStr(testLcid) == lcidStr) {  //is a number
            name = testName;
            lcid = testLcid;
            return;
        }
    }
    //
    name = key;
    lcid = 0;
    return;
}

static const WizIconOptions ICON_OPTIONS(WIZ_TINT_COLOR, "#a6a6a6", WIZ_TINT_COLOR);


WizPluginData::WizPluginData(QString path, QObject* parent)
    : QObject(parent)
    , m_path(path)
{
    WizPathAddBackslash(m_path);
    QString fileName = m_path + "manifest.ini";
    QString section = "Common";
    //
    m_settings = new WizSettings(fileName);
    m_name = m_settings->getString(section, "AppName");
    m_type = m_settings->getString(section, "Type");
    m_guid = m_settings->getString(section, "AppGUID");
    m_moduleCount = m_settings->getInt(section, "ModuleCount");
    //
    int realModuleCount = 0;
    QStringList groups = m_settings->childGroups();
    for (QString& pluginIndex : groups) {
        if (!pluginIndex.contains("Module_"))
            continue;
        WizPluginModuleData* data = new WizPluginModuleData(pluginIndex, *m_settings, this);
        //TODO: to validate the data, and if neccessary infomations are missed, discard it.
        m_modules.push_back(data);
        realModuleCount++;
    }
    if (realModuleCount != m_moduleCount)
        qWarning() << QString("App %s's ModuleCount not correct!").arg(m_name);
}
//
void WizPluginData::emitDocumentChanged()
{
    emit documentChanged();
    for (WizPluginModuleData* data : m_modules) {
        data->emitDocumentChanged();
    }
}

void WizPluginData::emitShowEvent()
{
    emit willShow();
    for (WizPluginModuleData* data : m_modules) {
        data->emitShowEvent();
    }
}

void WizPluginData::initStrings()
{
    WizPathAddBackslash(m_path);
    QString fileName = m_path + "manifest.ini";
    //
    WizSettings plugin(fileName);
    CWizStdStringArray keys;
    plugin.getKeys("Strings", keys);
    //
    QJsonObject object;
    //
    QString localeName;
    if (WizUserSettings* settings = WizUserSettings::currentSettings()) {
        localeName = settings->locale();
    }
    int lcid = localNameToLcid(localeName);
    QString suffix = lcid ? QString("_") + WizIntToStr(lcid) : QString("");
    for (auto key : keys) {
        //
        QString name;
        int l = 0;
        splitStringKey(key, name, l);
        if (l == 0 || l == lcid) {
            QString value = plugin.getString("Strings", key);
            object[name] = value;
        }
    }
    QJsonDocument doc(object);
    QString strings = QString::fromStdString(doc.toJson().toStdString());
    m_strings = strings;
}

WizPluginModuleData::WizPluginModuleData(QString& section, WizSettings& setting, QObject* parent)
    : QObject(parent)
    , m_section(section)
{
    m_parentPlugin = qobject_cast<WizPluginData*>(parent);
    m_path = m_parentPlugin->path();
    m_caption = setting.getString(section, "Caption");
    m_guid = setting.getString(section, "GUID");
    m_moduleType = setting.getString(section, "ModuleType");
    //
    m_slotType = setting.getString(section, "SlotType");
    m_buttonLocation = setting.getString(section, "ButtonLocation");
    m_menuLocation = setting.getString(section, "MenuLocation");
    m_iconFileName = m_path + setting.getString(section, "IconFileName");
    m_htmlFileName = m_path + setting.getString(section, "HtmlFileName");
    m_scriptFileName = m_path + setting.getString(section, "ScriptFileName");
    m_width = setting.getInt(section, "Width", 800);
    m_height = setting.getInt(section, "Height", 500);
}

void WizPluginModuleData::emitDocumentChanged()
{
    emit documentChanged();
}

void WizPluginModuleData::emitShowEvent()
{
    emit willShow();
}

WizPluginSelectorWindow::WizPluginSelectorWindow(WizExplorerApp& app, WizPluginModuleData* data, QWidget* parent)
    : WizPopupWidget(parent)
    , m_data(data)
    , m_windowWidth(data->width())
    , m_windowHeight(data->height())
{
    data->parentPlugin()->initStrings();
    //
    WizMainWindow* mw = qobject_cast<WizMainWindow*>(app.mainWindow());
    WizWebEngineViewInjectObjects objects = {
        {"WizPluginData", data->parentPlugin()},
        {"WizPluginModuleData", data},
        {"WizExplorerApp", mw->componentInterface()}
    };
    m_web = new WizWebEngineView(objects, this);
    //
    setContentsMargins(0, 8, 0, 0);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    layout->addWidget(m_web);
    //
    if (isDarkMode()) {
        QString html;
        WizLoadUnicodeTextFromFile(m_data->htmlFileName(), html);
        QString style = "<link type=\"text/css\" href=\"nightModeStyle.css\" rel=\"stylesheet\" />";
        WizHTMLAppendTextInHead(style, html);
        m_web->setHtml(html, QUrl::fromLocalFile(m_data->htmlFileName()));

    } else {
        m_web->load(QUrl::fromLocalFile(m_data->htmlFileName()));
    }
}

QSize WizPluginSelectorWindow::sizeHint() const
{
    return QSize(m_windowWidth, m_windowHeight);
}

WizPluginHtmlDialog::WizPluginHtmlDialog(WizExplorerApp& app, WizPluginModuleData* data, QWidget* parent)
    : QWidget(parent, Qt::Window)
    , m_data(data)
    , m_dialogWidth(data->width())
    , m_dialogHeight(data->height())
{
    data->parentPlugin()->initStrings();
    //
    setWindowTitle(data->caption());
    //
    WizMainWindow* mw = qobject_cast<WizMainWindow*>(app.mainWindow());
    WizWebEngineViewInjectObjects objects = {
        {"WizPluginData", data->parentPlugin()},
        {"WizPluginModuleData", data},
        {"WizExplorerApp", mw->componentInterface()}
    };
    m_web = new WizWebEngineView(objects, this);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    layout->addWidget(m_web);
    //
    m_web->load(QUrl::fromLocalFile(m_data->htmlFileName()));
}

QSize WizPluginHtmlDialog::dialogSize() const
{
    return QSize(m_dialogWidth, m_dialogHeight);
}

QSize WizPluginHtmlDialog::sizeHint() const
{
    return dialogSize();
}

WizPlugins::WizPlugins(QString basePath)
{
    init(basePath);
};

WizPlugins::WizPlugins(QStringList basePath)
{
    QStringListIterator paths(basePath);
    while (paths.hasNext())
         init(paths.next());
};


WizPlugins::~WizPlugins()
{
    for (auto data : m_data) {
        delete data;
    }
    m_data.clear();
};

void WizPlugins::init(QString basePath)
{
    CWizStdStringArray folders;
    WizEnumFolders(basePath, folders, 0);
    //
    for (auto folder : folders) {
        if (!QDir(folder).exists("manifest.ini"))
            continue;
        WizPluginData* data = new WizPluginData(folder, nullptr);
        m_data.push_back(data);
        qDebug() << "Loaded plugin: " + data->name();
    }
}

void WizPlugins::notifyDocumentChanged()
{
    for (auto data : m_data) {
        data->emitDocumentChanged();
    }
}

WizPlugins& WizPlugins::plugins()
{
    QStringList pluginBase = Utils::WizPathResolve::pluginsAllPath();
    static WizPlugins plugins(pluginBase);
    return plugins;
}

WizJSPluginManager::WizJSPluginManager(QStringList &pluginScanPathList, WizExplorerApp& app, QObject* parent)
    : QObject(parent)
    , m_app(app)
{
    for (QString &path : pluginScanPathList) {
        loadPluginData(path);
    }
}

WizJSPluginManager::~WizJSPluginManager()
{
    for (auto htmlDialog : m_pluginHtmlDialogCollection) {
        delete htmlDialog;
    }
    m_pluginHtmlDialogCollection.clear();
    
    for (auto selectorWindow : m_pluginHtmlDialogCollection) {
        delete selectorWindow;
    }
    m_pluginHtmlDialogCollection.clear();

}

void WizJSPluginManager::loadPluginData(QString &pluginScanPath)
{
    CWizStdStringArray folders;
    WizEnumFolders(pluginScanPath, folders, 0);
    
    for (auto folder : folders) {
        if (!QDir(folder).exists("manifest.ini"))
            continue;
        WizPluginData* data = new WizPluginData(folder, this);
        m_pluginDataCollection.push_back(data);
        qDebug() << "Loaded plugin: " + data->name();
    }
}

QList<WizPluginModuleData *> WizJSPluginManager::modulesByButtonLocation(QString buttonLocation) const
{
    QList<WizPluginModuleData *> ret;
    for (WizPluginData *pluginData : m_pluginDataCollection) {
        for (WizPluginModuleData *moduleData : pluginData->modules()) {
            if (moduleData->buttonLocation() == buttonLocation) {
                ret.push_back(moduleData);
            }
        }
    }
    return ret;
}

QList<WizPluginModuleData *> WizJSPluginManager::modulesByKeyValue(QString key, QString value) const
{
    QList<WizPluginModuleData *> ret;
    for (WizPluginData *pluginData : m_pluginDataCollection) {
        WizSettings *settings = pluginData->settings();
        for (WizPluginModuleData *moduleData : pluginData->modules()) {
            QString section = moduleData->section();
            if (settings->getString(section, key) == value) {
                ret.push_back(moduleData);
            }
        }
    }
    return ret;
}

WizPluginModuleData *WizJSPluginManager::moduleByGUID(QString guid) const
{
    WizPluginModuleData *ret = nullptr;
    for (WizPluginData *pluginData : m_pluginDataCollection) {
        for (WizPluginModuleData *moduleData : pluginData->modules()) {
            if (moduleData->guid() == guid) {
                ret = moduleData;
            }
        }
    }

    return ret;
}

QAction *WizJSPluginManager::createPluginAction(QWidget *parent, WizPluginModuleData *moduleData)
{
    QAction *ac = new QAction(parent);
    ac->setData(moduleData->guid());
    ac->setIcon(QIcon(moduleData->iconFileName()));
    ac->setIconText(moduleData->caption());
    ac->setText(moduleData->caption());
    ac->setToolTip(moduleData->caption());
    return ac;
}

WizPluginHtmlDialog *WizJSPluginManager::initPluginHtmlDialog(WizPluginModuleData *moduleData)
{
    WizPluginHtmlDialog *htmlDialog = new WizPluginHtmlDialog(m_app, moduleData, nullptr);
    m_pluginHtmlDialogCollection.insert(moduleData->guid(), htmlDialog);
    return htmlDialog;
}

WizPluginSelectorWindow *WizJSPluginManager::initPluginSelectorWindow(WizPluginModuleData *moduleData)
{
    WizPluginSelectorWindow *selectorWindow = new WizPluginSelectorWindow(m_app, moduleData, nullptr);
    m_pluginPopupDialogCollection.insert(moduleData->guid(), selectorWindow);
    return selectorWindow;
}

void WizJSPluginManager::showPluginHtmlDialog(WizPluginModuleData *moduleData)
{
    QString guid = moduleData->guid();
    WizPluginHtmlDialog* dialog;
    auto it = m_pluginHtmlDialogCollection.find(guid);
    if ( it == m_pluginHtmlDialogCollection.end()) {
        dialog = initPluginHtmlDialog(moduleData);
    } else {
        dialog = it.value();
    }
    //
    moduleData->emitShowEvent();
    dialog->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dialog->dialogSize(),
            qApp->desktop()->availableGeometry()
        )
    );
    dialog->show();
    dialog->raise();
}

void WizJSPluginManager::showPluginSelectorWindow(WizPluginModuleData *moduleData, QPoint &pt)
{
    QString guid = moduleData->guid();
    WizPluginSelectorWindow* selectorWindow;
    auto it = m_pluginPopupDialogCollection.find(guid);
    if ( it == m_pluginPopupDialogCollection.end()) {
        selectorWindow = initPluginSelectorWindow(moduleData);
    } else {
        selectorWindow = it.value();
    }
    //
    moduleData->emitShowEvent();
    if (isDarkMode()) {
        selectorWindow->web()->setVisible(false);
        QTimer::singleShot(500, [=] {
            selectorWindow->web()->setVisible(true);
        });
    }
    selectorWindow->showAtPoint(pt);
}

void WizJSPluginManager::handlePluginActionTriggered()
{
    QAction *ac = qobject_cast<QAction *>(sender());
    if (!ac)
        return;

    QString moduleGuid = ac->data().toString();
    if (moduleGuid.isEmpty())
        return;

    WizPluginModuleData *moduleData = moduleByGUID(moduleGuid);
    if (!moduleData)
        return;

    QString slotType = moduleData->slotType();
    if ( slotType == "SelectorWindow" ) {
        QToolBar *bar = qobject_cast<QToolBar *>(ac->parentWidget());
        if (!bar)
            return;
        QToolButton *button = qobject_cast<QToolButton *>(bar->widgetForAction(ac));
        if (!button)
            return;
        QRect rc = button->rect();
        QPoint pt = button->mapToGlobal(QPoint(rc.width()/2, rc.height()));
        showPluginSelectorWindow(moduleData, pt);
    } else if ( slotType == "HtmlDialog" ) {
        showPluginHtmlDialog(moduleData);
    }
}
