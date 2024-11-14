#include "MealyConverter.h"
#include <fstream>
#include <algorithm>

void MealyConverter::convert(const std::string& inputFile, const std::string& outputFile) {
    StateList inputStates;
    std::vector<std::string> inputs;
    std::vector<std::vector<StateOut>> transitionTable;
    std::vector<StateOut> uniqueTransitions;

    readMealy(inputFile, inputStates, inputs, transitionTable, uniqueTransitions);
    sortPairs(uniqueTransitions, inputStates);
    writeMoore(outputFile, uniqueTransitions, inputs, transitionTable, inputStates);
}

void MealyConverter::readMealy(const std::string& inputFile, StateList& inputStates, std::vector<std::string>& inputs, std::vector<std::vector<StateOut>>& transitionTable, std::vector<StateOut>& uniqueTransitions) {
    std::ifstream input(inputFile);
    std::string headerLine;
    getline(input, headerLine);
    inputStates = parseCSVLine(headerLine.substr(1));

    std::string line;
    while (getline(input, line)) {
        std::vector<StateOut> transitions;
        inputs.push_back(line.substr(0, line.find(';')));
        line = line.substr(line.find(';') + 1);

        std::string transitionStr;
        StateOut transition;
        line += ";";

        while (line.find(';') != std::string::npos) {
            transitionStr = line.substr(0, line.find(';'));
            line = line.substr(line.find(';') + 1);

            transition.output = transitionStr.substr(transitionStr.find('/') + 1);
            transition.state = transitionStr.substr(0, transitionStr.find('/'));

            transitions.push_back(transition);

            if (findIndex(uniqueTransitions, transition) == uniqueTransitions.end()) {
                uniqueTransitions.push_back(transition);
            }
        }
        transitionTable.push_back(transitions);
    }
    input.close();
}

void MealyConverter::writeMoore(const std::string& outputFile, const std::vector<StateOut>& uniqueTransitions, const std::vector<std::string>& inputs, const std::vector<std::vector<StateOut>>& transitionTable, const StateList& inputStates) {
    std::ofstream output(outputFile);

    output << ";";
    for (const auto& transition : uniqueTransitions) {
        output << transition.output << ";";
    }
    output << "\n;";

    for (size_t i = 0; i < uniqueTransitions.size(); ++i) {
        output << "q" << i << ";";
    }
    output << "\n";

    for (size_t i = 0; i < inputs.size(); ++i) {
        output << inputs[i] << ";";
        for (const auto& uniqueTransition : uniqueTransitions) {
            StateOut tempTransition = transitionTable[i][std::find(inputStates.begin(), inputStates.end(), uniqueTransition.state) - inputStates.begin()];
            int transitionIndex = findIndex(uniqueTransitions, tempTransition);
            if (transitionIndex != -1) {
                output << "q" << transitionIndex << ";";
            }
            else {
                output << ";";
            }
        }
        output << "\n";
    }

    output.close();
}

void MealyConverter::sortPairs(std::vector<StateOut>& uniqueTransitions, const StateList& inputStates) {
    std::sort(uniqueTransitions.begin(), uniqueTransitions.end(), [](const StateOut& a, const StateOut& b) {
        return a.state < b.state;
        });

    if (uniqueTransitions[0].state != inputStates[0]) {
        uniqueTransitions.insert(uniqueTransitions.begin(), { "-", inputStates[0] });
    }
}