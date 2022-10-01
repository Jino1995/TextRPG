#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

class CItem;

typedef struct tagPlayerData
{
	char	szClass_Name[24];
	int		iLevel;
	int		iMax_HP;
	int		iCur_HP;
	int		iAttack;
	int		iMax_Exp;
	int		iCur_Exp;
	int		iMony;
}PLAYER_DATA;

typedef struct tagMonsterData
{
	char	szName[24];
	int		iMax_HP;
	int		iCur_HP;
	int		iAttack;
	int		iDrop_Exp;
	int		iDrop_Mony;
	int		iLevel;
}MONSTER_DATA;

typedef struct tagItemData
{
	tagItemData() {}
	tagItemData(char* _pName, int _iAtt, int _iHp, int _iSale_Price, int _iPurchase_Price, EEquipmentSlot _eType)
		: iAttack(_iAtt), iHp(_iHp), iSale_Price(_iSale_Price), iPurchase_Price(_iPurchase_Price), eType(_eType), bEquip(false)
	{
		strcpy_s(szName, 24, _pName);
	}

	char				szName[24];
	int					iAttack;
	int					iHp;
	int					iSale_Price;
	int					iPurchase_Price;
	EEquipmentSlot		eType;
	bool				bEquip;
}ITEM_DATA;

#endif