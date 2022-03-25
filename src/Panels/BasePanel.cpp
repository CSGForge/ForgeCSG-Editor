#include "BasePanel.hpp"

#include <iostream>

namespace ForgeEditor
{
    void BasePanel::Render()
    {
        std::cout << "Base not overriden" << std::endl;
    }

    bool BasePanel::GetVisibility()
    {
        return mVisible;
    }

    void BasePanel::SetVisibility(bool visible)
    {
        mVisible = visible;
    }

    std::string BasePanel::GetName()
    {
        return mName;
    }

    void BasePanel::SetName(std::string name)
    {
        mName = name;
    }
}