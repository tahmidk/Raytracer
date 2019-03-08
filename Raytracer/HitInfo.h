#ifndef H_HitInfo
#define H_HitInfo

#include <glm/glm.hpp>
#include "Object.h"
#include <limits>

using namespace glm;

class HitInfo
{
	private:
		bool valid;
		float t_hit;
		vec3 P_hit;
		vec3 norm;
		Object * obj_hit;

	public:
		// Constructors
		HitInfo();
		HitInfo(float t, vec3 P, vec3 norm, Object * obj);

		// Getter methods
		bool is_valid();
		float get_t();
		vec3 get_point();
		vec3 get_norm();
		Object * get_object();
};

#endif // !H_HitInfo


