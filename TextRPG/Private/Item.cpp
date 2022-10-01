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
	cout << "�̸�: " << m_ItemData.szName << endl;
	cout << "���ݷ�: " << m_ItemData.iAttack << endl;
	cout << "ü��: " << m_ItemData.iHp << endl;
	cout << "���Ű�: " << m_ItemData.iPurchase_Price << endl;
	cout << "�ǸŰ�: " << (m_ItemData.iPurchase_Price >> 1) << endl;
	cout << "======================================" << endl;
}

void CItem::Release()
{
}
