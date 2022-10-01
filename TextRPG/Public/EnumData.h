#pragma once

#ifndef __ENUMDATA_H__
#define __ENUMDATA_H__


enum EClassData
{
	EClassData_Warrior = 1,
	EClassData_Wizard,
	EClassData_Thief,
	EClassData_END
};

enum EMonsterLevel
{
	EMonsterLevel_Beginner = 1,
	EMonsterLevel_Intermediate,
	EMonsterLevel_Advanced,
	EMonsterLevel_END
};

enum ETitleScreenSelect
{
	ETitleScreenSelect_NewGame = 1,
	ETitleScreenSelect_LoadGame,
	ETitleScreenSelect_END
};

enum EMainScreenSelect
{
	EMainScreenSelect_Dungeon = 1,
	EMainScreenSelect_Inventory,
	EMainScreenSelect_Shop,
	EMainScreenSelect_Save,
	EMainScreenSelect_EndGame,
	EMainScreenSelect_END
};

enum EBattleSelect
{
	EBattleSelect_Attack = 1,
	EBattleSelect_Run,
	EBattleSelect_END
};

enum ECombatResult
{ 
	ECombatResult_Win = 1,
	ECombatResult_Lose,
	ECombatResult_Run,
	ECombatResult_END
};

enum EShopSelect
{
	EShopSelect_Purchase = 1,
	EShopSelect_END
};

enum EPurchaseResult
{
	EPurchaseResult_Success = 1,
	EPurchaseResult_Fail_LakeOfMony,
	EPurchaseResult_Fail_FullOfInventory,
	EPurchaseResult_END
};

enum ESellResult
{
	ESellResult_Success = 1,
	ESellResult_Fail_Cur_EquipItem,
	ESellResult_END
};

enum EInventorySelect
{
	EInventorySelect_Equip = 1,
	EInventorySelect_UnEquip,
	EInventorySelect_END
};

enum EEquipmentSlot
{
	EEquipmentSlot_Weapon,
	EEquipmentSlot_Armor,
	EEquipmentSlot_END
};

enum LEVEL 
{ 
	LEVEL_1, 
	LEVEL_2, 
	LEVEL_3, 
	LEVEL_END 
};

#endif