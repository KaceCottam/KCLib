#include <iostream>
#include <functional>
#include <KCBinarySearchTree.hpp>

int main()
{
	KC::BinarySearchTree<int> a;
	std::cout<< "post order: " << std::endl;
	a << 4 << 2 << 7 << 1 << 3 << 6 << 9;
	a.PrintPostOrder();
	std::cout << std::endl;
	std::cout<< "pre order: " << std::endl;
	a.PrintPreOrder();
	std::cout << std::endl;
	std::cout << "in order: " << std::endl;
	a.PrintInOrder();
	std::cout << std::endl;
	std::cin.get();
}
