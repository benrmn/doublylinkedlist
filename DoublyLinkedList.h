#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList(): head(nullptr), tail(nullptr), sz(0) {}
    DoublyLinkedList(T data);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    void copy(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front() { return head->data; }
    const T& front() const { return head->data; }
    T& back() { return tail->data; }
    const T& back() const { return tail->data; }
    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
    // template<typename U> friend bool operator!=(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);

private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//constructor for data
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data): head(nullptr), tail(nullptr), sz(0) {
    Node<T>* newNode = new Node<T>(data);
    head = newNode;
    tail = newNode;
    tail->next = nullptr;
    head->next = nullptr;
    tail->prev = nullptr;
    head->prev = nullptr;
    sz++;
}

template<typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& src) {
    Node<T>* curNode = src.head;
    Node<T>* cur = nullptr;
    while (curNode != nullptr) {
        Node<T>* newNode = new Node<T>(curNode->data);
        if (head==nullptr) {
            head = newNode;
        } else {
            cur->next = newNode;
            newNode->prev = cur;
        }
        cur = newNode;
        tail = newNode;
        curNode = curNode->next;
    }
    this->sz = src.size();
}
//copy constructor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &src): head(nullptr), tail(nullptr), sz(0) {
    copy(src);
}

//copy assignment operator
template<typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &src) {
    if (this != &src) {
        clear();
        copy(src);
    }
    return *this;
}

//destructor
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// push_back
template<typename T>
void DoublyLinkedList<T>::push_back(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
    }
    if (tail != nullptr) {
        tail->next = newNode;
    }
    newNode->next = nullptr;
    newNode->prev = tail;
    tail = newNode;
    sz++;
}

// push_front
template<typename T>
void DoublyLinkedList<T>::push_front(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }
    sz++;
}
// pop_back
template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (head == nullptr) {
        return;
    }
    if (head->next==nullptr) {
        Node<T>* delTail = tail;
        tail = delTail->prev;
        head = nullptr;
        delete delTail;
    }
    if (tail != nullptr) {
        Node<T>* delTail = tail;
        tail = delTail->prev;
        tail->next = nullptr;
        delete delTail;
    }
    sz--;
}

// pop_front
template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (head == nullptr) {
        return;
    }
    if (head->next==nullptr) {
        Node<T>* delTail = head;
        head = delTail->next;
        tail = nullptr;
        delete delTail;
    }
    if (tail != nullptr) {
        Node<T>* delTail = head;
        head = delTail->next;
        head->prev = nullptr;
        delete delTail;
    }
    sz--;
}


// erase
template<typename T>
void DoublyLinkedList<T>::erase(unsigned int idx) {
    Node<T>* tempNode = head;
    for (int i=0; i<idx && tempNode!=nullptr; i++) {
        tempNode = tempNode->next;
    }
    if (idx==0) {
        pop_front();
    } else if (idx==sz-1) {
        pop_back();
    } else if (tempNode!=nullptr) {
        tempNode->prev->next = tempNode->next;
        tempNode->next->prev = tempNode->prev;
        delete tempNode;
        sz--;
    } else {
        return;
    }
}

//insert
template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx) {
    if (idx > sz) {
        return;
    }
    Node<T> *newNode = new Node<T>(data);
    Node<T> *curNode = head;
    if (idx == 0) {
        push_front(data);
    } else if (idx == sz) {
        push_back(data);
    } else if (curNode != nullptr) {
        for (int i=1; i<=idx && curNode!=nullptr; i++) {
            if (i==idx) {
                Node<T> *tempNode = curNode->next;
                curNode->next = newNode;
                newNode->prev = curNode;
                newNode->next = tempNode;
                tempNode->prev = newNode;
            }
            curNode = curNode->next;
        }
        sz++;
    } else {
        return;
    }
}
//clear function
template<typename T>
void DoublyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* cur = head;
        head = head->next;
        delete cur;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0;
}


//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}



//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs) {
    if (lhs.size()==rhs.size()) {
        DoublyLinkedList<T> tempLeft = lhs;
        DoublyLinkedList<T> tempRight = rhs;
        for (int i=0; i<rhs.size(); ++i) {
            if (tempLeft.front()!=tempRight.front()) {
                return false;
            }
            tempLeft.pop_front();
            tempRight.pop_front();
        }
    } else {
        return false;
    }
    return true;
}

template<typename T>
bool operator!=(const DoublyLinkedList<T> &lhs, const DoublyLinkedList<T> &rhs) {
    if (lhs.size()==rhs.size()) {
        DoublyLinkedList<T> tempLeft = lhs;
        DoublyLinkedList<T> tempRight = rhs;
        for (int i=0; i<rhs.size(); ++i) {
            if (tempLeft.front()==tempRight.front()) {
                return false;
            }
            tempLeft.pop_front();
            tempRight.pop_front();
        }
    } else {
        return false;
    }
    return true;
}


template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs) {
    os << rhs.to_str();
    return os;
}

#endif
