#include "agent.h"
#include "index.h"
#include "tokenizer.h"
#include <iostream>
#include <fstream>

Agent::Agent(const IndexBase& index)
    :m_index(index), termsFile(""), summarizeFile(""), tokens(*create_tokenizer())
{
    // TODO: implement
}

Agent::~Agent()
{
    // TODO: implement
    delete &tokens;
}

bool Agent::load_prompts(const std::string& terms_file, const std::string& summarize_file)
{
	// TODO: replace this line with your implementation
    std::ifstream t(terms_file);
    std::ifstream s(summarize_file);
    if(!t || !s)
    {
        return false;
    }
    termsFile = terms_file;
    summarizeFile = summarize_file;
    return true;
}

bool Agent::query(const std::string& question, std::string& answer)
{
	// TODO: replace this line with your implementation
    std::ifstream infile(termsFile);    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
        return false;
    }
    std::string s = "";
    std::string temp = "";
    while (getline(infile, temp))
    {
        s += temp + "\n";
    }
    std::string prompt = "";
    int index = s.find("{query}");
    for(int i = 0; i < s.size(); i++)
    {
        if(i == index)
        {
            prompt += question;
            i += 6;
            continue;
        }
        prompt += s.at(i);
    }
    std::string response;
    if(query_llm("terms", prompt, response) == false)
    {
        return false;
    }
    std::vector<std::vector<std::string>> groups;
    int start = 0;
    while(start < response.size())
    {
        int end = response.find("\n", start);
        std::string line;
        if(end == std::string::npos)
        {
            line = response.substr(start);
            start = response.size();
        }
        else
        {
            line = response.substr(start, end-start);
            start = end + 1;
        }
        tokens.tokenize(line);
        std::vector<std::string> group;
        std::string term;
        while(tokens.next(term))
        {
            group.push_back(term);
        }
        if(group.empty() == false)
        {
            groups.push_back(group);
        }
    }
    if(groups.empty() == true)
    {
        return false;
    }
    std::set<std::string> docs;
    for(const std::vector<std::string>& group : groups)
    {
        std::vector<std::string> doc = m_index.query(group);
        for(int i = 0; i < doc.size(); i++)
        {
            docs.insert(doc[i]);
        }
    }
    std::vector<std::string> docs1;
    for(std::string s : docs)
    {
        docs1.push_back(s);
    }
    if(docs1.empty() == true)
    {
        return false;
    }
    std::vector<std::string> res;
    int limit = 10;
    if(docs1.size() < 10)
    {
        limit = docs1.size();
    }
    for(int i = 0; i < limit; i++)
    {
        std::ifstream file(docs1[i]);
        if(!file)
        {
            continue;
        }
        std::string text = "";
        std::string line = "";
        while(getline(file, line))
        {
            text += line + "\n";
        }
        res.push_back(text);
    }
    std::ifstream infile2(summarizeFile);    // infile is a name of our choosing
    if ( ! infile2 )                // Did opening the file fail?
    {
        return false;
    }
    std::string s1 = "";
    std::string temp2 = "";
    while (getline(infile2, temp2))
    {
        s1 += temp2 + "\n";
    }
    int index1 = s1.find("{query}");
    std::string tempPrompt = "";
    for(int i = 0; i < s1.size(); i++)
    {
        if(i == index1)
        {
            tempPrompt += question;
            i += 6;
            continue;
        }
        tempPrompt += s1.at(i);
    }
    int index2 = tempPrompt.find("{documents}");
    std::string finalPrompt = "";
    for(int i = 0; i < tempPrompt.size(); i++)
    {
        if(i == index2)
        {
            i += 10;
            for(int j = 0; j < res.size(); j++)
            {
                finalPrompt += res[j] + "\n";
            }
            continue;
        }
        finalPrompt += tempPrompt.at(i);
    }
    if(query_llm("summarize", finalPrompt, answer) == false)
        return false;
    return true;
}
