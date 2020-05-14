#include "List.cpp"

int main()
{
    List l = List();
    for (int i = 0;i < 5;i++)
    {
        l.append(i);
    }
    l.print();
    l.insert(-2,0);
    l.print();
    l.remove_index(2);
    l.print();
    // l.insert(index, data);
    // negative index
    // out of bounds index
    // have to be careful with head

    // remove(index);

    // using circular list, implement Josephus

    // Generic types


    return 0;
}
