#ifndef CLASSES
#define CLASSES

#pragma once
#include "stdafx.h"

class DMain;
class DMainBase;
class DEntity;
class DPlayer;
class DObjectTable;
class DObjectList;
class DObjectClass;
class DObjectClassName;
class DPlayerPosition;
class DScoreboardBase;
class DScoreboard;
class DTransData;
class DTransBase;
class DTrans;
class DItemTable;
class DItem;
class DDroppedItemTable;


struct ArmaString
{
	int stringID;
	int stringSize;
	int string[0x28];
};


class DMainBase
{
public:


	char _0x0000[0x768];
	DObjectTable* dObjects; //0x0768
	char _0x076C[0x99C - 0x76C];
	DDroppedItemTable* SpriteTable; //0x99C
	size_t SpriteTableSize; //0x9A0
	size_t SpriteTableMaxSize; //0x9A4
	char _0x09A8;
	DDroppedItemTable* BulletTable; //0x9AC
	size_t BulletTableSize; //0x9B0
	size_t BulletTableMaxSize; //0x9B4
	char _0x0A44[0x0A60 - 0x9B8];
	DDroppedItemTable* AnimalTable; //0xA60 
	size_t AnimalTableSize; //0xA64
	char _0x0A68[0xB10 - 0xA68];
	DDroppedItemTable* FarAnimalTable; //0x0B10
	size_t FarAnimalTableSize; //0x0B14
	char _0x0B18[0x0FE8 - 0xB18];
	DDroppedItemTable* DroppedItemTable; //0x0FE8
	size_t DroppedItemTableSize; //0x0FEC
	char _0x0FF0[0x1098 - 0xFF0];
	DDroppedItemTable* FarDroppedItemTable; //0x1098
	size_t FarDroppedItemTableSize; //0x109C
	char _0x10A0[0x1374 - 0x10A0];
	DItemTable* ItemTable; //0x1374
	size_t ItemTableMaxSize; //0x1378
	size_t ItemTablePickedUpSize; //0x137C
	size_t ItemTableSize; //0x1380
	char _0x1384[0x16FC - 0x1384];
	DEntity* LocalPlayer; //0x16FC
};

class DMain
{
public:
	DMainBase* dMain; //0x0000
};


class DPlayer //base] + 0x778] + 0x0] + i*0x2C] + 0x4] //objectPtr
{
public:

	char _0x0000[0x1C];
	DPlayerPosition* dPlayerPosition; //0x001C
	char _0x0020[0x50 - 0x20];
	DObjectClass* dObjectClass; //0x0050  //-1 recursion of objNameBase
	char _0x0054[0x190 - 0x54];
	bool objectContact; //0x0190
	bool landContact; //0x0191
	bool waterContact; //0x0192
	char _0x0193[0x284 - 0x193];
	bool isDead; //0x0284;
	char _0x0286[0x28D - 0x285];
	bool isStopped; //0x028D
	char _0x028E[0x7F0 - 0x28E];
	int pID; //0x07F0
	char _0x07F4[0xA94 - 0x07F4];
	DEntity* dWeapon; //0x0A94
	char _0x0A98[0xC6C - 0xA98];
	float recoil; //0x0C6C
	char _0x0C70[0xC88 - 0xC70];
	float fatigue_diff; //0xC88
	float fatigue; //0xC8C

};

class DObjectTable //base] + 0x778] -1 recursion of objectTablePtr
{
public:
	DObjectList* dObjectList; //0x0000  //objectTablePtr
	size_t iTableSize; //0x0004         //objectTableSize
};

class DItem
{
public:
	char _0x0000[0x44];
	DPlayerPosition* dItemPosition; //0x044
	char _0x0048[0x78 - 0x48];
	DObjectClass* dObjectClass; //0x078
	char _0x007C[0x294 - 0x7C];
	float dBulletTimeAlive; //0x294
	char _0x0298[4];
	D3DXVECTOR3 dBulletPosition; //0x29C
	char _0x02A8[0x2AC - 0x2A8];
	bool isDead; //0x2AC
	char _0x02AD[0x2C4 - 0x2AD];
	D3DXVECTOR3 dBulletPositionTracer; //0x2C4
	D3DXVECTOR3 dBulletPosition2; //0x2D0
};

class DDroppedItemTable
{
public:
	DItem* dItem;
};

class DItemTable
{
public:
	int dValid;
	DItem* dItem; //(i*0x4)
	DItem* dItem2;
};


class DObjectList //base] + 0x778] + 0x0]
{
public:
	DEntity* dEntity; //this is the i*0x2C  // -1 recursion of objectPtr
	char pad[0x28];
};

class DObjectClass //base] + 0x778] + 0x70]
{
public:
	char _0x0000[52]; //this might be wrong?
	DObjectClassName* dObjectClassName; //0x0034
	char _0x0038[56];
	DObjectClassName* dObjectName; //0x0070 //objNameBase
	char _0x0074[0x76C - 0x74];
	DObjectClassName* dObjectCleanName; //0x05A0 //0x768

};

class DObjectClassName
{
public:
	char _0x0000[4];
	__int32 iNameLength; //0x0004      //entTypeSize
	char iName[100]; //0x0008              //entType
	//char iName;
	//char _0x000C[52];
};

class DPlayerPosition
{
public:
	char _0x0000[0x1C]; //0x0000
	float dX; //0x001C
	char _0x0020[4]; //0x0020
	float dY; //0x0024
	D3DXVECTOR3 dVecPositionCoords; //0x0028 //D3DV3
	char _0x0034[0x48 - 0x34];
	D3DXVECTOR3 dVelocity1; //0x0048
	float angVelocity; //0x0054
	float yVelocity2; //0x0058
	float Speed; //0x005C
	D3DXVECTOR3 dAcceleration; //0x0060
	char _0x006C[0x130 - 0x6C];
	D3DXVECTOR3 dHeadPositionCoords; //0x0130
};

class DEntity
{
public:
	char _0x0000[4];  //this is the 0x4 in (i * 2C) + 0x4
	DPlayer* dPlayer; //0x0004        //objectPtr
};

class DScoreboardBase
{
public:
	char _0x0000[0xC];
	DObjectClassName* dSObjectClassName;  //0x000C  //scoreBoardPointer
	size_t iScoreBoardSize;  //0x0010
};

class DScoreboard
{
public:
	DScoreboardBase* dScoreboard;
};


class DTransData
{
public:

	char unknown0[4]; //0x0000
	D3DXVECTOR3 InvView_right; //0x0004  
	D3DXVECTOR3 InvView_up; //0x0010  
	D3DXVECTOR3 InvView_forward; //0x001C  
	D3DXVECTOR3 InvView_Translation; //0x0028  

	D3DXVECTOR2 pad; //0x0034   (x = 1,y = -1)

	D3DXVECTOR3 ViewPortMatrix1; //0x003C  (x= viewPort.Width/2)
	D3DXVECTOR3 ViewPortMatrix2; //0x0048 -(y= viewPort.Height/2)
	D3DXVECTOR3 ViewPortMatrix3; //0x0054(x=viewPort.X + CenterScreenX,y=viewPort.Y + CenterScreenY,z=viewPort.MinZ)
	D3DXVECTOR3 ViewPortMatrix_unk; //not sure

	D3DXVECTOR3 ProjO1;//proj1.x  0x006C
	D3DXVECTOR3 ProjO2;//proj2.y  0x0078
	D3DXVECTOR3 ProjO3;//proj3.z  0x0084     =1.0001
	D3DXVECTOR3 ProjO4;//proj4.z  0x0090

	D3DXVECTOR3 Proj1;//proj1.x  0x009C
	D3DXVECTOR3 Proj2;//proj2.y  0x00A8
	D3DXVECTOR3 Proj3;//proj3.z  0x00B4     = 1.0
	D3DXVECTOR3 Proj4;//proj4.z  0x00C0

	D3DXVECTOR3 ProjD1;//   0x00CC     x = 1/Proj._11
	D3DXVECTOR3 ProjD2;//   0x00D8     y = 1/Proj._22
	D3DXVECTOR3 ProjD3;//   0x00E4     z=  1 
	D3DXVECTOR3 ProjD4;//   0x00F0

	D3DXVECTOR2 pad1; //.x bigass float  0x00FC

	D3DXVECTOR3 View_right; //0x0104    not the view
	D3DXVECTOR3 View_up; //0x0110  
	D3DXVECTOR3 View_forward; //0x011C  
	D3DXVECTOR3 View_Translation; //0x0128  	
};

class DTransBase //CE045C
{
public:
	char unknown0[0x94]; //0x0000
	DTransData* dTransData; //0x0094  
};
class DTrans
{
public:
	DTransBase* dTrans;
	D3DXVECTOR3 W2S(D3DXVECTOR3 in)
	{
		D3DXVECTOR3 out, temp;

		::D3DXVec3Subtract(&temp, &in, &dTrans->dTransData->InvView_Translation);
		float x = ::D3DXVec3Dot(&temp, &dTrans->dTransData->InvView_right);
		float y = ::D3DXVec3Dot(&temp, &dTrans->dTransData->InvView_up);
		float z = ::D3DXVec3Dot(&temp, &dTrans->dTransData->InvView_forward);

		out.x = dTrans->dTransData->ViewPortMatrix3.x * (1 + (x / dTrans->dTransData->ProjD1.x / z));
		out.y = dTrans->dTransData->ViewPortMatrix3.y * (1 - (y / dTrans->dTransData->ProjD2.y / z));
		out.z = z;

		return out;
	}
};


extern DMain* dMain;
extern DTrans* dTrans;
extern DScoreboard* dScoreboard;

#endif