#include "Algorithms.hpp"

namespace Algo
{
    std::queue<Command *> SelectionSort(std::vector<short> data)
    {
        std::queue<Command *> q;
        int smallestIndex = 0;
        for (int i = 0; i < data.size() - 1; i++)
        {
            q.push(new LookCommand(i));
            for (int j = i + 1; j < data.size(); j++)
            {
                q.push(new LookCommand(j, false));
                if (data[j] < data[smallestIndex])
                    smallestIndex = j;
            }
            std::swap(data.at(i), data.at(smallestIndex));
            q.push(new SwapCommand(i, smallestIndex));
        }
        return q;
    }
}