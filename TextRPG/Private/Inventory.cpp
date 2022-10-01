#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"

CInventory::CInventory()
{
}


CInventory::~CInventory()
{
}

void CInventory::Initialize()
{
}

void CInventory::Progress()
{
	int		iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "==========================================" << endl;
		cout << "1.장착 2.해제 3.나가기" << endl;
		cout << "==========================================" << endl;
		cout << "선택 : ";
		cin >> iSelect;

		switch (iSelect)
		{
		case EInventorySelect_Equip:
			Enter_Equip();
			break;
		case EInventorySelect_UnEquip:
			Enter_UnEquip();
			break;
		case EInventorySelect_END:

			return;
		}
	}
}

void CInventory::Render_Equip()
{
	int		iNum = 1;

	for (auto i : static_cast<CPlayer*>(m_pPlayer)->GetInventory())
	{
		cout << iNum++ << ")" << endl;

		if (i.IsEquipping())
			cout << "<<<<< 착용 중 >>>>>" << endl;

		i.Render();
	}
}

void CInventory::Render_UnEquip()
{
	m_pPlayer->Render();
}

void CInventory::Release()
{
	SAFE_DELETE<CPlayer*>(static_cast<CPlayer*>(m_pPlayer));
}

void CInventory::Enter_Equip()
{
	unsigned int		iSelect = 0;

	while (true)
	{
		system("cls");
		Render_Equip();
		cout << "0.나가기" << endl;
		cout << "==========================================" << endl;
		cout << "선택 : ";
		cin >> iSelect;

		if (0 < iSelect && iSelect <= static_cast<CPlayer*>(m_pPlayer)->GetInventory().size())
		{
			static_cast<CPlayer*>(m_pPlayer)->Equip_Item(iSelect - 1);
		}
		else if (0 == iSelect)
		{
			return;
		}
		system("cls");
	}
}

void CInventory::Enter_UnEquip()
{
	unsigned int		iSelect = 0;

	while (true)
	{
		system("cls");
		Render_UnEquip();
		cout << "0.나가기" << endl;
		cout << "==========================================" << endl;
		cout << "선택 : ";
		cin >> iSelect;

		if (0 < iSelect && iSelect <= static_cast<CPlayer*>(m_pPlayer)->GetInventory().size())
		{
			static_cast<CPlayer*>(m_pPlayer)->UnEquip_Item(static_cast<EEquipmentSlot>(iSelect - 1));
		}
		else if (0 == iSelect)
		{
			return;
		}
		system("cls");
	}
}
