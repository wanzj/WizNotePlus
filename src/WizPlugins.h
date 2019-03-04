#ifndef WIZPLUGINS_H
#define WIZPLUGINS_H

#include "share/WizWebEngineView.h"
#include "share/WizPopupWidget.h"
#include "share/WizSettings.h"
#include "WizCellButton.h"

class WizWebEngineView;
class WizExplorerApp;
class WizPluginSelectorWindow;
class WizPluginData;

class WizPluginModuleData : public QObject
{
    Q_OBJECT

public:
    WizPluginModuleData(QString& section, WizSettings& setting, QObject* parent);
    //
    Q_PROPERTY(QString section READ section)
    Q_PROPERTY(QString caption READ caption)
    Q_PROPERTY(QString guid READ guid)
    Q_PROPERTY(QString moduleType READ moduleType)
    Q_PROPERTY(QString iconFileName READ iconFileName)
    Q_PROPERTY(QString htmlFileName READ htmlFileName)
    Q_PROPERTY(QString scriptFileName READ scriptFileName)

public:
    WizPluginData* parentPlugin() { return m_parentPlugin; }
    QString section() { return m_section; }
    QString caption() { return m_caption; }
    QString guid() { return m_guid; }
    QString slotType() { return m_slotType; }
    QString moduleType() { return m_moduleType; }
    QString buttonLocation() { return m_buttonLocation; }
    QString menuLocation() { return m_menuLocation; }
    QString iconFileName() { return m_iconFileName; }
    QString htmlFileName() { return m_htmlFileName; }
    QString scriptFileName() { return m_scriptFileName; }
    int width() { return m_width; }
    int height() { return m_height; }
    void emitDocumentChanged();
    void emitShowEvent();
    
Q_SIGNALS:
    void documentChanged();
    void willShow();

private:
    // base info
    
    WizPluginData* m_parentPlugin;
    QString m_path;
    QString m_section;
    QString m_caption;
    QString m_guid;
    QString m_moduleType;

    // ModuleType=Action

    QString m_slotType;
    QString m_buttonLocation;
    QString m_menuLocation;
    QString m_iconFileName;
    QString m_htmlFileName;
    QString m_scriptFileName;
    int m_width;
    int m_height;

};

class WizPluginData : public QObject
{
    Q_OBJECT

public:
    WizPluginData(QString path, QObject* parent);
    //
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QString guid READ guid)
    Q_PROPERTY(QString strings READ strings)

public:
    WizSettings *settings() { return m_settings; }
    QString path() const { return m_path; }
    QString guid() const { return m_guid; }
    QString type() const { return m_type; }
    QString name() const { return m_name; }
    QString strings() const { return m_strings; }
    QVector<WizPluginModuleData*> modules() { return m_modules; }
    void initStrings();
    void emitDocumentChanged();
    void emitShowEvent();

Q_SIGNALS:
    void documentChanged();
    void willShow();

private:
    WizSettings *m_settings;
    QString m_path;
    QString m_guid;
    QString m_type;
    QString m_name;
    QString m_strings;
    int m_moduleCount;
    QVector<WizPluginModuleData*> m_modules;
    //
    friend class WizPluginSelectorWindow;
    friend class WizPluginModuleData;
};

class WizPluginSelectorWindow : public WizPopupWidget
{
public:
    WizPluginSelectorWindow(WizExplorerApp& app, WizPluginModuleData* data, QWidget* parent);
public:
    WizWebEngineView* web() const {return m_web; }
private:
    WizWebEngineView* m_web;
    WizPluginModuleData* m_data;
    int m_windowWidth;
    int m_windowHeight;

private:
    virtual QSize sizeHint() const;
    //
    friend class WizPluginData;
    friend class WizPluginModuleData;
};


class WizPluginHtmlDialog : public QWidget
{
    Q_OBJECT

public:
    WizPluginHtmlDialog(WizExplorerApp& app, WizPluginModuleData* data, QWidget* parent);
    QSize dialogSize() const;

private:
    WizWebEngineView* m_web;
    WizPluginModuleData* m_data;
    int m_dialogWidth;
    int m_dialogHeight;
    //
private:
    virtual QSize sizeHint() const;
    //
    friend class WizPluginData;
    friend class WizPluginModuleData;
};


class WizPlugins
{
private:
    WizPlugins(QString basePath);
    WizPlugins(QStringList basePath);
public:
    ~WizPlugins();
private:
    void init(QString basePath);
private:
    std::vector<WizPluginData*> m_data;
public:
    std::vector<WizPluginData*> pluginsByType(QString type) const;
    std::vector<WizPluginData*> pluginsAll() const { return m_data; }
    void notifyDocumentChanged();
public:
    static WizPlugins& plugins();
};

class WizJSPluginManager : public QObject
{
    Q_OBJECT

public:
    WizJSPluginManager(QStringList &pluginScanPathList, WizExplorerApp& app, QObject *parent = nullptr);
    ~WizJSPluginManager();
    //
    QList<WizPluginModuleData *> modulesByButtonLocation(QString buttonLocation) const;
    QList<WizPluginModuleData *> modulesByKeyValue(QString key, QString value) const;
    WizPluginModuleData *moduleByGUID(QString guid) const;
    //
    static QAction *createPluginAction(QWidget *parent, WizPluginModuleData *moduleData);
    WizPluginHtmlDialog *initPluginHtmlDialog(WizPluginModuleData *moduleData);
    void showPluginHtmlDialog(WizPluginModuleData *moduleData);
    WizPluginSelectorWindow *initPluginSelectorWindow(WizPluginModuleData *moduleData);
    void showPluginSelectorWindow(WizPluginModuleData *moduleData, QPoint &pt);

private:
    void loadPluginData(QString &pluginScanPath);

public slots:
    void handlePluginActionTriggered();

private:
    WizExplorerApp &m_app;
    QList<WizPluginData *> m_pluginDataCollection;
    QHash<QString, WizPluginHtmlDialog *> m_pluginHtmlDialogCollection;
    QHash<QString, WizPluginSelectorWindow *> m_pluginPopupDialogCollection;

};



#endif // WIZPLUGINS_H
