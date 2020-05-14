#include "List.h"

List::List()
{
    head = NULL;
    length = 0;
}

void List::append(int n)
{
    _makeNode(n);
}

void List::_makeNode(int n)
{
    Nptr node = new Node();
    node->data = n;
    node->next = NULL;
    _append(head,node);
}

void List::_append(Nptr& Ptr, Nptr node)
{
    if (!Ptr)
    {
        Ptr = node;
        node->next = head;
        ++length;
        return;
    }
    else if (Ptr->next==head)
    {
        Ptr->next = node;
        node->next = head;
        ++length;
        return; 
    }
    _append(Ptr->next,node);
}

void List::print()
{
    _print(head);
    cout << endl;
    
}

void List::_print(Nptr Ptr)
{
    if (Ptr->next != head)
    {
        cout << Ptr->data << " ";
        _print(Ptr->next);
    }
    else if (Ptr->next == head)
    {
        cout << Ptr->data << " ";
    }
}

bool List::search(int n)
{
    return _search(head, n);
}

bool List::_search(Nptr Ptr, int n)
{
    if(!Ptr)
    {
        cout << "Blah BLah" << endl;
        return false;
    }

    if(Ptr->data == n)
        return true;
    else
        return _search(Ptr->next, n);
}

void List::remove(int n)
{
    _remove(head, n);
}

void List::_remove(Nptr & Ptr, int n)
{
    if(!head)
    {
        cout << "Error: Empty List" << endl;
        return;
    }

    if(head->data == n)
    {
        Nptr temp = head;
        head = head->next;
        delete temp;
        length--;
        return;
    }

    if(Ptr->next->data == n)
    {
        _delNode(Ptr, Ptr->next);
        length--;
        return;
    }

    _remove(Ptr->next, n);
}

void List::_delNode(Nptr & Ptr1, Nptr & Ptr2)
{
    Nptr temp = Ptr2;
    Ptr1->next = Ptr2->next;
    delete temp;
}

void List::insert(int index, int data)
{
    _makeNode(head,data,index);
}

void List::_makeNode(Nptr &Ptr, int data, int index)
{
    Nptr node = new Node();
    node->data = data;
    if ((index > 0 && index >= length) || (index < 0 and (-1) * index >= length))
    {
        cout << "Out of bounds index" << endl;
        return;
    }
    if (index < 0)
    {
        index = index + length;
    }
    _insert(head, node, index, 0);
}


void List::_insert(Nptr &Ptr, Nptr node, int index, int count)
{
    if (index == 0 or index == count + 1)
    {
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
        else
        {
            cout << "insertion to middle" << endl;
            node->next = Ptr->next;
            Ptr->next = node;
            ++length;
            return;
        }
    }
    
    _insert(Ptr->next, node, index, ++count);
}

void List::remove_index(int index)
{
    if ((index > 0 && index >= length) || (index < 0 and (-1) * index >= length))
    {
        cout << "Out of bounds index" << endl;
        return;
    }
    
    if (index < 0)
    {
        index = index + length;
    }
    _remove_index(head, index, 0);
}

// Function that removes index
void List::_remove_index(Nptr &Ptr, int index, int count)
{
    if (index == 0)
    {
        Nptr tail = Ptr;
        while (tail -> next != head)
        {
            tail = tail -> next;
        }
        Nptr temp = head;
        head = head -> next;
        delete temp;
        tail -> next = head;
        --length;
        return;
    }
    else if (index == count + 1)
    {
        Nptr temp = Ptr -> next;
        Ptr -> next = Ptr -> next -> next;
        delete temp;
        --length;
        return;
    }
    _remove_index(Ptr->next, index, ++count);
}

// The function the user can access
int List::Josephus(int total, int k)
{
    return _Josephus(head, total, k);
}

// An implementation od the Josephus problem
int List::_Josephus(Nptr &Ptr, int total, int k)
{
    while (length > 1)
    {
        for (int i = 0; i < k - 1; ++i)
        {
            Ptr = Ptr->next;
        }
        _delNode(Ptr,Ptr->next);
        --length;
    }
    return Ptr->data;
}
