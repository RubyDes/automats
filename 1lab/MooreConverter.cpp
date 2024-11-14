#include "MooreConverter.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

void MooreConverter::convert(const std::string& inputFile, const std::string& outputFile) {
    StateList outputSignals;
    StateList stateNames;
    std::vector<std::vector<std::string>> transitionTable;

    readMoore(inputFile, outputSignals, stateNames, transitionTable);
    writeMealy(outputFile, outputSignals, stateNames, transitionTable);
}

void MooreConverter::readMoore(const std::string& inputFile, StateList& outputSignals, StateList& stateNames, std::vector<std::vector<std::string>>& transitionTable) {
    std::ifstream input(inputFile);
    std::string line;

    if (std::getline(input, line)) {
        outputSignals = parseCSVLine(line.substr(1));
    }

    if (std::getline(input, line)) {
        stateNames = parseCSVLine(line.substr(1));
    }

    while (std::getline(input, line)) {
        transitionTable.push_back(parseCSVLine(line));
    }

    input.close();
}

void MooreConverter::writeMealy(const std::string& outputFile, const StateList& outputSignals, const StateList& stateNames, const std::vector<std::vector<std::string>>& transitionTable) {
    std::ofstream output(outputFile);

    output << ";";
    for (const auto& state : stateNames) {
        output << replaceQWithA(state) << ";";
    }
    output << "\n";

    std::unordered_map<std::string, std::string> stateOutputMapping;
    for (size_t i = 0; i < stateNames.size(); ++i) {
        stateOutputMapping[stateNames[i]] = outputSignals[i];
    }

    for (const auto& row : transitionTable) {
        output << row[0] << ";";
        for (size_t i = 1; i < row.size(); ++i) {
            output << replaceQWithA(row[i]) << "/" << stateOutputMapping[row[i]] << ";";
        }
        output << "\n";
    }

    output.close();
}

std::string MooreConverter::replaceQWithA(const std::string& state) {
    std::string result = state;
    for (char& c : result) {
        if (c == 'q') {
            c = 'a';
        }
    }
    return result;
}