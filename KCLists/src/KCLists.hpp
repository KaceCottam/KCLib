#pragma once

#include <iostream>
#include <utility>

namespace KC
{
	template <typename T, bool DoublyLinked= true>
	class List;

	template <typename T>
	class List<T, true>
	{
	public:
		class Node final
		{
		public:
			T Data;
			Node* Next = nullptr;
			Node* Previous = nullptr;

			Node() = default;
			Node(Node const& other) : Data(other.Data)
			{
			}
			Node(Node&& other) noexcept
			{
				Data = other.Data;
				Next = other.Next;
				Previous = other.Previous;
				other.Data = 0;
				other.Next = nullptr;
				other.Previous = nullptr;
			}
			explicit Node(T const& data, Node* next = nullptr, Node* previous = nullptr) : Data{ data }, Next(next), Previous(previous)
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
				Current = Current->Previous;
				return *this;
			}
			TraversalNode operator--(int)
			{
				TraversalNode result(*this);
				--*this;
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
				for (auto i = 0; i < num; i++)
				{
					operator--();
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
			bool operator== (TraversalNode& other) const
			{
				return Current == other.Current;
			}
			bool operator== (Node& other) const
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
				temp -= right;
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
				Node::LinkNodes({ traversalNode->Previous, newNode, *traversalNode });
			}
			else
			{
				Node::LinkNodes({ newNode, Header });
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

				Node::LinkNodes({ traversalNode->Previous, traversalNode->Next });

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


		List<T, true>& operator=(List<T, true> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		List<T, true>& operator=(List<T, true>&& other) noexcept
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
		List<T, true>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		List<T, true>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		List<T, true>& operator<<(List<T, true> const& other)
		{
			Push(other);
			return *this;
		}
		List<T, true>& operator >> (T& data)
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

		~List()
		{
			Delete();
		}
	};

	template <typename T>
	class List<T, false>
	{
	public:
		class Node final
		{
		public:
			T Data;
			Node* Next = nullptr;

			Node() = default;
			Node(Node const& other) : Data(other.Data)
			{
			}
			Node(Node&& other) noexcept
			{
				Data = other.Data;
				Next = other.Next;
				other.Data = 0;
				other.Next = nullptr;
			}
			explicit Node(T const& data, Node* next = nullptr, Node* previous = nullptr) : Data{ data }, Next(next)
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
			TraversalNode& operator+=(int const num)
			{
				for (auto i = 0; i < num; i++)
				{
					operator++();
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
			bool operator== (TraversalNode& other) const
			{
				return Current == other.Current;
			}
			bool operator== (Node& other) const
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
		};
	protected:
		Node* Header = nullptr;
		int Length = 0;
	public:
		List() = default;

		List(List<T, false>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}
		List(List<T, false> const& other)
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
				Node::LinkNodes({ traversalNode->Previous, newNode, *traversalNode });
			}
			else
			{
				Node::LinkNodes({ newNode, Header });
				Header = newNode;
			}

			Length++;
		}
		void Push(List<T, false> const& other, int const& index = 0)
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

				Node::LinkNodes({ traversalNode->Previous, traversalNode->Next });

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


		List<T, false>& operator=(List<T, false> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		List<T, false>& operator=(List<T, false>&& other) noexcept
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
		List<T, false>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		List<T, false>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		List<T, false>& operator<<(List<T, false> const& other)
		{
			Push(other);
			return *this;
		}
		List<T, false>& operator >> (T& data)
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

		~List()
		{
			Delete();
		}
	};

	template<typename T = int, bool DoublyLinked = true>
	class LinkedList;

	template<typename T>
	class LinkedList<T, true> : public List<T, true>
	{
	protected:
		using List<T, true>::Header;
		using List<T, true>::Length;
		TraversalNode EndNode = nullptr;
		bool FlagChangedLastNode = false;
	public:
		using List<T, true>::GetHeader;
		using List<T, true>::GetLength;
		using List<T, true>::GetIndex;
		using List<T, true>::Delete;
		using List<T, true>::Pull;
		using List<T, true>::operator=;
		using List<T, true>::operator[];
		using List<T, true>::operator bool;
		using List<T, true>::operator >> ;

		LinkedList() : List<T, true>(), EndNode(nullptr)
		{
		}
		LinkedList(List<T, true>&& other) noexcept : List<T, true>(other)
		{
		}
		LinkedList(List<T, true> const& other)
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

		TraversalNode Begin()
		{
			return TraversalNode(Header);
		}
		TraversalNode End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode traversalNode = Begin();
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
			List<T, true>::Push(data, index);
		}
		void Push(List<T, true> const& other, int const& index = 0)
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
			auto newNode = new Node(data);
			Node::LinkNodes({ *previousHeader,newNode });
			++Length;
			FlagChangedLastNode = true;
		}
		void Append(List<T, true> const& other)
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

		LinkedList<T, true>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T, true>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T, true>& operator<<(List<T, true> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			TraversalNode trav1 = Header;
			TraversalNode trav2 = Header;
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
	class LinkedList<T, false> : public List<T, false>
	{
	protected:
		using List<T, false>::Header;
		using List<T, false>::Length;
		TraversalNode EndNode = nullptr;
		bool FlagChangedLastNode = false;
	public:
		using List<T, false>::GetHeader;
		using List<T, false>::GetLength;
		using List<T, false>::GetIndex;
		using List<T, false>::Delete;
		using List<T, false>::Pull;
		using List<T, false>::operator=;
		using List<T, false>::operator[];
		using List<T, false>::operator bool;
		using List<T, false>::operator >> ;

		LinkedList() : List<T, false>(), EndNode(nullptr)
		{
		}
		LinkedList(List<T, false>&& other) noexcept : List<T, false>(other)
		{
		}
		LinkedList(List<T, false> const& other)
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

		TraversalNode Begin()
		{
			return TraversalNode(Header);
		}
		TraversalNode End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode traversalNode = Begin();
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
			List<T, false>::Push(data, index);
		}
		void Push(List<T, false> const& other, int const& index = 0)
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
			auto newNode = new Node(data);
			Node::LinkNodes({ *previousHeader,newNode });
			++Length;
			FlagChangedLastNode = true;
		}
		void Append(List<T, false> const& other)
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

		LinkedList<T, false>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T, false>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}
		LinkedList<T, false>& operator<<(List<T, false> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			TraversalNode trav1 = Header;
			TraversalNode trav2 = Header;
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

	template<typename T = int, bool DoublyLinked = true>
	class CircleLinkedList;

	template<typename T>
	class CircleLinkedList<T, true> : public LinkedList<T, true>
	{
	protected:
		using LinkedList<T, true>::Header;
		using LinkedList<T, true>::Length;
		using LinkedList<T, true>::DetectCircle; // For constructors only
		using LinkedList<T, true>::End; // For constructors only
	public:
		using LinkedList<T, true>::GetHeader;
		using LinkedList<T, true>::GetLength;
		using LinkedList<T, true>::GetIndex;
		using LinkedList<T, true>::operator[];
		using LinkedList<T, true>::operator bool;
		using LinkedList<T, true>::Begin;

		CircleLinkedList() = default;
		CircleLinkedList(List<T, true>&& other) noexcept : LinkedList<T, true>(other)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(List<T, true> const& other) : LinkedList<T, true>(other)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(std::initializer_list<T> data) : LinkedList<T, true>(data)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(const int length, T const* data) : LinkedList<T, true>(length, data)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
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
				List<T, true>::Push(data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(List<T, true> const& other, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(other, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(other, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(length, data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(length, data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, true>::Push(data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, true>::Push(data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}

		T Pull(int const& index = 0)
		{
			if (index == 0)
				Node::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T, true>::Pull(index);
			return data;
		}

		T Pull(TraversalNode& traversalNode, int const& index = 0)
		{
			if (index == 0)
				Node::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T, true>::Pull(traversalNode, index);
			return data;
		}

		CircleLinkedList<T, true>& operator=(List<T, true> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		CircleLinkedList<T, true>& operator=(List<T, true>&& other) noexcept
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
					Node::LinkNodes(End(), Begin());
				}
			}

			return *this;
		}
		CircleLinkedList<T, true>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T, true>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T, true>& operator<<(List<T, true> const& other)
		{
			Push(other);
			return *this;
		}
		CircleLinkedList<T, true>& operator >> (T& data)
		{
			data = Pull();
			return *this;
		}

		~CircleLinkedList()
		{
			Delete();
		}
	};

	template<typename T>
	class CircleLinkedList<T, false> : public LinkedList<T, false>
	{
	protected:
		using LinkedList<T, false>::Header;
		using LinkedList<T, false>::Length;
		using LinkedList<T, false>::DetectCircle; // For constructors only
		using LinkedList<T, false>::End; // For constructors only
	public:
		using LinkedList<T, false>::GetHeader;
		using LinkedList<T, false>::GetLength;
		using LinkedList<T, false>::GetIndex;
		using LinkedList<T, false>::operator[];
		using LinkedList<T, false>::operator bool;
		using LinkedList<T, false>::Begin;

		CircleLinkedList() = default;
		CircleLinkedList(List<T, false>&& other) noexcept : LinkedList<T, true>(other)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(List<T, false> const& other) : LinkedList<T, false>(other)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(std::initializer_list<T> data) : LinkedList<T, false>(data)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
			}
		}
		CircleLinkedList(const int length, T const* data) : LinkedList<T, false>(length, data)
		{
			if (!DetectCircle())
			{
				Node::LinkNodes({ *End(), *Begin() });
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
				List<T, false>::Push(data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, false>::Push(data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(List<T, false> const& other, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, false>::Push(other, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, false>::Push(other, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, false>::Push(length, data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, false>::Push(length, data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T, false>::Push(data, index);
				Node::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T, false>::Push(data, index);
				if (index == 0)
				{
					Node::LinkNodes({ lastNode,Header });
				}
			}
		}

		T Pull(int const& index = 0)
		{
			if (index == 0)
				Node::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T, false>::Pull(index);
			return data;
		}

		T Pull(TraversalNode& traversalNode, int const& index = 0)
		{
			if (index == 0)
				Node::LinkNodes({ Begin()->Previous, Begin()->Next });
			T data = LinkedList<T, false>::Pull(traversalNode, index);
			return data;
		}

		CircleLinkedList<T, false>& operator=(List<T, false> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		CircleLinkedList<T, false>& operator=(List<T, false>&& other) noexcept
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
					Node::LinkNodes(End(), Begin());
				}
			}

			return *this;
		}
		CircleLinkedList<T, false>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T, false>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		CircleLinkedList<T, false>& operator<<(List<T, false> const& other)
		{
			Push(other);
			return *this;
		}
		CircleLinkedList<T, false>& operator >> (T& data)
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

template <typename T = int, bool Double = true>
auto operator<<(std::ostream& stream, const typename KC::List<T, Double>::Node& node) -> std::ostream&
{
	std::cout << node.Data;
	return stream;
}

template < typename T = int, bool Double = true>
auto operator<<(std::ostream& stream, const KC::List<T, Double>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		typename KC::List<T, Double>::Node& index = **list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}

template <typename T = int, bool Double = true>
auto operator<<(std::ostream& stream, const KC::LinkedList<T, Double>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		typename KC::List<T, Double>::Node& index = **list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}

template < typename T = int, bool Double = true>
auto operator<<(std::ostream& stream, const KC::CircleLinkedList<T, Double>& list) -> std::ostream&
{
	auto length = list.GetLength();
	for (auto i = 0; i < length; i++)
	{
		typename KC::List<T, Double>::Node& index = **list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
