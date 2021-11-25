#ifndef DEF_PRIMITIVE
#define DEF_PRIMITIVE
#include"RigidBody.h"
#include"../../Math/Matrix34.h"

class Primitive {
public:
	RigidBody* body;
	Matrix34 offset;
	virtual bool insideRegion(const Box& region) = 0;
};
#endif