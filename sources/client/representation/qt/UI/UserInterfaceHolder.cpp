#include "representation/qt/UI/UserInterfaceHolder.h"

UserInterfaceHolder::UserInterfaceHolder()
{
    QtWebEngine::initialize();
}

void UserInterfaceHolder::show(kv::ObjectUserInterface* object)
{
    if(channel_) delete channel_;
    channel_ = new QWebChannel(view_.page());
    view_.page()->setWebChannel(channel_);

    channel_->registerObject(object->objectName(), object);
    QString url = QString("file://%1/UI/%2.html").arg(QDir::currentPath()).arg(object->getFilename());
    view_.setUrl(QUrl(url));
    view_.resize(object->getWidth(), object->getHeight());
    view_.show();
}

UserInterfaceHolder::~UserInterfaceHolder()
{
    if(channel_) delete channel_;
}
