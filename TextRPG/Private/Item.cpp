#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{

}

CItem::CItem(ITEM_DATA _ItemData)
	:m_ItemData(_ItemData)
{

}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	
}

void CItem::Render()
{
	cout << "이름: " << m_ItemData.szName << endl;
	cout << "공격력: " << m_ItemData.iAttack << endl;
	cout << "체력: " << m_ItemData.iHp << endl;
	cout << "구매가: " << m_ItemData.iPurchase_Price << endl;
	cout << "판매가: " << (m_ItemData.iPurchase_Price >> 1) << endl;
	cout << "======================================" << endl;
}

void CItem::Release()
{
}
