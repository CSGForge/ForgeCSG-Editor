#pragma once

#include <string>

namespace ForgeEditor
{
    class BasePanel
    {
    public:
        virtual void Render();
        bool GetVisibility();
        void SetVisibility(bool visible);
        std::string GetName();
        void SetName(std::string name);

    private:
        bool mVisible = true;
        std::string mName;
    };
}