#pragma once
#pragma once
#ifndef DEF_RIGIDBODYFORCEREGISTRY
#define DEF_RIGIDBODYFORCEREGISTRY
#include "../../RigidBody.h"
#include "RigidBodyForceGenerator.h"

class RigidBodyForceRegistry
{
private:

	struct RigidBodyForceEntry
	{
		RigidBody* rigidbody;
		RigidBodyForceGenerator* forceGenerator;
	};

	using Registry = std::vector<RigidBodyForceEntry>;
	Registry registry;

public:
	//Registry accessors
	RigidBodyForceRegistry();
	void clear();
	void add(RigidBody* particule, RigidBodyForceGenerator* rigidbodyFg);
	void remove(RigidBody* particule, RigidBodyForceGenerator* rigidbodyFg);
	void UpdateForce(double duration);
};

#endif