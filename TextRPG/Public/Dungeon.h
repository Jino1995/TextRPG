#pragma once

#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "stdafx.h"

class CPlayer;
class CMonster;
class CObj;

class CDungeon
{
public:
	CDungeon();
	~CDungeon();

public:
	void Initialize();

	void Progress();

	void Render();

	void Release();

public:
	void Set_Player(CObj* _pPlayer);

private:
	void CreateMonster(EMonsterLevel _MonsterLevel);

	ECombatResult Battle();

private:
	CObj*			m_pPlayer;
	CMonster*		m_pMonster;
};

#endif