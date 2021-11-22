#pragma once
#ifndef DEF_PLANE
#define DEF_PLANE
#include "Primitive.h"

class Plane : public Primitive {
public:
	Vecteur3D normal;
	double offset;
};
#endif
