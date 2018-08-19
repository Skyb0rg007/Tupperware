/*
 * Comp 15
 * Skye Soss
 *
 * BinaryTree.h
 *
 * Interface for base class Binary Tree
 *
 * COMP15
 * Spring 2018
 *
 * Why don't you make like a tree...
 * and get outta here.
 */

#include <iostream>
#include "Queue.h"
using namespace std;

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

class FullTree : public exception
{
public:
    const char *what () const throw() { return "Full Tree!\n"; }
};

class EmptyTree : public exception
{
public:
    const char * what() const throw() { return "Empty Tree!\n"; }
};

// Prototypes for recursive wrapper functions
void destroy(BinaryNode*&);
int count_nodes(BinaryNode*);
TreeItem return_leftmost(BinaryNode*);
void print_inorder(BinaryNode *, ostream &);
void print_preorder(BinaryNode*, ostream&);
void print_postorder(BinaryNode*, ostream&);
void insert_bt(BinaryNode*&, TreeItem);
void find_bt(BinaryNode*, TreeItem&, bool&);
void remove_bt(BinaryNode*&, TreeItem);
void delete_deepest(BinaryNode*&, BinaryNode*&);
BinaryNode *copy_helper(BinaryNode*);
int num_leaves_helper(const BinaryNode*);
int height_helper(const BinaryNode*);
int total_age_helper(int&, const BinaryNode*);
BinaryNode *rightmost_helper(BinaryNode*);
void print_helper(ostream &output, const BinaryNode*);

class BinaryTree
{
public:
    BinaryTree();

    // Needs friend to access root from operator<<
    friend ostream &operator<<(ostream&, 
            const BinaryTree&);

    // virtual destructor to ensure
    // derived class version runs first
    virtual ~BinaryTree();

    // Copy and assignment operators
    BinaryTree(const BinaryTree &);
    BinaryTree& operator=(const BinaryTree);

    // implemented in base class, and
    // inherited by all derived classes
    int get_length() const;
    TreeItem get_leftmost() const;
    void inorder(ostream &) const;
    void preorder(ostream &) const;
    void postorder(ostream &) const;
    bool is_full() const;
    bool is_empty() const;
    int num_leaves() const;
    int height() const;
    double average_age() const;
    TreeItem rightmost_node() const;
    void print_root(ostream&) const;

    // virtual function is defined in base class,
    // overridden in derived class
    virtual void insert_item(TreeItem);
    virtual void find_item(TreeItem &, bool &) const;
    virtual void remove_item(TreeItem);

protected:
    BinaryNode *root;
};

#endif
