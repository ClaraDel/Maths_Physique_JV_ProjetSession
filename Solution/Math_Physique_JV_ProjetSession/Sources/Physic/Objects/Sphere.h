#pragma once
#ifndef DEF_SPHERE
#define DEF_SPHERE
#include "Primitive.h"

class Sphere : public Primitive {
public:
	double radius;
	bool Sphere::insideRegion(const Box& region){
		bool inside = true ;
		Vecteur3D sphereCenter = this.body.getPosition();
		Vecteur3D regionCenter = region.getPosition();
		if(sphereCenter.getX() + radius > regionCenter.getX() + region.m_width/2 || sphereCenter.getX() - radius > regionCenter.getX() - region.m_width/2 ){
			inside = false ;
		}
		if(sphereCenter.getY()+radius > regionCenter.getY()+(region.m_height*0.5) ||
		 sphereCenter.getY()-radius  >regionCenter.getY()-(region.m_height*0.5)){
			inside = false ;
		}
		if(sphereCenter.getZ()+radius < regionCenter.getZ() +(region.m_depth*0.5) ||
		sphereCenter.getZ()-radius > regionCenter.getZ() -(region.m_depth*0.5)){
			inside = false ;
		}
		return inside;
	}
};
#endif