#pragma once

#include <iostream>
#include <utility>

namespace KC
{
	template <typename T>
	class ListNode final
	{
	public:
		T Data;
		ListNode<T>* Next;
		ListNode<T>* Previous;

		ListNode() = default;
		ListNode(ListNode<T> const& other) : Data(other.Data), Next(nullptr), Previous(nullptr)
		{
		}
		ListNode(ListNode<T>&& other) noexcept
		{
			Data = other.Data;
			Next = other.Next;
			Previous = other.Previous;
			other.Data = 0;
			other.Next = nullptr;
			other.Previous = nullptr;
		}
		explicit ListNode(T const& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr) : Data{ data }, Next(next), Previous(previous)
		{
		}

		ListNode<T>& operator=(ListNode<T> const& other)
		{
			Data = other.Data;
			return *this;
		}

		ListNode<T>& operator=(ListNode<T>&& other) noexcept
		{
			if (this != &other)
			{
				Data = other.Data;
				other.Data = 0;
			}
			return *this;
		}
		explicit operator T() const
		{
			return Data;
		}
		T& operator*()
		{
			return Data;
		}
		T& operator->()
		{
			return Data;
		}

		static void LinkNodes(int const length, ListNode<T>** nodes)
		{
			ListNode<T>* trail = nodes[0];
			for (auto i = 1; i < length; i++)
			{
				ListNode<T>* head = nodes[i];
				if (trail)
				{
					trail->Next = head;
				}
				if (head)
				{
					head->Previous = trail;
				}
				trail = head;
			}
		}
		static void LinkNodes(int const length, ListNode<T>* nodes)
		{
			ListNode<T> trail = nodes;
			for (auto i = 0; i < length; i++)
			{
				ListNode<T> head = nodes + i;
				if (trail != head && head && trail)
				{
					trail->Next = head;
					head->Previous = trail;
					trail = head;
				}
			}
		}
		static void LinkNodes(std::initializer_list<ListNode<T>*> nodes)
		{
			auto nodeList = new ListNode<T>*[nodes.size()];
			auto index = 0;
			for (auto& i : nodes)
			{
				nodeList[index++] = i;
			}
			LinkNodes(nodes.size(), nodeList);
			delete[] nodeList;
		}
		static void LinkNodes(std::initializer_list<ListNode<T>> nodes)
		{
			auto nodeList = new ListNode<T>[nodes.size()];
			memcpy(nodeList, nodes.begin(), nodes.size());
			LinkNodes(nodes.size(), nodeList);
		}

		~ListNode() = default;
	};

	template <typename T>
	class TraversalNode final
	{
	public:
		ListNode<T>* Current;

		TraversalNode() : Current(nullptr)
		{
		}

		TraversalNode(ListNode<T>* node) : Current(node)
		{
		}
		TraversalNode<T>& operator++()
		{
			Current = Current->Next;
			return *this;
		}
		TraversalNode<T> operator++(int)
		{
			TraversalNode<T> result(*this);
			++*this;
			return result;
		}
		TraversalNode<T>& operator--()
		{
			Current = Current->Previous;
			return *this;
		}
		TraversalNode<T> operator--(int)
		{
			TraversalNode<T> result(*this);
			--*this;
			return result;
		}
		TraversalNode<T>& operator+=(int const num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator++();
			}
			return *this;
		}
		TraversalNode<T>& operator-=(const int num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator--();
			}
			return *this;
		}
		ListNode<T>* operator*()
		{
			return Current;
		}
		ListNode<T>* operator->()
		{
			return Current;
		}
		bool operator== (TraversalNode<T>& other) const
		{
			return Current == other.Current;
		}
		bool operator== (ListNode<T>& other) const
		{
			return Current == &other;
		}
		operator bool() const
		{
			return Current != nullptr;
		}
		operator ListNode<T>() const
		{
			return *Current;
		}

		TraversalNode<T> operator+(int const& right)
		{
			auto temp = *this;
			temp += right;
			return temp;
		}
		TraversalNode<T> operator-(int const& right)
		{
			auto temp = *this;
			temp -= right;
			return temp;
		}
	};


	template <class T>
	class List
	{
	protected:
		ListNode<T>* Header = nullptr;
		int Length = 0;
	public:
		List() = default;

		List(List<T>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}
		List(List<T> const& other)
		{
			Push(other);
		}
		List(std::initializer_list<T> data)
		{
			Push(data);
		}
		List(const int length, T const* data)
		{
			Push(length, data);
		}

		TraversalNode<T> GetHeader() const
		{
			return TraversalNode<T>(Header);
		}
		int GetLength() const
		{
			return Length;
		}
		ListNode<T>& GetIndex(const int index) const
		{
			if (index > Length - 1)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}
			if (index < 0)
			{
				throw std::out_of_range("Index is less than 0!");
			}

			TraversalNode<T> traversalNode = Header;

			traversalNode += index;

			return **traversalNode;
		}

		void Delete()
		{
			while (Header)
			{
				Pull();
			}
		}

		void Push(T const& data, int const& index = 0)
		{
			auto newNode = new ListNode<T>(data, Header);
			if (Header && index != 0)
			{
				TraversalNode<T> traversalNode(Header);
				traversalNode += index;
				ListNode<T>::LinkNodes({ traversalNode->Previous, newNode, *traversalNode });
			}
			else
			{
				ListNode<T>::LinkNodes({ newNode, Header });
				Header = newNode;
			}

			Length++;
		}
		void Push(List<T> const& other, int const& index = 0)
		{
			auto length = other.Length;
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(other[i], index);
			}
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(data[i], index);
			}
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			Push(data.size(), data.begin(), index);
		}

		T Pull(int const& index = 0)
		{
			if (!Header)
			{
				return 0;
			}

			T data;

			if (index == 0)
			{
				data = Header->Data;
				ListNode<T>* oldHeader = Header;
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
				TraversalNode<T> traversalNode(Header);
				traversalNode += index;

				data = traversalNode->Data;

				ListNode<T>::LinkNodes({ traversalNode->Previous, traversalNode->Next });

				delete *traversalNode;
			}

			Length--;

			return data;
		}

		T Pull(TraversalNode<T>& traversalNode, int const& index = 0)
		{
			if (traversalNode->Next == *traversalNode)
			{
				traversalNode.Current = nullptr;
			}
			else if (&GetIndex(index) == *traversalNode)
			{
				++traversalNode;
			}
			return Pull(index);

		}


		List<T>& operator=(List<T> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		List<T>& operator=(List<T>&& other) noexcept
		{
			Delete();

			if (this != &other)
			{
				Header = other.Header;
				Length = other.Length;
				other.Header = nullptr;
				other.Length = 0;
			}

			return *this;
		}
		List<T>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		List<T>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		List<T>& operator<<(List<T> const& other)
		{
			Push(other);
			return *this;
		}
		List<T>& operator >> (T& data)
		{
			data = Pull();
			return *this;
		}
		T& operator[](const int index) const
		{
			return GetIndex(index).Data;
		}
		operator bool() const
		{
			return Header != nullptr;
		}

		~List()
		{
			Delete();
		}
	};

	template<typename T>
	class LinkedList : public List<T>
	{
	protected:
		using List<T>::Header;
		using List<T>::Length;
		TraversalNode<T> EndNode;
		bool FlagChangedLastNode = false;
	public:
		using List<T>::GetHeader;
		using List<T>::GetLength;
		using List<T>::GetIndex;
		using List<T>::Delete;
		using List<T>::Pull;
		using List<T>::operator=;
		using List<T>::operator[];
		using List<T>::operator bool;
		using List<T>::operator >> ;

		LinkedList() : List<T>(), EndNode(nullptr)
		{
		}
		LinkedList(List<T>&& other) noexcept : List<T>(other)
		{
		}
		LinkedList(List<T> const& other)// : List<T>(other)
		{
			Push(other);
		}
		LinkedList(std::initializer_list<T> data)// : List<T>(data)
		{
			Push(data);
		}
		LinkedList(const int length, T const* data)// : List<T>(length, data)
		{
			Push(length, data);
		}

		TraversalNode<T> Begin()
		{
			return TraversalNode<T>(Header);
		}
		TraversalNode<T> End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode<T> traversalNode = Begin();
			traversalNode += Length - 1;
			EndNode = traversalNode;
			return traversalNode;
		}

		void Push(T const& data, int const& index = 0)
		{
			if (!Header)
			{
				FlagChangedLastNode = true;
			}
			List<T>::Push(data, index);
		}
		void Push(List<T> const& other, int const& index = 0)
		{
			auto length = other.Length;
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(other[i], index);
			}
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(data[i], index);
			}
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			Push(data.size(), data.begin(), index);
		}

		void Append(T const& data)
		{
			ListNode<T> previousHeader = End();
			Header = new ListNode<T>(data);
			ListNode<T>::LinkNodes({ *Header,previousHeader });
			++Length;
			FlagChangedLastNode = true;
		}
		void Append(List<T> const& other)
		{
			auto length = other.GetLength();
			for (auto i = 0; i > length; ++i)
			{
				Append(other.GetIndex(i));
			}
		}
		void Append(int const& length, T const* data)
		{
			Append(List<T>(length, data));
		}
		void Append(std::initializer_list<T> data)
		{
			Append(List<T>(data));
		}

		LinkedList<T>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T>& operator<<(List<T> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			TraversalNode<T> trav1 = Header;
			TraversalNode<T> trav2 = Header;
			while (*trav1 && *trav2 && trav2->Next)
			{
				++trav1;
				trav2 += 2;
				if (*trav1 == *trav2)
				{
					return true;
				}
			}
			return false;
		}
	};

	template<typename T>
	class CircleLinkedList : public LinkedList<T>
	{
	protected:
		using LinkedList<T>::Header;
		using LinkedList<T>::Length;
		using LinkedList<T>::DetectCircle; // For constructors only
		using LinkedList<T>::End; // For constructors only
	public:
		using LinkedList<T>::GetHeader;
		using LinkedList<T>::GetLength;
		using LinkedList<T>::GetIndex;
		using LinkedList<T>::operator[];
		using LinkedList<T>::operator bool;
		using LinkedList<T>::Begin;

		CircleLinkedList() = default;
		CircleLinkedList(List<T>&& other) noexcept : LinkedList<T>(other)
		{
			if (!DetectCircle())
			{
				ListNode<T>::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(List<T> const& other) : LinkedList<T>(other)
		{
			if (!DetectCircle())
			{
				ListNode<T>::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(std::initializer_list<T> data) : LinkedList<T>(data)
		{
			if (!DetectCircle())
			{
				ListNode<T>::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(const int length, T const* data) : LinkedList<T>(length, data)
		{
			if (!DetectCircle())
			{
				ListNode<T>::LinkNodes({ *End(), *Begin() });
			}
		}

		void Delete()
		{
			while (Header)
			{
				Pull();
			}
		}

		void Push(T const& data, int const& index = 0)
		{
			auto lastNode = Begin()->Previous;
			LinkedList<T>::Push(data, index);
			if (index == 0)
				ListNode<T>::LinkNodes({ lastNode, *Begin() });
		}
		void Push(List<T> const& other, int const& index = 0)
		{
			auto lastNode = Begin()->Previous;
			LinkedList<T>::Push(other, index);
			if (index == 0)
				ListNode<T>::LinkNodes({ lastNode, *Begin() });
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			auto lastNode = Begin()->Previous;
			LinkedList<T>::Push(length, data, index);
			if (index == 0)
				ListNode<T>::LinkNodes({ lastNode, *Begin() });
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			auto lastNode = Begin()->Previous;
			LinkedList<T>::Push(data, index);
			if (index == 0)
				ListNode<T>::LinkNodes({ lastNode, *Begin() });
		}

		T Pull(int const& index = 0)
		{
			if (index == 0)
				ListNode<T>::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T>::Pull(index);
			return data;
		}

		T Pull(TraversalNode<T>& traversalNode, int const& index = 0)
		{
			if (index == 0)
				ListNode<T>::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T>::Pull(traversalNode, index);
			return data;
		}

		CircleLinkedList<T>& operator=(List<T> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		CircleLinkedList<T>& operator=(List<T>&& other) noexcept
		{
			Delete();

			if (this != &other)
			{
				Header = other.Header;
				Length = other.Length;
				other.Header = nullptr;
				other.Length = 0;

				if (!DetectCircle())
				{
					ListNode<T>::LinkNodes(End(), Begin());
				}
			}

			return *this;
		}
		CircleLinkedList<T>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T>& operator<<(List<T> const& other)
		{
			Push(other);
			return *this;
		}
		CircleLinkedList<T>& operator >> (T& data)
		{
			data = Pull();
			return *this;
		}

		~CircleLinkedList()
		{
			Delete();
		}
	};
}

template <typename T>
auto operator<<(std::ostream& stream, const KC::ListNode<T>& node) -> std::ostream&
{
	std::cout << node.Data;
	return stream;
}

template <typename T>
auto operator<<(std::ostream& stream, const KC::List<T>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		KC::ListNode<T>& index = list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}

template <typename T>
auto operator<<(std::ostream& stream, const KC::LinkedList<T>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		KC::ListNode<T>& index = list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}

template <typename T>
auto operator<<(std::ostream& stream, const KC::CircleLinkedList<T>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		KC::ListNode<T>& index = list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
