#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

class CItem
{
public:
	CItem();
	CItem(ITEM_DATA _ItemData);
	~CItem();

public:
	void Initialize();
	void Render();
	void Release();

public:
	inline const char* Get_ItemName() const { return m_ItemData.szName; }
	inline int Get_SalePrice() { return m_ItemData.iSale_Price; }
	inline int Get_PurchasePrice() { return m_ItemData.iPurchase_Price; }
	inline int Get_Attack() { return m_ItemData.iAttack; }
	inline int Get_HP() { return m_ItemData.iHp; }
	inline ITEM_DATA Get_ItemData() { return m_ItemData; }
	inline EEquipmentSlot GetType() { return m_ItemData.eType; }
	inline bool IsEquipping() { return m_ItemData.bEquip; }

public:
	inline void SetEquipping(bool bVal) { m_ItemData.bEquip = bVal; }
	inline void SetItemData(ITEM_DATA	_ItemData) { m_ItemData = _ItemData; }

protected:
	ITEM_DATA	m_ItemData;
};

#endif