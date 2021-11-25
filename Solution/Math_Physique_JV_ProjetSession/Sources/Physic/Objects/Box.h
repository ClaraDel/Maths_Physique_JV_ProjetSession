#pragma once
#ifndef DEF_BOX
#define DEF_BOX
#include "Primitive.h"

class Box : public Primitive {
public:
	double m_height ;
	double m_width ;
	double m_depth ;
	//Vecteur3D halfSize;

	Primitive(double height, double width, double depth){
		m_height = height ;
		m_width = width ;
		m_depth = depth ;
	}
};
#endif
#pragma once
