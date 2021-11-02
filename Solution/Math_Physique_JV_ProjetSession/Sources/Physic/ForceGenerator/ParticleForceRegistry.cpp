#include "ParticleForceRegistry.h"

using namespace std;

ParticleForceRegistry::ParticleForceRegistry() {
	clear();
}

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

void ParticleForceRegistry::cleanInput() { //ne fonctionne pas
	Registry::iterator i = registry.end();
	cout << "test 1" << endl;
	for (; i != registry.end(); i++)
	{
		if (dynamic_cast<ConstantForce*>(i->forceGenerator)) {
			cout << "test 2" << endl;
			i = registry.erase(i);
		}
	}
}

void ParticleForceRegistry::clear()
{
	registry.clear();
}

void ParticleForceRegistry::UpdateForce(double duration)
{
	Registry::iterator i = registry.begin();
	for(; i!= registry.end(); i++)
	{
		i->forceGenerator->UpdateForce(i->particule, duration);
	}
}


