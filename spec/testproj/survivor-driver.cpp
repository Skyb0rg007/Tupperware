/* Copyright 2018 Skye Soss
 *
 */

#include "Survivor.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

#define FILE1 "castaways.txt"
#define FILE2 "stowaways.txt"

// Difference between the two arguments, casted to doubles
#define DIFF(X, Y) abs((double) (X) - (double) (Y))

using namespace std;

int main(void)
{
    // Randomly assign files to each binary tree
    srand(time(NULL));
    bool r = rand() % 2 == 0;
    string file1 = r ? FILE1 : FILE2,
           file2 = r ? FILE2 : FILE1;

    BinarySearchTree bst;
    BinaryTree bt;

    ifstream infile1, infile2;
    infile1.open(file1.c_str()); infile2.open(file2.c_str());

    if (!infile1.is_open() or !infile2.is_open()) {
        cerr << "Problem opening a file!" << endl;
        exit(1);
    }

    // Keep calling generate_next_survivor with the given file
    // as long as it can, each time that it succeeds insert it 
    // into the binary tree
    for (Survivor new_sur; new_sur.generate_next_survivor(infile1); 
            bst.insert_item(new_sur))
        ;
    for (Survivor new_sur; new_sur.generate_next_survivor(infile2); 
            bt.insert_item(new_sur))
        ;

    infile1.close(); infile2.close();

    // ROUND ONE:
    int bst_leaves = bst.num_leaves(), bt_leaves = bt.num_leaves();

    if (bst_leaves > bt_leaves)
        cout << "Loser had " << bt_leaves << " leaves\n"
                "ROUND ONE WINNER: BT\n" << bst << endl;
    else
        cout << "Loser had " << bst_leaves << " leaves\n"
                "ROUND ONE WINNER: BST\n" << bt << endl;

    BinaryTree winner = bst_leaves > bt_leaves ? bst : bt;

    // ROUND TWO:
    // As long as there is more than one Survivor
    while (winner.get_length() != 1)
    {
        double average = winner.average_age();
        Survivor loser, left, right;

        left = winner.get_leftmost();
        right = winner.rightmost_node();

        // Whichever is farthest from average is the loser
        if (DIFF(left.get_age(), average) > DIFF(right.get_age(), average))
            loser = left;
        else
            loser = right;

        winner.remove_item(loser);  // remove the loser

        // Format the output
        cout << "Average age of this round: " << average << endl;
        cout << "Voted off the island:" << endl;
        loser.print(cout);
        cout << endl;
    }
    // Print the winner!
    cout << "\nWINNING SURVIVOR: " << endl;
    winner.print_root(cout);

    return 0;
}
