#pragma once
#ifndef DEF_BOX
#define DEF_BOX

class Box  {
public:
	double m_height ;
	double m_width ;
	double m_depth ;
	Vecteur3D m_position ;

	Box(double height, double width, double depth, Vecteur3D position){
		m_height = height ;
		m_width = width ;
		m_depth = depth ;
		m_position = position;
	}
	
	
	Vecteur3D getPosition(){
		return m_position;
	}

	double getHeight() {
		return m_height;
	}

	double getWidth() {
		return m_width;
	}

	double getDepth() {
		return m_depth;
	}
	

	
};
#endif
#pragma once
