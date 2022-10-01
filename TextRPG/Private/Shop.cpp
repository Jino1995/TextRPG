#include "stdafx.h"
#include "Shop.h"
#include "Player.h"
#include "Item.h"
#include "Obj.h"
#include "Inventory.h"

CShop::CShop()
	:m_pPlayer(nullptr)
{
	memset(m_pItem, 0, sizeof(m_pItem));
}

CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	CItem*	pObj = new CItem(ITEM_DATA("�ʱ� ��", 10, 0, 25, 50, EEquipmentSlot_Weapon));
	pObj->Initialize();
	m_pItem[LEVEL_1][EEquipmentSlot_Weapon] = pObj;

	pObj = new CItem(ITEM_DATA("�ʱ� ��", 0, 5, 25, 50, EEquipmentSlot_Armor));
	pObj->Initialize();
	m_pItem[LEVEL_1][EEquipmentSlot_Armor] = pObj;

	pObj = new CItem(ITEM_DATA("�߱� ��", 50, 0, 250, 500, EEquipmentSlot_Weapon));
	pObj->Initialize();
	m_pItem[LEVEL_2][EEquipmentSlot_Weapon] = pObj;

	pObj = new CItem(ITEM_DATA("�߱� ��", 0, 100, 250, 500, EEquipmentSlot_Armor));
	pObj->Initialize();
	m_pItem[LEVEL_2][EEquipmentSlot_Armor] = pObj;

	pObj = new CItem(ITEM_DATA("��� ��", 100, 0, 500, 1000, EEquipmentSlot_Weapon));
	pObj->Initialize();
	m_pItem[LEVEL_3][EEquipmentSlot_Weapon] = pObj;

	pObj = new CItem(ITEM_DATA("��� ��", 0, 2000, 500, 1000, EEquipmentSlot_Armor));
	pObj->Initialize();
	m_pItem[LEVEL_3][EEquipmentSlot_Armor] = pObj;
}

void CShop::Progress()
{
	int	iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|                 Shop               |" << endl;
		cout << "======================================" << endl;
		cout << "1.�ʱ� 2.�߱� 3.��� 4.�Ǹ� 5.������" << endl;
		cout << "======================================" << endl;
		cout << "���� : ";
		cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			Render_Buy(LEVEL_1);
			break;
		case 2:
			Render_Buy(LEVEL_2);
			break;
		case 3:
			Render_Buy(LEVEL_3);
			break;
		case 4:
			Render_Sell();
			break;
		case 5:
			return;
		default:
			continue;
		}
	}
}

void CShop::Render_Buy(LEVEL _eLevel)
{
	int					iSelect = 0;
	EPurchaseResult		eResult = EPurchaseResult_END;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|             Shop(����)             |" << endl;
		cout << "======================================" << endl;
		m_pPlayer->Render();
		m_pItem[_eLevel][EEquipmentSlot_Weapon]->Render();
		m_pItem[_eLevel][EEquipmentSlot_Armor]->Render();
		cout << "1.���ⱸ��   2.������   3.������" << endl;
		cout << "======================================" << endl;
		cout << "�Է�: ";
		cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			eResult = Buy_Item(m_pItem[_eLevel][EEquipmentSlot_Weapon]);
			break;
		case 2:
			eResult = Buy_Item(m_pItem[_eLevel][EEquipmentSlot_Armor]);
			break;
		case 3:
			return;
		default:
			continue;
		}

		switch (eResult)
		{
		case EPurchaseResult_Success:
			cout << "���� �Ϸ�." << endl;
			system("pause");
			break;
		case EPurchaseResult_Fail_LakeOfMony:
			cout << "���� ����(��� ����)" << endl;
			system("pause");
			break;
		case EPurchaseResult_Fail_FullOfInventory:
			cout << "���� ����(�κ��丮 ����)" << endl;
			system("pause");
			break;
		}
	}
}

void CShop::Render_Sell()
{
	int					iSelect = 0;
	ESellResult			eResult = ESellResult_END;
	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|             Shop(�Ǹ�)             |" << endl;
		cout << "======================================" << endl;
		m_pPlayer->Render();
		m_pInventory->Render_Equip();
		m_pInventory->Render_UnEquip();
		cout << "�Է�: ";
		cin >> iSelect;

		if (0 < iSelect && iSelect <= static_cast<CPlayer*>(m_pPlayer)->GetInventory().size())
		{
			eResult = static_cast<CPlayer*>(m_pPlayer)->Sell_Item(iSelect - 1);
			switch (eResult)
			{
			case ESellResult_Fail_Cur_EquipItem:
				cout << "�Ǹ� ����(�������� ������)" << endl;
				system("pause");
				break;
			case ESellResult_Success:
				cout << "�Ǹ� �Ϸ�" << endl;
				system("pause");
				break;
			}
		}
		else if (0 == iSelect)
		{
			return;
		}
	}
}

void CShop::Release()
{
	//SAFE_DELETE_PARR(m_pItemList);
}

EPurchaseResult CShop::Buy_Item(CItem * _pPuritem)
{
	if (static_cast<CPlayer*>(m_pPlayer)->GetGold() < _pPuritem->Get_PurchasePrice())
	{
		return EPurchaseResult_Fail_LakeOfMony;
	}
	else
	{
		if (!static_cast<CPlayer*>(m_pPlayer)->Add_Item(*_pPuritem))
		{
			return EPurchaseResult_Fail_FullOfInventory;
		}

		static_cast<CPlayer*>(m_pPlayer)->GainGold(_pPuritem->Get_PurchasePrice() * -1);
		return EPurchaseResult_Success;
	}
}
