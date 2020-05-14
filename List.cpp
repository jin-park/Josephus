#include "List.h"

// The Constructor
List::List()
{
    // Initializing head to null
    head = NULL;
    // The length is initialized to 0
    length = 0;
}

// The append function the user can access
void List::append(int n)
{
    // Calls the function that actually makes the new node
    _makeNode(n);
}

// The function that makes a new node
void List::_makeNode(int n)
{
    Nptr node = new Node();
    // Initializing the node's data
    node->data = n;
    node->next = NULL;
    // Appending to end
    _append(head,node);
}

// The function that appends node to the end
void List::_append(Nptr& Ptr, Nptr node)
{
    // If Ptr is null then it is the first node
    if (!Ptr)
    {
        Ptr = node;
        // Pointing the node towards head because it is a circular list
        node->next = head;
        ++length;
        return;
    }
    // If Ptr is pointing to head then it is at the end
    else if (Ptr->next==head)
    {
        Ptr->next = node;
        node->next = head;
        ++length;
        return; 
    }
    // If not any of these Ptr moves one step
    _append(Ptr->next,node);
}

// The print function the user can access
void List::print()
{
    _print(head);
    cout << endl;
}

// The function that does the printing
void List::_print(Nptr Ptr)
{
    // If Ptr->next isn't head then it is not the end
    if (Ptr->next != head)
    {
        cout << Ptr->data << " ";
        _print(Ptr->next);
    }
    // However if it is then it is the end. Hence print one last time
    else if (Ptr->next == head)
    {
        cout << Ptr->data << " ";
    }
}

// The function that returns a boolean (whether the int n exists in the list or not)
bool List::search(int n)
{
    return _search(head, n);
}

// The function that does the searching
bool List::_search(Nptr Ptr, int n)
{
    // If Ptr is null then the list is empty. return false
    if(!Ptr)
    {
        cout << "Blah BLah" << endl;
        return false;
    }
    // If the node contains n, then return True
    if(Ptr->data == n)
    {
        return true;
    }
    // Else move onto the next node
    else
    {
        return _search(Ptr->next, n);
    }
}

// The remove function that the user can access
void List::remove(int n)
{
    _remove(head, n);
}

// Traverses list to remove int n
void List::_remove(Nptr & Ptr, int n)
{
    // If head is null the list is empty. Do not need to check
    if(!head)
    {
        cout << "Error: Empty List" << endl;
        return;
    }
    // If head contains the data no need to traverse
    else if(head->data == n)
    {
        Nptr temp = head;
        // Redirect head to head->next
        head = head->next;
        delete temp;
        length--;
        return;
    }
    // If Ptr->next contains int n then call delNode
    else if(Ptr->next->data == n)
    {
        _delNode(Ptr, Ptr->next);
        length--;
        return;
    }

    _remove(Ptr->next, n);
}

// The function that removes the last inputted Node 
void List::_delNode(Nptr & Ptr1, Nptr & Ptr2)
{
    Nptr temp = Ptr2;
    Ptr1->next = Ptr2->next;
    delete temp;
}

// The insert function the user can access
void List::insert(int index, int data)
{
    _makeNode(head,data,index);
}

// An override function for the previous _makeNode function
void List::_makeNode(Nptr &Ptr, int data, int index)
{
    // Makes a new node and calls the _insert function
    Nptr node = new Node();
    node->data = data;
    if ((index > 0 && index >= length) || (index < 0 and (-1) * index >= length))
    {
        cout << "Out of bounds index" << endl;
        return;
    }
    // If the index is negative then add the length to it to make it positive
    if (index < 0)
    {
        index = index + length;
    }
    _insert(head, node, index, 0);
}

// Inserts the node to the right place
void List::_insert(Nptr &Ptr, Nptr node, int index, int count)
{
    // If inserting to head or if the pointer is right before the targeted position
    if (index == 0 or index == count + 1)
    {
        // Append to head
        if (index == 0)
        {
            cout << "insertion to head" << endl;
            Nptr tail = Ptr;
            while (tail->next != head)
            {
                tail = tail -> next;
            }
            node->next = head;
            head = node;
            tail->next = head;
            ++length;
            return;
        }
        // Append to the correct position
        else
        {
            cout << "insertion to middle" << endl;
            node->next = Ptr->next;
            Ptr->next = node;
            ++length;
            return;
        }
    }
    // Else move onto the next pointer and increase count by one
    _insert(Ptr->next, node, index, ++count);
}

// The function that removes the specified index
void List::remove_index(int index)
{
    if ((index > 0 && index >= length) || (index < 0 and (-1) * index >= length))
    {
        cout << "Out of bounds index" << endl;
        return;
    }
    // If the index is negative then add the length to it to make it positive
    if (index < 0)
    {
        index = index + length;
    }
    // Call _remove_index with count initialized as 0
    _remove_index(head, index, 0);
}

// Function that removes index
void List::_remove_index(Nptr &Ptr, int index, int count)
{
    // If trying to remove first index
    if (index == 0)
    {
        Nptr tail = Ptr;
        // Traverse to the end of list
        while (tail->next != head)
        {
            tail = tail->next;
        }
        Nptr temp = head;
        head = head->next;
        delete temp;
        // Redirect the end node to the new head
        tail->next = head;
        --length;
        return;
    }
    // Or if the pointer is right before the specified index
    else if (index == count + 1)
    {
        Nptr temp = Ptr->next;
        Ptr->next = Ptr->next->next;
        delete temp;
        --length;
        return;
    }
    // Else move onto the next pointer with count increased by one
    _remove_index(Ptr->next, index, ++count);
}

// The Josephus function the user can access
int List::Josephus(int total, int k)
{
    // Returns the preson that survives
    return _Josephus(head, total, k);
}

// An implementation of the Josephus problem
int List::_Josephus(Nptr &Ptr, int total, int k)
{
    // Continues removing node until only one remains
    while (length > 1)
    {
        // Traverse for a certain time specified by user
        for (int i = 0; i < k - 1; ++i)
        {
            Ptr = Ptr->next;
        }
        // Kill one person
        _delNode(Ptr,Ptr->next);
        --length;
    }
    // Return the survivor index
    return Ptr->data;
}
