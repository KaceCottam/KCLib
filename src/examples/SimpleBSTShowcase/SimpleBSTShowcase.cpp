#include <iostream>
#include <KCBinarySearchTree.hpp>
int main()
{
	KC::BinarySearchTree<int> a;
	a << 5 << 4 << 7 << 8 << 1 << 9 << 3 << 2 << 5;
	a.PrintPostOrder();
	std::cout << std::endl;
	a.PrintPreOrder();
	std::cout << std::endl;
	a.PrintInOrder();
    std::cout << "Hello World!\n";
	std::cin.get();
}
