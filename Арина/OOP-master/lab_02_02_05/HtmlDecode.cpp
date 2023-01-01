#include "HtmlDecode.h"

const char DECODED_HTML_START_SYMBOL = '&';
const char DECODED_HTML_END_SYMBOL = ';';

const std::map <std::string, std::string> HTML_ENTITIES = {
        {"&quot;", "\""},
        {"&apos;", "\'"},
        {"&lt;",   "<"},
        {"&gt;",   ">"},
        {"&amp;",  "&"}
};

void FlushResult(const std::string &str, std::string &result)
{
    if (!str.empty())
    {
        result += str;
    }
}

void ResetEncodedStr(std::string &str, std::string &result)
{
    FlushResult(str, result);
    str.clear();
}

void ProcessEncodedStr(std::string &encodedStr, std::string::iterator &it, bool &isStarted, std::string &result)
{
    encodedStr += *it;
    if (*it != DECODED_HTML_END_SYMBOL)
    {
        return;
    }

    isStarted = false;
    auto decodedStr = HTML_ENTITIES.find(encodedStr);
    if (decodedStr != HTML_ENTITIES.end())
    {
        FlushResult(decodedStr->second, result);
        encodedStr.clear();
    }
    else
    {
        ResetEncodedStr(encodedStr, result);
    }
}

std::string HtmlDecode(std::string &htmlString)
{
    bool isStarted = false;
    std::string encodedStr = "";
    std::string result = "";

    for (std::string::iterator it = htmlString.begin(); it != htmlString.end(); ++it)
    {
        if (*it == DECODED_HTML_START_SYMBOL)
        {
            isStarted = true;
            ResetEncodedStr(encodedStr, result);
        }

        if (isStarted)
        {
            ProcessEncodedStr(encodedStr, it, isStarted, result);
        }
        else
        {
            result += *it;
        }
    }

    ResetEncodedStr(encodedStr, result);

    return result;
}