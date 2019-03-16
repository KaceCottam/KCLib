#pragma once

#include <stdexcept>
#include <KCNodes.hpp>
#include <initializer_list>

namespace KC
{
	template <class T, bool DoublyLinked>
	class LinkedList final
	{
	protected:
		using NodeT = Node<T, DoublyLinked>;
		using TraversalNodeT = TraversalNode<T, DoublyLinked>;
		using LinkedListT = LinkedList<T, DoublyLinked>;
		NodeT* Header = nullptr;
		TraversalNodeT EndNode;
		int Length = 0;
		bool FlagChangedLastNode = false;
	public:
		LinkedList();
		LinkedList(LinkedListT&& other) noexcept;
		LinkedList(LinkedListT const& other);
		LinkedListT& operator=(LinkedListT&& other) noexcept;
		LinkedListT& operator=(LinkedListT const& other);
		LinkedList(std::initializer_list<T> data);
		LinkedList(int length, T const* data);

		TraversalNodeT GetHeader() const;
		TraversalNodeT GetIndex(int index) const;
		int GetLength() const;
		bool IsEmpty() const;

		void Delete();

		LinkedListT& Append(T const& data);
		LinkedListT& Append(int const& length, T const* data);
		LinkedListT& Append(LinkedListT const& other);
		LinkedListT& Append(std::initializer_list<T> data);

		LinkedListT& Push(T const& data, int const& index = 0);
		LinkedListT& Push(int length, T const* data, int const& index = 0);
		LinkedListT& Push(LinkedListT const& other, int const& index = 0);
		LinkedListT& Push(std::initializer_list<T> data, int const& index = 0);

		T Pull(int const& index = 0);
		T Pull(TraversalNodeT& traversalNode, int const& index = 0);
		T& operator[](int index) const;

		TraversalNodeT Begin();
		TraversalNodeT End();

		~LinkedList();
	};

	template <class T, bool DoublyLinked>
	typename LinkedList<T, DoublyLinked>::TraversalNodeT LinkedList<T, DoublyLinked>::GetHeader() const
	{
		return TraversalNodeT(Header);
	}

	template <class T, bool DoublyLinked>
	int LinkedList<T, DoublyLinked>::GetLength() const
	{
		return Length;
	}

	template <class T, bool DoublyLinked>
	bool LinkedList<T, DoublyLinked>::IsEmpty() const
	{
		return Length == 0;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::GetIndex(const int index) const -> TraversalNodeT
	{
		if (index > Length - 1)
		{
			throw std::out_of_range("Index is greater than the length of list!");
		}
		if (index < 0)
		{
			throw std::out_of_range("Index is less than 0!");
		}

		TraversalNodeT traversalNode(Header);

		traversalNode += index;

		return traversalNode;
	}

	template <class T, bool DoublyLinked>
	void LinkedList<T, DoublyLinked>::Delete()
	{
		while (Header)
		{
			Pull();
		}
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Push(LinkedListT const& other, int const& index) -> LinkedListT&
	{
		auto length = other.Length;
		for (auto i = length - 1; i >= 0; --i)
		{
			Push(other[i], index);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Push(const int length, T const* data, int const& index) -> LinkedListT&
	{
		for (auto i = 0; i < length; ++i)
		{
			Push(data[i], index);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Push(std::initializer_list<T> data, int const& index) -> LinkedListT&
	{
		Push(data.size(), data.begin(), index);
		return *this;
	}

	template <class T, bool DoublyLinked>
	T LinkedList<T, DoublyLinked>::Pull(int const& index)
	{
		if (!Header)
		{
			return T();
		}

		T data;

		if (index == 0)
		{
			data = Header->Data;
			NodeT* oldHeader = Header;
			if (oldHeader != Header->Next)
			{
				Header = Header->Next;
			}
			else
			{
				Header = nullptr;
			}

			/*
			 *  Header can be equal to nullptr after this because
			 *  the Push() functions have the beginning node and
			 *  next node's previous and next pointers
			 *  respectively = nullptr.
			 */

			delete oldHeader;
		}
		else
		{
			TraversalNodeT traversalNode(Header);
			traversalNode += index;

			data = traversalNode->Data;

			NodeT::LinkNodes({traversalNode->Previous, traversalNode->Next});

			delete *traversalNode;
		}

		Length--;

		return data;
	}

	template <class T, bool DoublyLinked>
	T LinkedList<T, DoublyLinked>::Pull(TraversalNodeT& traversalNode, int const& index)
	{
		if (traversalNode->Next == *traversalNode)
		{
			traversalNode.Current = nullptr;
		}
		else if (*GetIndex(index) == *traversalNode)
		{
			++traversalNode;
		}
		return Pull(index);
	}

	template <class T, bool DoublyLinked>
	T& LinkedList<T, DoublyLinked>::operator[](const int index) const
	{
		return GetIndex(index)->Data;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList()
	{
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList(LinkedListT&& other) noexcept
	{
		Push(other);
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList(LinkedListT const& other)
	{
		Push(other);
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::operator=(LinkedListT&& other) noexcept -> LinkedListT&
	{
		if (this != &other)
		{
			Delete();
			Header = other.Header;
			Length = other.Length;
			other.Length = 0;
			other.Header = nullptr;
			FlagChangedLastNode = true;
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::operator=(LinkedListT const& other) -> LinkedListT&
	{
		if (this != &other)
		{
			Delete();
			Push(other);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList(std::initializer_list<T> data)
	{
		Push(data);
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList(const int length, T const* data)
	{
		Push(length, data);
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Begin() -> TraversalNodeT
	{
		return TraversalNodeT(Header);
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::End() -> TraversalNodeT
	{
		if (!FlagChangedLastNode)
		{
			return EndNode;
		}
		FlagChangedLastNode = false;
		TraversalNodeT traversalNode = Begin();
		traversalNode += Length - 1;
		EndNode = traversalNode;
		return traversalNode;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Push(T const& data, int const& index) -> LinkedListT&
	{
		if (!Header)
		{
			FlagChangedLastNode = true;
		}
		auto newNode = new NodeT(data);
		if (Header && index != 0)
		{
			if (index > Length - 1)
			{
				throw std::out_of_range("Index greater than length of the list!");
			}
			if (index < 0)
			{
				throw std::out_of_range("Index less than 0!");
			}
			TraversalNodeT traversalNode(Header);
			traversalNode += index;
			NodeT::LinkNodes({traversalNode->Previous, newNode, *traversalNode});
		}
		else
		{
			NodeT::LinkNodes({newNode, Header});
			Header = newNode;
		}

		Length++;
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Append(T const& data) -> LinkedListT&
	{
		if (!Header)
		{
			Push(data);
			return *this;
		}
		auto previousHeader = End();
		auto newNode = new NodeT(data);
		NodeT::LinkNodes({*previousHeader, newNode});
		++Length;
		FlagChangedLastNode = true;
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Append(LinkedListT const& other) -> LinkedListT&
	{
		auto length = other.GetLength();
		for (auto i = 0; i < length; ++i)
		{
			Append(other.GetIndex(i)->Data);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Append(int const& length, T const* data) -> LinkedListT&
	{
		for (auto i = 0; i < length; ++i)
		{
			Append(data[i]);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto LinkedList<T, DoublyLinked>::Append(std::initializer_list<T> data) -> LinkedListT&
	{
		Append(data.size(), data.begin());
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::~LinkedList()
	{
		while (Header)
		{
			Pull();
		}
	}
}
