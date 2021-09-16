#ifndef DEF_VECTEUR
#define DEF_VECTEUR

class Vecteur3D {

public:

	Vecteur3D operator*(float value) const;
	void operator*=(float value);

private:
	float x, y, z;

};

#endif