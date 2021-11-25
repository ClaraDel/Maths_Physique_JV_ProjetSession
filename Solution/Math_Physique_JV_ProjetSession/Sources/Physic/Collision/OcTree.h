#pragma once
#include "../Objects/RigidBody.h"
#include "../../Math/Vecteur3D.h"
#include "../Objects/Box.h"

class Node {
	private :
		Box m_region;
		std::vector<Node*> m_children;
		int m_level; //profondeur du noeuds
		int m_maxLevel;
		int m_maxChildren;
		Vecteur3D m_boxPosition ;
			
		
	public :
		Node(int level,int maxLevel,int maxChild,Box region);
		Vecteur3D getPosition();
		int GetChildIndex(const Vecteur3D& centreRb);
		void subdivise(); //subdivise the node in subregions
		bool isLeaf(); //return true if the node has no child
};

class OcTree {
	private:
		Node* root;
		int m_stopDeth;
		int m_maxChildren;
		double m_regionSize;
		std::vector<Primitive> m_primitives;

	public:
		void Build();
		OcTree(int stopDeth,int maxChild,double regionSize,vector<Primitive> primitives);
		void Clear();
};