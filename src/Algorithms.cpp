#include "Algorithms.hpp"

namespace Algo
{
    std::deque<Command *> SelectionSort(std::vector<short> data, bool commands)
    {
        std::deque<Command *> q;
        int smallestIndex = 0;
        for (int i = 0; i < data.size() - 1; i++)
        {
            smallestIndex = i;
            if (commands)
                q.push_back(new LookCommand(i));
            for (int j = i + 1; j < data.size(); j++)
            {
                if (commands)
                    q.push_back(new LookCommand(j, false));
                if (data[j] < data[smallestIndex])
                    smallestIndex = j;
            }
            if (i == smallestIndex)
                continue;
            if (commands)
                q.push_back(new SwapCommand(i, smallestIndex));
            std::swap(data.at(i), data.at(smallestIndex));
        }
        return q;
    }

    std::deque<Command*> InsertionSort(std::vector<short> data, bool commands)
    {
        std::deque<Command *> q;
        int j, jminus1;
        for (int i = 1; i < data.size(); i++)
        {
            j = i - 1;
            if (commands)
            {
                q.push_back(new LookCommand(j, false));
                q.push_back(new LookCommand(i, true));
            }
            while (j >= 0 && data[j] > data[j + 1])
            {
                if (commands)
                {
                    q.push_back(new SwapCommand(j, j+1));
                    q.push_back(new LookCommand(j, false));
                    q.push_back(new LookCommand(j+1, true));
                }
                std::swap(data.at(j), data.at(j+1));
                j -= 1;
            }
        }
        return q;
    }
}