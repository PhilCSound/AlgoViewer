#pragma once
#include "LookCommand.hpp"
#include "SwapCommand.hpp"
#include <algorithm>
#include <deque>

namespace Algo 
{
    std::deque<Command*> SelectionSort(std::vector<short> data, bool commands = true);
    std::deque<Command*> InsertionSort(std::vector<short> data, bool commands = true);
}