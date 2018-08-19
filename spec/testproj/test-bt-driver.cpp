/*
 * test-bt-driver.cpp
 *
 * Some BASIC functionality testing
 * on the Binary Tree class.
 * 
 * It can lull you into a false sense of
 * security, though. 
 *
 * Don't fall for it!
 * 
 * Write more testing code!
 * 
 * WILLLLSOOOOONNNNNN!!!!!
 *
 * COMP15
 * Spring 2018
 *
 */

#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "Survivor.h"
using namespace std;

void test_get_length(BinaryTree *, int);
void test_insert(BinaryTree *, int);
void test_preorder(BinaryTree *);
void test_inorder(BinaryTree *);
void test_postorder(BinaryTree *);
void test_find(BinaryTree *);
void test_remove(BinaryTree *, int);
void test_get_left(BinaryTree *);

int main()
{
    BinaryTree *BT = new BinaryTree;
    test_get_length(BT, 0);
    test_insert(BT, 5);
    test_preorder(BT);
    test_inorder(BT);
    test_postorder(BT);
    test_find(BT);    
    test_remove(BT, 2);
    test_get_left(BT);

    delete BT;
}

// Function test_get_length
// Parameters: BT pointer, int for expected length
void test_get_length(BinaryTree *bt, int num_items)
{
    if (bt->get_length() == num_items)
    {
        cout << "test get length SUCCESS!\n";
    }
    else
    {
        cout << "test get length FAIL\n";
    }
}

// Function test_insert
// Parameters: BT pointer, int for # of inserts
// Returns void
// Does: prints success if all the inserts worked
void test_insert(BinaryTree *bt, int num_items)
{
    Survivor *vives = new Survivor[num_items];
    for (int i = 0; i < num_items; i++)
    {
        string lname = "Hatch";
        lname += to_string(i+1);
        vives[i].set_name("Richard", lname);
        bt->insert_item(vives[i]);
    }
    if (bt->get_length() == num_items)
    {
        cout << "test insert SUCCESS!\n";
    }
    else
    {
        cout << "test insert FAIL\n";
    }
    delete []vives;
}

// Function test_find
// Attempts to find an existing and a
// non-existing item
void test_find(BinaryTree *BT)
{
    Survivor there("Richard", "Hatch1"), 
        notthere("Tom", "Hanks");
    bool found;
    BT->find_item(there, found);

    if (found)
        cout << "test find (existing item): SUCCESS\n";
    else
        cout << "test find (existing item): FAIL\n";

    BT->find_item(notthere, found);
    if (!found)
        cout << "test find (nonexisting): SUCCESS\n";
    else
        cout << "test find (nonexisting): FAIL\n";
}

// Print a preorder traversal
void test_preorder(BinaryTree *BT)
{
    cout << "Begin preorder test.\n";
    BT->preorder(cout);
    cout << "Expected Hatches: 1 2 4 5 3\n";
    cout << "Did that look right? If so then SUCCESS!\n\n";
}

// Print an inorder traversal
void test_inorder(BinaryTree *BT)
{
    cout << "Begin inorder test.\n";
    BT->inorder(cout);
    cout << "Expected Hatches: 4 2 5 1 3\n";
    cout << "Did that look right? If so then SUCCESS!\n\n";
}

// Print a postorder traversal
void test_postorder(BinaryTree *BT)
{
    cout << "Begin postorder test.\n";
    BT->postorder(cout);
    cout << "Expected Hatches: 4 5 2 3 1\n";
    cout << "Did that look right? If so then SUCCESS!\n\n";
}

// Function: test remove
// Remove a leaf node, a rooto, a node in the deepest leaf
// and a node that's already been removed
void test_remove(BinaryTree *BT, int new_length)
{
    Survivor leaf("Richard", "Hatch3"), 
        root("Richard", "Hatch1"),
        deepest("Richard", "Hatch5"),
        alreadyremoved("Richard", "Hatch5");

    BT->remove_item(leaf);
    BT->remove_item(root);
    BT->remove_item(deepest);
    BT->remove_item(alreadyremoved);

    if (BT->get_length() == new_length)
        cout << "test remove SUCCESS\n";
    else
        cout << "test remove FAIL\n";
}

// test_get_left
// Makes sure we correclty find the leftmost node
void test_get_left(BinaryTree *bt)
{
    TreeItem t = bt->get_leftmost();
    Survivor s;
    s.set_name("Richard", "Hatch2");
    if (t == s)
        cout << "test get_left SUCCESS\n";
    else
        cout << "test get_left FAIL\n";
}
