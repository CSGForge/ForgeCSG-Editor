#include "BasePanel.hpp"

namespace ForgeEditor
{
    void BasePanel::Render()
    {
        throw;
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