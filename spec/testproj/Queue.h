/* 
 * COMP15
 * Spring 2018
 * Skye Soss
 *
 * Queue practice problems
 */

#include <exception>
#include <string>
#include "Tree.h"

using namespace std;

#ifndef QUEUE_H_
#define QUEUE_H_

class FullQueue : public exception{
public:
    const char * what() const throw() {return "Oh no, the queue is full!\n";}; 
};

class EmptyQueue : public exception{
public:
    const char * what() const throw() {return "Sad, the queue is empty!\n";}
};

struct NodeType
{
    BinaryNode *value;
    NodeType *next;
};

class Queue
{
private:
    NodeType *front;
    NodeType *rear;

public:
    Queue();
    ~Queue();
    Queue(const Queue &);
    Queue & operator = (const Queue &);

    void enqueue(BinaryNode *&);
    bool is_full() const;

    void dequeue(BinaryNode *&);
    bool is_empty() const;
};

#endif
