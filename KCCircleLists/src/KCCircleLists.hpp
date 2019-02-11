#ifndef KCCIRCLELISTS_H
#define KCCIRCLELISTS_H

#include <iostream>

#include "../KCLists/src/KCLists.hpp"

namespace KC
{
	template <class T>
	class CircleList final : public List<T>
	{
	public:
		CircleList();
		CircleList(int length, T const* data);
		explicit CircleList(T const& data);
		CircleList(std::initializer_list<T> data);

		CircleList(CircleList<T> const& other);
		CircleList(CircleList<T>&& other) noexcept;

		explicit CircleList(List<T> const& other);

		auto Push(T const& data) -> void; // operator<<()
		auto Push(int length, T const* data) -> void;
		auto Push(std::initializer_list<T> data) -> void;

		auto Pull()->T; // operator>>()

		auto operator<<(T const& data)->CircleList<T>&;
		auto operator<<(std::initializer_list<T> data)->CircleList<T>&;
		auto operator=(CircleList<T>&& other) noexcept ->CircleList<T>&;
		auto operator=(CircleList<T> const& other)->CircleList<T>&;

		~CircleList();
	};
}

template <class T>
KC::CircleList<T>::CircleList() : List<T>()
{
}

template <class T>
KC::CircleList<T>::CircleList(const int length, T const* data) : List<T>(length, data)
{
	ListNode<T>* traversalNode = this->Header;
	for (auto i = 0; i < length - 1; i++)
	{
		traversalNode = traversalNode->Next;
	}
	traversalNode->Next = this->Header;
	this->Header->Previous = traversalNode;
}

template <class T>
KC::CircleList<T>::CircleList(T const& data) : List<T>(data)
{
	this->Header->Next = this->Header;
	this->Header->Previous = this->Header;
}

template <class T>
KC::CircleList<T>::CircleList(std::initializer_list<T> data) : List<T>(data)
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

template <class T>
KC::CircleList<T>::CircleList(CircleList<T> const& other) : CircleList(static_cast<List<T>>(other))
{
}

template <class T>
KC::CircleList<T>::CircleList(CircleList<T>&& other) noexcept : CircleList(static_cast<List<T>>(other))
{
}

template <class T>
KC::CircleList<T>::CircleList(List<T> const& other) : List<T>(other)
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

template <class T>
auto KC::CircleList<T>::Push(T const& data) -> void
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

template <class T>
auto KC::CircleList<T>::Push(const int length, T const* data) -> void
{
	for (auto i = length - 1; i >= 0; --i)
	{
		Push(data[i]);
	}
}

template <class T>
auto KC::CircleList<T>::Push(std::initializer_list<T> data) -> void
{
	auto length = data.size();
	Push(length, data.begin());
}

template <class T>
auto KC::CircleList<T>::Pull() -> T
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

template <class T>
auto KC::CircleList<T>::operator<<(T const& data) -> CircleList<T>&
{
	Push(data);
	return *this;
}

template <class T>
auto KC::CircleList<T>::operator<<(std::initializer_list<T> data) -> CircleList<T>&
{
	Push(data);
	return *this;
}

template <class T>
auto KC::CircleList<T>::operator=(CircleList<T>&& other) noexcept -> CircleList<T>&
{
	if(&other != this)
	{
		CircleList(static_cast<List<T>>(other));
	}
	return *this;
}

template <class T>
auto KC::CircleList<T>::operator=(CircleList<T> const& other) -> CircleList<T>&
{
	if(&other != this)
	{
		CircleList(static_cast<List<T>>(other));
	}
	return *this;
}

template <class T>
KC::CircleList<T>::~CircleList()
{
	while (this->Header != nullptr)
	{
		this->Pull();
	}
}

#endif // !KCCIRCLELISTS_H
