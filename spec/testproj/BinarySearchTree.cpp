/*
 * BinarySearchTree.cpp
 *
 * COMP15
 * Spring 2018
 *
 * Implementation for BST class.
 * Inherits from BinaryTree class.
 *
 * Beyonce also wants you to be a SURVIVOR.
 *
 * You thought you'd be stressed but you're chillin'.
 */

#include <cstddef>
#include "BinarySearchTree.h"

// Member function definitions
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

// Destructor requires no action, base class handles it
BinarySearchTree::~BinarySearchTree()
{
    // Do nothing
}

// Function to insert into a BST
// Throws exception if full
// Calls wrapper function for recursion
void BinarySearchTree::insert_item(TreeItem item)
{
    if (is_full())
        throw FullTree();
    else
        insert_bst(root, item);
}

// Wrapper function for insert
void insert_bst(BinaryNode *&tree, TreeItem item)
{
    if (tree == NULL)
    {
        tree = new BinaryNode; // this part is why pass by ref
        tree->right = NULL;
        tree->left = NULL;
        tree->info = item;
    }
    else if (item < tree->info)
    {
        insert_bst(tree->left, item);
    }
    else if (item > tree->info)   
    {
        insert_bst(tree->right, item);
    }
}

// Copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &from)
{
    root = bst_copy_helper(from.root);
}

// Same copy-swap idiom from the base class, see explanation there
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree from)
{
    swap(this->root, from.root);
    return *this;
}

// Attempts to remove an item
// Can throw EmptyTree if the tree is empty
void BinarySearchTree::remove_item(TreeItem item)
{
    if (is_empty())
        throw EmptyTree();
    else
    {
        find_and_remove(item, root);
    }
}

// Tries to find a node and remove it
// if the item is found, set the parent to a child, if one exists
void find_and_remove(const TreeItem item, BinaryNode *&node)
{
    if (node == NULL) return;
    if (node->info == item) {
        if (node->left == NULL) {
            if (node->right == NULL) {
                delete node;
                node = NULL;        // If both children are nonexistant
                return;             // Set ptr to null and return
            } else {
                BinaryNode *to_be_deleted = node;
                node = node->right;
                delete to_be_deleted;
                return;             // If a child exists, set ptr to it
            }
        } else {
            BinaryNode *to_be_deleted = node;
            node = node->left;
            destroy(to_be_deleted->right);  // Right side always gets removed
            delete to_be_deleted;           // Assuming left exists
            return;
        }
    }
}

// Attempts to match the given item with one in the tree
// Sets found to true if the item is found
void BinarySearchTree::find_item(TreeItem &item, bool &found) const
{
    found = bst_find_helper(item, root);
}

// Base case: the node is at the end, or the item is found
// otherwise recurse by calling itself on the children
bool bst_find_helper(TreeItem &item, BinaryNode *node)
{
    if (node == NULL) return false;
    if (node->info == item) {
        item = node->info;
        return true;
    } 
    return bst_find_helper(item, node->left) 
        or bst_find_helper(item, node->right);
    // Note: or is lazy evaluated so this will never match
    // two values
}

// Allocates a new node for each element in the 'from' tree
// Base case: 'from' tree is empty
// otherwise assign a new node the value and children of its counterpart
BinaryNode *bst_copy_helper(const BinaryNode *from)
{
    if (from == NULL)
        return NULL;

    BinaryNode *new_node = new BinaryNode;
    new_node->info = from->info;
    new_node->left  = bst_copy_helper(from->left);
    new_node->right = bst_copy_helper(from->right);

    return new_node;
}
