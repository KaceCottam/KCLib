//@KCLIB_FILE_COMMENT@
#pragma once
#include <initializer_list>
#include <exception>
#include <ostream>
#include <unordered_map>

namespace KC
{
	template <class T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree();

		struct Node final
		{
			friend bool operator<(const Node& lhs, const Node& rhs)
			{
				if (lhs.Data < rhs.Data)
					return true;
				if (rhs.Data < lhs.Data)
					return false;
				if (lhs.Left < rhs.Left)
					return true;
				if (rhs.Left < lhs.Left)
					return false;
				return lhs.Right < rhs.Right;
			}

			friend bool operator<=(const Node& lhs, const Node& rhs)
			{
				return !(rhs < lhs);
			}

			friend bool operator>(const Node& lhs, const Node& rhs)
			{
				return rhs < lhs;
			}

			friend bool operator>=(const Node& lhs, const Node& rhs)
			{
				return !(lhs < rhs);
			}

			friend bool operator==(const Node& lhs, const Node& rhs)
			{
				return lhs.Data == rhs.Data
					&& lhs.Left == rhs.Left
					&& lhs.Right == rhs.Right;
			}

			friend bool operator!=(const Node& lhs, const Node& rhs)
			{
				return !(lhs == rhs);
			}

			T Data;
			Node* Left = nullptr;
			Node* Right = nullptr;
			Node* Parent = nullptr;

			Node(const Node& other);
			Node(Node&& other) noexcept;
			Node& operator=(const Node& other);
			Node& operator=(Node&& other) noexcept;

			explicit Node(const T& data, Node* left = nullptr, Node* right = nullptr);

			friend static void LinkNodes(Node& left, Node& root, Node& right)
			{
				root.Left = &left;
				root.Right = &right;
			}

			friend static void LinkNodes(std::initializer_list<Node&> nodeList)
			{
				if (nodeList.size() != 3)
					throw std::exception("NodeList size is not 3!");
				LinkNodes(nodeList[0], nodeList[1], nodeList[2]);
			}
		};

		class TraversalNode
		{
		protected:
			Node* CurrentNode = nullptr;
			std::unordered_map<Node*, int> Steps;
		public:
			virtual ~TraversalNode();
			TraversalNode(const TraversalNode& other);
			TraversalNode(TraversalNode&& other) noexcept;
			TraversalNode& operator=(const TraversalNode& other);
			TraversalNode& operator=(TraversalNode&& other) noexcept;
			TraversalNode();

			bool CompletedCycle = false;

			virtual void CycleLeft();; 
			virtual void CycleRight(); 
			virtual void CycleUp(); 
			virtual void Cycle();

			explicit TraversalNode(Node* node); 
			explicit TraversalNode(Node& node);

			Node& operator*(); 
			Node* operator->(); 
			explicit operator bool(); 
			explicit operator Node*()
			{
				return CurrentNode;
			}

			Node* PeekLeft() const; 
			Node* PeekRight() const;
		};

		class PostOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			PostOrderTraversalNode(TraversalNode& node);
			PostOrderTraversalNode(TraversalNode&& node);
			explicit PostOrderTraversalNode(Node* node); 
			explicit PostOrderTraversalNode(Node& node);

			void Cycle() override;
		};

		class InOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			InOrderTraversalNode(TraversalNode& node);
			InOrderTraversalNode(TraversalNode&& node);
			explicit InOrderTraversalNode(Node* node); 
			explicit InOrderTraversalNode(Node& node);

			void Cycle() override;
		};

		class PreOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			PreOrderTraversalNode(TraversalNode& node);
			PreOrderTraversalNode(TraversalNode&& node);
			explicit PreOrderTraversalNode(Node* node); 
			explicit PreOrderTraversalNode(Node& node);

			void Cycle() override;
		};

	private:
		Node* Root = nullptr;
		int Length = 0;
	public:
		BinarySearchTree& Insert(T const& data); 
		BinarySearchTree& Insert(T const data[]); 
		BinarySearchTree& Insert(std::initializer_list<T> data);

		TraversalNode GetRoot();

		BinarySearchTree& operator<<(T const& data);

		BinarySearchTree& PrintInOrder(); 
		BinarySearchTree& PrintPostOrder(); 
		BinarySearchTree& PrintPreOrder();

		int GetLength() const;

		bool IsEmpty();

	private:
		void static DestroyTreeNodes(Node* node);
	public:
		void DestroyTree();

		~BinarySearchTree();
	};


	template <class T>
	BinarySearchTree<T>::BinarySearchTree() = default;
	template <class T>
	BinarySearchTree<T>::Node::Node(const Node& other) = default;
	template <class T>
	BinarySearchTree<T>::Node::Node(Node&& other) noexcept = default;
	template <class T>
	auto BinarySearchTree<T>::Node::operator=(const Node& other) -> Node& = default;
	template <class T>
	auto BinarySearchTree<T>::Node::operator=(Node&& other) noexcept -> Node& = default;

	template <class T>
	BinarySearchTree<T>::Node::Node(const T& data, Node* left, Node* right): Data(data), Left(left), Right(right)
	{
	}

	template <class T>
	BinarySearchTree<T>::TraversalNode::~TraversalNode() = default;
	template <class T>
	BinarySearchTree<T>::TraversalNode::TraversalNode(const TraversalNode& other) = default;
	template <class T>
	BinarySearchTree<T>::TraversalNode::TraversalNode(TraversalNode&& other) noexcept = default;
	template <class T>
	auto BinarySearchTree<T>::TraversalNode::operator=( const TraversalNode& other) -> TraversalNode& = default;
	template <class T>
	auto BinarySearchTree<T>::TraversalNode::operator=( TraversalNode&& other) noexcept -> TraversalNode& = default;
	template <class T>
	BinarySearchTree<T>::TraversalNode::TraversalNode() = default;

	template <class T>
	void BinarySearchTree<T>::TraversalNode::CycleLeft()
	{
		CurrentNode = CurrentNode->Left;
	}

	template <class T>
	void BinarySearchTree<T>::TraversalNode::CycleRight()
	{
		CurrentNode = CurrentNode->Right;
	}

	template <class T>
	void BinarySearchTree<T>::TraversalNode::CycleUp()
	{
		CurrentNode = CurrentNode->Parent;
	}

	template <class T>
	void BinarySearchTree<T>::TraversalNode::Cycle()
	{
	}

	template <class T>
	BinarySearchTree<T>::TraversalNode::TraversalNode(Node* node): CurrentNode(node)
	{
		Steps[node] = 0;
	}

	template <class T>
	BinarySearchTree<T>::TraversalNode::TraversalNode(Node& node): CurrentNode(&node)
	{
		Steps[&node] = 0;
	}

	template <class T>
	auto BinarySearchTree<T>::TraversalNode::operator*() -> Node&
	{
		return *CurrentNode;
	}

	template <class T>
	auto BinarySearchTree<T>::TraversalNode::operator->() -> Node*
	{
		return CurrentNode;
	}

	template <class T>
	BinarySearchTree<T>::TraversalNode::operator bool()
	{
		return CurrentNode != nullptr;
	}

	template <class T>
	auto BinarySearchTree<T>::TraversalNode::PeekLeft() const -> Node*
	{
		return CurrentNode->Left;
	}

	template <class T>
	auto BinarySearchTree<T>::TraversalNode::PeekRight() const -> Node*
	{
		return CurrentNode->Right;
	}

	template <class T>
	BinarySearchTree<T>::PostOrderTraversalNode::PostOrderTraversalNode(TraversalNode&& node) : TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::PostOrderTraversalNode::PostOrderTraversalNode(TraversalNode& node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::PostOrderTraversalNode::PostOrderTraversalNode(Node* node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::PostOrderTraversalNode::PostOrderTraversalNode(Node& node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	void BinarySearchTree<T>::PostOrderTraversalNode::Cycle()
	{
		++Steps[CurrentNode];
		CompletedCycle = false;
		while (Steps[CurrentNode] != 3)
		{
			switch (Steps[CurrentNode])
			{
			case 1:
				if (CurrentNode->Left)
					CurrentNode = CurrentNode->Left;
				break;
			case 2:
				if (CurrentNode->Right)
					CurrentNode = CurrentNode->Right;
				break;
			default:
				if (CurrentNode->Parent)
				{
					CurrentNode = CurrentNode->Parent;
				}
				else
				{
					Steps = std::unordered_map<Node*, int>();
					CompletedCycle = true;
				}
				break;
			}
			++Steps[CurrentNode];
		}
	}

	template <class T>
	BinarySearchTree<T>::InOrderTraversalNode::InOrderTraversalNode(TraversalNode&& node) : TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::InOrderTraversalNode::InOrderTraversalNode(TraversalNode& node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::InOrderTraversalNode::InOrderTraversalNode(Node* node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::InOrderTraversalNode::InOrderTraversalNode(Node& node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	void BinarySearchTree<T>::InOrderTraversalNode::Cycle()
	{
		++Steps[CurrentNode];
		CompletedCycle = false;
		while (Steps[CurrentNode] != 2)
		{
			switch (Steps[CurrentNode])
			{
			case 1:
				if (CurrentNode->Left)
					CurrentNode = CurrentNode->Left;
				break;
			case 3:
				if (CurrentNode->Right)
					CurrentNode = CurrentNode->Right;
				break;
			default:
				if (CurrentNode->Parent)
				{
					CurrentNode = CurrentNode->Parent;
				}
				else
				{
					Steps = std::unordered_map<Node*, int>();
					CompletedCycle = true;
				}
				break;
			}
			++Steps[CurrentNode];
		}
	}
	template <class T>
	BinarySearchTree<T>::PreOrderTraversalNode::PreOrderTraversalNode(TraversalNode&& node) : TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::PreOrderTraversalNode::PreOrderTraversalNode(TraversalNode& node): TraversalNode(node)
	{
		Cycle();
	}


	template <class T>
	BinarySearchTree<T>::PreOrderTraversalNode::PreOrderTraversalNode(Node* node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	BinarySearchTree<T>::PreOrderTraversalNode::PreOrderTraversalNode(Node& node): TraversalNode(node)
	{
		Cycle();
	}

	template <class T>
	void BinarySearchTree<T>::PreOrderTraversalNode::Cycle()
	{
		++Steps[CurrentNode];
		CompletedCycle = false;
		while (Steps[CurrentNode] != 1)
		{
			switch (Steps[CurrentNode])
			{
			case 2:
				if (CurrentNode->Left)
					CurrentNode = CurrentNode->Left;
				break;
			case 3:
				if (CurrentNode->Right)
					CurrentNode = CurrentNode->Right;
				break;
			default:
				if (CurrentNode->Parent)
				{
					CurrentNode = CurrentNode->Parent;
				}
				else
				{
					Steps = std::unordered_map<Node*, int>();
					CompletedCycle = true;
				}
				break;
			}
			++Steps[CurrentNode];
		}
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::Insert(T const& data)
	{
		// Root Node!
		auto newNode = new Node(data);
		if (!Root)
		{
			// No Root Node!
			Root = newNode;
			return *this;
		}

		auto traversalNode = TraversalNode(Root);
		// Compare data to each node.

		auto inserted = false;

		while (!inserted)
		{
			if (data < traversalNode->Data)
			{
				if (traversalNode.PeekLeft() != nullptr)
					traversalNode.CycleLeft();
				else
				{
					traversalNode->Left = newNode;
					newNode->Parent = (Node*)traversalNode;
					inserted = true;
				}
			}
			else if (data > traversalNode->Data)
			{
				if (traversalNode.PeekRight() != nullptr)
					traversalNode.CycleRight();
				else
				{
					traversalNode->Right = newNode;
					newNode->Parent = (Node*)traversalNode;
					inserted = true;
				}
			}
			else if (data == traversalNode->Data)
			{
				delete newNode;
				inserted = true;
			}
		}
		Length++;
		return *this;
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::Insert(const T data[])
	{
		for (auto& i : data)
		{
			Insert(i);
		}
		return *this;
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::Insert(std::initializer_list<T> data)
	{
		Insert(data.begin());
		return *this;
	}

	template <class T>
	auto BinarySearchTree<T>::GetRoot() -> TraversalNode
	{
		return TraversalNode(Root);
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::operator<<(T const& data)
	{
		return Insert(data);
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::PrintInOrder()
	{
		InOrderTraversalNode b = GetRoot();
		while (!b.CompletedCycle)
		{
			std::cout << b->Data << std::endl;
			b.Cycle();
		}
		return *this;
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::PrintPostOrder()
	{
		PostOrderTraversalNode b = GetRoot();
		while (!b.CompletedCycle)
		{
			std::cout << b->Data << std::endl;
			b.Cycle();
		}
		return *this;
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::PrintPreOrder()
	{
		PreOrderTraversalNode b = GetRoot();
		while (!b.CompletedCycle)
		{
			std::cout << b->Data << std::endl;
			b.Cycle();
		}
		return *this;
	}

	template <class T>
	int BinarySearchTree<T>::GetLength() const
	{
		return Length;
	}

	template <class T>
	bool BinarySearchTree<T>::IsEmpty()
	{
		return Root == nullptr;
	}

	template <class T>
	void BinarySearchTree<T>::DestroyTreeNodes(Node* node)
	{
		if (node != nullptr)
		{
			DestroyTreeNodes(node->Left);
			DestroyTreeNodes(node->Right);
			delete node;
		}
	}

	template <class T>
	void BinarySearchTree<T>::DestroyTree()
	{
		DestroyTreeNodes(Root);
	}

	template <class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		DestroyTree();
	}
}
