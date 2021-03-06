// selection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define	MAX	8
#define	LEN	sizeof(char)

char s_debug[10];
int  i_debug_pos = 0;

char get_char(FILE *fp, long int pos)
{
	char c;

	fseek(fp, LEN*pos, 0);
	fread(&c, LEN, 1, fp);

	return c;
}

void swap_char(FILE *fp, long int pos1, long int pos2)
{
	char c1, c2;

	fseek(fp, LEN*pos1, 0);
	fread(&c1, LEN, 1, fp);
	fseek(fp, LEN*pos2, 0);
	fread(&c2, LEN, 1, fp);

	fseek(fp, LEN*pos1, 0);
	fwrite(&c2, LEN, 1, fp);
	fseek(fp, LEN*pos2, 0);
	fwrite(&c1, LEN, 1, fp);
}

void swap_show(char *psd, int pos1, int pos2)
{
	char temp;

	temp = psd[pos1];
	psd[pos1] = psd[pos2];
	psd[pos2] = temp;

	printf("psd:[%s]\n", psd);
}

void select(FILE *fp, long int count)
{
	char c1, c2;
	int i, j, pos;

	for (i = 0; i < count-1; i++) {
		c1 = get_char(fp, i);
		pos = i;
		for (j = i+1; j < count; j++) {
			c2 = get_char(fp, j);
			if (c1 > c2) {
				c1 = c2;
				pos = j;
			}
		}

		if (i != pos) {
			swap_char(fp, i, pos);
			swap_show(s_debug, i, pos);
		}
	}
}

int main()
{
	FILE *data;
	FILE *fp;

	errno_t err;

	char c;
	int  j;

	err = fopen_s(&data, "data.txt", "r");
	if (NULL == data) {
		printf("open data.txt failed.\n");
		exit(0);
	}

	err = fopen_s(&fp, "result.txt", "w+");
	if (NULL == fp) {
		printf("open result.txt file failed!\n");
		fclose(fp);
	}
	else {
		for (j = 0; j < MAX; j++) {
			c = getc(data);
			putc(c, fp);
			s_debug[i_debug_pos++] = c;
		}
		fclose(data);
		rewind(fp);

		printf("processing...\n");
		printf("s_debug:[%s]\n", s_debug);
		select(fp, MAX);
		printf("process finished!\n");
		printf("s_debug:[%s]\n", s_debug);
		fclose(fp);
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
