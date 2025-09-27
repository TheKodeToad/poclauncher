#include <QtPlugin>

#include "Application.h"

Q_IMPORT_PLUGIN(NewsPlugin);

int coreMain(int argc, char** argv)
{
    Q_INIT_RESOURCE(multimc);
    Application app(argc, argv);
    return app.run();
}
