#include"ParticleContactResolver.h"
#include<vector>
using namespace std;

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*> particuleContactList) {

    int nbContactResolved = 0;
    while (nbContactResolved < particuleContactList.size()) {
        double minSepVel = 0;
        int minIndex = 0;
        for (int i = 0; i < particuleContactList.size(); i++) {
            //particuleContactList is the list of all contacts we want to resolve
            double separatingVelocity = particuleContactList[i]->calculateSeperatingVelocity();

            if (separatingVelocity >= 0) {
                nbContactResolved++;
                //exit the algotithm
                break;
            }
            else {
                if (separatingVelocity < minSepVel) {
                    //we keep track of the lowest value
                    minSepVel = separatingVelocity;
                    minIndex = i;
                }
            }
        }

        //resolve the contact with the lowest separatingVelocity 
        particuleContactList[minIndex]->resolve();

        nbContactResolved++;
    }
}