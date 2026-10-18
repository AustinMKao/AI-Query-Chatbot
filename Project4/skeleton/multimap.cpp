#include "multimap.h"
#include <string>

// TODO: implement at least one constructor
Multimap::Iterator::Iterator(Node* c, const std::string& k)
    :current(c), key(k)
{
//    // TODO: implement
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
    // TODO: implement
}

Multimap::~Multimap()
{
    // TODO: implement
    clearTree(root);
}

void Multimap::put(const std::string& key, const std::string& value)
{
    // TODO: implement
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
	// TODO: replace this line with your implementation
    Node* cur = root;
    if(cur == nullptr)
    {
        return new Iterator(nullptr, key);
    }
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
            while(cur->left != nullptr && cur->left->term == key)
            {
                cur = cur->left;
            }
            return new Iterator(cur, key);
        }
        
    }
    return new Iterator(nullptr, key);
}

bool Multimap::empty() const
{
	// TODO: replace this line with your implementation
    if(root == nullptr)
    {
        return true;
    }
    return false;
}

int Multimap::size() const
{
	// TODO: replace this line with your implementation
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
