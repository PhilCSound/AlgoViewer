#pragma once
#include "Command.hpp"
#include <vector>

class SetGroupCommand : public Command
{
public:
    SetGroupCommand(int indexL, int indexR, std::vector<short> data, std::string log = "") 
        { m_indexL = indexL; m_indexR = indexR; m_copyData = data; m_log = log; }
    
    void execute(AlgoVisualizer& data) override
    {
        data.lookSetGroup(m_indexL, m_indexR, m_copyData);
    }
    
    private:
    int m_indexL = 0;
    int m_indexR = 0;
    std::vector<short> m_copyData;
};