#pragma once
#include "Application.hpp"
#include "AlgoDisplayState.hpp"

int main()
{   

    Application app;
    State* initState = new AlgoDisplayState();
    app.PushState(initState);
    while (app.IsRunning())
    {
        app.Update();
    }
    
    return -2;
}