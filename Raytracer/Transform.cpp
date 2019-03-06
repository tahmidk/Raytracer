// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "pch.h"
#include "Transform.h"
#include <stdio.h>
// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
  mat3 ret;
  // YOUR CODE FOR HW2 HERE
  mat3 identity = mat3(1,0,0,0,1,0,0,0,1);
  float radians = degrees * (pi/180);
  vec3 normalized = normalize(axis);
  mat3 aat = mat3(normalized[0]*normalized[0], normalized[0]*normalized[1], normalized[0]*normalized[2],
                  normalized[0]*normalized[1], normalized[1]*normalized[1], normalized[1]*normalized[2],
                  normalized[0]*normalized[2], normalized[1]*normalized[2], normalized[2]*normalized[2]);
  mat3 ab = mat3(0, normalized[2], normalized[1]*-1,
                 normalized[2]*-1, 0, normalized[0],
                 normalized[1], normalized[0]*-1, 0);
  ret = glm::cos(radians) * identity + (1 - glm::cos(radians)) * aat + glm::sin(radians) * ab;
  // You will change this return call
  return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  mat3 rotationMat = rotate(degrees, up);
	//normalize eye and up after rotating
	float distance = (sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
	eye = normalize(rotationMat * eye) * distance;
	up = normalize(rotationMat * up);
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  mat3 rotationMat = rotate(degrees, cross(eye,up));
	//normalize eye and up after rotating
	float distance = (sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
	eye = normalize(rotationMat * eye) * distance;
	up = normalize(rotationMat * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // create the world coordinate frame
  vec3 a = eye - center;
  vec3 w = normalize(a);
  vec3 u = normalize(cross(up, w));
  vec3 v = cross(w, u);
  // create the rotation matrix
  mat4 rotation = mat4(u[0],v[0],w[0],0,u[1],v[1],w[1],0,u[2],v[2],w[2],0,0,0,0,1);
  // create the translation matrix
  mat4 translation = mat4(1,0,0,0,0,1,0,0,0,0,1,0,eye[0]*-1,eye[1]*-1,eye[2]*-1,1);
  // return rotation * translation
  ret = rotation * translation;
  return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  float theta = fovy * (pi/180) / 2;
  float d = 1/glm::tan(theta);
  ret = mat4(d/aspect,0,0,0,
        0,d,0,0,
        0,0,(1)*(zFar+zNear)/(zNear-zFar),-1,
        0,0,(2)*zFar*zNear/(zNear-zFar),0);
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  ret = mat4(sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1);
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  ret = mat4(1,0,0,0,0,1,0,0,0,0,1,0,tx,ty,tz,1);
  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
