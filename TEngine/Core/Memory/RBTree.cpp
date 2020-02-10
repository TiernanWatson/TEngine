#include "RBTree.h"

namespace TEngine
{
	RBTree::RBTree(RBNode* root)
		: root(root)
	{
		root->parent = nullptr;
		root->left = nullptr;
		root->right = nullptr;
		root->color = RBColor::BLACK;
	}

	RBNode* RBTree::Find(USIZE size) const
	{
		USIZE min_fit_size = SIZE_MAX;
		RBNode* min_fit = nullptr;
		RBNode* current = root;
		while (current != nullptr)
		{
			USIZE current_size = GET_SIZE(current);

			if (current_size >= size && current_size < min_fit_size)
			{
				min_fit = current;
				min_fit_size = current_size;
			}

			if (size < current_size)
				current = current->left;
			else
				current = current->right;
		}
		return min_fit;
	}

	void RBTree::Insert(RBNode* node)
	{
		USIZE value = GET_SIZE(node);

		node->left = nullptr;
		node->right = nullptr;
		node->color = RBColor::RED;

		RBNode* current = root;
		while (current != nullptr)
		{
			if (value < GET_SIZE(current))
			{
				if (current->left == nullptr)
				{
					node->parent = current;
					current->left = node;
					break;
				}
				else
				{
					current = current->left;
				}
			}
			else
			{
				if (current->right == nullptr)
				{
					node->parent = current;
					current->right = node;
					break;
				}
				else
				{
					current = current->right;
				}
			}
		}

		InsertFixup(node);
	}

	void RBTree::Remove(RBNode* node)
	{
		RBNode* right_min = GetMin(node->right);

		if (right_min->color == RBColor::RED)
		{
			Replace(node, right_min);
		}
	}

	void RBTree::InsertFixup(RBNode* node)
	{
		if (node->parent == nullptr)  // Root node
		{
			node->color = RBColor::BLACK;
		}
		else if (node->parent->color == RBColor::BLACK)
		{
			return;
		}
		else if (GetUncle(node) != nullptr && GetUncle(node)->color == RBColor::RED)
		{
			RBNode* grandparent = GetGrandparent(node);
			node->parent->color = RBColor::BLACK;
			GetUncle(node)->color = RBColor::BLACK;
			grandparent->color = RBColor::RED;
			InsertFixup(grandparent);
		}
		else  // Parent is red and if any uncle its black
		{
			RBNode* parent = node->parent;
			RBNode* grandparent = parent->parent;

			if (grandparent == nullptr)
				return;

			if (node == parent->right && parent == grandparent->left)
			{
				LeftRotate(parent);
				node = node->left;
			}
			else if (node == parent->left && parent == grandparent->right)
			{
				RightRotate(parent);
				node = node->right;
			}

			parent = node->parent;
			grandparent = parent->parent;

			if (node == parent->left)
				RightRotate(grandparent);
			else
				LeftRotate(grandparent);

			parent->color = RBColor::BLACK;
			grandparent->color = RBColor::RED;
		}
	}

	void RBTree::RemoveFixup(RBNode* node)
	{
	}

	void RBTree::LeftRotate(RBNode* ptr)
	{
		RBNode* right_child = ptr->right;
		ptr->right = right_child->left;

		if (ptr->right != nullptr)
			ptr->right->parent = ptr;

		right_child->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root = right_child;
		else if (ptr == ptr->parent->left)
			ptr->parent->left = right_child;
		else
			ptr->parent->right = right_child;

		right_child->left = ptr;
		ptr->parent = right_child;
	}

	void RBTree::RightRotate(RBNode* ptr)
	{
		RBNode* left_child = ptr->left;
		ptr->left = left_child->right;

		if (ptr->left != nullptr)
			ptr->left->parent = ptr;

		left_child->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root = left_child;
		else if (ptr == ptr->parent->left)
			ptr->parent->left = left_child;
		else
			ptr->parent->right = left_child;

		left_child->right = ptr;
		ptr->parent = left_child;
	}

	void RBTree::Replace(RBNode* replace, RBNode* with)
	{
		RBNode* parent = replace->parent;

		if (replace == parent->left)
		{
			parent->left = with;
		}
		else
		{
			parent->right = with;
		}

		if (with != nullptr)
		{
			with->parent = parent;

		}
	}

	void RBTree::Swap(RBNode* node1, RBNode* node2)
	{
		RBNode* parent = node1->parent;
		RBNode* left = node1->left;
		RBNode* right = node1->right;

		node1->parent = node2->parent;
		node1->left = node2->left;
		node1->right = node2->right;

		node1->right->parent = node1;
		node1->left->parent = node1;

		node2->parent = parent;
		node2->left = left;
		node2->right = right;

		node2->right->parent = node2;
		node2->left->parent = node2;
	}

	void RBTree::Swap(RBColor& color1, RBColor& color2)
	{
		RBColor temp = color1;
		color1 = color2;
		color2 = temp;
	}

	void RBTree::SetColor(RBNode* node, RBColor color)
	{
		node->color = color;
	}

	RBColor RBTree::GetColor(RBNode* node)
	{
		return node->color;
	}

	RBNode* RBTree::GetMin(RBNode* node)
	{
		RBNode* current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	RBNode* RBTree::GetUncle(RBNode* node)
	{
		if (node->parent == nullptr || node->parent->parent == nullptr)
			return nullptr;

		if (node->parent == node->parent->parent->left)
		{
			return node->parent->parent->right;
		}
		else
		{
			return node->parent->parent->left;
		}
	}
	
	RBNode* RBTree::GetGrandparent(RBNode* node)
	{
		if (node->parent == nullptr)
			return nullptr;

		return node->parent->parent;
	}
	
	RBNode* RBTree::GetSibling(RBNode* node)
	{
		if (node == node->parent->left)
		{
			return node->parent->right;
		}
		else
		{
			return node->parent->left;
		}
	}
}
