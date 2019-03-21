//@KCLIB_FILE_COMMENT
#pragma once

#include <stdexcept>
#include <initializer_list>

namespace KC
{
	template <class T, int Max = 100>
	class Stack final
	{
		int Size;
		T Header[Max];

	public:
		explicit Stack(int size = 0);

		~Stack();

		bool IsEmpty() const;

		Stack<T, Max>& Push(T const& data); 
		Stack<T, Max>& Push(int const length, T const* data); 
		Stack<T, Max>& Push(std::initializer_list<T> const& data);

		T Pop();

		T& Peek(int const index) const; 
		T& Peek() const;

		int GetSize() const;
	};

	template <class T, int Max>
	Stack<T, Max>::Stack(int size): Size{size}, Header{}
	{
	}

	template <class T, int Max>
	Stack<T, Max>::~Stack() = default;

	template <class T, int Max>
	bool Stack<T, Max>::IsEmpty() const
	{
		return Size == 0;
	}

	template <class T, int Max>
	Stack<T, Max>& Stack<T, Max>::Push(T const& data)
	{
		if (Size >= Max)
		{
			throw std::overflow_error("Stack overflow!");
		}
		Header[Size++] = data;
		return *this;
	}

	template <class T, int Max>
	Stack<T, Max>& Stack<T, Max>::Push(int const length, T const* data)
	{
		for (auto i = 0; i < length; i++)
		{
			Push(data[i]);
		}
		return *this;
	}

	template <class T, int Max>
	Stack<T, Max>& Stack<T, Max>::Push(std::initializer_list<T> const& data)
	{
		Push(data.size(), data.begin());
		return *this;
	}

	template <class T, int Max>
	T Stack<T, Max>::Pop()
	{
		if (Size <= 0)
		{
			throw std::out_of_range("Stack is empty!");
		}
		T data = Header[Size--];

		return data;
	}

	template <class T, int Max>
	T& Stack<T, Max>::Peek(int const index) const
	{
		if (index < 0 || index > Max)
		{
			throw std::out_of_range("Index out of range!");
		}
		if (Size <= 0)
		{
			throw std::out_of_range("Stack is empty!");
		}
		return Header[index];
	}

	template <class T, int Max>
	T& Stack<T, Max>::Peek() const
	{
		return Peek(Size - 1);
	}

	template <class T, int Max>
	int Stack<T, Max>::GetSize() const
	{
		return Size;
	}
}
