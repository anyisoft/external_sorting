// merge.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define	LEN	4

void merge(FILE *merge, FILE *sort1, FILE *sort2, int len)
{
	int s1, s2;
	char c, c1, c2;

	c1 = getc(sort1);
	c2 = getc(sort2);
	s1 = s2 = 0;

	while (1) {
		if (c1 < c2) {
			putc(c1, merge);
			s1++;
			if (s1 < len) {
				c1 = getc(sort1);
			}
			else {
				break;
			}
		}
		else {
			putc(c2, merge);
			s2++;
			if (s2 < len) {
				c2 = getc(sort2);
			}
			else {
				break;
			}
		}
	}

	if (s1 < len) {
		putc(c1, merge);
		s1++;
	}

	if (s2 < len) {
		putc(c2, merge);
		s2++;
	}

	while (s1 < len) {
		c = getc(sort1);
		putc(c, merge);
		s1++;
	}

	while (s2 < len) {
		c = getc(sort2);
		putc(c, merge);
		s2++;
	}
}

int main()
{
	FILE *fp;
	FILE *fp1;
	FILE *fp2;

	errno_t err;

	err = fopen_s(&fp, "result.txt", "r+");
	if (NULL == fp) {
		printf("open result.txt file failed!\n");
	}
	else {
		err = fopen_s(&fp1, "sort1.txt", "r+");
		if (NULL == fp1) {
			printf("open sort1.txt file failed!\n");
		}
		else {
			err = fopen_s(&fp2, "sort2.txt", "r+");
			if (NULL == fp2) {
				printf("open sort2.txt file failed!\n");
			}
			else {
				printf("processing...\n");
				merge(fp, fp1, fp2, LEN);
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
