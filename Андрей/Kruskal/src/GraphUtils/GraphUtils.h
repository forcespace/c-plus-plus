#pragma once

#include "./../Graph/Graph.h"
#include <iomanip>
#include <iostream>
#include <regex>

class GraphUtils
{
public:
    static void getGraphFromStream(std::istream& input, std::ostream& output, Graph& graph);
};
