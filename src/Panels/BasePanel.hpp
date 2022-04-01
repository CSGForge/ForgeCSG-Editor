#pragma once

#include <string>

#include "../ImGuiManager.hpp"
#include "../WorldManager.hpp"

namespace ForgeEditor
{
    class ImGuiManager;

    class BasePanel
    {
    public:
        virtual void Render();
        bool GetVisibility();
        void SetVisibility(bool visible);
        std::string GetName();
        void SetName(std::string name);

    protected:
        ImGuiManager *mImGuiManager;
        WorldManager *mWorldManager;
        bool mVisible = true;
        std::string mName;
    };
}