#pragma once
#ifndef DEF_PLANE
#define DEF_PLANE
#include "Primitive.h"

class Plane : public Primitive {
private:
	Vecteur3D center;
	Vecteur3D normal;
	double offset;
public:
	bool Plane::insideRegion(const Box& region){
		
	}
};
#endif
