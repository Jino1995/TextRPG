#pragma once

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Item.h"

class CWeapon : public CItem
{
public:
	CWeapon();

	CWeapon(ITEM_DATA _ItemData);

	~CWeapon();

public:
	virtual void Initialize();

	virtual void Render();

	virtual void Release();

};

#endif