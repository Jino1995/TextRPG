#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "stdafx.h"
#include "Obj.h"

class CPlayer;

class CMonster : public CObj
{
public:
	CMonster(char* _pName, int _iAtt, int _iMaxHp, int _iLevel);

	~CMonster();

	void Initialize();

	void Render() const;

	void Release();

public:
	void TakeDamage(const int Damage);

	void ApplyDamage(CObj* const DamageTarget) const;

	bool IsDead() const;

public:
	int GetDropEXP() const;

	int GetDropGold() const;

private:
	void Dead();

private:
	MONSTER_DATA	m_tMonsterData;
};

#endif