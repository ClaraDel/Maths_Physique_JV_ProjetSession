#pragma once

#include "Primitive.h"
#include "Box.h"
#include "../../Math/Vecteur3D.h"
#include <iostream>

#ifndef DEF_PLANE
#define DEF_PLANE
class Plane : public Primitive {
private:
	Vecteur3D m_center;
	Vecteur3D m_normal;
	double m_offset ;

public:

	std::string getType() {
		return "Plane";
	}

	Vecteur3D getNormal() const {
		return m_normal;
	}

	Vecteur3D getCenter() const {
		return m_center;
	}

	double getOffset() const{
		return m_offset;
	}

	bool insideRegion(Box& region) {
		bool inside1 = false;
		bool inside2 = false;
		bool inside3 = false;
		Vecteur3D regionCenter = region.getPosition();
		Vecteur3D normal = getNormal();
		Vecteur3D center = getCenter();
		
		if ((normal.getX() != 0 && std::abs(regionCenter.getX() - center.getX()) <= region.m_width * 0.5) || normal.getX() == 0){
			inside1 = true;
		}
		if ((normal.getY() != 0 && std::abs(regionCenter.getY() - center.getY()) <= region.m_height * 0.5) || normal.getY() == 0){
			inside2 = true;
		}
		if ((normal.getZ() != 0 && std::abs(regionCenter.getZ() - center.getZ()) <= region.m_depth * 0.5 )|| normal.getZ() == 0){
			inside3 = true ;
		}
		return inside1*inside2*inside3 ;
	}

	Plane(Vecteur3D center, Vecteur3D normal) {
			m_center = center;
			m_normal = normal;
			m_offset = -(m_normal.getX() * m_center.getX() + m_normal.getY() * m_center.getY() + m_normal.getZ() * m_center.getZ());
	}

	Vecteur3D getCentre() {
		return m_center;
	}
};
#endif