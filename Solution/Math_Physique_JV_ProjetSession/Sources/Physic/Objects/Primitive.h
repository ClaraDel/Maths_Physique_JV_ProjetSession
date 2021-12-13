#pragma once
#ifndef DEF_PRIMITIVE
#define DEF_PRIMITIVE

#include"RigidBody.h"
#include"../../Math/Matrix34.h"
#include "Box.h"


class Primitive {
	public:
		RigidBody* body;
		Matrix34 offset;
		virtual bool insideRegion(Box& region) = 0;
		virtual std::string getType() = 0;

};

#endif

