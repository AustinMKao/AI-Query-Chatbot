#include "multimap.h"
#include <string>

Multimap::Iterator::Iterator(Node* c, const std::string& k)
    :current(c), key(k)
{
}

Multimap::Iterator::~Iterator()
{}

bool Multimap::Iterator::next(std::string& value)
{
	if(current == nullptr)
    {
        return false;
    }
    value = current->value;
    Node* next;
    if(current->right != nullptr)
    {
        next = current->right;
        while(next->left != nullptr)
        {
            next = next->left;
        }
    }
    else
    {
        next = current->parent;
        Node* child = current;
        while(next != nullptr && next->right == child)
        {
            child = next;
            next = next->parent;
        }
    }
    if(next == nullptr || next->term != key)
    {
        current = nullptr;
        return true;
    }
    current = next;
    return true;
}


Multimap::Multimap()
    :root(nullptr), treeSize(0)
{
}

Multimap::~Multimap()
{
    clearTree(root);
}

void Multimap::put(const std::string& key, const std::string& value)
{
    if(root == nullptr)
    {
        root = new Node(key, value);
        treeSize++;
        return;
    }
    Node* current = root;
    for(;;)
    {
        if(key == current->term && value == current->value)
        {
            return;
        }
        else if(key < current->term || (key == current->term && value < current->value))
        {
            if(current->left != nullptr)
            {
                current = current->left;
            }
            else
            {
                current->left = new Node(key, value);
                current->left->parent = current;
                treeSize++;
                return;
            }
        }
        else
        {
            if(current->right != nullptr)
            {
                current = current->right;
            }
            else
            {
                current->right = new Node(key, value);
                current->right->parent = current;
                treeSize++;
                return;
            }
        }
    }
}

MultimapBase::IteratorBase* Multimap::get(const std::string& key) const
{
    Node* cur = root;
    Node* first = nullptr;
    while(cur != nullptr)
    {
        if(key < cur->term)
        {
            cur = cur->left;
        }
        else if(key > cur->term)
        {
            cur = cur->right;
        }
        else
        {
            first = cur;
            cur = cur->left;
        }
        
    }
    return new Iterator(first, key);
}

bool Multimap::empty() const
{
    if(root == nullptr)
    {
        return true;
    }
    return false;
}

int Multimap::size() const
{
    return treeSize;
}

void Multimap::clearTree(Node* n)
{
    if(n == nullptr)
    {
        return;
    }
    
    clearTree(n->left);
    clearTree(n->right);
    
    delete n;
}
