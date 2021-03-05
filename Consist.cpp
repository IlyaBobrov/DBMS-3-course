//
// Created by илья on 05.03.2021.
//

#include "Consist.hpp"

//---node---------------------------------------------------------------------------------------------------------------

template<typename T>
consNode<T>::consNode():next(nullptr), prev(nullptr), data(nullptr), ref_count(0) {}

template<typename T>
consNode<T>::consNode(T data):next(nullptr), prev(nullptr), data(data), ref_count(0) {}

template<typename T>
T consNode<T>::operator*() {
    return data;
}

//---iterator-----------------------------------------------------------------------------------------------------------

template<typename T>
consIterator<T>::consIterator() {
    current = nullptr;
}

template<typename T>
consIterator<T>::consIterator(consNode<T> *newNode) {
    current = newNode;
}

template<typename T>
consIterator<T> consIterator<T>::operator++() {
    current.ref_count--;    //сказали node что мы перешли на другой
    current = current.next;
    checkDeleteNodes(current->prev); //отдели на проверку node с которого ушли
    current.ref_count++;    //оповестили новый
    return *this;
}

template<typename T>
consIterator<T> consIterator<T>::operator--() {
    current.ref_count--;
    current = current.prev;
    checkDeleteNodes(current->next);
    current.ref_count++;
    return *this;
}

template<typename T>
T consIterator<T>::operator*() const {
    return current->data;
}

//---list---------------------------------------------------------------------------------------------------------------

template<typename T>
consList<T>::consList():Head(nullptr),Tail(nullptr),nodeCount(0) {}

template<typename T>
consList<T>::~consList() {
//todo диструктор
}

template<typename T>
unsigned int consList<T>::getSize() {
    return nodeCount;
}

template<typename T>
void consList<T>::pushBack(T data) {
    consNode<T> *newNode = new consNode(data);

    if (Tail == nullptr) {
        Head = newNode;
        Tail = newNode;
        newNode.ref_count = 1;
    } else {
        newNode->prev = Tail;
        Tail->ref_count++;      //
        Tail->next = newNode;
        Tail = newNode;
        newNode->ref_count = 1; //
    }
    nodeCount++;
}

template<typename T>
void consList<T>::pushFront(T data) {
    consNode<T> *newNode = new consNode(data);
    if (Head == nullptr) {
        Head = newNode;
        Tail = newNode;
        newNode->ref_count = 1;
    } else {
        newNode->next = Head;
        Head->ref_count++;      //
        Head->prev = newNode;
        Head = newNode;
        newNode->ref_count = 1; //
    }
    nodeCount++;
}

template<typename T>
consIterator<T> consList<T>::insert(consIterator<T> iter, T data) {
    //todo
    return consIterator<T>();
}

template<typename T>
consIterator<T> consList<T>::erase(consIterator<T> iter) {
    return consIterator<T>();
}

template<typename T>
consIterator<T> consList<T>::begin() {
    if (this.current == nullptr) {
        consIterator<T> begin;
        begin.current = Head;
        begin.container = this;
        Head->ref_count++;      //
        return begin;
    } else {
        consIterator<T> begin = this.current;
        begin.current->ref_count--;
        checkDeleteNodes(this.current)
        begin.current = Head;
        begin.container = this;
        Head->ref_count++;      //
        return begin;
    }
//    return consIterator<T>();
}

template<typename T>
consIterator<T> consList<T>::end() {
    consIterator<T> end;
    end.current = Tail;
    end.container = this;
    Tail->ref_count++;
    return end;
//    return consIterator<T>();
}

template<typename T>
void consList<T>::checkDeleteNodes(consNode<T> *node) {
    if (node->ref_count == 0) {
        delete node;
        nodeCount--;
    }
}