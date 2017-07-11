#include "../stdafx.h"
#include "SHash.h"

template<class KeyType,class ValueType>
void 
SHash<KeyType, ValueType>::InitHashTable(const int size)
{
	hash_size = size;
	pHashTable_ = malloc(sizeof(SHashNode<KeyType, ValueType>*) * hash_size);
}

template<class KeyType,class ValueType>
void 
SHash<KeyType, ValueType>::SetMaxSize(const int size)
{
	if (size < MIN_HASH_TABLE_SIZE){
		max_size_ = MIN_HASH_TABLE_SIZE;
		return;
	}

	max_size_ = size;
}

template<class KeyType,class ValueType>
unsigned int 
SHash<KeyType, ValueType>::HashKey(const KeyType *key)
{
	return GenHash(key, 4);
}

template<class KeyType,class ValueType>
unsigned int 
SHash<KeyType, ValueType>::GenHash(const KeyType* key, int len)
{
	unsigned int seed = hash_gen_seed;
	const unsigned m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = seed ^len;

	const unsigned char* data = (const KeyType*)key;

	while (len >= 4)
	{
		unsigned int k = *(unsigned int *)data;
		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch (len)
	{
	case 3:
		h ^= data[2] << 16; break;
	case 2:
		h ^= data[1] << 8; break;
	case 1:
		h ^= data[0]; h *= m;
	default:
		break;
	}

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return (unsigned int)h;
}

template<class KeyType,class ValueType>
void 
SHash<KeyType, ValueType>::Insert(KeyType key, ValueType val)
{
	if (table_size_ >= max_size_)return;

	unsigned int pos = HashKey(&key)&hash_size;
	SHashNode<KeyType, ValueType> *pHead = pHashTable_[pos];

	while (pHead)
	{
		if (pHead->Key() == key) pHead = pHead->Next();
	}

	SHashNode<KeyType, ValueType> *pNew = (SHashNode<KeyType, ValueType>*)malloc(sizeof(SHashNode<KeyType, ValueType>));
	memset(pNew, 0, sizeof(SHashNode<KeyType, ValueType>));

	pNew->Key() = key;
	pNew->Val() = val;

	pNew->Next() = pHashTable_[pos];
	pHashTable[pos] = pNew;
	table_size_++;
}

template<class KeyType,class ValueType>
SHashNode<KeyType,ValueType>*
SHash<KeyType, ValueType>::Lookup(const KeyType key)
{
	unsigned int pos = HashKey(key) % hash_size;

	if (pHashTable_[pos]){

		SHashNode<KeyType, ValueType> *pHead = pHashTable_[pos];
		while (pHead)
		{
			if (pHead->Key() == key)return pHead;
			pHead = pHead->Next();
		}
	}
	return NULL;
}

template<class KeyType,class ValueType>
void
SHash<KeyType, ValueType>::DumpTable()
{
	for (int i = 0; i < hash_size; i++)
	{
		SHashNode<KeyType, ValueType> *pHead = pHashTable_[i];
		if (pHead){
			while (pHead){
				//´òÓ¡node key
				printf("%lp,%lp", &pHead->Key(), &pHead->Val());
				pHead = pHead->Next();
			}
		}
	}
}