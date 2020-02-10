#pragma once
#include "../PortableTypes.h"

//#define GET_SIZE(rb_node) *((USIZE*)rb_node - 1)
#define GET_SIZE(rb_node) rb_node->size

namespace TEngine
{
	enum class RBColor
	{
		RED,
		BLACK
	};

	// Size is from mem header (overlaps - combat cache misses)
	struct RBNode
	{
		USIZE size;
		RBNode* left;
		RBNode* parent;
		RBNode* right;
		RBColor color;
	};

	// RBTree used for heap management (free nodes)
	class RBTree
	{
	public:
		RBTree(RBNode* root);

		RBNode* Find(USIZE size) const;

		void Insert(RBNode* node);
		void Remove(RBNode* node);

	private:
		RBNode* root;

		void InsertFixup(RBNode* node);
		void RemoveFixup(RBNode* node);

		void LeftRotate(RBNode* node);
		void RightRotate(RBNode* node);

		void Replace(RBNode* replace, RBNode* with);
		void Swap(RBNode* node1, RBNode* node2);
		void Swap(RBColor& color1, RBColor& color2);

		void SetColor(RBNode* node, RBColor color);
		RBColor GetColor(RBNode* node);

		RBNode* GetMin(RBNode* node);

		RBNode* GetUncle(RBNode* node);
		RBNode* GetGrandparent(RBNode* node);
		RBNode* GetSibling(RBNode* node);
	};
}
