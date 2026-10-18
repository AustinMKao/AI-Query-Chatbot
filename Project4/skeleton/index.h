#ifndef INDEX_H
#define INDEX_H

#include "provided.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

class Index : public IndexBase
{
public:
    Index();
    virtual ~Index();
    virtual int build_index(const std::string& path);
    virtual void add_doc(const std::string& doc_file);
    virtual std::vector<std::string> query(const std::vector<std::string>& terms) const;

private:
    // TODO: add private members
    TokenizerBase* tokens;
    MultimapBase* multi;
};

#endif // INDEX_H
