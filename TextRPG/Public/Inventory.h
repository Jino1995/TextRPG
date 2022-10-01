#pragma once

#ifndef __CINVENTORY_H__
#define __CINVENTORY_H__

class CPlayer;
class CObj;

class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	void Initialize();
	void Progress();
	void Render_Equip();
	void Render_UnEquip();
	void Release();

public:
	void Enter_Equip();
	void Enter_UnEquip();

public:
	void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

private:
	CObj*		m_pPlayer;
};

#endif