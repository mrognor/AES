#include "base64.h"

unsigned char ConvertSymbol(unsigned char c)
{
    if (c >= 48 && c <= 57)
        return c += 4; // -48 + 26*2

    if (c >= 65 && c <= 90)
        return c -= 65;

    if (c >= 97 && c <= 122)
        return (c -= 71); // 97 - 26

    if (c == '+')
        return 62;
    
    if (c == '/')
        return 63;

    return 0;
}

std::string RegularStringToBase64String(const std::string& str)
{
    std::string res;

    if (str.length() >= 3)
    {
        for (uint64_t i = 0; i <= str.length() - 3; i += 3)
        {
            res += Symbols[(unsigned char)str[i] >> 2];
            res += Symbols[(((unsigned char)str[i] & 0b00000011) << 4) + ((unsigned char)str[i + 1] >> 4)];
            res += Symbols[(((unsigned char)str[i + 1] & 0b00001111) << 2) + ((unsigned char)str[i + 2] >> 6)];
            res += Symbols[(unsigned char)str[i + 2] & 0b00111111];
        }
    }

    if (str.length() % 3 == 1)
    {
        res += Symbols[(unsigned char)str[str.length() - 1] >> 2];
        res += Symbols[(((unsigned char)str[str.length() - 1] & 0b00000011) << 4)];
        res += "==";
    }
    else if (str.length() % 3 == 2)
    {
        res += Symbols[(unsigned char)str[str.length() - 2] >> 2];
        res += Symbols[(((unsigned char)str[str.length() - 2] & 0b00000011) << 4) + ((unsigned char)str[str.length() - 1] >> 4)];
        res += Symbols[(((unsigned char)str[str.length() - 1] & 0b00001111) << 2)];
        res += "=";
    }

    return res;
}

std::string Base64StringToRegularString(const std::string& str)
{
    std::string res;
    
    for (uint64_t i = 0; i <= str.length() - 4; i += 4)
    {
        res += ((ConvertSymbol(str[i]) << 2) + (ConvertSymbol(str[i + 1]) >> 4));

        if (str[i + 2] == '=')
            break;
        else
            res += (((ConvertSymbol(str[i + 1]) & 0b00001111) << 4) + (ConvertSymbol(str[i + 2]) >> 2));

        if (str[i + 3] == '=')
            break;
        else
            res += (((ConvertSymbol(str[i + 2]) & 0b00000011) << 6) + ConvertSymbol(str[i + 3]));
    }

    return res;
}