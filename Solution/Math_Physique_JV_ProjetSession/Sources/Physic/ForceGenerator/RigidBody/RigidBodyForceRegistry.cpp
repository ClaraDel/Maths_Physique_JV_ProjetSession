using namespace std;
#include "RigidBodyForceRegistry.h"

RigidBodyForceRegistry::RigidBodyForceRegistry() {
	clear();
}

void RigidBodyForceRegistry::add(RigidBody* rigidbody, RigidBodyForceGenerator* rigidbodyFg)
{
	RigidBodyForceEntry rbfe{ rigidbody , rigidbodyFg };
	registry.push_back(rbfe);
}

void RigidBodyForceRegistry::remove(RigidBody* rigidbody, RigidBodyForceGenerator* rigidbodyFg) {
	//parcourir le registre trouver le bon struct et l'enlever '
	Registry::iterator i = registry.begin();
	for (; i != registry.end(); i++)
	{
		if(i->forceGenerator == rigidbodyFg && i->rigidbody == rigidbody){
			registry.erase(i);
		}
	}
}

void RigidBodyForceRegistry::clear()
{
	registry.clear();
}

void RigidBodyForceRegistry::UpdateForce(double duration)
{
	Registry::iterator i = registry.begin();
	for(; i!= registry.end(); i++)
	{
		i->forceGenerator->UpdateForce(i->rigidbody, duration);
	}
}


