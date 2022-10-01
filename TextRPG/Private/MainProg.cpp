#include "stdafx.h"
#include "MainProg.h"
#include "Monster.h"
#include "Player.h"
#include "Dungeon.h"
#include "Shop.h"
#include "Inventory.h"

CMainProg::CMainProg()
	:m_pPlayer(nullptr), m_pDungeon(nullptr), m_pShop(nullptr), m_pInventory(nullptr)
{
	
}

CMainProg::~CMainProg()
{
	Release();
}

void CMainProg::Initialize()
{
	if (!m_pDungeon)
	{
		m_pDungeon = new CDungeon();
		m_pDungeon->Initialize();
	}

	if (!m_pShop)
	{
		m_pShop = new CShop();
		m_pShop->Initialize();
	}

	if (!m_pInventory)
	{
		m_pInventory = new CInventory();
		m_pInventory->Initialize();
	}
}


void CMainProg::Progress()
{
	bool bResult = false;
	
	while (true)
	{
		bResult = TitleScreen();
		if (!bResult)
		{
			break;
		}

		m_pDungeon->Set_Player(m_pPlayer);
		m_pInventory->Set_Player(m_pPlayer);
		m_pShop->Set_Player(m_pPlayer);
		m_pShop->Set_Inventory(m_pInventory);

		MainScreen();
	}
}

void CMainProg::Release()
{
	SAFE_DELETE<CObj*>(m_pPlayer);
	SAFE_DELETE(m_pDungeon);
	SAFE_DELETE(m_pShop);
}

bool CMainProg::TitleScreen()
{
	int		iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|              TEXT RPG              |" << endl;
		cout << "======================================" << endl;
		cout << "|           1. New Game              |" << endl;
		cout << "|           2. Load Game             |" << endl;
		cout << "|           3. Exit Game             |" << endl;
		cout << "--------------------------------------" << endl;
		cout << "입력 : ";
		cin >> iSelect;
		switch (iSelect)
		{
		case ETitleScreenSelect_NewGame:
			if(Create_New_Character())
				return true;
			break;
		case ETitleScreenSelect_LoadGame:
			if (Load())
				return true;
			break;
		case ETitleScreenSelect_END:
			return false;
		}
	}
}

void CMainProg::MainScreen()
{
	int		iSelect	= 0;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|                마을                |" << endl;
		cout << "======================================" << endl;
		m_pPlayer->Render();
		cout << "1.사냥터 2.인벤 3.상점 4.저장 5.종료" << endl;
		cout << "이동 : ";
		cin >> iSelect;
		//Progress
		switch (iSelect)
		{
		case EMainScreenSelect_Dungeon:
			EnterDungeon();
			break;
		case EMainScreenSelect_Inventory:
			EnterInventory();
			break;
		case EMainScreenSelect_Shop:
			EnterShop();
			break;
		case EMainScreenSelect_Save:
			Save();
			break;
		case EMainScreenSelect_EndGame:
			return;
		}
	}
}

void CMainProg::EnterDungeon()
{
	m_pDungeon->Progress();
}

void CMainProg::EnterInventory()
{
	m_pInventory->Progress();
}

void CMainProg::EnterShop()
{
	m_pShop->Progress();
}

bool CMainProg::Create_New_Character()
{
	int iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|             캐릭터 선택            |" << endl;
		cout << "======================================" << endl;
		cout << "| 1. 전사   : HP : 100   Attack : 10 |" << endl;
		cout << "| 2. 마법사 : HP : 200   Attack : 20 |" << endl;
		cout << "| 3. 도적   : HP : 300   Attack : 30 |" << endl;
		cout << "| 4. 이전                            |" << endl;
		cout << "--------------------------------------" << endl;
		cout << "입력 : ";
		cin >> iSelect;
		
		switch (iSelect)
		{
		case EClassData_Warrior:
		case EClassData_Wizard:
		case EClassData_Thief:
			m_pPlayer = new CPlayer(static_cast<EClassData>(iSelect));
			return true;
			break;
		case EClassData_END:
			return false;
			break;
		}
	}
	return false;
}

void CMainProg::Save()
{
	FILE *fpNew_SaveFile = nullptr;

	errno_t err = fopen_s(&fpNew_SaveFile, SaveFilePath, "wb");
	if (err)
	{
		cout << "세이브 파일 생성 오류!" << endl;
		system("pause");
		return;
	}

	fwrite(static_cast<CPlayer*>(m_pPlayer)->GetPlayerData(), sizeof(PLAYER_DATA), 1, fpNew_SaveFile);

	int		iEquip_Buff[2] = { 0 };
	int		index = 0;
	for (auto i : static_cast<CPlayer*>(m_pPlayer)->GetEquipmentData())
	{
		iEquip_Buff[index++] = i;
	}
	fwrite(iEquip_Buff, sizeof(int), 2, fpNew_SaveFile);

	ITEM_DATA		iInventory_Buff[10] = {  };
	index = 0;
	for (auto i : static_cast<CPlayer*>(m_pPlayer)->GetInventoryData())
	{
		iInventory_Buff[index++] = i.Get_ItemData();
	}
	fwrite(iEquip_Buff, sizeof(ITEM_DATA), index, fpNew_SaveFile);
	cout << "저장 완료!" << endl;
	fclose(fpNew_SaveFile);
	system("pause");
}

bool CMainProg::Load()
{
	FILE *fpNew_LoadFile	= nullptr;
	PLAYER_DATA *Load_Data	= new PLAYER_DATA();

	SAFE_DELETE(m_pPlayer);
	m_pPlayer = new CPlayer();

	errno_t err = fopen_s(&fpNew_LoadFile, SaveFilePath, "rb");
	if (err)
	{
		cout << "세이브 데이터가 없습니다!" << endl;
		system("pause");
		return false;
	}

	fread(Load_Data, sizeof(PLAYER_DATA), 1, fpNew_LoadFile);
	static_cast<CPlayer*>(m_pPlayer)->SetPlayerData(Load_Data);

	vector<int>			VecEquip_Buff;
	for (int i = 0; i < 2; ++i)
	{
		int*		iEquip_Buff = 0;
		fread(iEquip_Buff, sizeof(int), 1, fpNew_LoadFile);
		VecEquip_Buff.push_back(*iEquip_Buff);
	}
	static_cast<CPlayer*>(m_pPlayer)->SetEquipmentData(VecEquip_Buff);
	
	vector<CItem>		VecInventory_Buff;
	ITEM_DATA*		tInventory_Buff = nullptr;
	int				index = 0;
	while (fread(tInventory_Buff, sizeof(ITEM_DATA), 1, fpNew_LoadFile) != EOF)
	{
		VecInventory_Buff.push_back(CItem(*tInventory_Buff));
		index++;
	}
	static_cast<CPlayer*>(m_pPlayer)->SetInventoryData(VecInventory_Buff);

	fclose(fpNew_LoadFile);
	return true;
}
