/*==================================================================
	File:	[BVHNode.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	Represents a single node in the BHV tree
==================================================================*/

#include "pch.h"
#include "BVHNode.h"

#include <algorithm>

/*-------------------------------------------------------------------
	Func:	Constructor: [BVHNode]
	Args:	box - the bounding box representing this node
	Desc:	Initializes a standard BVHNode
	Rtrn:	None
-------------------------------------------------------------------*/
BVHNode::BVHNode(BoundingBox & box)
{
	this->node_box = box;
	this->node_left = nullptr;
	this->node_right = nullptr;
}

/*-------------------------------------------------------------------
	Func:	Destructor: [BVHNode]
	Args:	None
	Desc:	Deallocates all memory used by this node
	Rtrn:	None
-------------------------------------------------------------------*/
BVHNode::~BVHNode()
{
	if (this->node_left != nullptr) {
		delete (this->node_left);
		this->node_left = nullptr;
	}
	if (this->node_right != nullptr) {
		delete (this->node_right);
		this->node_right = nullptr;
	}
}

/*----------------------[Utility methods]------------------------*/
/*-------------------------------------------------------------------
	Func:	[intersect_node]
	Args:	ray - the intersecting ray
			hit_info - the HitInfo object to record collision data in
	Desc:	Recursively determines whether the given ray intersects any
			of the object primitives contained within this node's subsection
	Rtrn:	A pointer to the object of intersection
			nullptr if no intersections

	PRECONDITION: Caller must verify ray hits this node's bounding box before
	calling this method
-------------------------------------------------------------------*/
bool BVHNode::intersect_node(Ray & ray, HitInfo * hit_info)
{
	// If this node is a leaf (left and right children are null), check the
	// primitives it contains
	if (this->node_left == nullptr && this->node_right == nullptr) {
		*hit_info = check_primitives(ray);
		if (hit_info->is_valid())
			return true;

		return false;
	}

	// Otherwise, check the left and right children
	float t_left, t_right;
	bool hit_left = this->node_left->get_box().intersect_box(ray, &t_left);
	bool hit_right = this->node_right->get_box().intersect_box(ray, &t_right);
	
	// Ray hit both children
	if (hit_left && hit_right) {
		// Left child hit first
		if (t_left < t_right) {
			if (!this->node_left->intersect_node(ray, hit_info))
				if (!this->node_right->intersect_node(ray, hit_info))
					return false;
				else
					return true;
			else
				return true;
		}
		// Right child hit first
		else {
			if (!this->node_right->intersect_node(ray, hit_info))
				if (!this->node_left->intersect_node(ray, hit_info))
					return false;
				else
					return true;
			else
				return true;
		}
	}
	// Ray only hit left child
	else if (hit_left)
		return (this->node_left->intersect_node(ray, hit_info));
	// Ray only hit right child
	else if (hit_right)
		return (this->node_right->intersect_node(ray, hit_info));

	// No intersections
	return false;
}

/*-------------------------------------------------------------------
	Func:	[check_primitives]
	Args:	ray - the incoming ray
	Desc:	Checks the primitives of this node against the given ray
			and records the collision data before returning it
	Rtrn:	The collision data
-------------------------------------------------------------------*/
HitInfo BVHNode::check_primitives(Ray & ray) {
	// True if at least 1 Ray-Scene collision detected, false otherwise
	bool collision = false;

	// Set minimum distance to collided object to infinity and object to NULL
	float t_min = numeric_limits<float>::infinity();
	vec3 P_hit;		// A variable to hold point of collision in world-coord
	vec3 norm_hit;	// A variable to hold surface normal at point of contact
	Object * obj_hit = nullptr;

	list<Object*> objects = node_box.get_objects();
	for (Object * obj : objects) {
		float t_hit;	// Output parameter to store t parameter at hit location
		vec3 norm;		// Output parameter to store surface normal

		// Transform ray by inverse M before running the intersection test
		mat4 M = obj->get_transf();
		mat4 M_inv = inverse(M);
		Ray ray_transf = ray.transformRay(M_inv);
		bool intersects = obj->intersects_ray(ray_transf, &t_hit, &norm);

		// If the intersection is closer to the ray origin, record it as long
		// as it's also greater than the minimum allowed t for this array
		if (intersects && (t_hit > ray.get_tmin()) && (t_hit < t_min)) {
			// Collision detected
			collision = true;

			// Appropriately re-untransform and update point and surface normal at hit point
			t_min = t_hit;
			P_hit = vec3(M * vec4(ray_transf.evaluate(t_min), 1.0f));
			norm_hit = vec3(transpose(M_inv) * vec4(norm, 0.0f));
			obj_hit = obj;
		}
	}

	// At least 1 collision detected
	if (collision == true)
		return HitInfo(t_min, P_hit, norm_hit, obj_hit);

	// Not collisions w/ any of the objects in this scene
	return HitInfo();
}

/*-------------------------------------------------------------------
	Func:	[longest_axis]
	Args:	None
	Desc:	Finds and returns the longest axis of this bounding box
	Rtrn:	One of the 3 axes
-------------------------------------------------------------------*/
axis BVHNode::longest_axis()
{
	const float len_x = node_box.get_xmax() - node_box.get_xmin();
	const float len_y = node_box.get_ymax() - node_box.get_ymin();
	const float len_z = node_box.get_zmax() - node_box.get_zmin();

	float len_max = std::max(std::max(len_x, len_y), len_z);
	if (len_max == len_x) 
		return axis_x;
	else if (len_max == len_y) 
		return axis_y;
	return axis_z;
}

// Setter methods
void BVHNode::set_left(BVHNode * left)		{ this->node_left = left; }
void BVHNode::set_right(BVHNode * right)	{ this->node_right = right; }

// Getter methods
BVHNode * BVHNode::get_left()	{ return node_left; }
BVHNode * BVHNode::get_right()	{ return node_right; }
BoundingBox BVHNode::get_box()	{ return node_box; }
int BVHNode::get_size()			{ return node_box.num_objects(); }
