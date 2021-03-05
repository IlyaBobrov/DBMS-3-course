//
// Created by илья on 05.03.2021.
//

#ifndef PROGRAM_FILES_CPP__CONSIST_HPP
#define PROGRAM_FILES_CPP__CONSIST_HPP

#include <iostream>

template<typename T>
class consList;

template<typename T>
class consIterator;

//---node---------------------------------------------------------------------------------------------------------------

template<typename T>
class consNode {
public:
    consNode() : next(nullptr), prev(nullptr), data(nullptr), ref_count(0) {}

    explicit consNode(T data) : next(nullptr), prev(nullptr), data(data), ref_count(0) {}

//    int operator*();

private:
    T data;

    consNode *next, *prev;

    unsigned int ref_count{};

    friend class consList<T>;

    friend class consIterator<T>;
};

//---iterator-----------------------------------------------------------------------------------------------------------

template<typename T>
class consIterator {
public:
    consIterator() : current(nullptr) {}

    explicit consIterator(consNode<T> *newNode) : current(newNode) {}

    consIterator operator++() {
        current->ref_count--;    //сказали node что мы перешли на другой
        current = current->next;
        checkDeleteNodes(current->prev); //отдели на проверку node с которого ушли
        current->ref_count++;    //оповестили новый
        return *this;
    }

    consIterator operator--() {
        current->ref_count--;
        current = current->prev;
        checkDeleteNodes(current->next);
        current->ref_count++;
        return *this;
    }

//    consIterator operator=() const;

    consIterator &operator=(const consIterator &right) {
        if (this == &right) {
            return *this;
        }
        //todo: присваивание
        return *this;
    }

    T operator*() const {
        return current->data;
    }

private:
    consList<T> *container;
    consNode<T> *current;

    friend class consList<T>;
};

//---list---------------------------------------------------------------------------------------------------------------

template<typename T>
class consList /*: public List*/ {
public:
    consList() : Head(nullptr), Tail(nullptr), size(0) {}

    ~consList() {}

    consList(std::initializer_list<T> list) {
        Head = nullptr;
        Tail = nullptr;
        size = 0;
        for (auto i = list.begin(); i < list.end(); i++) {
            this->pushBack(*i);
        }
    }

//    mpList(const mpList &)

    unsigned int getSize() {
        return size;
    }

    void pushBack(T data) {
        consNode<T> *newNode = new consNode(data);

        if (Tail == nullptr) {
            Head = newNode;
            Tail = newNode;
            newNode->ref_count = 1;
        } else {
            newNode->prev = Tail;
            Tail->ref_count++;      //
            Tail->next = newNode;
            Tail = newNode;
            newNode->ref_count = 1; //
        }
        size++;
    }

    void pushFront(T data) {
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
        size++;
    }

    consIterator<T> insert(consIterator<T> iter, T data) {
        if (iter.current == nullptr) {
            pushBack(data);
            return end();
        }

        consNode<T> *nextNode = iter.current;
        consNode<T> *prevNode = nextNode->prev;
        consNode<T> *newNode = new consNode(data);

        newNode->prev = prevNode;
        newNode->next = nextNode;
        nextNode->prev = newNode;

        if (prevNode == nullptr) {
            newNode->ref_count = 1;
            Head = newNode;
        } else {
            prevNode->next = newNode;
            newNode->ref_count = 2;
        }

        consIterator<T> iterNewNode = newNode;
        iterNewNode.container = this;
        newNode->ref_count++;

        size++;
        return iterNewNode;
    }

    consIterator<T> erase(consIterator<T> iter) {
        static_assert(iter.current != nullptr);    //???

        consNode<T> *eraseNode = iter.current;
        consNode<T> *beforeNode = eraseNode->prev;
        consNode<T> *afterNode = eraseNode->next;

        if (eraseNode == Head) {
            Head = afterNode;
        } else {
            beforeNode->next = afterNode;
        }

        if (eraseNode == Tail) {
            Tail = beforeNode;
        } else {
            afterNode->prev = beforeNode;
        }

        iter.current->ref_count = iter.current->ref_count - 2;

        checkDeleteNodes(eraseNode);

//    mpIterator iterOut;
        consIterator<T> iterOut;
        iterOut.current = afterNode;
        iterOut.container = this;
        iterOut.current->ref_count++;

        return iterOut;
    }

    consIterator<T> begin() {
//        if (this.current == nullptr) {
        consIterator<T> begin;
        begin.current = Head;
        begin.container = this;
        Head->ref_count++;      //todo
        return begin;
        /*} else {
            consIterator<T> begin = this.current;
            begin.current->ref_count--;
            checkDeleteNodes(this.current)
            begin.current = Head;
            begin.container = this;
            Head->ref_count++;      //
            return begin;
    }*/
    }

    consIterator<T> end() {
        consIterator<T> end;
        end.current = Tail;
        end.container = this;
        Tail->ref_count++;      //todo
        return end;
    }

    void checkDeleteNodes(consNode<T> *node) {
        if (node->ref_count == 0) {
            delete node;
            size--;
        }
    } //??? *

private:
    consNode<T> *Head, *Tail;
    unsigned int size;
    unsigned int const INIT_REF_COUNT = 0;

    friend class consIterator<T>;

};


#endif //PROGRAM_FILES_CPP__CONSIST_HPP
