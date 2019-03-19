//@KCLIB_FILE_COMMENT@
#pragma once
#include <initializer_list>
#include <exception>
#include <ostream>
#include <unordered_map>

namespace KC
{
	template <class T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree() = default;

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

			Node(const Node& other) = default;
			Node(Node&& other) noexcept = default;
			Node& operator=(const Node& other) = default;
			Node& operator=(Node&& other) noexcept = default;

			explicit Node(const T& data, Node* left = nullptr, Node* right = nullptr)
				: Data(data), Left(left), Right(right)
			{
			}

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
			virtual ~TraversalNode() = default;
			TraversalNode(const TraversalNode& other) = default;
			TraversalNode(TraversalNode&& other) noexcept = default;
			TraversalNode& operator=(const TraversalNode& other) = default;
			TraversalNode& operator=(TraversalNode&& other) noexcept = default;
			TraversalNode() = default;

			bool CompletedCycle = false;

			virtual void CycleLeft()
			{
				CurrentNode = CurrentNode->Left;
			};

			virtual void CycleRight()
			{
				CurrentNode = CurrentNode->Right;
			}

			virtual void CycleUp()
			{
				CurrentNode = CurrentNode->Parent;
			}

			virtual void Cycle()
			{
			}

			explicit TraversalNode(Node* node) : CurrentNode(node)
			{
				Steps[node] = 0;
			}

			explicit TraversalNode(Node& node) : CurrentNode(&node)
			{
				Steps[&node] = 0;
			}

			Node& operator*()
			{
				return *CurrentNode;
			}

			Node* operator->()
			{
				return CurrentNode;
			}

			explicit operator bool()
			{
				return CurrentNode != nullptr;
			}

			Node* PeekLeft() const
			{
				return CurrentNode->Left;
			}

			Node* PeekRight() const
			{
				return CurrentNode->Right;
			}

			explicit operator Node*()
			{
				return CurrentNode;
			}
		};

		class PostOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			explicit PostOrderTraversalNode(Node* node) : TraversalNode(node)
			{
			}

			explicit PostOrderTraversalNode(Node& node) : TraversalNode(node)
			{
			}

			void Cycle() override
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
		};

		class InOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			explicit InOrderTraversalNode(Node* node) : TraversalNode(node)
			{
			}

			explicit InOrderTraversalNode(Node& node) : TraversalNode(node)
			{
			}

			void Cycle() override
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
		};

		class PreOrderTraversalNode final : public TraversalNode
		{
			using TraversalNode::CurrentNode;
			using TraversalNode::Steps;
		public:
			using TraversalNode::CompletedCycle;

			explicit PreOrderTraversalNode(Node* node) : TraversalNode(node)
			{
			}

			explicit PreOrderTraversalNode(Node& node) : TraversalNode(node)
			{
			}

			void Cycle() override
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
		};

	private:
		Node* Root = nullptr;
	public:
		BinarySearchTree& Insert(T const& data)
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

			bool inserted = false;

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
			return *this;
		}

		BinarySearchTree& Insert(T const data[])
		{
			for (auto& i : data)
			{
				Insert(i);
			}
			return *this;
		}

		BinarySearchTree& Insert(std::initializer_list<T> data)
		{
			Insert(data.begin());
			return *this;
		}

		template <class TraversalType=PreOrderTraversalNode>
		TraversalType GetRoot()
		{
			return TraversalType(Root);
		}

		BinarySearchTree& operator<<(T const& data)
		{
			return Insert(data);
		}

		void PrintInOrder()
		{
			auto b = GetRoot<InOrderTraversalNode>();
			b.Cycle();
			while (!b.CompletedCycle)
			{
				std::cout << b->Data << std::endl;
				b.Cycle();
			}
		}

		void PrintPostOrder()
		{
			auto b = GetRoot<PostOrderTraversalNode>();
			b.Cycle();
			while (!b.CompletedCycle)
			{
				std::cout << b->Data << std::endl;
				b.Cycle();
			}
		}

		void PrintPreOrder()
		{
			auto b = GetRoot<PreOrderTraversalNode>();
			b.Cycle();
			while (!b.CompletedCycle)
			{
				std::cout << b->Data << std::endl;
				b.Cycle();
			}
		}

		bool IsEmpty()
		{
			return Root != nullptr;
		}

	private:
		void static DestroyTreeNodes(Node* node)
		{
			if (node != nullptr)
			{
				DestroyTreeNodes(node->Left);
				DestroyTreeNodes(node->Right);
				delete node;
			}
		}
	public:
		void DestroyTree()
		{
			DestroyTreeNodes(Root);
		}

		~BinarySearchTree()
		{
			DestroyTree();
		}
	};
}
