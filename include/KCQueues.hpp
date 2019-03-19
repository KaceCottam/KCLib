//@KCLIB_FILE_COMMENT
#pragma once

#include <stdexcept>
#include <KCNodes.hpp>
#include <initializer_list>

namespace KC
{
	template <class T>
	class Queue final
	{
	protected:
		using NodeT = Node<T, false>;
		using TraversalNodeT = TraversalNode<T, false>;
		using QueueT = Queue<T>;

		NodeT* Header = nullptr;
		int Length = 0;
	public:
		Queue() = default;
		Queue(QueueT&& other) noexcept = default;
		Queue(QueueT const& other);
		QueueT& operator=(QueueT&& other) noexcept;
		QueueT& operator=(QueueT const& other);
		Queue(std::initializer_list<T> data);
		Queue(int length, T const* data);

		TraversalNodeT GetHeader() const;
		TraversalNodeT GetEnd() const;
		int GetLength() const;
		bool IsEmpty() const;

		void Delete();

		QueueT& Enqueue(T const& data);
		QueueT& Enqueue(int num, T const* data);
		QueueT& Enqueue(std::initializer_list<T> data);
		QueueT& Enqueue(QueueT const& data);

		T Dequeue();
		T& Peek() const;
		T& Peek(int index) const;

		~Queue();
	};

	template <class T>
	Queue<T>::Queue(QueueT const& other)
	{
		Enqueue(other);
	}

	template <class T>
	auto Queue<T>::operator=(QueueT&& other) noexcept -> QueueT&
	{
		if (this != &other)
		{
			Delete();
			Header = other.Header;
			Length = other.Length;
		}
		return *this;
	}

	template <class T>
	auto Queue<T>::operator=(QueueT const& other) -> QueueT&
	{
		if (this != &other)
		{
			Delete();
			Enqueue(other);
		}
		return *this;
	}

	template <class T>
	Queue<T>::Queue(std::initializer_list<T> data)
	{
		Enqueue(data);
	}

	template <class T>
	Queue<T>::Queue(int const length, T const* data)
	{
		Enqueue(length, data);
	}

	template <class T>
	auto Queue<T>::GetHeader() const -> TraversalNodeT
	{
		return TraversalNodeT(Header);
	}

	template <class T>
	auto Queue<T>::GetEnd() const -> TraversalNodeT
	{
		TraversalNodeT traversalNode(Header);
		traversalNode += Length - 1;
		return traversalNode;
	}

	template <class T>
	int Queue<T>::GetLength() const
	{
		return Length;
	}

	template <class T>
	bool Queue<T>::IsEmpty() const
	{
		return Length == 0;
	}

	template <class T>
	void Queue<T>::Delete()
	{
		while (Header)
		{
			Dequeue();
		}
	}

	template <class T>
	auto Queue<T>::Enqueue(T const& data) -> QueueT&
	{
		auto newNode = new NodeT(data);
		if (!Header)
		{
			Header = newNode;
			Length++;
			return *this;
		}
		auto endNode = GetEnd();
		NodeT::LinkNodes({*endNode, newNode});
		Length++;
		return *this;
	}

	template <class T>
	auto Queue<T>::Enqueue(int const num, T const* data) -> QueueT&
	{
		for (auto i = 0; i < num; i++)
		{
			Enqueue(data[i]);
		}
		return *this;
	}

	template <class T>
	auto Queue<T>::Enqueue(std::initializer_list<T> data) -> QueueT&
	{
		Enqueue(data.size(), data.begin());
		return *this;
	}

	template <class T>
	auto Queue<T>::Enqueue(QueueT const& data) -> QueueT&
	{
		auto travel = data.GetHeader();
		while (*travel)
		{
			Enqueue(travel->Data);
			++travel;
		}
		return *this;
	}

	template <class T>
	T Queue<T>::Dequeue()
	{
		if (!Header)
		{
			throw std::exception("Dequeuing from a queue with no data!");
		}
		auto const data = Header->Data;
		auto oldHeader = Header;
		Header = Header->Next;
		Length--;
		delete oldHeader;
		return data;
	}

	template <class T>
	T& Queue<T>::Peek() const
	{
		return Peek(Length - 1);
	}

	template <class T>
	T& Queue<T>::Peek(int const index) const
	{
		auto travel = GetHeader();
		travel += (Length-1)-index;
		return travel->Data;
	}

	template <class T>
	Queue<T>::~Queue()
	{
		Delete();
	}
}
