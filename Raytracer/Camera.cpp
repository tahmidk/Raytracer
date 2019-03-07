#include "pch.h"
#include "Camera.h"
#include <math.h>

Camera::Camera()
{
	up = glm::normalize(scn->getCamPos() - scn->getLookAt());
	w = glm::normalize(glm::cross(w, scn->getUpVector()));
	v = glm::cross(w, up);
	fovy = scn->getFovy() * PI  / 180.0;
	double z = tan(fovy / 2);

	z = (1 / z) * scn->getHeight() / 2;
	fovx = 2 * atan((scn->getWidth() / 2) / z);
}


Camera::~Camera()
{
}

Ray Camera::generateRay(Sampler sample)
{
	vec3 camPos = scn->getCamPos();
	int h = scn->getHeight();
	int w = scn->getWidth();

	float alpha = (-2) * tan(fovx / 2) * (sample.getX() - w / 2) / w;
	float beta = 2 * tan(fovy / 2) * (h / 2 - sample.getY()) / h;

	vec3 dirn = glm::normalize(alpha * this->up + beta * this->v - this->w);
	return Ray(camPos, dirn);
}
