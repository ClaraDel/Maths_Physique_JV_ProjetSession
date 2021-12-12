#pragma once


#include "../Objects/Primitive.h"
#include "CollisionData.h"
#include "../Objects/Plane.h"
#include "../Objects/Sphere.h"

#ifndef DEF_POSSIBLECOLLISION
#define DEF_POSSIBLECOLLISIONs
class PossibleCollision {
    private :
        std::pair<Primitive*,Primitive*> primitives;

    public :
        PossibleCollision(Primitive* primitive1, Primitive* primitive2);


        CollisionData narrowPhaseCollisions();


};

#endif
#pragma once