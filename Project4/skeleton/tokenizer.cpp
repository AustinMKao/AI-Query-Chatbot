#include "tokenizer.h"

Tokenizer::Tokenizer()
    :tokens(""), position(0)
{}

void Tokenizer::tokenize(const std::string& input)
{
    tokens = "";
    for(auto x: input)
    {
        tokens += tolower(static_cast<unsigned char>(x));
    }
    position = 0;
}

bool Tokenizer::next(std::string& token)
{
    token = "";
    while(position < tokens.size() && isalpha(static_cast<unsigned char>(tokens[position])) == false && isdigit(static_cast<unsigned char>(tokens[position])) == false)
    {
        position++;
    }
    while(position < tokens.size() && (isalpha(static_cast<unsigned char>(tokens[position])) == true || isdigit(static_cast<unsigned char>(tokens[position]))))
    {
        token += tokens.at(position);
        position++;
    }
    if(token.empty() == true)
    {
        return false;
    }
    return true;
}
