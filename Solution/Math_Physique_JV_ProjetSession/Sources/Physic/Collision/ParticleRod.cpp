#include "ParticleRod.h"

unsigned ParticleRod::addContact(ParticleContact* contact) 
{
    double currentLenght = ParticleLink::currentLenght();

    if (currentLenght == lenght) {
        return 0;

    }
    else {
        float penetration;
        //calculate the normal between these two particle
        Vecteur3D normal = particule[1]->getPosition() - particule[0]->getPosition();
        normal.normalization();

        if (currentLenght > lenght) {
            penetration = currentLenght - lenght;
        }
        else {
            normal = -1 * normal;
            penetration = lenght - currentLenght;
        }

        //we don't want boudiness
        *contact = ParticleContact(particule[0], particule[1], 0, penetration, normal);

        return 1;
    }
}