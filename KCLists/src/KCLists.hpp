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

		static void LinkNodes(int const length, ListNode<T>* nodes)
		{
			ListNode<T>* trail = nodes;
			for (auto i = 0; i < length; i++)
			{
				ListNode<T>* head = nodes + i;
				if (trail != head)
				{
					trail->Next = head;
					head->Previous = trail;
					trail = head;
				}
			}
		}
		static void LinkNodes(std::initializer_list<ListNode<T>> nodes)
		{
			LinkNodes(nodes.size(), nodes.begin());
		}

		~ListNode() = default;
	};

	template <typename T>
	class TraversalNode final
	{
	public:
		ListNode<T>* Current;

		TraversalNode(ListNode<T>* node) : Current(node)
		{
		}
		TraversalNode<T>& operator++()
		{
			Current = Current->Next;
			return *this;
		}
		TraversalNode<T>& operator--()
		{
			Current = Current->Previous;
			return *this;
		}
		TraversalNode<T>& operator+=(int const num)
		{
			for (auto i = 0; i < num; i++)
			{
				*this++;
			}
			return *this;
		}
		TraversalNode<T>& operator-=(const int num)
		{
			for (auto i = 0; i < num; i++)
			{
				*this--;
			}
			return *this;
		}
		ListNode<T>& operator*()
		{
			return *Current;
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
	};

	template <class T>
	class List
	{
	protected:
		ListNode<T>* Header;
		int Length;
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

		ListNode<T>& GetHeader() const
		{
			return *Header;
		}
		int GetLength() const
		{
			return Length;
		}
		T const& GetIndex(const int index) const
		{
			if (Length - 1 < index)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}

			TraversalNode<T> traversalNode = Header;

			traversalNode += index;

			return traversalNode->Data;
		}

		void Delete()
		{
			while (Header)
			{
				Pull();
			}
		}

		void Push(T const& data)
		{
			ListNode<T>* previousHeader = Header;
			Header = new ListNode<T>(data);
			if (previousHeader)
			{
				ListNode<T>::LinkNodes({ Header,previousHeader });
			}
			Length++;
		}
		void Push(const int length, T const* data)
		{
			Push(List<T>(length, data));
		}
		void Push(std::initializer_list<T> data)
		{
			Push(data.size(), data.begin());
		}
		void Push(List<T> const& other)
		{
			auto length = other.Length;
			for (auto i = length; i > 0; --i)
			{
				Push(other.GetIndex(i));
			}
		}

		T Pull()
		{
			if (!Header)
			{
				return 0;
			}

			T data = Header->Data;
			ListNode<T>* oldHeader = Header;
			Header = Header->Next;

			/*
			 *  Header can be equal to nullptr after this because
			 *  the Push() functions have the beginning node and
			 *  next node's previous and next pointers
			 *  respectively = nullptr.
			 */

			delete oldHeader;
			Length--;

			return data;
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
			return GetIndex(index);
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
	class LinkedList final : public List<T>
	{
	private:
		TraversalNode<T> EndNode;
		bool FlagChangedLastNode = false;
		bool FlagIsCirlce = false;
	public:
		TraversalNode<T> Begin()
		{
			return TraversalNode<T>(*this->Header);
		}
		TraversalNode<T> End()
		{
			if (!FlagChangedLastNode)
			{
				return EndNode;
			}
			FlagChangedLastNode = false;
			TraversalNode<T> traversalNode = Begin();
			traversalNode += this->Length - 1;
			EndNode = traversalNode;
			return traversalNode;
		}
		void Append(T const& data)
		{
			auto node = new ListNode<T>(data);
			ListNode<T>::LinkNodes({ End(), node });
		}
		
		// TODO: Append fxns (4)
		// TODO: Begin/End fxns
		// TODO: Overload operator<< fxns
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
		const KC::ListNode<T>& index = list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
