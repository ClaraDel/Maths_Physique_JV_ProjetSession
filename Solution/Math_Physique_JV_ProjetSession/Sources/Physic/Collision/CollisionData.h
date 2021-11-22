#pragma once

#include"../Particule.h"
class CollisionData {
	private:
		// penetration of the contact
		double m_penetration;
		//normal of the contact
		Vecteur3D m_contactNormal;
		//position of the contact
		Vecteur3D m_contactPoint;

	public:
		Vecteur3D getContactPoint();
		Vecteur3D getContactNormal();
		double getPenetration();

		void setContactPoint(Vecteur3D contactPoint);
		void setContactPoint(Vecteur3D contactNormal);
		void setPenetration(double penetration);
};
