#pragma once
#include "Command.hpp"

class LookCommand : public Command
{
public:
    LookCommand(int index, bool isIndexI = true, std::string log = "") 
        { m_index = index; m_isIndexI = isIndexI; m_log = log; }
    
    void execute(AlgoVisualizer& data) override
    {
        data.lookAtIndex(m_index, m_isIndexI);
    }
    
    private:
    int m_index = 0;
    bool m_isIndexI = true; //if not false then we can assume index j.

};