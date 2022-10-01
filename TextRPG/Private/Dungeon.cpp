#include "stdafx.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"

CDungeon::CDungeon()
{
	m_pPlayer = nullptr;
	m_pMonster = nullptr;
}

CDungeon::~CDungeon()
{
	Release();
}

void CDungeon::Initialize()
{

}

void CDungeon::Progress()
{
	int					iSelect	= 0;
	ECombatResult		CombatResult = ECombatResult_END;

	while (true)
	{
		Render();
		cout << "이동 : ";
		cin >> iSelect;

		switch (iSelect)
		{
		case EMonsterLevel_Beginner:
		case EMonsterLevel_Intermediate:
		case EMonsterLevel_Advanced:
			CreateMonster(static_cast<EMonsterLevel>(iSelect));
			CombatResult = Battle();
			break;
		case EMonsterLevel::EMonsterLevel_END:
			return;
		}

		switch (CombatResult)
		{
		case ECombatResult_Win:
			static_cast<CPlayer*>(m_pPlayer)->Combat_Win(m_pMonster);
			break;
		case ECombatResult_Lose:
			static_cast<CPlayer*>(m_pPlayer)->Combat_Lost();
			break;
		case ECombatResult_Run:
			static_cast<CPlayer*>(m_pPlayer)->Combat_Run();
			break;
		}
		SAFE_DELETE(m_pMonster);
	}
}

void CDungeon::Render()
{
	system("cls");
	cout << "======================================" << endl;
	cout << "|             Hunting Room           |" << endl;
	cout << "======================================" << endl;
	m_pPlayer->Render();
	cout << "1.초급 2.중급 3.고급 4.나가기" << endl;
	cout << "======================================" << endl;
}

void CDungeon::Release()
{
}

void CDungeon::Set_Player(CObj * _pPlayer)
{
	m_pPlayer = _pPlayer;
}

void CDungeon::CreateMonster(EMonsterLevel _MonsterLevel)
{
	switch (_MonsterLevel)
	{
	case EMonsterLevel_Beginner:
		m_pMonster = new CMonster("슬라임", 5, 30, 1);
		m_pMonster->Initialize();
		break;
	case EMonsterLevel_Intermediate:
		m_pMonster = new CMonster("오우거", 30, 200, 2);
		m_pMonster->Initialize();
		break;
	case EMonsterLevel_Advanced:
		m_pMonster = new CMonster("골렘", 100, 500, 10);
		m_pMonster->Initialize();
		break;
	}
}

ECombatResult CDungeon::Battle()
{
	int iSelect = 0;

	while (true)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "|                Battle              |" << endl;
		cout << "======================================" << endl;
		m_pPlayer->Render();
		m_pMonster->Render();
		cout << "1.공격 2.도망" << endl;
		cout << "======================================" << endl;
		cout << "선택 : ";
		cin >> iSelect;

		switch (iSelect)
		{
		case EBattleSelect_Attack:
			m_pPlayer->ApplyDamage(m_pMonster);
			if (m_pMonster->IsDead())
			{
				cout << "승리!" << endl;
				system("pause");
				return ECombatResult_Win;
			}

			m_pMonster->ApplyDamage(m_pPlayer);
			if (m_pPlayer->IsDead())
			{
				cout << "패배!" << endl;
				system("pause");
				return ECombatResult_Lose;
			}
			break;
		case EBattleSelect_Run:
			return ECombatResult_Run;
		}
	}
}
