
// Created by илья on 04.03.2021.


#define CATCH_CONFIG_MAIN

#include <cstdlib>
#include "Catch.hpp"
#include "Consist.hpp"
#include <list>

using namespace std;

#define fori(n) for(int i = 0; i < n; i++)
#define forj(n) for(int j = 0; j < n; j++)

TEST_CASE("consList(), pushFront(), pushPack(), getSize()") {
    int n = 10;

    consList<int> l1;
    list<int> l2;
    l1.pushFront(0);
    l2.push_front(0);

    fori(n) {
        l1.pushBack(1);
        l2.push_back(1);
    }

    REQUIRE(l1.getSize() == n + 1);
    REQUIRE(l2.size() == l1.getSize());
}

TEST_CASE("consList l1{1,2,3,4, 5}") {
    consList<int> l1{1, 2, 3, 4, 5};
    REQUIRE(l1.getSize() == 5);
}








