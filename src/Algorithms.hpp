#pragma once
#include "LookCommand.hpp"
#include "SwapCommand.hpp"
#include "SetGroupCommand.hpp"
#include <algorithm>
#include <deque>
#include <cmath>

namespace Algo 
{
    std::deque<Command*> SelectionSort(std::vector<short> data, bool commands = true);
    std::deque<Command*> InsertionSort(std::vector<short> data, bool commands = true);
    std::deque<Command*> MergeSort(std::vector<short> data, bool commands = true);
    std::deque<Command*> RadixSort(std::vector<short> data, bool commands = true);
}