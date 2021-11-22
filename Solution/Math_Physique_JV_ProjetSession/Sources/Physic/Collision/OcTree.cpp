#include "OcTree.h"


OcTree::Node* OcTree::Build(Vecteur3D position, int stopDeth) {
	if (stopDeth < 0) return NULL;
	else {
		Node* node = new Node;
		node->position = position;
		

	}

int OcTree::GetChildIndex(const Vecteur3D &centreRb){
	int index;
	if(centreRb.x > position.x ) index +=1 ;
	if(centreRb.y > position.y ) index +=2 ;
	if(centreRb.z > position.z ) index +=4 ;
	return index ;
}
}