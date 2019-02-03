#ifndef USERINTERFACEHOLDER_H
#define USERINTERFACEHOLDER_H

#include <QtWebEngine>
#include <QWebEngineView>
#include "../core_headers/ObjectUserInterface.h"

class UserInterfaceHolder
{
public:
    UserInterfaceHolder();
    ~UserInterfaceHolder();
    void show(kv::ObjectUserInterface* object);
private:
    QWebChannel *channel_ = nullptr;
    QWebEngineView view_;
};

#endif
