#include <iostream>
#include "List.cpp"
int main()
{
    int total;
    int k;
    std::cin >> total >> k;
    List list = List();
    for (int i = 0; i < total; ++i)
    {
        list.append(i);
    } 
    cout << list.Josephus(total,k) << endl;
    return 0;
}