#pragma once

#ifndef __SHOP_H__
#define __SHOP_H__

class CPlayer;
class CItem;
class CObj;
class CInventory;

class CShop
{
public:
	CShop();
	~CShop();

public:
	void Initialize();
	void Progress();
	void Render_Buy(LEVEL _eLevel);
	void Render_Sell();
	void Release();

public:
	inline void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	inline void Set_Inventory(CInventory* _pInventory) { m_pInventory = _pInventory; }

private:
	EPurchaseResult Buy_Item(CItem* _pPuritem);

private:
	CObj*			m_pPlayer;
	CItem*			m_pItem[LEVEL_END][EEquipmentSlot_END];
	CInventory*		m_pInventory;
};

#endif