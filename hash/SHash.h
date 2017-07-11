#ifndef __SHASH_H__
#define __SHASH_H__

#pragma once
#define MIN_HASH_TABLE_SIZE 256

template<class KeyType,class ValueType>
class SHashNode{
public:
	KeyType & Key(){ return key_; }
	ValueType & Val(){ return value_; }
	SHashNode<KeyType, ValueType>* Next(){ return &pNext_; }
private:
	KeyType key_;
	ValueType value_;
	SHashNode<KeyType, ValueType> *pNext_;
};

static unsigned int hash_gen_seed = 5381;
//非特化版本 需对keytype valueType 进行偏特化
template<class KeyType,class ValueType>
class SHash{
public:
	void InitHashTable(const int size = 16);

	void SetMaxSize(const int size);

	unsigned int HashKey(const KeyType* key);

	unsigned int GenHash(const KeyType* key, int len);

	void Insert(const KeyType key,ValueType val);

	SHashNode<KeyType, ValueType> *Lookup(const KeyType key);

	void DumpTable();

private:
	SHashNode<KeyType, ValueType> **pHashTable_; //双指针
	int table_size_; /*hash表的大小*/
	int hash_size; /*hash的数量*/
	int max_size_; /*hash表的最大值*/
};
#endif