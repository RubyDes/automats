#pragma once
#ifndef AUTOMATONCONVERTER_H
#define AUTOMATONCONVERTER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Transition.h"

using TransitionTable = std::vector<std::vector<Trans>>;
using StateList = std::vector<std::string>;

class AutomatonConverter {
public:
    virtual ~AutomatonConverter() = default;
    virtual void convert(const std::string& inputFile, const std::string& outputFile) = 0;

protected:
    bool isEqual(const StateOut& transition1, const StateOut& transition2);
    std::vector<StateOut>::iterator findIndex(std::vector<StateOut>& transitions, const StateOut& transition);
    int findIndex(const std::vector<StateOut>& transitions, const StateOut& transition);
    StateList parseCSVLine(const std::string& line);
};

#endif