#include <iostream>
#include "MealyConverter.h"
#include "MooreConverter.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <convertingType > <input-file> <output-file>\n";
        return 1;
    }

    std::string convertingType  = argv[1];
    AutomatonConverter* converter = nullptr;

    if (convertingType  == "mealy-to-moore") {
        converter = new MealyConverter();
    }
    else if (convertingType  == "moore-to-mealy") {
        converter = new MooreConverter();
    }
    else {
        std::cerr << "Invalid convertingType. Prit mealy-to-moore or moore-to-mealy";
        return 1;
    }

    converter->convert(argv[2], argv[3]);
    delete converter;

    return 0;
}