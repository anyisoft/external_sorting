// split_merge.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define	LEN	8

void append_char_show(char *str_m, char c)
{
	str_m[strlen(str_m)] = c;
	printf("str_m:[%s]\n", str_m);
}

void merge_sort(FILE *merge, FILE *sort1, FILE *sort2, int len)
{
	int s1, s2;
	int i, j, k;
	char c, c1, c2;

	char str_m[10];
	char str_1[10];
	char str_2[10];

	for (i = 1; i < len; i *= 2) {

		memset(str_m, 0x0, sizeof(str_m));
		memset(str_1, 0x0, sizeof(str_1));
		memset(str_2, 0x0, sizeof(str_2));

		for (j = 0; j < len / 2; j++) {
			c = getc(merge);
			putc(c, sort1);
			str_1[strlen(str_1)] = c;
		}
		printf("str_1:[%s]\n", str_1);

		for (; j < len; j++) {
			c = getc(merge);
			putc(c, sort2);
			str_2[strlen(str_2)] = c;
		}
		printf("str_2:[%s]\n", str_2);

		rewind(merge);
		rewind(sort1);
		rewind(sort2);

		for (k = 0; k < len / 2; k += i) {
			c1 = getc(sort1);
			c2 = getc(sort2);
			s1 = s2 = 0;

			while (1) {
				if (c1 < c2) {
					putc(c1, merge);
					append_char_show(str_m, c1);
					s1++;
					if (s1 < i) {
						c1 = getc(sort1);
					}
					else {
						break;
					}
				}
				else {
					putc(c2, merge);
					append_char_show(str_m, c2);
					s2++;
					if (s2 < i) {
						c2 = getc(sort2);
					}
					else {
						break;
					}
				}
			}

			if (s1 < i) {
				putc(c1, merge);
				append_char_show(str_m, c1);
				s1++;
			}

			if (s2 < i) {
				putc(c2, merge);
				append_char_show(str_m, c2);
				s2++;
			}

			while (s1 < i) {
				c = getc(sort1);
				putc(c, merge);
				append_char_show(str_m, c);
				s1++;
			}

			while (s2 < i) {
				c = getc(sort2);
				putc(c, merge);
				append_char_show(str_m, c);
				s2++;
			}
		}

		memset(str_m, 0x0, sizeof(str_m));
		rewind(merge);
		rewind(sort1);
		rewind(sort2);
	}
}

int main()
{
	FILE *data;
	FILE *fp;
	FILE *fp1;
	FILE *fp2;

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
	}
	else {
		for (j = 0; j < LEN; j++) {
			c = getc(data);
			putc(c, fp);
		}
		fclose(data);
		rewind(fp);

		err = fopen_s(&fp1, "split1.txt", "w+");
		if (NULL == fp1) {
			printf("open split1.txt file failed!\n");
		}
		else {
			err = fopen_s(&fp2, "split2.txt", "w+");
			if (NULL == fp2) {
				printf("open split2.txt file failed!\n");
			}
			else {
				printf("processing...\n");
				merge_sort(fp, fp1, fp2, LEN);
				printf("process finished!\n");
				fclose(fp);
				fclose(fp1);
				fclose(fp2);
			}
		}
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
