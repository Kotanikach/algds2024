#include "pch.h"
#include "gtest/gtest.h"

extern "C" {
#include "../Laba2.c"
}

TEST(TreapInsertionTest, InsertionTest1) {
    Treap treap;
    treap.tree = nullptr;

    insert(&treap, 5, 10);
    insert(&treap, 3, 15);
    insert(&treap, 8, 5);

    char result[100] = "\0";
    PrintTree(treap.tree, result);
    EXPECT_STREQ("(5,10)(3,15)(8,5)", result);
}

TEST(TreapInsertionTest, InsertionTest2) {
    Treap treap;
    treap.tree = nullptr;

    insert(&treap, 6, 6);
    insert(&treap, 7, 0);
    insert(&treap, 8, 15);

    char result[100] = "\0";
    PrintTree(treap.tree, result);
    EXPECT_STREQ("(6,6)(7,0)(8,15)", result);
}

TEST(TreapDeletionTest, DeletionTest1) {
    Treap treap;
    treap.tree = nullptr;

    insert(&treap, 5, 10);
    insert(&treap, 3, 15);
    insert(&treap, 8, 5);
    insert(&treap, 2, 20);

    removeNode(&treap, 3); 

    char result[100] = "\0";
    PrintTree(treap.tree, result);
    EXPECT_STREQ("(5,10)(2,20)(8,5)", result);
}

TEST(TreapDeletionTest, DeletionTest2) {
    Treap treap;
    treap.tree = nullptr;

    insert(&treap, 6, 1);
    insert(&treap, 2, 5);
    insert(&treap, 4, 9);
    insert(&treap, 3, 20);

    removeNode(&treap, 1); 

    char result[100] = "\0";
    PrintTree(treap.tree, result);
    EXPECT_STREQ("(6,1)(2,5)(4,9)(3,20)", result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}