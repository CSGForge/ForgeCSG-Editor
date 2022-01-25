#pragma once

#include <string>
#include <memory>
#include "Window.hpp"

namespace ForgeEditor
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
        Window &GetWindow();
        static Application &GetApplication();

    private:
        static Application *sInstance;
        std::unique_ptr<Window> mWindow;
        bool mRunning;
        std::string mName;
    };
}