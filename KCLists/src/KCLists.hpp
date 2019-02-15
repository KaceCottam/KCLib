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

		static void LinkNodes(std::initializer_list<ListNode<T>> nodes)
		{
			ListNode<T>& trail = *nodes.begin();
			for (auto& head : nodes)
			{
				if (trail != head)
				{
					trail->Next = head;
					head->Previous = trail;
					trail = head;
				}
			}
		}

		~ListNode() = default;
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
			auto length = other.GetLength();
			for (auto i = 0; i < length; i++)
			{
				Push(other.GetIndex(i));
			}
		}
		//explicit List(T const& data) : Header{ new ListNode<T>(data) }, Length(1)
		//{
		//}
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

			ListNode<T>* traversalNode = Header;

			for (auto i = 0; i < index; i++)
			{
				traversalNode = traversalNode->Next;
			}

			return traversalNode->Data;
		}

		void Push(T const& data)
		{
			ListNode<T>* previousHeader = Header;
			Header = new ListNode<T>(data);
			if (previousHeader)
			{
				Header->Next = previousHeader;
				previousHeader->Previous = Header;
			}
			Length++;
		}
		void Push(const int length, T const* data)
		{
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(data[i]);
			}
		}
		void Push(std::initializer_list<T> data)
		{
			auto length = data.size();
			Push(length, data.begin());
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

			delete oldHeader;
			Length--;

			return data;
		}

		List<T>& operator=(List<T> const& other)
		{
			while (Header)
			{
				Pull();
			}

			auto length = other.Length;
			for (auto i = length; i > 0; --i)
			{
				Push(other.GetIndex(i));
			}

			return *this;
		}
		List<T>& operator=(List<T>&& other) noexcept
		{
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
		List<T>& operator>>(T& data)
		{
			data = Pull();
			return *this;
		}
		List<T>& operator<<(std::initializer_list<T> data)
		{
			Push(data);
			return *this;
		}
		T& operator[](const int index) const
		{
			return GetIndex(index);
		}

		~List()
		{
			while (Header)
			{
				Pull();
			}
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
		const KC::ListNode<T>& index = list.GetIndex(i);
		std::cout << "[" << i << ":$" << &index << "] " << index << std::endl;
	}
	return stream;
}
