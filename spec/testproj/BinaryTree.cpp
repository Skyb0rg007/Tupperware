/*
 * BinaryTree.cpp
 *
 * Implementation for base class BinaryTree
 * Starter code for Project 1
 * 
 * Skye Soss
 * COMP15
 * Spring 2018
 *
 * What did the Binary Tree traversal get a dinner?
 *
 * The pre-fix menu!
 */

#include <cstddef>
#include "Queue.h"
#include "BinaryTree.h"
#include <utility>

// Simple maximum macro for use later
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

// Constructor
BinaryTree::BinaryTree()
{
    root = NULL;
}

// Destructor
BinaryTree::~BinaryTree()
{
    destroy(root);
}

// Function get_length (const)
// Counts the total number of nodes in the tree
int BinaryTree::get_length() const
{
    return count_nodes(root);
}

// Inorder traversal
void BinaryTree::inorder(ostream &out) const
{
    print_inorder(root, out);
}

// preorder traversal
void BinaryTree::preorder(ostream &out) const
{
    print_preorder(root, out);
}

// postorder traversal
void BinaryTree::postorder(ostream &out) const
{
    print_postorder(root, out);
}

// Function insert_item
// Checks for fullness, throws exception if necessary
// insert item into next open slot
void BinaryTree::insert_item(TreeItem item)
{
    if (is_full())
        throw FullTree();
    else
        insert_bt(root, item);
}

// Function find_item
// finds the given item using queue as auxiliary structure
void BinaryTree::find_item(TreeItem &item, bool & found) const
{
    find_bt(root, item, found);
}

// Function remove_item
// Checks for empty tree, throws exception if necssary
// remove item, if found
void BinaryTree::remove_item(TreeItem item)
{
    if (is_empty())
        throw EmptyTree();
    else
    {    
        bool found = false;
        find_item(item, found);
        if (found)
            remove_bt(root, item);
    }
}

// Return the item at the deepest left node
// (Would come first in an in-order traversal)
// Throws exception if tree is empty
TreeItem BinaryTree::get_leftmost() const
{
    return return_leftmost(root);
}

// Copy constructor
// Uses the copy_helper function to recursively copy
// the root
BinaryTree::BinaryTree(const BinaryTree &from)
{
    root = copy_helper(from.root);
}

// Uses the copy-and-swap functionality
// Accepts the argument by value, invoking copy constructor
// Then we swap the pointers to the roots, effectively swapping them
// And as the 'from' BinaryTree falls out of scope, it calls the
// destructor on the original root, killing two birds with one stone
BinaryTree& BinaryTree::operator=(BinaryTree from)
{
    swap(this->root, from.root);
    return *this;
}

// Tries to allocate another TreeItem and catches the bad_alloc error
// Returns false if we cannot allocate any more
bool BinaryTree::is_full() const
{
    try {
        TreeItem *t = new TreeItem;
        delete t;
        return false;
    } catch (bad_alloc e) {
        return true;
    }
}

// Returns whether the tree is empty
// That can only be true if the root pointer points to nothing
bool BinaryTree::is_empty() const
{
    return root == NULL;
}

// Returns the number of leaves on the tree
int BinaryTree::num_leaves() const
{
    return num_leaves_helper(root);
}

// Returns the max number of leaves in the tree
int BinaryTree::height() const
{
    return height_helper(root);
}

// Returns the average of all the ages
// Modifies the num_people variable to effectively return two values
// as average cannot be computed incrementally
double BinaryTree::average_age() const
{
    int num_people = 0;
    int total_age = total_age_helper(num_people, root);
    return (double) total_age / (double) num_people;
}

// Returns the farthest right node
// Can throw an EmptyTree error if the tree is empty
TreeItem BinaryTree::rightmost_node() const
{
    BinaryNode *node = rightmost_helper(root);
    if (node != NULL)
        return node->info;
    else
        throw EmptyTree();
}

// Outputs the contents of the tree to the output stream
void BinaryTree::print_root(ostream &output) const
{
    if (root == NULL) return;
    root->info.print(output);
}

// Overloading the << operator in order to print the tree easier
ostream &operator<<(ostream &output, const BinaryTree &tree)
{
    tree.print_root(output);
    output << "\nheight: " << tree.height() << endl
        << "nodes: " << tree.get_length() << endl
        << "leaves: " << tree.num_leaves() << endl;
    return output;
}

/* Definitions for Recursive Wrapper Functions */

// Used in the average_age function
// Keeps trying to access the right element,
// but stops when node->right is null
BinaryNode *rightmost_helper(BinaryNode *node)
{
    if (node == NULL)
        return NULL;
    BinaryNode *res = rightmost_helper(node->right);
    if (res != NULL)
        return res;
    return node;
} 

// Also increments the num_people parameter to be used in average calculation
int total_age_helper(int &num_people, const BinaryNode *node)
{
    if (node == NULL)
        return 0;
    num_people++;
    return node->info.get_age() 
         + total_age_helper(num_people, node->left)
         + total_age_helper(num_people, node->right);
}

// Returns the tallest branch of the tree
// Base case is when the pointer is null
// And going one deeper increments by 1
int height_helper(const BinaryNode *node)
{
    if (node == NULL)
        return 0;
    int left  = height_helper(node->left),
        right = height_helper(node->right);
    return 1 + MAX(left, right);
}

// Returns the number of leaves in the tree
// Base case: tree is null, return 1
// Otherwise add the number of leaves in each child
int num_leaves_helper(const BinaryNode *node)
{
    // Not a leaf if it's NULL
    if (node == NULL)
        return 0;
    // Only a leaf if it has no children
    if (node->left == NULL and node->right == NULL)
        return 1;
    else 
        return num_leaves_helper(node->left) + num_leaves_helper(node->right);
}

// Recursively copies each element from one tree to another
// Base case: tree is null: stop copying
// Otherwise add a new node, and copy it's value and children
BinaryNode *copy_helper(BinaryNode *from)
{
    if (from == NULL)
        return NULL;

    BinaryNode *new_node = new BinaryNode;
    new_node->info = from->info;
    new_node->left  = copy_helper(from->left);
    new_node->right = copy_helper(from->right);

    return new_node;
}

// Function destroy (wrapper)
// Used by destructor and = operator
// Follows postfix order, deletes nodes one by one
void destroy(BinaryNode *&tree)
{
    if (tree != NULL)
    {
        destroy(tree->left);
        destroy(tree->right);
        delete tree;
    }
}

// Recursively counts the total number of nodes in the tree
int count_nodes(BinaryNode *tree)
{
    if (tree == NULL)
        return 0;
    else
        return count_nodes(tree->left) + count_nodes(tree->right) + 1;
}

// Print in  order
void print_inorder(BinaryNode *tree, ostream &out)
{
    if (tree != NULL)
    {
        print_inorder(tree->left, out);
        tree->info.print(out);
        print_inorder(tree->right, out);
    }
} 

// Print in prefix order
void print_preorder(BinaryNode *tree, ostream &out)
{
    if (tree != NULL)
    {
        tree->info.print(out);
        print_preorder(tree->left, out);
        print_preorder(tree->right, out);
    }
} 

// Print in postfix order
void print_postorder(BinaryNode *tree, ostream &out)
{
    if (tree != NULL)
    {
        print_postorder(tree->left, out);
        print_postorder(tree->right, out);
        tree->info.print(out);
    }
}

// Function insert_bt (wrapper)
// Params: BinaryNode reference, TreeItem
// Returns: void
// Does: Finds next open spot using a queue
//       allocates a new BinaryNode and sets
//       its info to the given tree
void insert_bt(BinaryNode *&tree, TreeItem item)
{
    // enqueue and dequeue until empty
    BinaryNode *temp = NULL;
    BinaryNode *node = new BinaryNode;
    node->info = item;
    node->left = NULL;
    node->right = NULL;
    if (tree == NULL)
    {
        tree = node;
        return;
    }
    
    Queue q;
    q.enqueue(tree);
    while (!q.is_empty())
    {
        q.dequeue(temp);
        if (temp->left != NULL)
        {
            q.enqueue(temp->left);
        }
        else
        {
            temp->left = node;
            return;
        }
        if (temp->right != NULL)
        {
            q.enqueue(temp->right);
        }
        else
        {
            temp->right = node;
            return;
        }
    }
}

// Function find_bt (not a member function)
// Parameters: BinaryNode (root), TreeItem reference, bool reference
// Returns: void
// Does: Uses an auxiliary queue to iterate through each node
//       until the item is found. Updates the item reference with
//       the one actually found, and bool reference with true/false. 
void find_bt(BinaryNode *tree, TreeItem &item, bool &found)
{ 
    found = false;
    if (tree == NULL)
    {
        return;
    }

    Queue q;
    q.enqueue(tree);

    while (!q.is_empty())
    {
        BinaryNode *node; 
        q.dequeue(node);
        if (node->info == item)
        {
            item = node->info;
            found = true;
            return;
        }
        if (node->left != NULL)
            q.enqueue(node->left);
        if (node->right != NULL)
            q.enqueue(node->right);
    }
}

// Function remove_bt (wrapper)
// Parameters: BinaryNode reference (root), TreeItem to remove
// Returns: void
// Does: Uses an auxiliary queue to find the deepest item
//       swaps one to delete with deepest item
//       deletes deepest item
void remove_bt(BinaryNode *&tree, TreeItem item) 
{
    if (tree == NULL)
    {
        return;
    }

    Queue q;
    q.enqueue(tree);

    BinaryNode *deep = NULL, *keynode = NULL;

    while (!q.is_empty())
    {
        q.dequeue(deep);
        if (deep->info == item)
            keynode = deep;
        if (deep->left != NULL)
            q.enqueue(deep->left);
        if (deep->right != NULL)
            q.enqueue(deep->right);
    }

    TreeItem val = deep->info;
    delete_deepest(tree, deep);
    if (deep != keynode)
        keynode->info = val;
}

// Delete deepest node in the tree
// Helper function for remove
void delete_deepest(BinaryNode *&tree, BinaryNode *&deepnode)
{
    Queue q;
    q.enqueue(tree);

    BinaryNode *temp;
    while (!q.is_empty())
    {
        q.dequeue(temp);
        if (temp->right != NULL)
        {
            if (temp->right->info == deepnode->info)
            {
                temp->right = NULL;
                delete deepnode;
                return;
            }
            else
                q.enqueue(temp->right);
        }
        if (temp->left != NULL)
        {
                if (temp->left->info == deepnode->info)
                {
                    temp->left = NULL;
                    delete deepnode;
                    return;
                }
                else
                    q.enqueue(temp->left);
        }
    }
}

// Function return_leftmost(wrapper)
// Params: BinaryNode *, the tree
// Returns: TreeItem, the info in the deepest left node
// Throws exception if tree is empty, it has no leftmost ndoe
TreeItem return_leftmost(BinaryNode *tree)
{
    if (tree == NULL)
        throw EmptyTree();
    else if (tree->left == NULL)
        return tree->info;
    else
       return return_leftmost(tree->left);
}
