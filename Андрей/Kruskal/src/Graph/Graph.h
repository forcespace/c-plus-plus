#pragma once

#include <vector>
#include <iomanip>
#include <iostream>

class Graph
{
public:
    explicit Graph(int size)
    {
        parent = new int[size];
        graphInMatrixView.emplace_back(std::pair<std::vector<int>, int>({}, 0));

        for (int index = 0; index < size; index++)
        {
            parent[index] = index;
            graphInMatrixView.emplace_back(std::pair<std::vector<int>, int>({}, index + 1));
            graphInMatrixView.at(index + 1).first.resize(size + 1, 0);
        }
    }

    void addWeightedEdge(int firstNode, int secondNode, int weight)
    {
        graph.emplace_back(std::make_pair(weight, Edge(firstNode, secondNode)));
        graphInMatrixView.at(firstNode).first.at(secondNode) = weight;
        graphInMatrixView.at(secondNode).first.at(firstNode) = weight;
    }

    int findParentNode(int index)
    {
        return index == parent[index] ? index : findParentNode(parent[index]);
    }

    void unionSet(int first, int last)
    {
        parent[first] = parent[last];
    }

    void runKraskalAlgorithm()
    {
        int uRep, vRep, weight = 0;

        sort(graph.begin(), graph.end());

        for (auto& index : graph)
        {
            uRep = findParentNode(index.second.first);
            vRep = findParentNode(index.second.second);
            if (uRep != vRep)
            {
                result.emplace_back(index);
                weight += index.first;
                std::cout << "Found " << index.second.first << " - " << index.second.second << " : " << index.first << std::endl;
                unionSet(uRep, vRep);
            }
        }

        findLastWay(weight);
        std::cout << "Min weight: " << weight << std::endl;
    }

private:
    using Edge = std::pair<int, int>;

    void findLastWay(int& weight)
    {
        std::vector<int> visitedNodes(graph.size(), 0);

        for (auto& element : result)
        {
            visitedNodes[element.second.first]++;
            visitedNodes[element.second.second]++;
        }

        std::vector<int> findVector;
        for (auto index = 0; index < visitedNodes.size(); index ++)
        {
            if (visitedNodes[index] == 1)
            {
                findVector.emplace_back(index);
            }
        }

        if (findVector.size() == 2)
        {
            auto node = std::find_if(graph.begin(), graph.end(), [&findVector](std::pair<int, Edge> pair)
            { return (findVector[0] == pair.second.first && findVector[1] == pair.second.second) || (findVector[1] == pair.second.first && findVector[0] == pair.second.second); });

            if (node == graph.end())
            {
                return;
            }

            auto lastWay = findLastWayByDijkstra(node->second.first, node->second.second);
            std::cout << "Found " << node->second.first << " - " << node->second.second << " : " << lastWay << std::endl;
            weight += lastWay;
        }
    }

    int findLastWayByDijkstra(int startIndex, int endIndex)
    {
        std::vector<int> minimalValue;
        std::vector<int> visitedNodes;
        int temp, minindex, min;

        for (int index = 0; index < graphInMatrixView.size(); index++)
        {
            minimalValue.push_back(10000);
            visitedNodes.push_back(1);
        }

        minimalValue[startIndex] = 0;

        do
        {
            minindex = 10000;
            min = 10000;
            for (int index = 1; index < graphInMatrixView.size(); index++)
            {
                if ((visitedNodes.at(index) == 1) && (minimalValue.at(index) < min))
                {
                    min = minimalValue.at(index);
                    minindex = index;
                }
            }

            if (minindex != 10000)
            {
                for (int index = 1; index < graphInMatrixView.size(); index++)
                {
                    if (graphInMatrixView.at(minindex).first.at(index) > 0)
                    {
                        temp = min + graphInMatrixView.at(minindex).first.at(index);

                        if (temp < minimalValue.at(index))
                        {
                            minimalValue[index] = temp;
                        }
                    }
                }

                visitedNodes[minindex] = 0;
            }
        } while (minindex < 10000);

        return minimalValue[endIndex];
    }

    std::vector<std::pair<int, Edge>> graph = {};
    std::vector<std::pair<std::vector<int>, int>> graphInMatrixView = {};
    std::vector<std::pair<int, Edge>> result = {};
    int* parent;
};