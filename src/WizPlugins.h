#ifndef WIZPLUGINS_H
#define WIZPLUGINS_H

#include <QDialog>
#include <QIcon>
#include "share/WizWebEngineView.h"
#include "share/WizPopupWidget.h"
#include "share/WizSettings.h"

class WizWebEngineView;
class WizExplorerApp;
class WizPluginPopupWidget;
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
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString buttonType READ buttonType)
    Q_PROPERTY(QString menuType READ menuType)
    Q_PROPERTY(QString iconFileName READ iconFileName)
    Q_PROPERTY(QString htmlFileName READ htmlFileName)
    Q_PROPERTY(QString scriptFileName READ scriptFileName)
    Q_PROPERTY(QString dialogWidth READ dialogWidth)
    Q_PROPERTY(QString dialogHeight READ dialogHeight)

public:
    WizPluginData* parentPlugin() { return m_parentPlugin; }
    QString section() { return m_section; }
    QString caption() { return m_caption; }
    QString guid() { return m_guid; }
    QString type() { return m_type; }
    QString buttonType() { return m_buttonType; }
    QString menuType() { return m_menuType; }
    QString iconFileName() { return m_iconFileName; }
    QString htmlFileName() { return m_htmlFileName; }
    QString scriptFileName() { return m_scriptFileName; }
    QString dialogWidth() { return m_dialogWidth; }
    QString dialogHeight() { return m_dialogHeight; }
    void emitDocumentChanged();
    void emitShowEvent();
    
Q_SIGNALS:
    void documentChanged();
    void willShow();

private:
    WizPluginData* m_parentPlugin;
    QString m_path;
    QString m_section;
    QString m_caption;
    QString m_guid;
    QString m_type;
    QString m_buttonType;
    QString m_menuType;
    QString m_iconFileName;
    QString m_htmlFileName;
    QString m_scriptFileName;
    QString m_dialogWidth;
    QString m_dialogHeight;
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
    //Q_PROPERTY(QString scriptFileName READ scriptFileName)
    Q_PROPERTY(QString strings READ strings)
    //Q_PROPERTY(QString modules READ modules) //必须是 QObject 才行
public:
    QString path() const { return m_path; }
    QString guid() const { return m_guid; }
    //QString scriptFileName() const { return m_scriptFileName; }
    //QIcon icon() const { return m_icon; }
    QString type() const { return m_type; }
    QString name() const { return m_name; }
    QString strings() const { return m_strings; }
    std::vector<WizPluginModuleData*> modules() { return m_modules; }
    void initStrings();
    void emitDocumentChanged();
    void emitShowEvent();
Q_SIGNALS:
    void documentChanged();
    void willShow();
private:
    QString m_path;
    QString m_guid;
    QString m_type;
    //QString m_scriptFileName;
    //QIcon m_icon;
    QString m_name;
    QString m_strings;
    int m_moduleCount;
    std::vector<WizPluginModuleData*> m_modules;
    //
    friend class WizPluginPopupWidget;
    friend class WizPluginModuleData
;
};

class WizPluginPopupWidget : public WizPopupWidget
{
public:
    WizPluginPopupWidget(WizExplorerApp& app, WizPluginModuleData* data, QWidget* parent);
public:
    WizWebEngineView* web() const {return m_web; }
private:
    WizWebEngineView* m_web;
    WizPluginModuleData* m_data;
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
    std::vector<WizPluginModuleData*> modulesByButtonType(QString buttonType) const;
    std::vector<WizPluginData*> pluginsAll() const { return m_data; }
    void notifyDocumentChanged();
public:
    static WizPlugins& plugins();
};



#endif // WIZPLUGINS_H
