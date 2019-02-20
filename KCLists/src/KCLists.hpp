#pragma once

#include <iostream>
#include <utility>

namespace KC
{
	template <bool = true, typename T = int>
	class ListNode;

	template <typename T = int >
	class ListNode<true, T> final
	{
	public:
		T Data;
		ListNode<true, T>* Next = nullptr;
		ListNode<true, T>* Previous = nullptr;

		ListNode() = default;
		ListNode(ListNode<true, T> const& other) : Data(other.Data)
		{
		}
		ListNode(ListNode<true, T>&& other) noexcept
		{
			Data = other.Data;
			Next = other.Next;
			Previous = other.Previous;
			other.Data = 0;
			other.Next = nullptr;
			other.Previous = nullptr;
		}
		explicit ListNode(T const& data, ListNode<true, T>* next = nullptr, ListNode<true, T>* previous = nullptr) : Data{ data }, Next(next), Previous(previous)
		{
		}

		ListNode<true, T>& operator=(ListNode<true, T> const& other)
		{
			Data = other.Data;
			return *this;
		}

		ListNode<true, T>& operator=(ListNode<true, T>&& other) noexcept
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

		static void LinkNodes(int const length, ListNode<true, T>** nodes)
		{
			ListNode<true, T>* trail = nodes[0];
			for (auto i = 1; i < length; i++)
			{
				ListNode<true, T>* head = nodes[i];
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
		static void LinkNodes(std::initializer_list<ListNode<true, T>*> nodes)
		{
			auto nodeList = new ListNode<true, T>*[nodes.size()];
			auto index = 0;
			for (auto& i : nodes)
			{
				nodeList[index++] = i;
			}
			LinkNodes(nodes.size(), nodeList);
			delete[] nodeList;
		}

		~ListNode() = default;
	};

	template <typename T = int >
	class ListNode<false, T> final
	{
	public:
		T Data;
		ListNode<false, T>* Next = nullptr;

		ListNode() = default;
		ListNode(ListNode<false, T> const& other) : Data(other.Data)
		{
		}
		ListNode(ListNode<false, T>&& other) noexcept
		{
			Data = other.Data;
			Next = other.Next;
			other.Data = 0;
			other.Next = nullptr;
		}
		explicit ListNode(T const& data, ListNode<false, T>* next = nullptr, ListNode<false, T>* previous = nullptr) : Data{ data }, Next(next)
		{
		}

		ListNode<false, T>& operator=(ListNode<false, T> const& other)
		{
			Data = other.Data;
			return *this;
		}

		ListNode<false, T>& operator=(ListNode<false, T>&& other) noexcept
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

		static void LinkNodes(int const length, ListNode<false, T>** nodes)
		{
			ListNode<false, T>* trail = nodes[0];
			for (auto i = 1; i < length; i++)
			{
				ListNode<false, T>* head = nodes[i];
				if (trail)
				{
					trail->Next = head;
				}
				trail = head;
			}
		}
		static void LinkNodes(std::initializer_list<ListNode<false, T>*> nodes)
		{
			auto nodeList = new ListNode<false, T>*[nodes.size()];
			auto index = 0;
			for (auto& i : nodes)
			{
				nodeList[index++] = i;
			}
			LinkNodes(nodes.size(), nodeList);
			delete[] nodeList;
		}

		~ListNode() = default;
	};

	template <bool = true, typename T = int>
	class TraversalNode;

	template <typename T = int>
	class TraversalNode<true, T> final
	{
	public:
		ListNode<true, T>* Current = nullptr;

		TraversalNode() = default;

		TraversalNode(ListNode<true, T>* node) : Current(node)
		{
		}
		TraversalNode<true, T>& operator++()
		{
			Current = Current->Next;
			return *this;
		}
		TraversalNode<true, T> operator++(int)
		{
			TraversalNode<true, T> result(*this);
			++*this;
			return result;
		}
		TraversalNode<true, T>& operator--()
		{
			Current = Current->Previous;
			return *this;
		}
		TraversalNode<true, T> operator--(int)
		{
			TraversalNode<true, T> result(*this);
			--*this;
			return result;
		}
		TraversalNode<true, T>& operator+=(int const num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator++();
			}
			return *this;
		}
		TraversalNode<true, T>& operator-=(const int num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator--();
			}
			return *this;
		}
		ListNode<true, T>* operator*()
		{
			return Current;
		}
		ListNode<true, T>* operator->()
		{
			return Current;
		}
		bool operator== (TraversalNode<true, T>& other) const
		{
			return Current == other.Current;
		}
		bool operator== (ListNode<true, T>& other) const
		{
			return Current == &other;
		}
		operator bool() const
		{
			return Current != nullptr;
		}
		operator ListNode<true, T>() const
		{
			return *Current;
		}

		TraversalNode<true, T> operator+(int const& right)
		{
			auto temp = *this;
			temp += right;
			return temp;
		}
		TraversalNode<true, T> operator-(int const& right)
		{
			auto temp = *this;
			temp -= right;
			return temp;
		}
	};

	template <typename T = int>
	class TraversalNode<false, T> final
	{
	public:
		ListNode<false, T>* Current = nullptr;

		TraversalNode() = default;

		TraversalNode(ListNode<false, T>* node) : Current(node)
		{
		}
		TraversalNode<false, T>& operator++()
		{
			Current = Current->Next;
			return *this;
		}
		TraversalNode<false, T> operator++(int)
		{
			TraversalNode<false, T> result(*this);
			++*this;
			return result;
		}
		TraversalNode<false, T>& operator+=(int const num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator++();
			}
			return *this;
		}
		ListNode<false, T>* operator*()
		{
			return Current;
		}
		ListNode<false, T>* operator->()
		{
			return Current;
		}
		bool operator== (TraversalNode<false, T>& other) const
		{
			return Current == other.Current;
		}
		bool operator== (ListNode<false, T>& other) const
		{
			return Current == &other;
		}
		operator bool() const
		{
			return Current != nullptr;
		}
		operator ListNode<false, T>() const
		{
			return *Current;
		}

		TraversalNode<false, T> operator+(int const& right)
		{
			auto temp = *this;
			temp += right;
			return temp;
		}
	};

	template <bool = true, typename T = int>
	class List;

	template <typename T = int>
	class List<true, T>
	{
	protected:
		ListNode<true, T>* Header = nullptr;
		int Length = 0;
	public:
		List() = default;

		List(List<true, T>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}
		List(List<true, T> const& other)
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

		TraversalNode<true, T> GetHeader() const
		{
			return TraversalNode<true, T>(Header);
		}
		int GetLength() const
		{
			return Length;
		}
		TraversalNode<true, T> GetIndex(const int index) const
		{
			if (index > Length - 1)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}
			if (index < 0)
			{
				throw std::out_of_range("Index is less than 0!");
			}

			TraversalNode<true, T> traversalNode = Header;

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
			auto newNode = new ListNode<true, T>(data, Header);
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
				TraversalNode<true, T> traversalNode(Header);
				traversalNode += index;
				ListNode<true, T>::LinkNodes({ traversalNode->Previous, newNode, *traversalNode });
			}
			else
			{
				ListNode<true, T>::LinkNodes({ newNode, Header });
				Header = newNode;
			}

			Length++;
		}
		void Push(List<true, T> const& other, int const& index = 0)
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
				ListNode<true, T>* oldHeader = Header;
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
				TraversalNode<true, T> traversalNode(Header);
				traversalNode += index;

				data = traversalNode->Data;

				ListNode<true, T>::LinkNodes({ traversalNode->Previous, traversalNode->Next });

				delete *traversalNode;
			}

			Length--;

			return data;
		}

		T Pull(TraversalNode<true, T>& traversalNode, int const& index = 0)
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


		List<true, T>& operator=(List<true, T> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		List<true, T>& operator=(List<true, T>&& other) noexcept
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
		List<true, T>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		List<true, T>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		List<true, T>& operator<<(List<true, T> const& other)
		{
			Push(other);
			return *this;
		}
		List<true, T>& operator >> (T& data)
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

	template <typename T = int>
	class List<false, T>
	{
	protected:
		ListNode<false, T>* Header = nullptr;
		int Length = 0;
	public:
		List() = default;

		List(List<false, T>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}
		List(List<false, T> const& other)
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

		TraversalNode<false, T> GetHeader() const
		{
			return TraversalNode<false, T>(Header);
		}
		int GetLength() const
		{
			return Length;
		}
		TraversalNode<false, T> GetIndex(const int index) const
		{
			if (index > Length - 1)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}
			if (index < 0)
			{
				throw std::out_of_range("Index is less than 0!");
			}

			TraversalNode<false, T> traversalNode = Header;

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
			auto newNode = new ListNode<false, T>(data, Header);
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
				TraversalNode<false, T> traversalNode(Header);
				traversalNode += index;
				ListNode<false, T>::LinkNodes({ traversalNode->Previous, newNode, *traversalNode });
			}
			else
			{
				ListNode<false, T>::LinkNodes({ newNode, Header });
				Header = newNode;
			}

			Length++;
		}
		void Push(List<false, T> const& other, int const& index = 0)
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
				ListNode<false, T>* oldHeader = Header;
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
				TraversalNode<false, T> traversalNode(Header);
				traversalNode += index;

				data = traversalNode->Data;

				ListNode<false, T>::LinkNodes({ traversalNode->Previous, traversalNode->Next });

				delete *traversalNode;
			}

			Length--;

			return data;
		}

		T Pull(TraversalNode<false, T>& traversalNode, int const& index = 0)
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


		List<false, T>& operator=(List<false, T> const& other)
		{
			Delete();

			Push(other);

			return *this;
		}
		List<false, T>& operator=(List<false, T>&& other) noexcept
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
		List<false, T>& operator<<(T const& data)
		{
			Push(data);
			return *this;
		}
		List<false, T>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		List<false, T>& operator<<(List<false, T> const& other)
		{
			Push(other);
			return *this;
		}
		List<false, T>& operator >> (T& data)
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

	template<bool = true, typename T = int>
	class LinkedList;

	template<typename T>
	class LinkedList<true, T> : public List<true, T>
	{
	protected:
		using List<true, T>::Header;
		using List<true, T>::Length;
		TraversalNode<true, T> EndNode = nullptr;
		bool FlagChangedLastNode = false;
	public:
		using List<true, T>::GetHeader;
		using List<true, T>::GetLength;
		using List<true, T>::GetIndex;
		using List<true, T>::Delete;
		using List<true, T>::Pull;
		using List<true, T>::operator=;
		using List<true, T>::operator[];
		using List<true, T>::operator bool;
		using List<true, T>::operator >> ;

		LinkedList() : List<true, T>(), EndNode(nullptr)
		{
		}
		LinkedList(List<true, T>&& other) noexcept : List<true, T>(other)
		{
		}
		LinkedList(List<true, T> const& other)
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

		TraversalNode<true, T> Begin()
		{
			return TraversalNode<true, T>(Header);
		}
		TraversalNode<true, T> End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode<true, T> traversalNode = Begin();
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
			List<true, T>::Push(data, index);
		}
		void Push(List<true, T> const& other, int const& index = 0)
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
			auto newNode = new ListNode<true, T>(data);
			ListNode<true, T>::LinkNodes({ *previousHeader,newNode });
			++Length;
			FlagChangedLastNode = true;
		}
		void Append(List<true, T> const& other)
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

		LinkedList<true, T>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}
		LinkedList<true, T>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}
		LinkedList<true, T>& operator<<(List<true, T> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			TraversalNode<true, T> trav1 = Header;
			TraversalNode<true, T> trav2 = Header;
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
	class LinkedList<false, T> : public List<false, T>
	{
	protected:
		using List<true, T>::Header;
		using List<true, T>::Length;
		TraversalNode<true, T> EndNode = nullptr;
		bool FlagChangedLastNode = false;
	public:
		using List<true, T>::GetHeader;
		using List<true, T>::GetLength;
		using List<true, T>::GetIndex;
		using List<true, T>::Delete;
		using List<true, T>::Pull;
		using List<true, T>::operator=;
		using List<true, T>::operator[];
		using List<true, T>::operator bool;
		using List<true, T>::operator >> ;

		LinkedList() : List<true, T>(), EndNode(nullptr)
		{
		}
		LinkedList(List<true, T>&& other) noexcept : List<true, T>(other)
		{
		}
		LinkedList(List<true, T> const& other)
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

		TraversalNode<true, T> Begin()
		{
			return TraversalNode<true, T>(Header);
		}
		TraversalNode<true, T> End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode<true, T> traversalNode = Begin();
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
			List<true, T>::Push(data, index);
		}
		void Push(List<true, T> const& other, int const& index = 0)
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
			auto newNode = new ListNode<true, T>(data);
			ListNode<true, T>::LinkNodes({ *previousHeader,newNode });
			++Length;
			FlagChangedLastNode = true;
		}
		void Append(List<true, T> const& other)
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

		LinkedList<true, T>& operator<<(T const& data)
		{
			Append(data);
			return *this;
		}
		LinkedList<true, T>& operator<<(std::initializer_list<T> data)
		{
			Append(data);
			return *this;
		}
		LinkedList<true, T>& operator<<(List<true, T> const& other)
		{
			Append(other);
			return *this;
		}

		// Used specifically for when CircleLinkedLists are converted to LinkedLists
		bool DetectCircle() const
		{
			TraversalNode<true, T> trav1 = Header;
			TraversalNode<true, T> trav2 = Header;
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
			if (*Begin() == nullptr)
			{
				List<T>::Push(data, index);
				ListNode<T>::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T>::Push(data, index);
				if (index == 0)
				{
					ListNode<T>::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(List<T> const& other, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T>::Push(other, index);
				ListNode<T>::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T>::Push(other, index);
				if (index == 0)
				{
					ListNode<T>::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(const int length, T const* data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T>::Push(length, data, index);
				ListNode<T>::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T>::Push(length, data, index);
				if (index == 0)
				{
					ListNode<T>::LinkNodes({ lastNode,Header });
				}
			}
		}
		void Push(std::initializer_list<T> data, int const& index = 0)
		{
			if (*Begin() == nullptr)
			{
				List<T>::Push(data, index);
				ListNode<T>::LinkNodes({ *End(),Header });
			}
			else
			{
				auto lastNode = Begin()->Previous;
				List<T>::Push(data, index);
				if (index == 0)
				{
					ListNode<T>::LinkNodes({ lastNode,Header });
				}
			}
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
		KC::ListNode<T>& index = **list.GetIndex(i);
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
		KC::ListNode<T>& index = **list.GetIndex(i);
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
		KC::ListNode<T>& index = **list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
