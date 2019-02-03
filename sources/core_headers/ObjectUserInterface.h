#pragma once

#include <QObject>

namespace kv
{
class ObjectUserInterface : public QObject
{
    Q_OBJECT
public:
    quint32 getWidth() { return width_; }
    quint32 getHeight() { return height_; }
    QString getFilename() { return filename_; }
private:
    QString filename_;
    quint32 width_, height_;
};
}
