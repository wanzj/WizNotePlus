#include "IWizExplorerWindow.h"
#include "WizMainWindow.h"
#include "WizDocumentView.h"
#include "share/WizDatabaseManager.h"
#include "share/WizDatabase.h"

IWizExplorerWindow::IWizExplorerWindow(WizMainWindow* mw, QObject* parent)
    : QObject(parent)
    , m_mainWindow(mw)
{

}

QObject* IWizExplorerWindow::CurrentDocumentBrowserObject()
{
    return m_mainWindow->CurrentDocumentBrowserObject();
}

QObject *IWizExplorerWindow::CurrentDocument()
{
    WizDocumentView *docView = m_mainWindow->documentView();
    if (!docView) 
        return nullptr;

    WizDatabase &db = WizDatabaseManager::instance()->db(
        docView->note().strKbGUID
    );
    WIZDOCUMENTDATA data;
    if (db.documentFromGuid(docView->note().strGUID, data)) {
        return new WizDocument(db, data, this);
    } else {
        return nullptr;
    }
}