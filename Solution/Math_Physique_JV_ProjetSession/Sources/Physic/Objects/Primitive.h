#include"RigidBody.h"
#include"../../Math/Matrix34.h"
#include "Box.h"


class Primitive {
	public:
		RigidBody* body;
		Matrix34 offset;
		std::vector<double> m_dimensionAttribute;
		virtual bool insideRegion(Box& region) = 0;
		virtual std::string getType() = 0;

		std::vector<double> getDimension(){
			return m_dimensionAttribute;
		}
};
