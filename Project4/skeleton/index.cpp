#include "index.h"
#include "multimap.h"
#include "tokenizer.h"

Index::Index()
    :tokens(create_tokenizer()), multi(create_multimap())
{
    // TODO: implement
}

Index::~Index()
{
    // TODO: implement
    delete tokens;
    delete multi;
}

int Index::build_index(const std::string& path)
{
	// TODO: replace this line with your implementation
    std::vector<std::string> files = get_filenames(path);
    int count = 0;
    for(int i = 0; i < files.size(); i++)
    {
        add_doc(files[i]);
        count++;
    }
    return count;
}

void Index::add_doc(const std::string& doc_file)
{
    // TODO: implement
    std::ifstream infile(doc_file);    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
        std::cerr << "Error: Cannot open " << doc_file << "!" << std::endl;
        return;
    }
    std::string s;
    while (getline(infile, s))
    {
        if ( ! infile)
            std::cerr << "End of file when trying to read a string" << std::endl;
        tokens->tokenize(s);
        std::string token;
        while(tokens->next(token) == true)
        {
            multi->put(token, doc_file);
        }
    }
}

std::vector<std::string> Index::query(const std::vector<std::string>& terms) const
{
	// TODO: replace this line with your implementation
    if(terms.empty() == true)
    {
        return {};
    }
    std::set<std::string> result;
    std::string term = terms[0];
    std::string term1 = "";
    for(auto& x: term)
    {
        term1 += tolower(static_cast<unsigned char>(x));
    }
    MultimapBase::IteratorBase* it = multi->get(term1);
    std::string doc;
    while(it->next(doc) == true)
    {
        result.insert(doc);
    }
    delete it;
    for(int i = 1; i < terms.size(); i++)
    {
        std::set<std::string> temp;
        std::string t = terms[i];
        std::string t1 = "";
        for(auto& x: t)
        {
            t1 += tolower(static_cast<unsigned char>(x));
        }
        MultimapBase::IteratorBase* it2 = multi->get(t1);
        while(it2->next(doc) == true)
        {
            if (result.find(doc) != result.end())
            {
                temp.insert(doc);
            }
        }
        delete it2;
        result = temp;
    }
    std::vector<std::string> actualResult;
    for(std::string s : result)
    {
        actualResult.push_back(s);
    }
    return actualResult;
}
