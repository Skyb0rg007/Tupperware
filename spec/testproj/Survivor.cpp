/* 
 * Skye Soss
 * Comp 15
 *
 */

#include "Survivor.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default constructor: everything is basically zero
Survivor::Survivor()
{
    firstname = "";
    lastname  = "";
    hometown  = "";
    state     = "";
    age = 0;
}

// If given a first and last name, set those to given values
Survivor::Survivor(string fst, string lst)
{
    firstname = fst;
    lastname  = lst;
}

// If given everything, set all of them
Survivor::Survivor(string fst, string lst, string home, string st, int a)
{
    firstname = fst;
    lastname  = lst;
    hometown  = home;
    state = st;
    age = a;
}

// Simple age getter
int Survivor::get_age() const
{
    return age;
}

// print the Survivor with a specific format
void Survivor::print(ostream &output) const
{
    output << firstname << " " << lastname << "\n"
           << "hometown: " << hometown << ", " << state << "\n"
           << "age: " << age << "\n";
}

// Uses the file to turn the Survivor into the next one in the file
bool Survivor::generate_next_survivor(ifstream &infile)
{
    if (infile.eof())
        return false;

    infile >> firstname >> lastname
           >> hometown  >> state 
           >> age;

    if (infile.eof())
        return false;   // Lets the caller know that this one didnt work

    return true;
}

// Simple setter for the Survivor class
void Survivor::set_name(string first, string last)
{
    firstname = first;
    lastname  = last;
}

// Compares first and last name
bool Survivor::operator==(const Survivor &other)
{
    return firstname == other.firstname
        and lastname == other.lastname;
}

// Compares first and last name
bool Survivor::operator<(const Survivor &other)
{
    return lastname != other.lastname ? 
           lastname  < other.lastname : // Compare lastnames if theyre !=
           firstname < other.firstname; // Otherwise resort to firstnames
}

// Compares first and last name
bool Survivor::operator>(const Survivor &other)
{
    return *this == other ? false : not (*this < other);
}
