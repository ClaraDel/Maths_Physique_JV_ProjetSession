#ifndef DEF_PARTICULE
#define DEF_PARTICULE

#pragma once

class Particule
{
    public:
    
	Particule operator*(float value) const;
	void operator*=(float value);
	
};

#endif