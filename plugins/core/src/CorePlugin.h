#pragma once

#include <QObject>
#include <QString>

class CorePlugin : public QObject {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.poclauncher.Core" FILE "../../plugin.json");

   public:
    void bootstrap();
    bool portable();

   private:
    void initDir(const QString& dirParam);

    QString m_rootPath;
    bool m_portable;
};
