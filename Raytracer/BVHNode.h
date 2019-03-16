#ifndef H_BVHNode
#define H_BVHNode

#include "BoundingBox.h"
#include "HitInfo.h"

class BVHNode
{
private:
	BoundingBox node_box;
	BVHNode * node_left;
	BVHNode * node_right;

	// Helper methods
	HitInfo check_primitives(Ray & ray);

public:
	// Constructor + Desctructor
	BVHNode(BoundingBox & node_box);
	~BVHNode();

	// Utility methods
	bool intersect_node(Ray & ray, HitInfo * hit_info);
	axis longest_axis();

	// Setter methods
	void set_left(BVHNode * left);
	void set_right(BVHNode * right);

	// Getter methods
	BVHNode * get_left();
	BVHNode * get_right();
	BoundingBox get_box();
	int get_size();
};

#endif