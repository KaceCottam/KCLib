#include <Catch2/catch.hpp>
#include <KCLib/KCBinarySearchTree.hpp>

TEMPLATE_TEST_CASE("template works with multiple types","[bst][multiple values][insert]",int,float,char,double,long,long long)
{
	using bst = KC::BinarySearchTree<TestType>;
	bst tree;
	SECTION("tree is empty")
	{
		REQUIRE(tree.IsEmpty());
	}
	SECTION("9 values are added to the tree, 1 of them is the same")
	{
	tree << 44 << 17 << 78 << 32 << 50 << 88 << 48 << 62 << 32;
		SECTION("tree is no longer empty and correct size")
		{
			REQUIRE(!tree.IsEmpty());
			REQUIRE(tree.GetLength() == 8);
		}
		SECTION("InOrder is correct")
		{
			typename bst::InOrderTraversalNode traveler = tree.GetRoot();
			REQUIRE(traveler->Data == 17);
			traveler.Cycle();
			REQUIRE(traveler->Data == 32);
			traveler.Cycle();
			REQUIRE(traveler->Data == 44);
			traveler.Cycle();
			REQUIRE(traveler->Data == 48);
			traveler.Cycle();
			REQUIRE(traveler->Data == 50);
			traveler.Cycle();
			REQUIRE(traveler->Data == 62);
			traveler.Cycle();
			REQUIRE(traveler->Data == 78);
			traveler.Cycle();
			REQUIRE(traveler->Data == 88);
		}
		SECTION("PostOrder is correct")
		{
			typename bst::PreOrderTraversalNode traveler = tree.GetRoot();
			REQUIRE(traveler->Data == 44);
			traveler.Cycle();
			REQUIRE(traveler->Data == 17);
			traveler.Cycle();
			REQUIRE(traveler->Data == 32);
			traveler.Cycle();
			REQUIRE(traveler->Data == 78);
			traveler.Cycle();
			REQUIRE(traveler->Data == 50);
			traveler.Cycle();
			REQUIRE(traveler->Data == 48);
			traveler.Cycle();
			REQUIRE(traveler->Data == 62);
			traveler.Cycle();
			REQUIRE(traveler->Data == 88);
		}
		SECTION("PostOrder is correct")
		{
			typename bst::PostOrderTraversalNode traveler = tree.GetRoot();
			REQUIRE(traveler->Data == 32);
			traveler.Cycle();
			REQUIRE(traveler->Data == 17);
			traveler.Cycle();
			REQUIRE(traveler->Data == 48);
			traveler.Cycle();
			REQUIRE(traveler->Data == 62);
			traveler.Cycle();
			REQUIRE(traveler->Data == 50);
			traveler.Cycle();
			REQUIRE(traveler->Data == 88);
			traveler.Cycle();
			REQUIRE(traveler->Data == 78);
			traveler.Cycle();
			REQUIRE(traveler->Data == 44);
		}
	}
}
