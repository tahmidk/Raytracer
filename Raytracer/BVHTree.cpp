/*==================================================================
	File:	[BVHTree.cpp]
	Auth:	Steven Natalius
			Tahmid Khan

	Desc:	Represents the entirety of a BHV tree built using a list
			of object primitives
==================================================================*/

#include "pch.h"
#include "BVHTree.h"

#include <algorithm>
#include <vector>
#include <iostream>

/*----------------------[ Comparators ]------------------------*/
bool comparator_x(Object * obj1, Object * obj2)
{
	float obj1_x = obj1->get_centroid().x;
	float obj2_x = obj2->get_centroid().x;
	return (obj1_x < obj2_x);
}

bool comparator_y(Object * obj1, Object * obj2)
{
	float obj1_y = obj1->get_centroid().y;
	float obj2_y = obj2->get_centroid().y;
	return (obj1_y < obj2_y);
}

bool comparator_z(Object * obj1, Object * obj2)
{
	float obj1_z = obj1->get_centroid().z;
	float obj2_z = obj2->get_centroid().z;
	return (obj1_z < obj2_z);
}

BVHTree::BVHTree()
{
	this->root = nullptr;
	this->objects = list<Object*>();
}

/*-------------------------------------------------------------------
	Func:	Constructor: [BVHTree]
	Args:	objects - a pointer to a series of object pointers as
				initialized by the Parser class
	Desc:	Initializes and build the BVH tree
	Rtrn:	None
-------------------------------------------------------------------*/
BVHTree::BVHTree(Object ** objects)
{
	// Make the world bounding box of the root by unioning all objects'
	// individual bounding boxes
	Object * curr_obj = objects[0];
	if (curr_obj == nullptr) {
		cerr << "No objects detected..." << endl;
		return;
	}
	// Initialize world box
	BoundingBox world_box(curr_obj);

	curr_obj = objects[1];
	for (int obj_num = 1; curr_obj != nullptr; obj_num++) {
		BoundingBox obj_box(curr_obj);
		world_box = world_box + obj_box;

		curr_obj = objects[obj_num + 1];
	}

	// Build root and call recursive helper
	this->root = new BVHNode(world_box);
	_build(this->root);
}

/*-------------------------------------------------------------------
	Func:	Destructor: [BVHTree]
	Args:	None
	Desc:	Deallocates entire tree
	Rtrn:	None
-------------------------------------------------------------------*/
BVHTree::~BVHTree()
{
	//delete (this->root);
}

/*-------------------------------------------------------------------
	Func:	[intersect]
	Args:	ray - the intersecting ray
			hit_info - the HitInfo object to record collision data in
	Desc:	Determines whether the given ray intersects any of the 
			object primitives in this BVH Tree
	Rtrn:	A pointer to the object of intersection
			nullptr if no intersections
-------------------------------------------------------------------*/
bool BVHTree::intersect(Ray & ray, HitInfo * hit_info) {
	if (this->root != nullptr) {
		// If the ray doesn't even intersect this node's bounding box, return failure
		float t_hit;
		if (this->root->get_box().intersect_box(ray, &t_hit))
			return (this->root->intersect_node(ray, hit_info));
		else
			return nullptr;
	}
	
	cerr << "Root of BVHTree is null!" << endl;
	return nullptr;
}

/*-------------------------------------------------------------------
	Func:	[build]
	Args:	None
	Desc:	Builds the BVH tree
	Rtrn:	None
-------------------------------------------------------------------*/
void BVHTree::build()
{
	// Make the world bounding box of the root by unioning all objects'
	// individual bounding boxes
	BoundingBox world_box(objects.front());
	for (auto it = objects.begin(); it != objects.end(); it++) {
		if (it == objects.begin())
			continue;
		BoundingBox obj_box(*it);
		world_box = world_box + obj_box;
	}

	// Build root and call recursive helper
	this->root = new BVHNode(world_box);
	_build(this->root);
}

/*-------------------------------------------------------------------
	Func:	[_build]
	Args:	root - the root of the tree or subtree
	Desc:	Recursive helper to the build() method
	Rtrn:	None
-------------------------------------------------------------------*/
void BVHTree::_build(BVHNode * node) {
	// Base case
	if (node->get_size() <= MAX_NODE_SIZE)
		return;

	// Recursive case
	list<Object*> left;
	list<Object*> right;

	// First split this node using Midpoint Splitting Algorithm
	BoundingBox node_box = node->get_box();
	//vector<Object*> node_objects(node_box.get_objects().begin(), node_box.get_objects().end());
	list<Object*> node_objects_list = node_box.get_objects();
	vector<Object*> node_objects;
	node_objects.reserve(node_objects_list.size());
	copy(node_objects_list.begin(), node_objects_list.end(), back_inserter(node_objects));

	float midpoint;
	axis a = node->longest_axis();
	switch (a){
		// Split along the x-axis
		case axis_x:
			midpoint = node_box.get_centroid().x;
			for (Object * obj : node_objects) {
				if (obj->get_centroid().x < midpoint)
					left.push_back(obj);
				else
					right.push_back(obj);
			}
			break;
		// Split along the y-axis
		case axis_y:
			midpoint = node_box.get_centroid().y;
			for (Object * obj : node_objects) {
				if (obj->get_centroid().y < midpoint)
					left.push_back(obj);
				else
					right.push_back(obj);
			}
			break;
		// Split along the z-axis
		case axis_z:
			midpoint = node_box.get_centroid().z;
			for (Object * obj : node_objects) {
				if (obj->get_centroid().z < midpoint)
					left.push_back(obj);
				else
					right.push_back(obj);
			}
			break;
		default:
			break;
	}

	// If at this point, one side is empty, split by median
	// Sort objects along the longest axis and split the resulting list in half
	if (left.empty() || right.empty()) {
		// Empty both the lists
		left.clear();
		right.clear();

		// Sort by the longest axis
		switch (a){
			case axis_x:
				std::sort(node_objects.begin(), node_objects.end(), comparator_x);
				break;
			case axis_y:
				std::sort(node_objects.begin(), node_objects.end(), comparator_y);
				break;
			case axis_z:
				std::sort(node_objects.begin(), node_objects.end(), comparator_z);
				break;
			default:
				break;
		}

		// Split right down the sorted middle
		int mid = node->get_size() / 2;
		auto it = node_objects.begin();
		for (int i = 0; i < node->get_size(); i++) {
			Object * obj = *(it++);
			if (i < mid)
				left.push_back(obj);
			else
				right.push_back(obj);
		}
	}

	// Make the left BVHNode
	BoundingBox left_box(left.front());
	for (auto it = left.begin(); it != left.end(); it++) {
		if (it == left.begin())
			continue;
		BoundingBox obj_box(*it);
		left_box = left_box + obj_box;
	}
	BVHNode * left_new = new BVHNode(left_box);
	node->set_left(left_new);

	// Make the right BVHNode
	BoundingBox right_box(right.front());
	for (auto it = right.begin(); it != right.end(); it++) {
		if (it == right.begin())
			continue;
		BoundingBox obj_box(*it);
		right_box = right_box + obj_box;
	}
	BVHNode * right_new = new BVHNode(right_box);
	node->set_right(right_new);

	// Finally make the left and right subtrees recursively
	#pragma omp parallel sections
	{
		#pragma omp section
		_build(node->get_left());
		#pragma omp section
		_build(node->get_right());
	}

	return;
}
