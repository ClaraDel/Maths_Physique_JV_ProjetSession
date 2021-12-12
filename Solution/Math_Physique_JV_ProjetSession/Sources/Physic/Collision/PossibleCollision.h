#pragma once


#include "../Objects/Primitive.h"
#include "CollisionData.h"
#include "../Objects/Plane.h"
#include "../Objects/Sphere.h"

#ifndef DEF_POSSIBLECOLLISION
#define DEF_POSSIBLECOLLISIONs
class PossibleCollision {
    private :
        std::pair<Primitive,Primitive> primitives;

    public :
        PossibleCollision(Primitive primitive1, Primitive primitive2){
            primitives.first = primitive1;
            primitives.second = primitive2;
     
       }
        PossibleCollision() {
            primitives.first = Primitive();
            primitives.second = Primitive();
        }


        CollisionData narrowPhaseCollisions();


};

#endif
#pragma once