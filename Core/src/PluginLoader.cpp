#include <QDir>
#include <QHash>
#include <QList>

#include <QPluginLoader>
#include <QString>

#include "PluginLoader.h"

using namespace Qt::Literals;

struct PluginLoader::Data {
    QList<Plugin> plugins;
    QHash<int, QObject*> instances;
    QHash<int, std::any> impls;
};

PluginLoader::PluginLoader() : m_data(std::make_unique<Data>())
{
    for (const QStaticPlugin& plugin : QPluginLoader::staticPlugins())
        insert(plugin.metaData(), plugin.instance());
}

PluginLoader::~PluginLoader()
{}

int PluginLoader::loadDynamic(QDir dir)
{
    int count = 0;

    for (QString fileName : dir.entryList()) {
        qDebug() << "Discovered plugin" << fileName;

        QString absolutePath = dir.absoluteFilePath(fileName);
        QPluginLoader loader(absolutePath);

        if (!loader.load()) {
            qWarning() << "Failed to load plugin from" << fileName;
            continue;
        }

        qDebug() << "Loaded plugin" << fileName;

        ++count;
        insert(loader.metaData(), loader.instance());
    }

    return count;
}

const QList<Plugin>& PluginLoader::plugins() const
{
    return m_data->plugins;
}

void PluginLoader::insert(const QJsonObject& metaData, QObject* instance)
{
    QMetaType type = instance->metaObject()->metaType();

    m_data->plugins.append(Plugin{ metaData, instance });

    if (m_data->instances.contains(type.id())) {
        qWarning() << "Multiple instances of" << type.name();
        return;
    }

    m_data->instances[type.id()] = instance;
}

QObject* PluginLoader::getInstance(QMetaType type) const
{
    return m_data->instances.value(type.id());
}

std::any& PluginLoader::getOrInsertImpls(QMetaType type) const
{
    return m_data->impls[type.id()];
}
