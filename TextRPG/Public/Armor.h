#pragma once

#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "Item.h"

class CArmor : public CItem
{
public:
	CArmor();

	CArmor(ITEM_DATA _ItemData);

	~CArmor();

public:
	virtual void Initialize();

	virtual void Render();

	virtual void Release();
};

#endif