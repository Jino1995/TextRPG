#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

#include "stdafx.h"

class CObj
{
public:
	CObj();

	virtual ~CObj();

	virtual	void Initialize() = 0;

	virtual void Render() const = 0;

	virtual void Release() = 0;

public:
	virtual void TakeDamage(const int Damage) = 0;

	virtual void ApplyDamage(CObj* const DamageTarget) const = 0;

	virtual bool IsDead() const;

protected:
	virtual void Dead() = 0;

protected:
	bool			m_bDead;
};

#endif