#include "OcTree.h"

using namespace std;

void OcTree::Build(vector<Primitive> primitivesToAdd) {
	double middle = m_regionSize/2;
	Box region = Box(m_regionSize, m_regionSize, m_regionSize, Vecteur3D(0,50,0));
	root = new Node(0, m_maxPrimitive, m_maxLevel, region) ;
	root->AddPrimitive(primitivesToAdd);
}

vector<PossibleCollision> OcTree::getPossibleCollision(){
	vector<PossibleCollision> result;
	if(root != nullptr){
		root->browse(result);
	}
	return result;
}

void Node::AddPrimitive(std::vector<Primitive> primitives){
	for (int i = 0; i < primitives.size(); i++) {
		if(primitives[i].insideRegion(m_region)){
			m_primitives.push_back(primitives[i]);
		}
	}
	if(m_primitives.size() > m_maxPrimitive && m_level < m_maxLevel){
		subdivise();
	}
}

int Node::GetChildIndex(const Vecteur3D &centreRb){
	int index;
	if(centreRb.getX() > m_region.m_position.getX() ) index +=1 ;
	if(centreRb.getY() > m_region.m_position.getY() ) index +=2 ;
	if(centreRb.getZ() > m_region.m_position.getZ() ) index +=4 ;
	return index ;
}

void Node::browse(vector<PossibleCollision>& possibleCollision){
	if(isLeaf()){
		if(m_primitives.size()>1){
			for(int i= 0,i<m_primitives.size(), i++){
				for(int j=i+1,j<m_primitives.size(),j++){
					possibleCollision.push_back(m_primitives[i],m_primitives[j]);
				}
			}
			
		}
		return;
	}
	for(int i=0;i <m_children.size();i++){
		m_children[i]->browse(possibleCollision);
	}
}

void Node::subdivise(){	
	for (int i=0; i<8; i++){
		Vecteur3D boxPosition = Vecteur3D();
		if(i < 4) {
			boxPosition.setZ(m_region.getPosition().getZ() - m_region.m_depth/4.0);
		} else {
			boxPosition.setZ(m_region.getPosition().getZ() + m_region.m_depth/4.0);
		}
		if(i<2 || i == 4 || i == 5){
			boxPosition.setY(m_region.getPosition().getY() - m_region.m_height/4.0);
		} else {
			boxPosition.setY(m_region.getPosition().getY() + m_region.m_height/4.0);
		}
		if(i % 2 == 0){
			boxPosition.setX(m_region.getPosition().getX() - m_region.m_width/4.0);
		} else {
			boxPosition.setX(m_region.getPosition().getX() + m_region.m_width/4.0);
		}
		Box region = Box(m_region.getHeight() / 2.0, m_region.getWidth() / 2.0, m_region.getDepth() / 2.0, boxPosition);
		Node* node = new Node(m_level+1,  region);
		node->AddPrimitive(m_primitives);
		m_children.push_back(node);
	}
}

bool Node::isLeaf() {
	return (m_children.size() == 0);
}

void OcTree::Clear() {
	delete root ;
}
OcTree::~OcTree() {
	Clear();
}

Node::~Node(){
	for(int i =0;i<m_children.size();i++){
		if (m_children[i] != nullptr) delete m_children[i];
	}
	m_children.clear();
}