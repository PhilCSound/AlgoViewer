#pragma once
#include "AlgoVisualizer.hpp"
#include <string>

//TODO CLEAN UP LOG LOGIC
class Command
{
public:
    virtual void execute(AlgoVisualizer& data) = 0;
    std::string& toString() { return m_log; }
protected:
    std::string m_log;
};