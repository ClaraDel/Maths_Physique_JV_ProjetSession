#ifndef DEF_PARTICULE
#define DEF_PARTICULE

#pragma once

class Particule
{
    private :
    double masse;
    double inverseMasse; 

    public:
    Particule(double m);
	Particule operator*(float value) const;
	void operator*=(float value);
    double GetInverseMasse(); //voir quel type mettre

	
};

// accesseurs pour l’attribut InverseMasse.
double Particule::GetInverseMasse(){
	return inverseMasse;
}

#endif