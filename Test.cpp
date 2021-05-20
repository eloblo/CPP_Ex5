#include "doctest.h"
using namespace std;
#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("pre order") {
    BinaryTree<int> bt;
    bt.add_root(1).add_left(1, 9).add_left(9, 4).add_right(9, 5).add_right(1, 3).add_left(1, 2);
    auto it = bt.begin_preorder();
    CHECK(*it++ == 1);
    CHECK(*it++ == 2);
    CHECK(*it++ == 3);
    CHECK(*it++ == 5);
    CHECK(*it++ == 4);
    CHECK(it == nullptr);
}

TEST_CASE("in order") {
    BinaryTree<int> bt;
    bt.add_root(1).add_left(1, 9).add_left(9, 4).add_right(9, 5).add_right(1, 3).add_left(1, 2);
    auto it = bt.begin_inorder();
    CHECK(*it++ == 4);
    CHECK(*it++ == 2);
    CHECK(*it++ == 5);
    CHECK(*it++ == 1);
    CHECK(*it++ == 3);
    CHECK(it == nullptr);
}

TEST_CASE("post order") {
    BinaryTree<int> bt;
    bt.add_root(1).add_left(1, 9).add_left(9, 4).add_right(9, 5).add_right(1, 3).add_left(1, 2);
    auto it = bt.begin_postorder();
    CHECK(*it++ == 4);
    CHECK(*it++ == 5);
    CHECK(*it++ == 2);
    CHECK(*it++ == 3);
    CHECK(*it++ == 1);
    CHECK(it == nullptr);
}

TEST_CASE("for each") {
    BinaryTree<string> bt;
    bt.add_root("1").add_left("1", "9").add_left("9", "4").add_right("9", "5").add_right("1", "3").add_left("1", "2");
    for (const string& node: bt) { 
    	CHECK_THROWS(node.size());
    }
}

TEST_CASE("bad add"){
	BinaryTree<int> bt;
	CHECK_THROWS(bt.add_left(1, 9));
	bt.add_root(1).add_left(1, 9).add_left(9, 4).add_right(9, 5).add_right(1, 3).add_left(1, 2);
	CHECK_THROWS(bt.add_left(20, 9));
	CHECK_THROWS(bt.add_left(9, 13));
}
