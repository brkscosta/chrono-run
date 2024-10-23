#include "app/App.h"


int main(int argc, char* argv[])
{
    std::unique_ptr<app::App> app = std::make_unique<app::App>();
    app->start();

    return 0;
}