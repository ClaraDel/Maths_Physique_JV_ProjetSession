#include "Particule.h"
#include <iostream>
#include <string>
#include "Vecteur3D.cpp"

using namespace std;

Particule::Particule(double m){
	masse = m;
	if(m!=0){
		inverseMasse = 1/m;
	} else {
		inverseMasse = 0;
	}
}


Particule Particule::operator*(float value) const
{
	//

	return Particule();
}