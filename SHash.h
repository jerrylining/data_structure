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
//���ػ��汾 ���keytype valueType ����ƫ�ػ�
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
	SHashNode<KeyType, ValueType> **pHashTable_; //˫ָ��
	int table_size_; /*hash��Ĵ�С*/
	int hash_size; /*hash������*/
	int max_size_; /*hash������ֵ*/
};
#endif