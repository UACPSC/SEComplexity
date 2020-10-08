/*
    srcComplexity.cpp

    Calculates the cyclomatic complexity of source code.

    Source code must be in srcML format
*/

#include <iostream>
#include <string>

#include "srcMLXPathCount.hpp"

int main(int argc, const char* argv[]) {

    // number of arguments is 0..1
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " <srcML_filename>" << '\n'
                  << "       " << argv[0] << '\n';
        return 1;
    }

    // input is filename, or stdin as "-"
    std::string filename = argc == 2 ? argv[1] : "-";

    // use the number of conditions to calculate cyclomatic complexity
    int conditionCount = srcMLXPathCount(argv[1], "count(//src:condition)");
    if (conditionCount < 0) {
        std::cerr << "Error in applying xpath\n";
        return 1;
    }
    int complexity = conditionCount + 1;

    // output the cyclomatic complexity
    std::cout << complexity << '\n';

    return 0;
}
