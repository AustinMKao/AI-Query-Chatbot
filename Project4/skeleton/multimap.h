#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "provided.h"
#include <string>

class Multimap : public MultimapBase
{
private:
    struct Node
    {
        Node(const std::string& t, const std::string& v)
        {
            term = t;
            value = v;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
        std::string term;
        std::string value;
        Node* left;
        Node* right;
        Node* parent;
    };
public:
    // Nested Iterator class
    class Iterator : public MultimapBase::IteratorBase
    {
    public:
		// TODO: declare at least one constructor
        Iterator(Node* c, const std::string& k);
        virtual ~Iterator();
        virtual bool next(std::string& value);

    private:
        // TODO: add private members
        Node* current;
        std::string key;
    };

    Multimap();
    virtual ~Multimap();
    virtual void put(const std::string& key, const std::string& value);
    virtual MultimapBase::IteratorBase* get(const std::string& key) const;
    virtual bool empty() const;
    virtual int size() const;

private:
    // TODO: add private members
    Node* root;
    int treeSize;
    
    void clearTree(Node* n);
    
};

#endif // MULTIMAP_H
