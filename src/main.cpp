#pragma once
#include "Application.hpp"

int main()
{   

    Application app;

    while (app.IsRunning())
    {
        app.Update();
    }
    
    return -2;
}