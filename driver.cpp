#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
    DoublyLinkedList<int> ll;
    DoublyLinkedList<int> lll;

    //ll.push_front(1);
    lll.push_front(2);
    ll.push_front(2);
    /*ll.push_front(3);
    ll.push_front(4);
    ll.push_front(5);*/
    //std::cout << "here";
    lll.to_str();
    ll.to_str();
    if (ll==lll) {
        std::cout << "works";
    }


    return 0;
}