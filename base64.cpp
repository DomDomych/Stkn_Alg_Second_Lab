#include <string>
#include "stop.hpp"
#include "base64.hpp"

std::string create_line(Stop* current){
    std::string line = 
                        current->name+" "+
                        std::to_string(current->coord_x)+" "+
                        std::to_string(current->coord_y)+" "+
                        std::to_string(current->time);
    return line;
}

const std::string Base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Encode(std::string& input){
    std::string result;
    int val=0,bits=-6;

    for(unsigned char c:input){
        val = (val<<8)+c;
        bits+=8;
        while(bits>=0){
            result.push_back(Base64[(val >> bits) & 0x3F]);
            bits -= 6;
        }
    }
    if (bits > -6)
    {
        result.push_back(Base64[((val << 8) >> (bits + 8)) & 0x3F]);
    }

    while (result.size() % 4)
    {
        result.push_back('=');
    }
    return result;
}