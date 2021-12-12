#include "PossibleCollision.h"

PossibleCollision::PossibleCollision(Primitive* primitive1, Primitive* primitive2){
	primitives.first = primitive1;
	primitives.second = primitive2;
}

CollisionData PossibleCollision::narrowPhaseCollisions(){
	CollisionData data = CollisionData();
	if(primitives.first->getType() == "Plane" && primitives.second->getType() == "Sphere"){
		
        Plane& plane = dynamic_cast<Plane&>(*primitives.second);
        Sphere& sphere = dynamic_cast<Sphere&>(*primitives.first);
		Vecteur3D posSphere = primitives.second->body->getPosition();
		Vecteur3D normal = plane.getNormal();
		double d = plane.getOffset();

		double distance = normal.getX()*posSphere.getX()+normal.getY()*posSphere.getY()+normal.getZ()*posSphere.getZ();
		if(distance <= d){
			data.setPenetration(d-distance);
			data.setContactNormal(normal);
			data.setContactPoint(Vecteur3D(posSphere.getX(),posSphere.getY(),posSphere.getZ()));
		}

	}
	
	else if(primitives.first->getType() == "Sphere" && primitives.second->getType() == "Plane"){
        Plane& plane = dynamic_cast<Plane&>(*primitives.second);
        Sphere& sphere = dynamic_cast<Sphere&>(*primitives.first);
		Vecteur3D posSphere = primitives.first->body->getPosition();
		Vecteur3D normal = plane.getNormal();
		double d = plane.getOffset();
		double equation_plan = normal.getX()*posSphere.getX()+normal.getY()*posSphere.getY()+normal.getZ()*posSphere.getZ() + d;
		if(equation_plan <= 0){
			//revoir la pénétration itou
			data.setPenetration(plane.getCentre() - posSphere);
			data.setContactNormal(normal);
			data.setContactPoint(Vecteur3D(posSphere.getX(),posSphere.getY(),posSphere.getZ()));
		}
	} 
	
	else if(primitives.first->getType()== "Sphere" && primitives.second->getType()== "Sphere"){
		Vecteur3D posSphere1 = primitives.first->body->getPosition();
		Vecteur3D posSphere2 = primitives.second->body->getPosition();
		double distance = sqrt((posSphere1.getX() * posSphere2.getX() + posSphere1.getY() * posSphere2.getY() + posSphere1.getZ() * posSphere2.getZ()));
		if (distance <= primitives.first->getDimension()[0]+ primitives.second->getDimension()[0]) {
			data.setPenetration(abs(primitives.first->getDimension()[0] + primitives.second->getDimension()[0] - distance));
			data.setContactNormal((posSphere1-posSphere2).normalization());
			//voir si on le si on fait ou pas
			data.setContactPoint(Vecteur3D(aled));
		}
	}
    return data;
}
