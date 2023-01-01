#include <iostream>
#include "src/GraphUtils/GraphUtils.h"

int main()
{
    int size;
    std::string line;
    std::cout << "Pass size of graph" << std::endl;
    std::getline(std::cin, line);
    size = std::stoi(line);

    auto graph = new Graph(size);
    GraphUtils::getGraphFromStream(std::cin, std::cout, *graph);

    graph->runKraskalAlgorithm();

    return 0;
}
