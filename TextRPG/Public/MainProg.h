#pragma once

#ifndef __MAINPROG_H__
#define __MAINPROG_H__

#include "stdafx.h"

class CObj;
class CDungeon;
class CShop;
class CInventory;

class CMainProg
{
public:
	CMainProg();
	~CMainProg();

public:
	void Initialize();
	void Progress();
	void Release();

private:
	bool Create_New_Character();

private:
	bool TitleScreen();
	void MainScreen();
	
private:
	void EnterDungeon();
	void EnterInventory();
	void EnterShop();


private:
	void Save();
	bool Load();

private:
	CObj*			m_pPlayer;
	CDungeon*		m_pDungeon;
	CShop*			m_pShop;
	CInventory*		m_pInventory;
};

#endif