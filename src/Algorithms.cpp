#include "Algorithms.hpp"

namespace Algo
{
    //Private namespace functions
    //Empty namespace can only be accessed from this file. "Algorithms.cpp"
    namespace
    {
        std::deque<Command*> MergeSorts(std::vector<short>& data, int lowPoint, 
            int highPoint, bool commands)
            {
                std::deque<Command*> q;
                std::deque<Command*> newCommands;
                if (lowPoint < highPoint)
                {
                    int midPoint = (lowPoint + highPoint) * 0.5f;
                    newCommands = MergeSorts(data, lowPoint, midPoint, commands);
                    if (commands)
                        q.insert(q.end(), newCommands.begin(), newCommands.end());
                    newCommands.clear();
                    newCommands = MergeSorts(data, midPoint + 1, highPoint, commands);
                    if (commands)
                        q.insert(q.end(), newCommands.begin(), newCommands.end());

                    //Definately a hack for now.
                    std::sort(data.begin() + lowPoint, data.begin() + midPoint +1);
                    std::sort(data.begin() + midPoint + 1, data.begin() + highPoint +1);
                    std::vector<short> mergedData;
                    std::merge(data.begin() + lowPoint, data.begin() + midPoint+1, 
                        data.begin() + midPoint + 1, data.begin() + highPoint +1, std::back_inserter(mergedData));
                    if (!commands)
                        return q;
                    std::copy(mergedData.begin(), mergedData.end(), data.begin() + lowPoint);
                    q.push_back(new SetGroupCommand(lowPoint, highPoint, mergedData));
                }
                return q;
            }
    }



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

    std::deque<Command*> MergeSort(std::vector<short> data, bool commands)
    {
        std::deque<Command *> q;
        q = MergeSorts(data, 0, data.size() - 1, commands);
        return q;
    }

}