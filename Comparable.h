#include "stdafx.h"
#include <iostream>

#pragma once
#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

//比较器实现

enum CMP_T{
	MIN_CMP = -1,
	EQ_CMP,
	MAX_CMP
};

template<class KeyType>
class Comparable
{
public:
	Comparable(KeyType key) :Key_(key){};
	~Comparable();

	CMP_T Compare(const KeyType& key)const{
		return (key == Key_) ? EQ_CMP : ((key < Key_) ? MIN_CMP : MAX_CMP);
	}

	KeyType& Key()const{ return Key_; }

#ifdef USE_DEBUG
	std::ostream & Print(std::ostream & os)const{
		os << Key_;
		return os;
	}
#endif
private:
	KeyType Key_;
};

template<class KeyType>
inline std::ostream & operator <<(std::ostream & os, const Comparable<KeyType> & item)
{
	return item.Print(os);
}
#endif