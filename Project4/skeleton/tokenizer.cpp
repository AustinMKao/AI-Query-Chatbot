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
    while(position < tokens.size() && !isalnum(static_cast<unsigned char>(tokens[position])))
    {
        position++;
    }
    while(position < tokens.size() && isalnum(static_cast<unsigned char>(tokens[position])))
    {
        token += tokens.at(position);
        position++;
    }
    return !token.empty();
}
