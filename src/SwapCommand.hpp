#pragma once
#include "Command.hpp"

class SwapCommand : public Command
{
public:
    SwapCommand(int indexLeft, int indexRight, std::string log = "") 
        { m_indexL = indexLeft; m_indexR = indexRight; m_log = log; }
    
    void execute(AlgoVisualizer& data) override
    {
        data.swap(m_indexL, m_indexR);
    }
    
    private:
    int m_indexL = 0;
    int m_indexR = 0;

};