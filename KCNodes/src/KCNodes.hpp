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
		static void LinkNodes(int const length, NodeT** nodes)
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
	};

	template <class T>
	class NodeBase<T, true>
	{
		using NodeT = Node<T, true>;
	public:
		NodeT* Previous = nullptr;

		static void LinkNodes(int const length, NodeT** nodes)
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
	};

	template <class T, bool DoublyLinked>
	class Node : public NodeBase<T, DoublyLinked>
	{
	protected:
		using NodeT = Node<T, DoublyLinked>;
	public:
		T Data;
		NodeT* Next = nullptr;

		Node(const NodeT& other) = default;
		Node(NodeT&& other) noexcept = default;
		Node() = default;

		explicit Node(T const& data) : Data{data}
		{
		}

		NodeT& operator=(NodeT const& other)
		{
			Data = other.Data;
			return *this;
		}

		NodeT& operator=(NodeT&& other) noexcept
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

		using NodeBase<T, DoublyLinked>::LinkNodes;
		static void LinkNodes(std::initializer_list<NodeT*> nodes)
		{
			auto nodeList = new NodeT*[nodes.size()];
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

		TraversalNodeT& operator--()
		{
			Current = Current->Previous;
			return *this;
		}

		TraversalNodeT operator--(int)
		{
			TraversalNodeT result(*this);
			--*this;
			return result;
		}

		TraversalNodeT operator-(int const& right)
		{
			auto temp = *this;
			temp -= right;
			return temp;
		}

		TraversalNodeT& operator-=(const int num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator--();
			}
			return *this;
		}
	};

	template <class T, bool DoublyLinked>
	class TraversalNode : public TraversalNodeBase<T, DoublyLinked>
	{
	protected:
		using TraversalNodeT = TraversalNode<T, DoublyLinked>;
		using NodeT = Node<T, DoublyLinked>;
	public:
		TraversalNode() = default;

		explicit TraversalNode(NodeT* node) 
		{
			this->Current = node;
		}

		TraversalNodeT& operator++()
		{
			this->Current = this->Current->Next;
			return *this;
		}

		TraversalNodeT operator++(int)
		{
			TraversalNodeT result(*this);
			++*this;
			return result;
		}

		TraversalNodeT& operator+=(int const num)
		{
			for (auto i = 0; i < num; i++)
			{
				operator++();
			}
			return *this;
		}

		NodeT* operator*()
		{
			return this->Current;
		}

		NodeT* operator->()
		{
			return this->Current;
		}

		bool operator==(TraversalNodeT& other) const
		{
			return this->Current == other.Current;
		}

		bool operator==(NodeT& other) const
		{
			return this->Current == &other;
		}

		operator bool() const
		{
			return this->Current != nullptr;
		}

		operator NodeT() const
		{
			return *this->Current;
		}

		TraversalNodeT operator+(int const& right)
		{
			auto temp = *this;
			temp += right;
			return temp;
		}
	};
}
