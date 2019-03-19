//@KCLIB_FILE_COMMENT
#pragma once
#include <initializer_list>

namespace KC
{
	template <class, bool>
	class Node;

	template <class T, bool DoublyLinked = false>
	class NodeBase
	{
		using NodeT = Node<T, DoublyLinked>;
	public:
		static void LinkNodes(int length, NodeT** nodes);
	};

	template <class T, bool DoublyLinked>
	void NodeBase<T, DoublyLinked>::LinkNodes(int const length, NodeT** nodes)
	{
		NodeT* trail = nodes[0];
		for (auto i = 1; i < length; i++)
		{
			NodeT* head = nodes[i];
			if (trail)
			{
				trail->Next = head;
			}
			trail = head;
		}
	}

	template <class T>
	class NodeBase<T, true>
	{
		using NodeT = Node<T, true>;
	public:
		NodeT* Previous = nullptr;

		static void LinkNodes(int length, NodeT** nodes);
	};

	template <class T>
	void NodeBase<T, true>::LinkNodes(int const length, NodeT** nodes)
	{
		NodeT* trail = nodes[0];
		for (auto i = 1; i < length; i++)
		{
			NodeT* head = nodes[i];
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

	template <class T, bool DoublyLinked>
	class Node : public NodeBase<T, DoublyLinked>
	{
	protected:
		using NodeT = Node<T, DoublyLinked>;
	public:
		T Data;
		NodeT* Next = nullptr;

		Node(const NodeT& other);
		Node(NodeT&& other) noexcept;
		Node();

		explicit Node(T const& data);

		NodeT& operator=(NodeT const& other);

		NodeT& operator=(NodeT&& other) noexcept;

		explicit operator T() const;

		T& operator*();

		T& operator->();

		static void LinkNodes(std::initializer_list<NodeT*> nodes);

		~Node() = default;
	};

	template <class T, bool DoublyLinked>
	Node<T, DoublyLinked>::Node(const NodeT& other) = default;
	template <class T, bool DoublyLinked>
	Node<T, DoublyLinked>::Node(NodeT&& other) noexcept = default;
	template <class T, bool DoublyLinked>
	Node<T, DoublyLinked>::Node() = default;

	template <class T, bool DoublyLinked>
	Node<T, DoublyLinked>::Node(T const& data): Data{data}
	{
	}

	template <class T, bool DoublyLinked>
	auto Node<T, DoublyLinked>::operator=(NodeT const& other) -> NodeT&
	{
		Data = other.Data;
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto Node<T, DoublyLinked>::operator=(NodeT&& other) noexcept -> NodeT&
	{
		if (this != &other)
		{
			Data = other.Data;
			other.Data = 0;
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	Node<T, DoublyLinked>::operator T() const
	{
		return Data;
	}

	template <class T, bool DoublyLinked>
	T& Node<T, DoublyLinked>::operator*()
	{
		return Data;
	}

	template <class T, bool DoublyLinked>
	T& Node<T, DoublyLinked>::operator->()
	{
		return Data;
	}

	template <class T, bool DoublyLinked>
	void Node<T, DoublyLinked>::LinkNodes(std::initializer_list<NodeT*> nodes)
	{
		auto nodeList = new NodeT*[nodes.size()];
		auto index = 0;
		for (auto& i : nodes)
		{
			nodeList[index++] = i;
		}
		NodeBase<T, DoublyLinked>::LinkNodes(nodes.size(), nodeList);
		delete[] nodeList;
	}

	template <class, bool>
	class TraversalNode;

	template <class T, bool DoublyLinked = false>
	class TraversalNodeBase
	{
	protected:
		using NodeT = Node<T, DoublyLinked>;
		using TraversalNodeT = TraversalNode<T, DoublyLinked>;
	public:
		Node<T, DoublyLinked>* Current = nullptr;
	};

	template <class T>
	class TraversalNodeBase<T, true>
	{
	protected:
		using NodeT = Node<T, true>;
		using TraversalNodeT = TraversalNode<T, true>;
	public:
		Node<T, true>* Current = nullptr;

		TraversalNodeT& operator--();

		TraversalNodeT operator--(int);

		TraversalNodeT operator-(int const& right);

		TraversalNodeT& operator-=(int num);
	};

	template <class T>
	auto TraversalNodeBase<T, true>::operator--() -> TraversalNodeT&
	{
		Current = Current->Previous;
		return *this;
	}

	template <class T>
	auto TraversalNodeBase<T, true>::operator--(int) -> TraversalNodeT
	{
		TraversalNodeT result(*this);
		--*this;
		return result;
	}

	template <class T>
	auto TraversalNodeBase<T, true>::operator-(int const& right) -> TraversalNodeT
	{
		auto temp = *this;
		temp -= right;
		return temp;
	}

	template <class T>
	auto TraversalNodeBase<T, true>::operator-=(const int num) -> TraversalNodeT&
	{
		for (auto i = 0; i < num; i++)
		{
			operator--();
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	class TraversalNode : public TraversalNodeBase<T, DoublyLinked>
	{
	protected:
		using TraversalNodeT = TraversalNode<T, DoublyLinked>;
		using NodeT = Node<T, DoublyLinked>;
	public:
		TraversalNode();

		explicit TraversalNode(NodeT* node);

		TraversalNodeT& operator++();

		TraversalNodeT operator++(int);

		TraversalNodeT& operator+=(int num);

		NodeT* operator*();

		NodeT* operator->();

		bool operator==(TraversalNodeT& other) const;

		bool operator==(NodeT& other) const;

		operator bool() const;

		operator NodeT*() const;

		operator NodeT() const;

		TraversalNodeT operator+(int const& right);
	};

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked>::TraversalNode() = default;

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked>::TraversalNode(NodeT* node)
	{
		this->Current = node;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator++() -> TraversalNodeT&
	{
		this->Current = this->Current->Next;
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator++(int) -> TraversalNodeT
	{
		TraversalNodeT result(*this);
		++*this;
		return result;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator+=( int const num) -> TraversalNodeT&
	{
		for (auto i = 0; i < num; i++)
		{
			operator++();
		}
		return *this;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator*() -> NodeT*
	{
		return this->Current;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator->() -> NodeT*
	{
		return this->Current;
	}

	template <class T, bool DoublyLinked>
	bool TraversalNode<T, DoublyLinked>::operator==(TraversalNodeT& other) const
	{
		return this->Current == other.Current;
	}

	template <class T, bool DoublyLinked>
	bool TraversalNode<T, DoublyLinked>::operator==(NodeT& other) const
	{
		return this->Current == &other;
	}

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked>::operator bool() const
	{
		return this->Current != nullptr;
	}

	template<class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked>::operator NodeT*() const
	{
		return this->Current;
	}

	template <class T, bool DoublyLinked>
	TraversalNode<T, DoublyLinked>::operator NodeT() const
	{
		return *this->Current;
	}

	template <class T, bool DoublyLinked>
	auto TraversalNode<T, DoublyLinked>::operator+( int const& right) -> TraversalNodeT
	{
		auto temp = *this;
		temp += right;
		return temp;
	}
}
