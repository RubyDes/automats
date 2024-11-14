#include "AutomatonConverter.h"
#include <algorithm>
#include <sstream>

bool AutomatonConverter::isEqual(const StateOut& transition1, const StateOut& transition2) {
    return transition1.state == transition2.state && transition1.output == transition2.output;
}

std::vector<StateOut>::iterator AutomatonConverter::findIndex(std::vector<StateOut>& transitions, const StateOut& transition) {
    return std::find_if(transitions.begin(), transitions.end(), [&](const StateOut& t) {
        return isEqual(t, transition);
        });
}

int AutomatonConverter::findIndex(const std::vector<StateOut>& transitions, const StateOut& transition) {
    for (size_t i = 0; i < transitions.size(); ++i) {
        if (isEqual(transitions[i], transition)) {
            return i;
        }
    }
    return -1;
}

StateList AutomatonConverter::parseCSVLine(const std::string& line) {
    StateList elements;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ';')) {
        elements.push_back(item);
    }
    return elements;
}