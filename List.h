#include<iostream>
#include<cstdlib>

using namespace std;

class List
{
    typedef struct Node
	{
		int data;
		Node *next;
	}* Nptr;

    Nptr head;
    
    void _makeNode(int);
    void _makeNode(Nptr&, int, int);
    void _append(Nptr &, Nptr);
    void _print(Nptr);
    bool _search(Nptr, int);
    void _remove(Nptr &, int);
    void _remove_index(Nptr &, int, int);
    void _delNode(Nptr &, Nptr &);
    void _insert(Nptr &, Nptr, int, int);
    int _Josephus(Nptr&, int, int);
public:
    List();
    void append(int);
    void print();
    bool search(int);
    void remove(int);
    void remove_index(int);
    void insert(int, int);
    int Josephus(int, int);
    int length;
};


