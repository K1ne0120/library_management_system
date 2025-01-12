#define _CRT_SECURE_NO_WARNINGS
#pragma commnent (lib,"winmm.lib")
//头文件
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <wchar.h>
#include <time.h>
#include "manager.h"
#include "functions.h"
#include "user.h"
#include <mmsystem.h>



//主程序
int main() {
	
	mciSendString(L"open C:\\Users\\swp\\Desktop\\music.mp3 alias BGM", NULL, 0, NULL);
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
	setlocale(LC_ALL, "");
	
	int HIDE = 0;
	HideCursor(HIDE);
	int count = 0;
	int ccount = 0;
	while (1) {
		system("cls");
		main_menu(); // 显示主菜单
		char choice = _getch(); // 获取用户输入

		HIDE = 1;
		HideCursor(HIDE);

		switch (choice) {
		case '1':
			system("cls");
			
			while (1) {
				if (user_load_menu()) {
					while (1) {
						user_menu();
						break;
					}
					break;
				}
				else {
					system("cls");
					Landing_failed();
					count++;
					if (count == 3) {
						system("cls");
						printf("*===========================================================*\n");
						printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||        <*- 账户或密码已错误三次，自动退出程序 —*>       ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("*===========================================================*\n");
						Sleep(3000);
						exit(0);
					}
					Sleep(2000);
					break;
				}
			}
			break;
		case '2':
			system("cls");
			while (1) {
				if (manager_load_menu()) {
					while (1) {
						manager_menu();
						break;
					}
					break;
				}
				else {
					system("cls");
					Landing_failed();
					ccount++;
					if (ccount == 3) {
						system("cls");
						printf("*===========================================================*\n");
						printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||        <*- 账户或密码已错误三次，自动退出程序 —*>       ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("||                                                         ||\n");
						printf("*===========================================================*\n");
						Sleep(3000);
						exit(0);
					}
					Sleep(2000);
					break;
				}
			}
			
			break;
		case '3':
			system("cls");
			int a = register_menu();
			if (a==1) {
				system("cls");
				enroll(a);
				Sleep(5000);
			}
			else if (a ==2) {
				system("cls");
				enroll(a);
				Sleep(5000);
			}
			else if (a == 3){
				system("cls");
				enroll(a);
				Sleep(2000);
			}
			break;
		case '4':
			exit(0); // 退出程序
		default:
			system("cls");
			printf("*===========================================================*\n");
			printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                <*- 输入无效，请重新输入 —*>             ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("*===========================================================*\n");
			Sleep(1000); // 暂停以便用户阅读消息
			break;
		}
	}
	mciSendString(L"close BGM repeat", NULL, 0, NULL);
	return 0; // 这一行永远不会被执行
}

//隐藏密码
void hide_password(char* password, int max_length) {
	int i = 0;
	char ch;
	/*printf("                  密码: ");*/
	while (i < max_length - 1) {
		ch = _getch(); // 读取字符
		if (ch == '\r') { // 回车结束输入
			break;
		}
		else if (ch == 8) { // 处理删除键（Backspace）
			if (i > 0) {
				i--; // 递减索引
				printf("\b \b"); // 光标向后移动，打印空格覆盖星号，然后再移动光标
			}
		}
		else {
			password[i++] = ch; // 保存字符
			printf("*"); // 显示星号
		}
	}
	password[i] = '\0'; // 添加字符串结束符
	printf("\n"); // 换行
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;  // 列
	coord.Y = y;  // 行
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void search(const int b, const int a) {
	if (b == 1) {
		printf("*===========================================================*\n");
		printf("||                    <<·—— 查阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		if (a == 1) {
			printf("||               * 请输入书名:                             ||\n");
		}
		else if (a == 2) {
			printf("||               * 请输入出版社:                           ||\n");
		}
		else if (a == 3) {
			printf("||               * 请输入ISBN:                             ||\n");
		}

		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");
	}
	else if (b == 2) {
		printf("*===========================================================*\n");
		printf("||                    <<·—— 查阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||               * 正在搜索书籍，请稍等...                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");
	}
	else if (b == 3) {
		printf("*===========================================================*\n");
		printf("||                    <<·—— 查阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||               * 输入无效，请重新输入                    ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");
	}
	else if (b == 4) {
		printf("*===========================================================*\n");
		printf("||                    <<·—— 查阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||               * 未找到匹配的书籍，请重试                ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");
	}
}