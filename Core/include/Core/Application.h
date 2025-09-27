#pragma once

#include <QApplication>
#include <memory>

class PluginLoader;
class QIcon;

#define APPLICATION ((Application*)QApplication::instance())

class Application : public QApplication {
   public:
    Application(int& argc, char** argv);
    ~Application();
    int run();

    PluginLoader& pluginLoader();
    const PluginLoader& pluginLoader() const;

    bool portable() const;

   private:
    void initDir(const QString& dirParam);

    struct Data;
    std::unique_ptr<Data> m_data;
};
