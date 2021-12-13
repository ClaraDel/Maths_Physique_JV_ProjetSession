#include "CollisionData.h"


CollisionData::CollisionData() {
	m_penetration = 0;
	m_contactNormal = Vecteur3D();
	m_contactPoint = Vecteur3D();
}

Vecteur3D CollisionData::getContactPoint(){
	return m_contactPoint;
}

void CollisionData::setContactPoint(Vecteur3D contactPoint){
	m_contactPoint = contactPoint;
}

Vecteur3D CollisionData::getContactNormal(){
	return m_contactNormal;
}

void CollisionData::setContactNormal(Vecteur3D contactNormal){
	m_contactNormal = contactNormal;
}

double CollisionData::getPenetration(){
	return m_penetration;
}

void CollisionData::setPenetration(double penetration){
	m_penetration = penetration;
}


//we print each element of the vector like this (x, y, z)
void CollisionData::print(std::ostream& flux) const
{
	flux << "Point de contact = " << m_contactPoint << ", normale = " << m_contactNormal << ", interpenetration = " << m_penetration ;
}


//print a message
std::ostream& operator<< (std::ostream& flux, CollisionData const& data)
{
	data.print(flux);
	return flux;
}

bool CollisionData::isEqual(CollisionData const& data) const
{ 
	if ( m_penetration == data.m_penetration  && m_contactNormal == data.m_contactNormal && m_contactPoint == data.m_contactPoint) {
		return true;
	} else {
		return false;
	}
}

bool operator==(CollisionData const& a,CollisionData const& b)
{
	return a.isEqual(b);
}

bool operator!=(CollisionData const& a,CollisionData const& b)
{
	if (a == b) 
		return false;
	else
		return true;
}