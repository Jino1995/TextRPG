#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

CMonster::CMonster(char* _pName, int _iAtt, int _iMaxHp, int _iLevel)
{
	strcpy_s(m_tMonsterData.szName, 16, _pName);
	m_tMonsterData.iAttack = _iAtt;
	m_tMonsterData.iMax_HP = _iMaxHp;
	m_tMonsterData.iCur_HP = _iMaxHp;
	m_tMonsterData.iLevel = _iLevel;
	m_tMonsterData.iDrop_Exp = 0;
	m_tMonsterData.iDrop_Mony = 0;

	m_bDead = false;
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tMonsterData.iDrop_Exp = rand() % 50 + ((m_tMonsterData.iLevel - 1) * 50);
	m_tMonsterData.iDrop_Mony = rand() % 50 + ((m_tMonsterData.iLevel - 1) * 50);
}

void CMonster::Render() const
{
	cout << "--------------------------------------" << endl;
	cout << " 이름   : " << m_tMonsterData.szName << endl;
	cout << " 공격   : " << m_tMonsterData.iAttack << endl;
	cout << " 체력   : " << m_tMonsterData.iCur_HP << " / " << m_tMonsterData.iMax_HP << endl;
	cout << "--------------------------------------" << endl;
}

void CMonster::Release()
{
	
}

void CMonster::TakeDamage(int Damage)
{
	m_tMonsterData.iCur_HP -= Damage;
	if (m_tMonsterData.iCur_HP <= 0)
	{
		m_tMonsterData.iCur_HP = 0;
		Dead();
	}
}

void CMonster::ApplyDamage(CObj* const DamageTarget) const
{
	DamageTarget->TakeDamage(m_tMonsterData.iAttack);
}

bool CMonster::IsDead() const
{
	return m_bDead;
}

int CMonster::GetDropEXP() const
{
	return m_tMonsterData.iDrop_Exp;
}

int CMonster::GetDropGold() const
{
	return m_tMonsterData.iDrop_Mony;
}

void CMonster::Dead()
{
	m_bDead = true;
}
