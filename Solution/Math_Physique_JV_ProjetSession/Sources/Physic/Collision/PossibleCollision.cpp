#include "PossibleCollision.h"

CollisionData PossibleCollision::narrowPhaseCollisions(){
	CollisionData data = CollisionData();
	if(primitives.first.getType() == "Plane" && primitives.second.getType() == "Sphere"){
		
        Plane& plane = dynamic_cast<Plane&>(primitives.second);
        Sphere& sphere = dynamic_cast<Sphere&>(primitives.first);
		Vecteur3D posSphere = primitives.second.body->getPosition();

		if(primitives.first.)
	}
	
	else if(primitives.first.getType() == "Sphere" && primitives.second.getType() == "Plane"){
        Plane& plane = dynamic_cast<Plane&>(primitives.second);
        Sphere& sphere = dynamic_cast<Sphere&>(primitives.first);
		Vecteur3D posSphere = primitives.first.body->getPosition();
	} 
	
	else if(primitives.first.getType() == "Sphere" && primitives.second.getType() == "Sphere"){
		Vecteur3D posSphere1 = primitives.first.body->getPosition();
		Vecteur3D posSphere2 = primitives.second.body->getPosition();
		double distance = sqrt((posSphere1.getX() * posSphere2.getX() + posSphere1.getY() * posSphere2.getY() + posSphere1.getZ() * posSphere2.getZ()));
		if (distance <= primitives.first.getRadius()+ primitives.second.getRadius()) {
			data.setPenetration(0);
			data.setContactNormal(Vecteur3D());
			data.setContactPoint(Vecteur3D());
		}
	}



    return data;
}
