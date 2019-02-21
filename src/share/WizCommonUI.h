#ifndef WIZCOMMONUI_H
#define WIZCOMMONUI_H

#include "WizQtHelper.h"

class WizCommonUI : public QObject
{
    Q_OBJECT
public:
    WizCommonUI(QObject* parent);
    //interface WizKMControls.WizCommonUI
    Q_INVOKABLE QString LoadTextFromFile(const QString& strFileName) { return loadTextFromFile(strFileName); }
    Q_INVOKABLE QString ClipboardToImage(int hwnd, const QString& strOptions) { return clipboardToImage(hwnd, strOptions); }

private:
    //interface WizKMControls.WizCommonUI;
    QString loadTextFromFile(const QString& strFileName);
    QString clipboardToImage(int hwnd, const QString& strOptions);

};

#endif // WIZCOMMONUI_H
