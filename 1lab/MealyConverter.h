#pragma once
#ifndef MEALYCONVERTER_H
#define MEALYCONVERTER_H

#include "AutomatonConverter.h"

class MealyConverter : public AutomatonConverter {
public:
    void convert(const std::string& inputFile, const std::string& outputFile) override;

private:
    void readMealy(const std::string& inputFile, StateList& inputStates, std::vector<std::string>& inputs, std::vector<std::vector<StateOut>>& transitionTable, std::vector<StateOut>& uniqueTransitions);
    void writeMoore(const std::string& outputFile, const std::vector<StateOut>& uniqueTransitions, const std::vector<std::string>& inputs, const std::vector<std::vector<StateOut>>& transitionTable, const StateList& inputStates);
    void sortPairs(std::vector<StateOut>& uniqueTransitions, const StateList& inputStates);
};

#endif