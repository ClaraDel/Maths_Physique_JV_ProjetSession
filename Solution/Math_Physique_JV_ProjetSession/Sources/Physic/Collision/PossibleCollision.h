#pragma once
#ifndef DEF_POSSIBLECOLLISION
#define DEF_POSSIBLECOLLISION

#include "../Objects/Primitive.h"
#include "CollisionData.h"
#include "../Objects/Plane.h"
#include "../Objects/Sphere.h"

class PossibleCollision {
    private :
        std::pair<Primitive,Primitive> primitives;

    public :
        PossibleCollision(Primitive primitive1, Primitive primitive2){
            primitives.first = primitive1;
            primitives.second = primitive2;
     
       }


        CollisionData narrowPhaseCollisions();


};

#endif
#pragma once