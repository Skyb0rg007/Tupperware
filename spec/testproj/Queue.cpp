#include "Queue.h"
#include <cstddef>
#include <new>

Queue::Queue()
{
    front = NULL;
    rear = NULL;
}

Queue::~Queue()
{
    NodeType *temp;

    while (front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
    rear = NULL;
}

Queue::Queue(const Queue &q)
{
    if (q.front == NULL)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        try
        {
            front = new NodeType;
            front->value = q.front->value;
            front->next = NULL;
            rear = front;
            NodeType *curr = front;
            NodeType *orig = q.front;
            while (orig->next != NULL)
            {
                curr->next = new NodeType;
                curr->next->value = orig->next->value;
                curr->next->next = NULL;
                rear = curr->next;
                orig = orig->next;
                curr = curr->next;
            }
        } 
        catch(bad_alloc exception)
        {
            cerr << "Out of memory, unable to create queue\n";
        }
        
    }
}

Queue & Queue::operator =(const Queue &q)
{
    NodeType *temp;
    while (front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }

    if (q.front == NULL)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        try
        {
            front = new NodeType;
            front->value = q.front->value;
            front->next = NULL;
            rear = front;
            NodeType *curr = front;
            NodeType *orig = q.front;
            while (orig->next != NULL)
            {
                curr->next = new NodeType;
                curr->next->value = orig->next->value;
                curr->next->next = NULL;
                rear = curr->next;
                orig = orig->next;
                curr = curr->next;
            }
        }
        catch (bad_alloc exception)
        {
            cerr << "Out of memory, could not create new list\n";
            return *this;
        }
    }
    return *this;
}


bool Queue::is_full() const
{
    NodeType *location;
    try 
    {
        location = new NodeType;
        delete location;
        return false;
    }
    catch(std::bad_alloc exception)
    {
        return true;
    }
}

bool Queue::is_empty() const
{
    return (front == NULL);
}

void Queue::enqueue(BinaryNode *&new_item)
{
    if (is_full())
        throw FullQueue();
    else
    {
        NodeType *new_node;
        new_node = new NodeType;
        new_node->value = new_item;
        new_node->next = NULL;
        if (rear == NULL)
            front = new_node;
        else
            rear->next = new_node;
        rear = new_node;
    }
}

void Queue::dequeue(BinaryNode *&item)
{
    if (is_empty())
        throw EmptyQueue();
    else
    {
        NodeType *temp;
        temp = front;
        temp->value = front->value;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        item = temp->value;
        delete temp;
    }
}


