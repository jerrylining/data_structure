// data_structure.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "tree\AvlTree.h"

typedef struct{
	size_t len;
	char *data;
}ngx_str_t;

char *
ngx_hex_dump(char *dst, char *src, size_t len)
{
	static char  hex[] = "0123456789abcdef";

	while (len--) {
		*dst++ = hex[*src >> 4];
		*dst++ = hex[*src++ & 0xf];
	}

	return dst;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ngx_str_t *str = new ngx_str_t;

	str->len = 10;
	str->data = "fasfda";

	ngx_str_t *ptr = str;
	return 0;
}

