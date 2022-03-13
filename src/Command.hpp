#pragma once
#include "DataDeck.hpp"

class Command
{
public:
    virtual void execute(DataDeck& data) = 0;
};