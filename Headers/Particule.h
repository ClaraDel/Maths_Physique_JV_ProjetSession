#ifndef DEF_PARTICULE
#define DEF_PARTICULE

#pragma once

class Particule
{
    private :
    int InverseMasse; // voir quel type mettre

    public:

	Particule operator*(float value) const;
	void operator*=(float value);
    int GetInverseMasse(); //voir quel type mettre

	
};

// accesseurs pour l’attribut InverseMasse.
int Particule::GetInverseMasse(){
	return InverseMasse;

}

#endif