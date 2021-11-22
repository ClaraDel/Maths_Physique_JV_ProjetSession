#pragma once
#include "../RigidBody.h"
class OcTree {

	struct Node {
		Vecteur3D position;
		Node* child[8];
		
	};

	public:
		int getChildren(const Vecteur3D& objectCentre);
		Node* Build(Vecteur3D position, int stopDeth);

};