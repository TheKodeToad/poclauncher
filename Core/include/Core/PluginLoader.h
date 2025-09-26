#pragma once

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <any>
#include <concepts>
#include <memory>

class QDir;
class QObject;

struct Plugin {
    QJsonObject object;
    QObject* instance;
};

class PluginLoader {
   public:
    PluginLoader();
    ~PluginLoader();

    /**
     * Load external plugins.
     * @param dir The directory to load from
     * @return The number of successfully loaded plugins
     */
    int loadDynamic(QDir dir);

    /**
     * @return Dynamic and static plugin data.
     */
    const QList<Plugin>& plugins() const;

    /**
     * @return The instance of plugin class T
     */
    template <typename T>
    T* instance() const
        requires std::derived_from<T, QObject>
    {
        return (T*)getInstance(QMetaType::fromType<T>());
    }

    /**
     * @return Cached implementers of plugin class T
     */
    template <typename T>
    const QList<T*>& impls() const
    {
        // TODO: is there a better way to do this
        std::any& holder = getOrInsertImpls(QMetaType::fromType<T>());

        if (holder.has_value())
            return *std::any_cast<QList<T*>>(&holder);

        QList<T*> list;

        for (const Plugin& plugin : plugins()) {
            auto casted = qobject_cast<T*>(plugin.instance);

            if (casted != nullptr)
                list.append(casted);
        }

        holder = std::move(list);
        return *std::any_cast<QList<T*>>(&holder);
    }

   private:
    QObject* getInstance(QMetaType type) const;
    std::any& getOrInsertImpls(QMetaType type) const;
    void insert(const QJsonObject& metaData, QObject* instance);

    struct Data;
    std::unique_ptr<Data> m_data;
};
