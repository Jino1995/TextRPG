#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"

CPlayer::CPlayer()
	: m_VecEquip(2, -1)
{
	m_tPlayerData = new PLAYER_DATA();

	m_VecInventory.reserve(MAX_INVENTORY);
	m_VecEquip.push_back(EEquipmentSlot_END);
	m_VecEquip.push_back(EEquipmentSlot_END);
}

CPlayer::CPlayer(EClassData ClassName)
{
	m_tPlayerData = new PLAYER_DATA();

	switch (ClassName)
	{
	case EClassData_Warrior:
		strcpy_s(m_tPlayerData->szClass_Name, sizeof(m_tPlayerData->szClass_Name), "전사");
		m_tPlayerData->iAttack = 10;
		m_tPlayerData->iMax_HP = 100;
		break;
	case EClassData_Wizard:
		strcpy_s(m_tPlayerData->szClass_Name, sizeof(m_tPlayerData->szClass_Name), "마법사");
		m_tPlayerData->iAttack = 20;
		m_tPlayerData->iMax_HP = 200;
		break;
	case EClassData_Thief:
		strcpy_s(m_tPlayerData->szClass_Name, sizeof(m_tPlayerData->szClass_Name), "도적");
		m_tPlayerData->iAttack = 30;
		m_tPlayerData->iMax_HP = 300;
		break;
	}

	m_tPlayerData->iLevel = 1;
	m_tPlayerData->iCur_HP = m_tPlayerData->iMax_HP;
	m_tPlayerData->iMax_Exp = 100;
	m_tPlayerData->iCur_Exp = 0;
	m_tPlayerData->iMony = 10000;

	m_VecInventory.reserve(MAX_INVENTORY);
	m_VecEquip.push_back(EEquipmentSlot_END);
	m_VecEquip.push_back(EEquipmentSlot_END);
}

CPlayer::CPlayer(PLAYER_DATA* New_Data)
	: m_tPlayerData(New_Data)
{

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
#ifdef _DEBUG
	m_tPlayerData->iMony = 10000;
#endif
}

void CPlayer::Render() const
{
	cout << "--------------------------------------" << endl;
	cout << " 직업   : " << m_tPlayerData->szClass_Name << endl;
	cout << " 레벨   : " << m_tPlayerData->iLevel << endl;
	cout << " 공격   : " << m_tPlayerData->iAttack << endl;
	cout << " 체력   : " << m_tPlayerData->iCur_HP << " / " << m_tPlayerData->iMax_HP << endl;
	cout << " 경험치 : " << m_tPlayerData->iCur_Exp << " / " << m_tPlayerData->iMax_Exp << endl;
	cout << " 소지금 : " << m_tPlayerData->iMony << endl;
	cout << "--------------------------------------" << endl;

	for (unsigned int i = 0; i < m_VecEquip.size(); ++i)
	{
		if (m_VecEquip[i] != EEquipmentSlot_END)
		{
			cout << i + 1 << ") " << m_VecInventory[m_VecEquip[i]].Get_ItemName() << endl;
			cout << "====================================" << endl;
		}
	}

}

void CPlayer::Release()
{
	SAFE_DELETE(m_tPlayerData);
}

void CPlayer::TakeDamage(int Damage)
{
	m_tPlayerData->iCur_HP -= Damage;
	if (m_tPlayerData->iCur_HP <= 0)
	{
		m_tPlayerData->iCur_HP = 0;
		Dead();
	}
}

void CPlayer::ApplyDamage(CObj* const DamageTarget) const
{
	DamageTarget->TakeDamage(m_tPlayerData->iAttack);
}

void CPlayer::Dead()
{
	m_bDead = true;
	m_tPlayerData->iCur_Exp = m_tPlayerData->iCur_Exp >> 1;
	m_tPlayerData->iMony = m_tPlayerData->iMony >> 1;
}

void CPlayer::Resurrection()
{
	if (m_bDead)
	{
		m_bDead = false;
		m_tPlayerData->iCur_HP = m_tPlayerData->iMax_HP;
	}
}

void CPlayer::GainReward(const CMonster* const KillTarget)
{
	GainGold(KillTarget->GetDropGold());
	GainEXP(KillTarget->GetDropEXP());
}

void CPlayer::GainGold(const int iGold)
{
	m_tPlayerData->iMony += iGold;
}

void CPlayer::GainEXP(const int iExp)
{
	m_tPlayerData->iCur_Exp += iExp;
	while (m_tPlayerData->iCur_Exp >= m_tPlayerData->iMax_Exp)
	{
		LevelUp();
	}
}

void CPlayer::LevelUp()
{
	m_tPlayerData->iCur_Exp -= m_tPlayerData->iMax_Exp;
	++m_tPlayerData->iLevel;
	m_tPlayerData->iMax_HP += 100;
	m_tPlayerData->iCur_HP = m_tPlayerData->iMax_HP;
	m_tPlayerData->iMax_Exp += 100;
	m_tPlayerData->iAttack += 10;
}

void CPlayer::Combat_Win(const CMonster* const _KilledMonster)
{
	GainReward(_KilledMonster);
}

void CPlayer::Combat_Lost()
{
	Resurrection();
}

void CPlayer::Combat_Run()
{
	m_tPlayerData->iMony = 0;
	m_tPlayerData->iCur_Exp = 0;
}

void CPlayer::Equip_Item(int _iInventory_num)
{
	int					iEquip_num = m_VecEquip[m_VecInventory[_iInventory_num].GetType()];
	EEquipmentSlot		eEquip_type = m_VecInventory[_iInventory_num].GetType();
	
	if (iEquip_num != EEquipmentSlot_END)
	{
		UnEquip_Item(eEquip_type);
	}

	m_tPlayerData->iAttack += (m_VecInventory[_iInventory_num].Get_Attack());
	m_tPlayerData->iMax_HP += (m_VecInventory[_iInventory_num].Get_HP());
	m_VecInventory[_iInventory_num].SetEquipping(true);

	m_VecEquip[eEquip_type] = eEquip_type;
}

void CPlayer::UnEquip_Item(EEquipmentSlot _Slot)
{
	m_tPlayerData->iAttack += (m_VecInventory[m_VecEquip[_Slot]].Get_Attack() * -1);
	m_tPlayerData->iMax_HP += (m_VecInventory[m_VecEquip[_Slot]].Get_HP() * -1);

	if (m_tPlayerData->iMax_HP < m_tPlayerData->iCur_HP)
		m_tPlayerData->iCur_HP = m_tPlayerData->iMax_HP;

	m_VecInventory[m_VecEquip[_Slot]].SetEquipping(false);
	m_VecEquip[_Slot] = EEquipmentSlot_END;
}

bool CPlayer::Add_Item(CItem _item)
{
	if (MAX_INVENTORY <= m_VecInventory.size())
	{
		return false;
	}

	m_VecInventory.push_back(_item);
	return true;
}

ESellResult CPlayer::Sell_Item(int _iItemSlotNum)
{
	if (m_VecEquip[EEquipmentSlot_Weapon] == _iItemSlotNum || m_VecEquip[EEquipmentSlot_Armor] == _iItemSlotNum)
	{	
		return ESellResult_Fail_Cur_EquipItem;
	}
	
	auto iter = m_VecInventory.begin();
	iter += _iItemSlotNum;

	m_tPlayerData->iMony += m_VecInventory[_iItemSlotNum].Get_SalePrice();

	m_VecInventory.erase(iter);
	return ESellResult_Success;
}
