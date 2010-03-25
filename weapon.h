#ifndef _WEAPON_H_
#define _WEAPON_H_


//typedef unsigned char WEAPON_TYPE;
enum WEAPON_TYPE
{
 WEAPON_NONE = 0,
 WEAPON_MACHINE_GUN,
 WEAPON_MISSILE,
 WEAPON_COUNT
};



class WEAPON
{
public:
 WEAPON();

 void set(WEAPON_TYPE newtype);

protected:
 WEAPON_TYPE type;
};


#endif
