#include "Framework.h"

std::vector<std::string> Utility::SplitString(std::string source, const std::string& delim)
{
    std::vector<std::string> result;

    size_t cutAt = 0;

    while ((cutAt = source.find_first_of(delim)) != source.npos)
    {
        if (cutAt > 0)
            result.push_back(source.substr(0, cutAt));

        source = source.substr(cutAt + 1);
    }

    if (source.size() > 0)
        result.push_back(source);

    return result;
}
