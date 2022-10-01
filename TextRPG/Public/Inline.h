#pragma once

#ifndef __INLINE_H__
#define __INLINE_H__

template<typename T>
inline void SAFE_DELETE(T _p)
{
	if (_p)
	{
		delete _p;
		_p = nullptr;
	}
}

template<typename T>
inline void SAFE_DELETE_ARR(T _p)
{
	if (_p)
	{
		delete[] _p;
		_p = nullptr;
	}
}

template<typename T>
inline void SAFE_DELETE_PARR(T _p)
{
	if (_p)
	{
		int iSize = sizeof(_p) / sizeof(T);
		for (int i = 0; i < iSize; ++i)
		{
			if(_p[i])
				delete _p[i];
		}
		_p = nullptr;
	}
}

#endif