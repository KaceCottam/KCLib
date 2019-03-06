#pragma once

#include <iostream>
#include <utility>

namespace KC
{
	template <typename T, bool DoublyLinked = true>
	class List
	{
	public:
		class Node final
		{
		public:
			T Data;
			Node* Next = nullptr;
			typename std::enable_if<DoublyLinked, Node*>::type Previous = nullptr;

			Node() = default;

			Node(Node const& other) = default;

			Node(Node&& other) noexcept = default;

			explicit Node(T const& data, Node* next = nullptr, Node* previous = nullptr) : Data{data}, Next(next),
			                                                                               Previous(previous)
			{
			}

			Node& operator=(Node const& other)
			{
				Data = other.Data;
				return *this;
			}

			Node& operator=(Node&& other) noexcept
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

			static void LinkNodes(int const length, Node** nodes)
			{
				Node* trail = nodes[0];
				for (auto i = 1; i < length; i++)
				{
					Node* head = nodes[i];
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

			static void LinkNodes(std::initializer_list<Node*> nodes)
			{
				auto nodeList = new Node*[nodes.size()];
				auto index = 0;
				for (auto& i : nodes)
				{
					nodeList[index++] = i;
				}
				LinkNodes(nodes.size(), nodeList);
				delete[] nodeList;
			}

			~Node() = default;
		};

		class TraversalNode final
		{
		public:
			Node* Current = nullptr;

			TraversalNode() = default;

			TraversalNode(Node* node) : Current(node)
			{
			}

			TraversalNode& operator++()
			{
				Current = Current->Next;
				return *this;
			}

			TraversalNode operator++(int)
			{
				TraversalNode result(*this);
				++*this;
				return result;
			}

			TraversalNode& operator--()
			{
				if (DoublyLinked)
				{
					Current = Current->Previous;
				}
				return *this;
			}

			TraversalNode operator--(int)
			{
				TraversalNode result(*this);
				if (DoublyLinked)
				{
					--*this;
				}
				return result;
			}

			TraversalNode& operator+=(int const num)
			{
				for (auto i = 0; i < num; i++)
				{
					operator++();
				}
				return *this;
			}

			TraversalNode& operator-=(const int num)
			{
				if (DoublyLinked)
				{
					for (auto i = 0; i < num; i++)
					{
						operator--();
					}
				}
				return *this;
			}

			Node* operator*()
			{
				return Current;
			}

			Node* operator->()
			{
				return Current;
			}

			bool operator==(TraversalNode& other) const
			{
				return Current == other.Current;
			}

			bool operator==(Node& other) const
			{
				return Current == &other;
			}

			operator bool() const
			{
				return Current != nullptr;
			}

			operator Node() const
			{
				return *Current;
			}

			TraversalNode operator+(int const& right)
			{
				auto temp = *this;
				temp += right;
				return temp;
			}

			TraversalNode operator-(int const& right)
			{
				auto temp = *this;
				if (DoublyLinked)
				{
					temp -= right;
				}
				return temp;
			}
		};

	protected:
		Node* Header = nullptr;
		int Length = 0;
	public:
		List() = default;

		List(List<T, true>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}

		List(List<T, true> const& other)
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

		TraversalNode GetHeader() const
		{
			return TraversalNode(Header);
		}

		int GetLength() const
		{
			return Length;
		}

		TraversalNode GetIndex(const int index) const
		{
			if (index > Length - 1)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}
			if (index < 0)
			{
				throw std::out_of_range("Index is less than 0!");
			}

			TraversalNode traversalNode = Header;

			traversalNode += index;

			return traversalNode;
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
			auto newNode = new Node(data, Header);
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
				TraversalNode traversalNode(Header);
				traversalNode += index;
				Node::LinkNodes({traversalNode->Previous, newNode, *traversalNode});
			}
			else
			{
				Node::LinkNodes({newNode, Header});
				Header = newNode;
			}

			Length++;
		}

		void Push(List<T, true> const& other, int const& index = 0)
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
				Node* oldHeader = Header;
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
				TraversalNode traversalNode(Header);
				traversalNode += index;

				data = traversalNode->Data;

				Node::LinkNodes({traversalNode->Previous, traversalNode->Next});

				delete *traversalNode;
			}

			Length--;

			return data;
		}

		T Pull(TraversalNode& traversalNode, int const& index = 0)
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


		List<T, DoublyLinked>& operator=(List<T, DoublyLinked> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}

		List<T, DoublyLinked>& operator=(List<T, DoublyLinked>&& other) noexcept
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

		List<T, DoublyLinked>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}

		List<T, DoublyLinked>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}

		List<T, DoublyLinked>& operator<<(List<T, DoublyLinked> const& other)
		{
			Push(other);
			return *this;
		}

		List<T, DoublyLinked>& operator >>(T& data)
		{
			data = Pull();
			return *this;
		}

		T& operator[](const int index) const
		{
			return GetIndex(index)->Data;
		}

		operator bool() const
		{
			return Header != nullptr;
		}

		bool IsEmpty() const
		{
			return Header == nullptr;
		}

		~List()
		{
			Delete();
		}
	};

	template <typename T, bool DoublyLinked = true>
	class LinkedList : public List<T, DoublyLinked>
	{
	protected:
		using List<T, DoublyLinked>::Header;
		using List<T, DoublyLinked>::Length;
		typename List<T, DoublyLinked>::TraversalNode EndNode = nullptr;
		bool FlagChangedLastNode = false;
	public:
		using List<T, DoublyLinked>::GetHeader;
		using List<T, DoublyLinked>::GetLength;
		using List<T, DoublyLinked>::GetIndex;
		using List<T, DoublyLinked>::Delete;
		using List<T, DoublyLinked>::Pull;
		using List<T, DoublyLinked>::operator=;
		using List<T, DoublyLinked>::operator[];
		using List<T, DoublyLinked>::operator bool;
		using List<T, DoublyLinked>::operator >> ;

		LinkedList() : List<T, DoublyLinked>(), EndNode(nullptr)
		{
		}

		LinkedList(List<T, DoublyLinked>&& other) noexcept : List<T, DoublyLinked>(other)
		{
		}

		LinkedList(List<T, DoublyLinked> const& other)
		{
			Push(other);
		}

		LinkedList(std::initializer_list<T> data)
		{
			Push(data);
		}

		LinkedList(const int length, T const* data)
		{
			Push(length, data);
		}

		typename List<T, DoublyLinked>::TraversalNode Begin()
		{
			return TraversalNode(Header);
		}

		typename List<T, DoublyLinked>::TraversalNode End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			typename List<T, DoublyLinked>::TraversalNode traversalNode = Begin();
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
			List<T, DoublyLinked>::Push(data, index);
		}

		void Push(List<T, DoublyLinked> const& other, int const& index = 0)
		{
			auto length = other.GetLength();
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
			if (!Header)
			{
				Push(data);
				return;
			}
			auto previousHeader = End();
			auto newNode = new typename List<T, DoublyLinked>::Node(data);
			typename List<T, DoublyLinked>::Node::LinkNodes({*previousHeader, newNode});
			++Length;
			FlagChangedLastNode = true;
		}

		void Append(List<T, DoublyLinked> const& other)
		{
			auto length = other.GetLength();
			for (auto i = 0; i < length; ++i)
			{
				Append(other.GetIndex(i)->Data);
			}
		}

		void Append(int const& length, T const* data)
		{
			for (auto i = 0; i < length; ++i)
			{
				Append(data[i]);
			}
		}

		void Append(std::initializer_list<T> data)
		{
			Append(data.size(), data.begin());
		}

		LinkedList<T, DoublyLinked>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}

		LinkedList<T, DoublyLinked>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}

		LinkedList<T, DoublyLinked>& operator<<(List<T, true> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			typename List<T, DoublyLinked>::TraversalNode trav1 = Header;
			typename List<T, DoublyLinked>::TraversalNode trav2 = Header;
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

	template <class T>
	using SinglyLinkedList = LinkedList<T, false>;
	template <class T>
	using DoublyLinkedList = LinkedList<T, true>;

	template <typename T = int, bool DoublyLinked = true>
	class CircleLinkedList : public LinkedList<T, DoublyLinked>
	{
	protected:
		using LinkedList<T, DoublyLinked>::Header;
		using LinkedList<T, DoublyLinked>::Length;
		using LinkedList<T, DoublyLinked>::DetectCircle; // For constructors only
		using LinkedList<T, DoublyLinked>::End; // For constructors only
	public:
		using LinkedList<T, DoublyLinked>::GetHeader;
		using LinkedList<T, DoublyLinked>::GetLength;
		using LinkedList<T, DoublyLinked>::GetIndex;
		using LinkedList<T, DoublyLinked>::operator[];
		using LinkedList<T, DoublyLinked>::operator bool;
		using LinkedList<T, DoublyLinked>::Begin;

		CircleLinkedList() = default;

		CircleLinkedList(List<T, DoublyLinked>&& other) noexcept : LinkedList<T, DoublyLinked>(other)
		{
			if (!DetectCircle())
			{
				LinkedList<T, DoublyLinked>::Node::LinkNodes({*End(), *Begin()});
			}
		}

		CircleLinkedList(List<T, DoublyLinked> const& other) : LinkedList<T, DoublyLinked>(other)
		{
			if (!DetectCircle())
			{
				LinkedList<T, DoublyLinked>::Node::LinkNodes({*End(), *Begin()});
			}
		}

		CircleLinkedList(std::initializer_list<T> data) : LinkedList<T, DoublyLinked>(data)
		{
			if (!DetectCircle())
			{
				LinkedList<T, DoublyLinked>::Node::LinkNodes({*End(), *Begin()});
			}
		}

		CircleLinkedList(const int length, T const* data) : LinkedList<T, DoublyLinked>(length, data)
		{
			if (!DetectCircle())
			{
				LinkedList<T, DoublyLinked>::Node::LinkNodes({*End(), *Begin()});
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
			if (*Begin() == nullptr)
			{
				List<T, DoublyLinked>::Push(data, index);
				List<T, DoublyLinked>::Node::LinkNodes({*End(), Header});
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, DoublyLinked>::Push(data, index);
				if (index == 0)
				{
					List<T, DoublyLinked>::Node::LinkNodes({lastNode, Header});
				}
			}
		}

		void Push(List<T, true> const& other, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(other, index);
				List<T, DoublyLinked>::Node::LinkNodes({*End(), Header});
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(other, index);
				if (index == 0)
				{
					List<T, DoublyLinked>::Node::LinkNodes({lastNode, Header});
				}
			}
		}

		void Push(const int length, T const* data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(length, data, index);
				List<T, DoublyLinked>::Node::LinkNodes({*End(), Header});
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(length, data, index);
				if (index == 0)
				{
					List<T, DoublyLinked>::Node::LinkNodes({lastNode, Header});
				}
			}
		}

		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(data, index);
				List<T, DoublyLinked>::Node::LinkNodes({*End(), Header});
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(data, index);
				if (index == 0)
				{
					List<T, DoublyLinked>::Node::LinkNodes({lastNode, Header});
				}
			}
		}

		T Pull(int const& index = 0)
		{
			if (index == 0)
				List<T, DoublyLinked>::Node::LinkNodes({Begin()->Previous, Begin()->Next});
			T data = LinkedList<T, DoublyLinked>::Pull(index);
			return data;
		}

		T Pull(typename List<T, DoublyLinked>::TraversalNode& traversalNode, int const& index = 0)
		{
			if (index == 0)
				List<T, DoublyLinked>::Node::LinkNodes({Begin()->Previous, Begin()->Next});
			T data = LinkedList<T, DoublyLinked>::Pull(traversalNode, index);
			return data;
		}

		CircleLinkedList<T, DoublyLinked>& operator=(List<T, true> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}

		CircleLinkedList<T, DoublyLinked>& operator=(List<T, true>&& other) noexcept
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
					List<T, DoublyLinked>::Node::LinkNodes(End(), Begin());
				}
			}

			return *this;
		}

		CircleLinkedList<T, DoublyLinked>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}

		CircleLinkedList<T, DoublyLinked>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}

		CircleLinkedList<T, DoublyLinked>& operator<<(List<T, true> const& other)
		{
			Push(other);
			return *this;
		}

		CircleLinkedList<T, DoublyLinked>& operator >>(T& data)
		{
			data = Pull();
			return *this;
		}

		~CircleLinkedList()
		{
			Delete();
		}
	};

	template <class T>
	using SinglyCircleLinkedList = CircleLinkedList<T, false>;
	template <class T>
	using DoublyCircleLinkedList = CircleLinkedList<T, true>;
}

template <typename T = int, bool Double = true>
std::ostream& operator<<(std::ostream& stream, const typename KC::List<T, Double>::Node& node)
{
	std::cout << node.Data;
	return stream;
}

template <typename T = int, bool Double = true>
std::ostream& operator<<(std::ostream& stream, const KC::List<T, Double>& list)
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		typename KC::List<T, Double>::Node& index = **list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
