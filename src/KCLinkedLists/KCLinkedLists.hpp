//@KCLIB_FILE_COMMENT@
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
		Node<T, DoublyLinked>* Header = nullptr;
		TraversalNode<T, DoublyLinked> EndNode;
		int Length = 0;
		bool FlagChangedLastNode = false;
	public:
		LinkedList();
		LinkedList(LinkedList<T, DoublyLinked>&& other) noexcept;
		LinkedList(LinkedList<T, DoublyLinked> const& other);
		LinkedList<T, DoublyLinked>& operator=(LinkedList<T, DoublyLinked>&& other) noexcept;
		LinkedList<T, DoublyLinked>& operator=(LinkedList<T, DoublyLinked> const& other);
		LinkedList(std::initializer_list<T> data);
		LinkedList(int length, T const* data);

		TraversalNode<T, DoublyLinked> GetHeader() const;
		TraversalNode<T, DoublyLinked> GetIndex(int index) const;
		int GetLength() const;
		bool IsEmpty() const;

		void Delete();

		LinkedList<T, DoublyLinked>& Append(T const& data);
		LinkedList<T, DoublyLinked>& Append(int const& length, T const* data);
		LinkedList<T, DoublyLinked>& Append(LinkedList<T, DoublyLinked> const& other);
		LinkedList<T, DoublyLinked>& Append(std::initializer_list<T> data);

		LinkedList<T, DoublyLinked>& Push(T const& data, int const& index = 0);
		LinkedList<T, DoublyLinked>& Push(int length, T const* data, int const& index = 0);
		LinkedList<T, DoublyLinked>& Push(LinkedList<T, DoublyLinked> const& other, int const& index = 0);
		LinkedList<T, DoublyLinked>& Push(std::initializer_list<T> data, int const& index = 0);

		T Pull(int const& index = 0);
		T Pull(TraversalNode<T, DoublyLinked>& traversalNode, int const& index = 0);
		T& operator[](int index) const;

		TraversalNode<T, DoublyLinked> Begin();
		TraversalNode<T, DoublyLinked> End();

		~LinkedList();
	};

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked> LinkedList<T, DoublyLinked>::GetHeader() const
	{
		return TraversalNode<T, DoublyLinked>(Header);
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
	TraversalNode<T, DoublyLinked> LinkedList<T, DoublyLinked>::GetIndex(const int index) const
	{
		if (index > Length - 1)
		{
			throw std::out_of_range("Index is greater than the length of list!");
		}
		if (index < 0)
		{
			throw std::out_of_range("Index is less than 0!");
		}

		TraversalNode<T, DoublyLinked> traversalNode(Header);

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
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Push(LinkedList<T, DoublyLinked> const& other, int const& index)
	{
		auto length = other.Length;
		for (auto i = length - 1; i >= 0; --i)
		{
			Push(other[i], index);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Push(const int length, T const* data, int const& index)
	{
		for (auto i = 0; i < length; ++i)
		{
			Push(data[i], index);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Push(std::initializer_list<T> data, int const& index)
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
			Node<T, DoublyLinked>* oldHeader = Header;
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
			TraversalNode<T, DoublyLinked> traversalNode(Header);
			traversalNode += index;

			data = traversalNode->Data;

			Node<T, DoublyLinked>::LinkNodes({traversalNode->Previous, traversalNode->Next});

			delete *traversalNode;
		}

		Length--;

		return data;
	}

	template <class T, bool DoublyLinked>
	T LinkedList<T, DoublyLinked>::Pull(TraversalNode<T, DoublyLinked>& traversalNode, int const& index)
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
	LinkedList<T, DoublyLinked>::LinkedList(LinkedList<T, DoublyLinked>&& other) noexcept
	{
		Push(other);
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>::LinkedList(LinkedList<T, DoublyLinked> const& other)
	{
		Push(other);
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::operator=(LinkedList<T, DoublyLinked>&& other) noexcept
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
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::operator=(LinkedList<T, DoublyLinked> const& other)
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
	TraversalNode<T, DoublyLinked> LinkedList<T, DoublyLinked>::Begin()
	{
		return TraversalNode<T, DoublyLinked>(Header);
	}

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked> LinkedList<T, DoublyLinked>::End()
	{
		if (!FlagChangedLastNode)
		{
			return EndNode;
		}
		FlagChangedLastNode = false;
		TraversalNode<T, DoublyLinked> traversalNode = Begin();
		traversalNode += Length - 1;
		EndNode = traversalNode;
		return traversalNode;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Push(T const& data, int const& index)
	{
		if (!Header)
		{
			FlagChangedLastNode = true;
		}
		auto newNode = new Node<T, DoublyLinked>(data);
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
			TraversalNode<T, DoublyLinked> traversalNode(Header);
			traversalNode += index;
			Node<T, DoublyLinked>::LinkNodes({traversalNode->Previous, newNode, *traversalNode});
		}
		else
		{
			Node<T, DoublyLinked>::LinkNodes({newNode, Header});
			Header = newNode;
		}

		Length++;
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Append(T const& data)
	{
		if (!Header)
		{
			Push(data);
			return *this;
		}
		auto previousHeader = End();
		auto newNode = new Node<T, DoublyLinked>(data);
		Node<T, DoublyLinked>::LinkNodes({*previousHeader, newNode});
		++Length;
		FlagChangedLastNode = true;
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Append(LinkedList<T, DoublyLinked> const& other)
	{
		auto length = other.GetLength();
		for (auto i = 0; i < length; ++i)
		{
			Append(other.GetIndex(i)->Data);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Append(int const& length, T const* data)
	{
		for (auto i = 0; i < length; ++i)
		{
			Append(data[i]);
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	LinkedList<T, DoublyLinked>&
	LinkedList<T, DoublyLinked>::Append(std::initializer_list<T> data)
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
