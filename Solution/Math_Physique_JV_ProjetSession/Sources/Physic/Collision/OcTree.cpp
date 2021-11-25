#include "OcTree.h"


void OcTree::Build(Vecteur3D position, int stopDeth) {
	Box region = Box::Primitive(m_regionSize,m_regionSize,m_regionSize);
	root = new Node(0, m_stopDeth,m_maxChild,region);
	
		

	}

int Node::GetChildIndex(const Vecteur3D &centreRb){
	int index;
	if(centreRb.getX() > m_boxPosition.getX() ) index +=1 ;
	if(centreRb.getZ() > m_boxPosition.getZ() ) index +=4 ;
	return index ;
}


Vecteur3D Node::getPosition(){
	return m_boxPosition;
}