#include "stdafx.h"
#include "Weapon.h"


CWeapon::CWeapon()
{

}

CWeapon::CWeapon(ITEM_DATA _ItemData)
	: CItem(_ItemData)
{

}


CWeapon::~CWeapon()
{
	Release();
}

void CWeapon::Initialize()
{

}

void CWeapon::Render()
{
	
}

void CWeapon::Release()
{

}

