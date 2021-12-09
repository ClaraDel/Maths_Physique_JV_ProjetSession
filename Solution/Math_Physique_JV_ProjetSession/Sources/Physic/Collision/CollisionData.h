#pragma once

#include"../Objects/Particule.h"
#include "../../Math/Vecteur3D.h"
#include<iostream>;

class CollisionData {
	private:
		// penetration of the contact
		double m_penetration;
		//normal of the contact
		Vecteur3D m_contactNormal;
		//position of the contact
		Vecteur3D m_contactPoint;

	public:
		CollisionData();
		Vecteur3D getContactPoint();
		Vecteur3D getContactNormal();
		double getPenetration();

		void setContactPoint(Vecteur3D contactPoint);
		void setContactNormal(Vecteur3D contactNormal);
		void setPenetration(double penetration);

		void print(std::ostream& flux) const;
};

std::ostream& operator<< (std::ostream& flux, CollisionData const& data);
