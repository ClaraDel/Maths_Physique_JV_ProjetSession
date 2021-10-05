#include "ParticleForceRegistry.h"

using namespace std;


void ParticleForceRegistry::add(Particule* particule, ParticleForceGenerator* particuleFg)
{
	ParticleForceEntry pfe{ particule , particuleFg };
	registry.push_back(pfe);
}

void ParticleForceRegistry::remove(Particule* particule, ParticleForceGenerator* particuleFg) {
	//parcourir le registre trouver le bon struct et l'enlever '
	Registry::iterator i = registry.begin();
	for (; i != registry.end(); i++)
	{
		if(i->forceGenerator == particuleFg && i->particule == particule){
			registry.erase(i);
		}
	}

}

void ParticleForceRegistry::UpdateForce(double duration)
{
	Registry::iterator i = registry.begin();
	for(; i!= registry.end(); i++)
	{
		i->forceGenerator->UpdateForce(i->particule, duration);
	}
}


