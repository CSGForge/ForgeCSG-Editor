#include "Application.hpp"

#include <CSGForge-Core/csg.hpp>

int main(int argc, char *argv[])
{
    auto world = new ForgeCore::World();
    world->AddBrush()->SetPlanes(std::vector<ForgeCore::Plane>{
        ForgeCore::Plane(glm::vec3(1, 0, 0), -1),
        ForgeCore::Plane(glm::vec3(-1, 0, 0), -1),
        ForgeCore::Plane(glm::vec3(0, 1, 0), -1),
        ForgeCore::Plane(glm::vec3(0, -1, 0), -1),
        ForgeCore::Plane(glm::vec3(0, 0, 1), -1),
        ForgeCore::Plane(glm::vec3(0, 0, -1), -1),
    });
    printf("Bruh\n");

    auto *app = new ForgeEditor::Application();
    app->Run();
    delete app;
    return 0;
}