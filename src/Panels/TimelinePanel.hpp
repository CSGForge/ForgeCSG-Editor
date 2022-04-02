#pragma once

#include "BasePanel.hpp"

namespace ForgeEditor
{
    class TimelinePanel : BasePanel
    {
    public:
        TimelinePanel();
        ~TimelinePanel() = default;

        void Render() override;

    private:
    };
}