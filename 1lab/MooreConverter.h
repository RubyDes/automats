#pragma once
#ifndef MOORECONVERTER_H
#define MOORECONVERTER_H

#include "AutomatonConverter.h"

class MooreConverter : public AutomatonConverter {
public:
    void convert(const std::string& inputFile, const std::string& outputFile) override;

private:
    void readMoore(const std::string& inputFile, StateList& outputSignals, StateList& stateNames, std::vector<std::vector<std::string>>& transitionTable);
    void writeMealy(const std::string& outputFile, const StateList& outputSignals, const StateList& stateNames, const std::vector<std::vector<std::string>>& transitionTable);
    std::string replaceQWithA(const std::string& state);
};

#endif