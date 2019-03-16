#ifndef H_BVHTree
#define H_BVHTree

#include "Object.h"
#include "BVHNode.h"
#include "HitInfo.h"

// The maximum number of primitives to allow in a single node of the tree
constexpr int MAX_NODE_SIZE = 2;

class BVHTree
{
private:
	BVHNode * root;
	list<Object*> objects;

	// Helper methods
	void build();
	void _build(BVHNode * root);

public:
	BVHTree();
	BVHTree(Object ** objects);
	~BVHTree();

	// Utility methods
	bool intersect(Ray & ray, HitInfo * hit_info);
};

#endif