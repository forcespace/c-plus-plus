#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

struct Tree
{
    std::string name;
    std::vector<Tree *> sons;
    int level{};
    int value{};
};

void showLevel(int level);

void showTree(Tree *top);

void pushToTree(Tree *top, Tree *newNode);

int main()
{

    //    std::ifstream file;
//    file.open("src/file.txt");

//    if (!file.is_open())
//    {
//        std::cout << "File not read" << std::endl;
//        return 0;
//    }

//    std::string line2;
//    while (file >> line2)
//    {
//        std::cout << line2 << std::endl;
//    }

//    std::queue<int> q;

    Tree *top = new Tree;

    std::string line;
    const char levelSymbol = '*';
    const std::string endTree = "#";
    size_t level;
    bool vertexIsOr = false;


    while (std::getline(std::cin, line) && line != endTree)
    {
        level = std::count(line.begin(), line.end(), levelSymbol);
        line.erase(line.begin(), line.begin() + (int) level);
        vertexIsOr = line.find("||") != std::string::npos;

        std::cout << level;
        std::cout << " - " << line[0];


        if (vertexIsOr)
        {
            std::cout << " OR" << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }


    return 0;
}

void pushToTree(Tree *top, Tree *newNode)
{

}

void showLevel(int level)
{
    for (auto index = 0; index < level; index++)
    {
        std::cout << std::endl;
        std::cout << '-' << std::endl;
    }
}

void showTree(Tree *top)
{
    if (top == nullptr)
    {
        return;
    }

    showLevel(top->level);
    std::cout << top->value << std::endl;

    for (auto index = 0; index < top->sons.size(); index++)
    {
        showTree(top->sons[index]);
    }
}