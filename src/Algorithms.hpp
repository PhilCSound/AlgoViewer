#pragma once
#include "LookCommand.hpp"
#include "SwapCommand.hpp"
#include <algorithm>
#include <queue>

namespace Algo
{
    std::queue<Command*> SelectionSort(std::vector<short> data);
}