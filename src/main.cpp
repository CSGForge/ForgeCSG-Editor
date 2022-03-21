#include "Application.hpp"

int main(int argc, char *argv[])
{
    auto *app = new ForgeEditor::Application();
    app->Run();
    delete app;
    return 0;
}