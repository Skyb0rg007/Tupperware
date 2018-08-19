/* 
 * Skye Soss
 * Comp 15
 *
 */


#ifndef __SURVIVOR_H__
#define __SURVIVOR_H__

#include <string>
#include <iostream>
#include <fstream>

// The Survivor/TreeItem class
class Survivor
{
private:
    std::string firstname;
    std::string lastname;
    std::string hometown;
    std::string state;
    int age;
public:
    // Default Constructor
    Survivor();
    // Constructor taking the private fields
    Survivor(std::string, std::string);
    Survivor(std::string, std::string, std::string, std::string, int);

    // Member functions. Their uses are explained in the .cpp
    int get_age() const;
    void print(std::ostream&) const;
    bool generate_next_survivor(std::ifstream&);
    void set_name(std::string, std::string);
    bool operator==(const Survivor&);
    bool operator< (const Survivor&);
    bool operator> (const Survivor&);
};

typedef Survivor TreeItem; 

#endif
