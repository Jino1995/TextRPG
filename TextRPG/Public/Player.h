#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "stdafx.h"
#include "Obj.h"
#include "Item.h"

class CMonster;

class CPlayer : public CObj
{
public:
	CPlayer();
	CPlayer(EClassData ClassName);
	CPlayer(PLAYER_DATA* New_Data);
	~CPlayer();

public:
	void Initialize();
	void Render() const;
	void Release();

public:
	void TakeDamage(const int Damage);
	void ApplyDamage(CObj* const DamageTarget) const;
	void Resurrection();

public:
	void GainReward(const CMonster* const KillTarget);
	void GainGold(const int iGold);
	void GainEXP(const int iExp);

public:
	void Combat_Win(const CMonster* const _KilledMonster);
	void Combat_Lost();
	void Combat_Run();

public:
	void Equip_Item(int _iInventory_num);
	void UnEquip_Item(EEquipmentSlot _Slot);

public:
	bool Add_Item(CItem _item);
	ESellResult Sell_Item(int _iItemSlotNum);

public:
	inline PLAYER_DATA* GetPlayerData() const { return m_tPlayerData; }
	inline vector<CItem> GetInventoryData() const { return m_VecInventory; }
	inline vector<int> GetEquipmentData() const { return m_VecEquip; }
	inline int GetGold() { return m_tPlayerData->iMony; }
	inline vector<CItem> GetInventory() { return m_VecInventory; }
	inline vector<int> GetEquipment() { return m_VecEquip; }
	inline bool IsDead() const { return m_bDead; }

public:
	inline void SetPlayerData(PLAYER_DATA* _New_Data) { m_tPlayerData = _New_Data; }
	inline void SetInventoryData(vector<CItem> _VecInventory) { m_VecInventory = _VecInventory; }
	inline void SetEquipmentData(vector<int> _VecEquip) { m_VecEquip = _VecEquip; }

private:
	void LevelUp();
	void Dead();

private:
	PLAYER_DATA*		m_tPlayerData;
	vector<CItem>		m_VecInventory;
	vector<int>			m_VecEquip;

};

#endif