#pragma once
#include "AlgoVisualizer.hpp"

class Command
{
public:
    virtual void execute(AlgoVisualizer& data) = 0;
};