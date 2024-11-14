#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

struct Trans {
    std::string nextState;
    std::string output;
};

struct StateOut {
    std::string output;
    std::string state;
};

#endif