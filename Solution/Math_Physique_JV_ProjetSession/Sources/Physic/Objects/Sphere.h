#pragma once
#ifndef DEF_SPHERE
#define DEF_SPHERE
#include "Primitive.h"
#include "Box.h"

class Sphere : public Primitive {
public:
	double m_radius;

	Sphere(RigidBody* rigid, double radius) {
		body = rigid;
		m_radius = radius;
	}

	std::string getType() {
		return "Sphere";
	}

	double getRadius() {
		return m_radius;
	}


	bool insideRegionStrict(Box& region) {
		bool inside = true;
		Vecteur3D sphereCenter = body->getPosition();
		Vecteur3D regionCenter = region.getPosition();
		if (sphereCenter.getX() + m_radius > regionCenter.getX() + region.m_width / 2 || sphereCenter.getX() - m_radius > regionCenter.getX() - region.m_width / 2) {
			inside = false;
		}
		if (sphereCenter.getY() + m_radius > regionCenter.getY() + (region.m_height * 0.5) ||
			sphereCenter.getY() - m_radius > regionCenter.getY() - (region.m_height * 0.5)) {
			inside = false;
		}
		if (sphereCenter.getZ() + m_radius < regionCenter.getZ() + (region.m_depth * 0.5) ||
			sphereCenter.getZ() - m_radius > regionCenter.getZ() - (region.m_depth * 0.5)) {
			inside = false;
		}
		return inside;
	}

	bool insideRegion(Box& region) {
		bool inside = true;
		Vecteur3D sphereCenter = body->getPosition();
		Vecteur3D regionCenter = region.getPosition();
		if (sphereCenter.getX() - m_radius > regionCenter.getX() + region.m_width / 2 || sphereCenter.getX() + m_radius > regionCenter.getX() - region.m_width / 2) {
			inside = false;
		}
		if (sphereCenter.getY() - m_radius > regionCenter.getY() + (region.m_height * 0.5) ||
			sphereCenter.getY() + m_radius > regionCenter.getY() - (region.m_height * 0.5)) {
			inside = false;
		}
		if (sphereCenter.getZ() - m_radius < regionCenter.getZ() + (region.m_depth * 0.5) ||
			sphereCenter.getZ() + m_radius > regionCenter.getZ() - (region.m_depth * 0.5)) {
			inside = false;
		}
		return inside;
	}
};
#endif