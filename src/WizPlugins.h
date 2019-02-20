#ifndef WIZPLUGINS_H
#define WIZPLUGINS_H

#include <QDialog>
#include <QIcon>
#include "share/WizWebEngineView.h"
#include "share/WizPopupWidget.h"

class WizWebEngineView;
class WizExplorerApp;
class WizPluginPopupWidget;

class WizPluginData : public QObject
{
    Q_OBJECT
public:
    WizPluginData(QString path, QObject* parent);
    //
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QString guid READ guid)
    Q_PROPERTY(QString scriptFileName READ scriptFileName)
    Q_PROPERTY(QString strings READ strings)
public:
    QString path() const { return m_path; }
    QString guid() const { return m_guid; }
    QString scriptFileName() const { return m_scriptFileName; }
    QIcon icon() const { return m_icon; }
    QString type() const { return m_type; }
    QString name() const { return m_name; }
    QString strings() const { return m_strings; }
    std::vector<WizChildPluginData*> childPlugins() { return m_childPlugins; }
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
    QString m_scriptFileName;
    QIcon m_icon;
    QString m_name;
    QString m_strings;
    int m_pluginCount;
    std::vector<WizChildPluginData*> m_childPlugins;
    //
    friend class WizPluginPopupWidget;
    friend class WizChildPluginData;
};

class WizChildPluginData : public QObject
{
    Q_OBJECT

public:
    WizChildPluginData(QString& section, WizSettings& setting, QObject* parent);

public:
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

private:
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

class WizPluginPopupWidget : public WizPopupWidget
{
public:
    WizPluginPopupWidget(WizExplorerApp& app, WizPluginData* data, QWidget* parent);
public:
    WizWebEngineView* web() const {return m_web; }
private:
    WizWebEngineView* m_web;
    WizPluginData* m_data;
    //
    friend class WizPluginData;
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
    std::vector<WizChildPluginData*> pluginsByButtonType(QString buttonType) const;
    std::vector<WizPluginData*> pluginsAll() const { return m_data; }
    void notifyDocumentChanged();
public:
    static WizPlugins& plugins();
};



#endif // WIZPLUGINS_H
