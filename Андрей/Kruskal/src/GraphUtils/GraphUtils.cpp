#include "GraphUtils.h"

void GraphUtils::getGraphFromStream(std::istream& input, std::ostream& output, Graph& graph)
{
    std::string line;
    int index = 0;

    output << "Now, pass graph in type of `1 -> 2 (3)`. 1 node is pointed on 2 with value 3" << std::endl;

    while (std::getline(input, line) && line != "###")
    {
        std::regex regex("^(\\d+)\\W+(\\d+)\\W+(\\d+)", std::regex_constants::icase);
        std::smatch matches;

        std::regex_search(line, matches, regex);
        if (matches.empty())
        {
            continue;
        }

        int firstNode = std::stoi(matches[1]);
        int secondNode = std::stoi(matches[2]);
        int value = std::stoi(matches[3]);

        graph.addWeightedEdge(firstNode, secondNode, value);
        index++;
    }
}
