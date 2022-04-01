#include "Algorithms.hpp"

namespace Algo
{
    std::deque<Command *> SelectionSort(std::vector<short> data)
    {
        std::deque<Command *> q;
        int smallestIndex = 0;
        for (int i = 0; i < data.size() - 1; i++)
        {
            smallestIndex = i;
            q.push_back(new LookCommand(i));
            for (int j = i + 1; j < data.size(); j++)
            {
                q.push_back(new LookCommand(j, false));
                if (data[j] < data[smallestIndex])
                    smallestIndex = j;
            }
            std::swap(data.at(i), data.at(smallestIndex));
            q.push_back(new SwapCommand(i, smallestIndex));
        }

        return q;
    }
}