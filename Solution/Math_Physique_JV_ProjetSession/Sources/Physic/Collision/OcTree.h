#pragma once
#include "../Objects/RigidBody.h"
#include "../../Math/Vecteur3D.h"
#include "../Objects/Box.h"
#include "../Objects/Primitive.h"

class Node {
	private :
		Box m_region;
		std::vector<Primitive> m_primitives;
		std::vector<Node*> m_children;
		int m_level; //profondeur du noeuds		
		int m_maxPrimitive;	
		int m_maxLevel;
		
	public :
		Node(int level, int maxPrimitive, int maxLevel, Box region){
			m_level = level;
			m_region = region;
			m_maxPrimitive = maxPrimitive;
			m_maxLevel = maxLevel;
		};

		Node(int level, Box region){
			m_level = level;
			m_region = region;
			m_maxPrimitive =2;
			m_maxLevel = 6;
		};

		Vecteur3D getPosition();
		int GetChildIndex(const Vecteur3D& centreRb);
		void subdivise(); //subdivise the node in subregions
		bool isLeaf(); //return true if the node has no child
		void AddPrimitive(std::vector<Primitive> primitives);
		void browse(std::vector<PossibleCollision>& possibleCollision);
};

class OcTree {
	private:
		Node* root;
		double m_regionSize;
		std::vector<Primitive> m_primitivesToAdd;

	public:
		void Build();
		std::vector<PossibleCollision> getPossibleCollision();
		OcTree(int maxLevel, double regionSize, int maxPrimitive ){
			m_maxLevel = maxLevel ;
			regionSize = m_regionSize ;
			m_maxPrimitive = maxPrimitive ;
		};
		void Clear();
};