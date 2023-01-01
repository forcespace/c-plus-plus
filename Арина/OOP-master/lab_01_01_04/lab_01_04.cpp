#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replaceString;
};

std::optional <Args> ParseArgs(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cout << "Invalid arguments count\n"
                  << "Usage: lab_01_04.exe <input file> <output file> <searchString> <replacementString>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];
    return args;
}

std::string ReplaceString(const std::string &subject, const std::string &searchString, const std::string &replacementString)
{
    if (searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;
    std::string result;
    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        result.append(subject, pos, foundPos - pos);
        if (foundPos != std::string::npos)
        {
            result.append(replacementString);
            pos = foundPos + searchString.length();
        }
        else
        {
            break;
        }
    }
    return result;
}

void CopyFileWithReplace(std::istream &input, std::ostream &output,
                         const std::string &searchString, const std::string &replaceString)
{
    std::string line;

    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replaceString) << "\n";
    }
}

bool CopyFileWithReplaceWrapper(const std::string &inputFileName, const std::string &outputFileName,
                                const std::string &searchString, const std::string &replaceString)
{
    bool result = true;
    std::ifstream input;
    std::ofstream output;

    input.open(inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        result = false;
    }

    output.open(outputFileName);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << outputFileName << "' for writing\n";
        result = false;
    }

    CopyFileWithReplace(input, output, searchString, replaceString);

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        result = false;
    }

    if (!output.flush()) // Если не удалось сбросить данные на диск
    {
        std::cout << "Failed to write data to output file\n";
        result = false;
    }

    return result;
}

int main(int argc, char *argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    bool result = CopyFileWithReplaceWrapper(args->inputFileName, args->outputFileName, args->searchString, args->replaceString);

    return (result) ? 0 : 1;
}
