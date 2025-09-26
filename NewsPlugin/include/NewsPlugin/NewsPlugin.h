#pragma once

#include <QDebug>
#include <QObject>
#include <QString>
#include <QtPlugin>

class NewsPlugin : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.poclauncher.TestPlugin" FILE "../../plugin.json");

   public:
    NewsPlugin();
};
