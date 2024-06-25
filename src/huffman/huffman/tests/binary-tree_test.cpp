#ifdef TEST_BUILD

#include <Vector>
#include "util.h"
#include "catch.hpp"
#include "memory"
#include <data/binary-tree.h>
#include <tests/testfunctions.h>
#include <iostream>


TEST_CASE("Binary basic Tree testsing") {

    std::unique_ptr<data::Leaf<char>> A = std::make_unique<data::Leaf<char>>('A');
    std::unique_ptr<data::Leaf<char>> B = std::make_unique<data::Leaf<char>>('B');
    std::unique_ptr<data::Leaf<char>> C = std::make_unique<data::Leaf<char>>('C');
    std::unique_ptr<data::Leaf<char>> D = std::make_unique<data::Leaf<char>>('D');


    std::unique_ptr<data::Branch<char>> rightBranch = std::make_unique<data::Branch<char>>(std::move(A), std::move(B));
    std::unique_ptr<data::Branch<char>> leftBranch = std::make_unique<data::Branch<char>>(std::move(C), std::move(D));
    std::unique_ptr<data::Branch<char>> rootBranch = std::make_unique<data::Branch<char>>(std::move(rightBranch), std::move(leftBranch));

    data::Leaf<int> myleaf(9);
    REQUIRE(myleaf.getValue() == 9);
    data::Node<int>& mynode = myleaf;
    auto newLeaf = static_cast<data::Leaf<int>&>(mynode);
    REQUIRE(newLeaf.getValue() == 9);

    REQUIRE(tests::TreeTraversal(*rootBranch) == std::vector<char> {'A', 'B', 'C', 'D'});

}



#endif