#include "OcTree.h"

using namespace std;

//create the first node and add all objects in the Octree
void OcTree::Build(vector<Primitive*> primitivesToAdd) {
	Box region = Box(m_regionSize, m_regionSize, m_regionSize, Vecteur3D(5,5,0));
	root = new Node(0, m_maxPrimitive, m_maxLevel, region) ;
	root->AddPrimitive(primitivesToAdd);
}

//return a vector of all objects which may potentially collide
vector<PossibleCollision> OcTree::getPossibleCollision(){
	vector<PossibleCollision> result;
	if(root != nullptr){
		root->browse(result);
	}
	return result;
}

//If an object (primitive) is totally or partially included in a region, add that object to the region
void Node::AddPrimitive(std::vector<Primitive*> primitives){
	for (int i = 0; i < primitives.size(); i++) {
		if(primitives[i]->insideRegion(m_region)){
			m_primitives.push_back(primitives[i]);
			//cout << "m_primitives n." << primitives[i] << " added in level " << m_level << ", regionWidth " << m_region.getWidth() << " conter " << m_region.getPosition() << endl ;
		}
	}
	//if the number of primitive inside a region exceed the max number, subdivise the region
	if(m_primitives.size() > m_maxPrimitive && m_level < m_maxLevel){
		//cout << "call subdivise from AddPrimitive with level = " << m_level << " and m_primitives.size() = " << m_primitives.size() << endl;
		subdivise();
	}
}

//return the id of a child node according to his position
int Node::GetChildIndex(const Vecteur3D &centreRb){
	int index = 0;
	if(centreRb.getX() > m_region.m_position.getX() ) index +=1 ;
	if(centreRb.getY() > m_region.m_position.getY() ) index +=2 ;
	if(centreRb.getZ() > m_region.m_position.getZ() ) index +=4 ;
	return index ;
}

//build the vector of possible collisions on the leaf of the tree
void Node::browse(vector<PossibleCollision>& possibleCollision){
	if(isLeaf()){
		if(m_primitives.size()>1){
			for (int i = 0; i < m_primitives.size(); i++) {
				for (int j = i + 1; j < m_primitives.size(); j++) {
					possibleCollision.push_back(PossibleCollision(m_primitives[i], m_primitives[j]));
				}
			}
		}
		return;
	}
	for(int i=0;i <m_children.size();i++){
		m_children[i]->browse(possibleCollision);
	}
}

//subdivise the octree in 4 regions 
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
	//cout << "level " << m_level << " subdivised" ;
}

//return true if the node is a leaf
bool Node::isLeaf() {
	return (m_children.size() == 0);
}

//delete the root node of the octree
void OcTree::Clear() {
	if (root != nullptr) {
		delete root;
		root = nullptr;
	}
}

//destructor of the Octree
OcTree::~OcTree() {
	Clear();
}

//delete all the children nodes
Node::~Node(){

	if (!m_children.empty()) {
		for (Node* node : m_children) {
			if (node != nullptr) delete node;
		}
	}
	
	m_children.clear();
}