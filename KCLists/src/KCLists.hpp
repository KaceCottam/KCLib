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

		ListNode() : Next(nullptr), Previous(nullptr)
		{
		}
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
		explicit ListNode(T const& data) : Data{ data }, Next(nullptr), Previous(nullptr)
		{
		}

		~ListNode() = default;

		auto operator=(T const& data) -> ListNode<T>&
		{
			this->Data = data;
			return *this;
		}
		auto operator=(ListNode<T> const& other) -> ListNode<T>&
		{
			this->Data = other.Data;
			return *this;
		}
		auto operator=(ListNode<T>&& other) noexcept -> ListNode<T>&
		{
			if (this != &other)
			{
				Data = other.Data;
				other.Data = 0;
			}
			return *this;
		}
	};

	template <class T>
	class List
	{
	protected:
		ListNode<T>* Header;
		int Length;
	public:
		List() : Header{ nullptr }, Length(0)
		{
		}
		List(List<T>&& other) noexcept
		{
			Header = other.Header;
			Length = other.Length;
			other.Header = nullptr;
			other.Length = 0;
		}
		List(List<T> const& other) : Header(new ListNode<T>(other.Header->Data)), Length(1)
		{
			auto length = other.GetLength();
			for (auto i = 1; i < length; i++)
			{
				this->Push(other.GetIndex(i));
			}
		}
		explicit List(T const& data) : Header{ new ListNode<T>(data) }, Length(1)
		{
		}
		List(std::initializer_list<T> data) : Header(new ListNode<T>(*(data.end() - 1))), Length(1)
		{
			auto length = data.size() - 1;
			this->Push(length, data.begin());
		}
		List(const int length, T const* data) : Header{ new ListNode<T>{ data[0] } }, Length(1)
		{
			for (auto i = 1; i < length; i++)
			{
				Push(data[i]);
			}
		}

		auto GetHeader() const -> ListNode<T>&
		{
			return *Header;
		}

		auto GetLength() const -> int
		{
			return Length;
		}

		auto Push(T const& data) -> void
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
		auto Push(const int length, T const* data) -> void
		{
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(data[i]);
			}
		}

		auto Push(std::initializer_list<T> data) -> void
		{
			auto length = data.size();
			Push(length, data.begin());
		}

		auto Pull() -> T
		{
			if (!Header)
				return 0;
			T data = Header->Data;
			ListNode<T>* oldHeader = Header;
			Header = Header->Next;
			delete oldHeader;
			Length--;
			return data;
		}

		auto GetIndex(const int index) const -> T&
		{
			ListNode<T>* traversalNode = Header;
			for (auto i = 0; i < index && traversalNode; i++)
			{
				traversalNode = traversalNode->Next;
			}
			if (traversalNode == nullptr)
			{
				return nullptr;
			}
			return traversalNode->Data;
		}

		auto operator=(List<T> const& other) -> List<T>&
		{
			while (Header)
			{
				Pull();
			}
			Header = new ListNode<T>(other.Header->Data);
			auto length = other.Length;
			for (auto i = length; i > 1; --i)
			{
				this->Push(other.GetIndex(i));
			}
			return *this;
		}
		auto operator=(List<T>&& other) noexcept -> List<T>&
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
		auto operator<<(T const& data) -> List<T>&
		{
			Push(data);
			return *this;
		}
		auto operator>>(T& data) -> List<T>&
		{
			data = Pull();
			return *this;
		}
		auto operator<<(std::initializer_list<T> data) -> List<T>&
		{
			Push(data);
			return *this;
		}
		auto operator[](const int index) const -> T&
		{
			if (Length - 1 > index)
			{
				throw std::out_of_range("Index is greater than the length of list!");
			}
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

	template <class T>
	class LinkedList final : public List<T>
	{
		using List<T>::GetHeader;
	public:
		LinkedList() : List<T>()
		{
		}
		LinkedList(const int length, T const* data) : List<T>(data[0])
		{
			for (auto i = 1; i < length; i++)
			{
				Append(data[i]);
			}
		}
		explicit LinkedList(T const& data) : List<T>(data)
		{
		}
		LinkedList(std::initializer_list<T> data) : List<T>(data)
		{
		}

		auto Begin() const -> ListNode<T>&
		{
			return this->Header;
		}

		auto End() const -> ListNode<T>&
		{
			ListNode<T>* traversalNode = this->Header;
			while (traversalNode->Next)
			{
				traversalNode = traversalNode->Next;
			}
			return *traversalNode;
		}

		auto Append(T const& data) -> void
		{
			if (!this->Header)
			{
				this->Push(data);
				return;
			}
			auto newNode = new ListNode<T>(data);
			newNode->Previous = &this->End();
			this->End().Next = newNode;
			++this->Length;
		}
		auto Append(const int length, T const* data) -> void
		{
			for (auto i = 0; i < length; i++)
			{
				Append(data[i]);
			}
		}
		auto Append(std::initializer_list<T> data) -> void
		{
			auto length = data.size();
			Append(length, data.begin());
		}

		auto PushAt(const int index, T const& data) -> void
		{
			ListNode<T>* traversalNode = this->Header;
			for (auto i = 0; i < index - 1 && traversalNode; i++)
			{
				traversalNode = traversalNode->Next;
			}
			if (!traversalNode)
			{
				Append(data);
				return;
			}
			auto newNode = new ListNode<T>(data);
			newNode->Previous = traversalNode;
			newNode->Next = traversalNode->Next;
			newNode->Next->Previous = newNode;
			traversalNode->Next = newNode;
			++this->Length;
		}
		auto PushAt(const int index, const int length, T const* data) -> void
		{
			for (auto i = 0; i < length; i++)
			{
				PushAt(index + i, data[i]);
			}
		}
		auto PushAt(int index, std::initializer_list<T> data) -> void
		{
			auto length = data.size();
			PushAt(index, length, data.begin());
		}

		auto Pop() -> T
		{
			auto endNode = &this->End();
			auto beforeEndNode = endNode->Previous;
			T data = endNode->Data;
			delete endNode;
			beforeEndNode->Next = nullptr;
			--this->Length;
			return data;
		}

		auto PullAt(const int index) -> T
		{
			ListNode<T>* traversalNode = this->Header;
			ListNode<T>* beforeTraversalNode = this->Header;
			for (auto i = 0; i < index && traversalNode; i++)
			{
				beforeTraversalNode = traversalNode;
				traversalNode = traversalNode->Next;
			}
			if (!traversalNode)
			{
				return Pop();
			}
			T data = traversalNode->Data;
			traversalNode->Next->Previous = beforeTraversalNode;
			beforeTraversalNode->Next = traversalNode->Next;
			delete traversalNode;
			--this->Length;
			return data;
		}

		auto operator<<(T const& data) -> LinkedList<T>&
		{
			Append(data);
			return *this;
		}
		auto operator<<(std::initializer_list<T> data) -> LinkedList<T>&
		{
			Append(data);
			return *this;
		}
	};

	template <class T>
	class CircleList final : public List<T>
	{
	public:
		CircleList() : List<T>()
		{
		}
		CircleList(const int length, T const* data) : List<T>(length, data)
		{
			ListNode<T>* traversalNode = this->Header;
			for (auto i = 0; i < length - 1; i++)
			{
				traversalNode = traversalNode->Next;
			}
			traversalNode->Next = this->Header;
			this->Header->Previous = traversalNode;
		}
		explicit CircleList(T const& data) : List<T>(data)
		{
			this->Header->Next = this->Header;
			this->Header->Previous = this->Header;
		}
		CircleList(std::initializer_list<T> data) : List<T>(data)
		{
			if (!this->Header)
			{
				return;
			}
			ListNode<T>* traversalNode = this->Header;
			auto length = data.size();
			for (auto i = 0; i < static_cast<int>(length - 1); i++)
			{
				traversalNode = traversalNode->Next;
			}
			traversalNode->Next = this->Header;
			this->Header->Previous = traversalNode;
		}
		CircleList(CircleList<T> const& other) : CircleList(static_cast<List<T>>(other))
		{
		}
		CircleList(CircleList<T>&& other) noexcept : CircleList(static_cast<List<T>>(other))
		{
		}
		explicit CircleList(List<T> const& other) : List<T>(other)
		{
			ListNode<T>* traversalNode = this->Header;
			auto length = this->Length;
			for (auto i = 0; i < static_cast<int>(length - 1); i++)
			{
				traversalNode = traversalNode->Next;
			}
			traversalNode->Next = this->Header;
			this->Header->Previous = traversalNode;
		}

		auto Push(T const& data) -> void
		{
			ListNode<T>* oldHeader = this->Header;
			this->Header = new ListNode<T>(data);
			if (oldHeader)
			{
				this->Header->Previous = oldHeader->Previous;
				this->Header->Previous->Next = this->Header;
				this->Header->Next = oldHeader;
				oldHeader->Previous = this->Header;
			}
			else
			{
				this->Header->Previous = this->Header;
				this->Header->Next = this->Header;
			}
			++this->Length;
		}
		auto Push(const int length, T const* data) -> void
		{
			for (auto i = length - 1; i >= 0; --i)
			{
				Push(data[i]);
			}
		}
		auto Push(std::initializer_list<T> data) -> void
		{
			auto length = data.size();
			Push(length, data.begin());
		}

		auto Pull() -> T
		{
			if (!this->Header)
				return 0;
			T data = this->Header->Data;

			ListNode<T>* oldHeader = this->Header;
			this->Header->Previous->Next = this->Header->Next;
			this->Header->Next->Previous = this->Header->Previous;
			if (this->Header->Next == this->Header)
			{
				this->Header->Next = nullptr;
				this->Header->Previous = nullptr;
			}
			this->Header = oldHeader->Next;

			delete oldHeader;
			--this->Length;
			return data;
		}

		auto operator<<(T const& data) -> CircleList<T>&
		{
			Push(data);
			return *this;
		}

		auto operator<<(std::initializer_list<T> data) -> CircleList<T>&
		{
			Push(data);
			return *this;
		}
		auto operator=(CircleList<T>&& other) noexcept -> CircleList<T>&
		{
			if (&other != this)
			{
				CircleList(static_cast<List<T>>(other));
			}
			return *this;
		}
		auto operator=(CircleList<T> const& other) -> CircleList<T>&
		{
			if (&other != this)
			{
				CircleList(static_cast<List<T>>(other));
			}
			return *this;
		}
		~CircleList()
		{
			while (this->Header != nullptr)
			{
				this->Pull();
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
		std::cout << "[" << i << ":$" << &list.GetIndex(i) << "] " << list.GetIndex(i) << std::endl;
	}
	return stream;
}
