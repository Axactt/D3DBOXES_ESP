#pragma once
#include<windows.h>
#define STR_MERGE_IMPL(a,b) a##b
#define STR_MERGE(a,b) STR_MERGE_IMPL(a,b)
#define MAKE_PAD(size) STR_MERGE(_pad,__counter__)[size]
#define DEFINE_MEMBER_N(type,name,offset)  struct{unsigned char MAKE_PAD(offset);type name;}

struct Vec2
{
	float x {};
	float y {};
};
struct Vec3
{
	float x {};
	float y {};
	float z {};
 };
struct Vec4
{
	float x {};
	float y {};
	float z {};
	float w {};
};

struct Matrix34
{
	float m_matrix[3][4] {}; // sIZE OF MATRIX IS EQUIVALENT TO 3(ROWS) X 4(COULMNS)=12 X 4(float byte)= 48 bytes;
};

class LocalEntity
{

// This is entity object class which represents local entity (player entity) structure
//In game memory. the padding is being done to represent actual localplayer object
//The required padding is to reach the class object structure members at various offsets
// various important structure members chosen with their offsets
// so these can be directly accessed by using as "class Ent" members
//As class Ent will be assigned actual running in-game address
	//These members when accessed at defined original padding(offset) 
// can be made to read and access the real-time values of game in runtime
public:
	
		// isDormant;
		char pad1[0xED];
		bool isDormant; // 0xED(0x01) ;
		
		//iTeamNum
		char pad2[0x6];
		int iTeamNum; //{ 0xF4 };(0x04)
		
		//iHealth
		char pad3[0x8];
		int iHealth;// { 0x100 };(0x04)

		//char padz[0x04];
		//Vec3 m_vecViewOffset;// {0x108}; (0x12)
		
		//vecorigin
		char pad4[0x34];
		Vec3  vecOrigin; //{ 0x138 };(0x12)
		
		// bone_matrix
		//char pad5[0X255E];
		//Matrix34 m_dwBoneMatrix; // { 0x26A8 };(0x48)  // use Matrix34 struct here for bone-position of size 4x12(float) bytes
		// bone_matrix
		char pad5[0X255E];
		int m_dwBoneMatrix; // { 0x26A8 };(0x4) 
		//aim_punch_angle
		char pad6[0X990];
		Vec3 m_aimPunchAngle; //{ 0x303C };(0x12)
		
		//armor-value
		char pad7[0xE77E];
		int  m_ArmorValue;// { 0x117CC };(0X4)
	
};

class EntListObjPtr
{
public:
	// Each pointer to entity is 0x10 (16 bytes) APART
	//Hence this kind of padding structure is made
	//So EntListObjPtr class is basically a pointer to local__entity object instance
	//The extra padding of char[12] bytes is given to represnt structure as in actual game memory
	LocalEntity* entityObjPtr {};
	char padding[12];
};
class EntList // List of entity pointers to parse up
{
public:
// We created an array of class EntListObj  object
// as class EntListObj basically represents pointer to entity 
//EntListObj class have a char padding[12] to represent it as in-game 
//class entity pointer structure holding Entity object pointers which are 0x10 bytes apart
// Now this  member of class Entlist is said to be an array of 32 local__Entity pointers
// The elements of array are class object EntListObjPtr(which in size are 16 bytes apart)
	
	EntListObjPtr entlistObjPtrArray[32];
};

class HackLogic
{
public:

	ptrdiff_t dwEntityList = 0x4DFFEF4;
	ptrdiff_t dwViewMatrix = 0x4DF0D24;
	ptrdiff_t engine {};
	ptrdiff_t client {};
	LocalEntity* localEntity {};
	EntList* entList {};
	float viewMatrix[16];
	Vec2 crossHair2D {};  // cross-hair position on gthe screen
	int crossHairSize {4}; // for the size of cross-hair
	void Init();
	void Update();
	bool checkValidEnt( LocalEntity* ent );
	bool worldToScreen( Vec3 pos, Vec2& screen );

	Vec3 GetBonePosition( LocalEntity* ent, int bone ); // to get headbones 
};
