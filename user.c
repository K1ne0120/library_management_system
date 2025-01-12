#define _CRT_SECURE_NO_WARNINGS

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
#include "user.h"
#include "functions.h"

#define NAME_MAX_LENGTH 30 //账户最大长度
#define PASSWORD_MAX_LENGTH 30 //密码最大长度
#define ACCOUNT_MAX_LENGTH 65 //账户信息最大长度 账户信息为 账户+密码
#define MAX_LINE_LENGTH 256 //检查账户文件每行最大长度
#define MAX_BOOKS_NAME 20  //书名最大长度
#define MAX_BOOKS_LOCATION 5 //书籍位置最大长度
#define MAX_BOOKS_AUTHOR 20 //书籍作者最大长度
#define MAX_BOOKS_ISBN 14 //书籍ISBN最大长度
#define MAX_BOOKS_WHETHER 4 //书籍是否被借阅
#define MAX_DATA 11 //日期最大长度


char user_name[NAME_MAX_LENGTH]; // 定义共享变量





void user_menu() {
	while (1) {
		system("cls");
		int HIDE = 0;
		HideCursor(HIDE);

		printf("*===========================================================*\n");
		printf("||                  <<·—— 用户操作界面 ——·>>               ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||       <*- 查阅书籍 —*>          <*- 借阅书籍 —*>        ||\n");
		printf("||                                                         ||\n");
		printf("||            请按 1                    请按 2             ||\n");
		printf("||                                                         ||\n");
		printf("||       <*- 归还书籍 —*>        <*- 修改个人信息 —*>      ||\n");
		printf("||                                                         ||\n");
		printf("||            请按 3                    请按 4             ||\n");
		printf("||                                                         ||\n");
		printf("||                   <*- 返回登陆界面 —*>                  ||\n");
		printf("||                                                         ||\n");
		printf("||                        请按 5                           ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");


		char choice = _getch(); // 获取用户输入

		HIDE = 1;
		HideCursor(HIDE);

		switch (choice) {
		case '1':
			system("cls");
			while (1) {
				search_books_user_menu();
				break;
			}
			break;
		case '2':
			system("cls");
			borrow_books_user_menu(L"sweep");
			break;
		case '3':
			system("cls");
			return_books_user_menu();
			break;
		case '4':
			system("cls");
			modify_user_information_menu();
			break;
		case '5':
			system("cls");
			return;
		default:
			system("cls");
			printf("*===========================================================*\n");
			printf("||                  <<·—— 用户操作界面 ——·>>               ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||               <*- 输入无效，请重新输入 —*>              ||\n");
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

			
			Sleep(2000); // 暂停以便用户阅读消息
			break;
		}
	}
	return 0; // 这一行永远不会被执行
}

void search_books_user_menu() {
	wchar_t search_term[MAX_BOOKS_NAME];
    int choice;
	int count = 1;
    while (1) {
        system("cls"); // 清屏

		printf("*===========================================================*\n");
		printf("||                    <<·—— 查阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                1. 按书名搜索                            ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                2. 按出版社搜索                          ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                3. 按ISBN搜索                            ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                4. 返回主菜单                            ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");

		
        
		int HIDE = 0;
		HideCursor(HIDE);

        choice = _getch(); // 获取用户输入
		
		HIDE = 1;
		HideCursor(HIDE);

        switch (choice) {
			case '1':
				system("cls");  // 清屏

				
				search(1,1);

				if (count == 1) {
					getchar();
					count++;
				}

				gotoxy(30, 9);
				fgetws(search_term, sizeof(search_term) / sizeof(wchar_t), stdin);
				search_term[wcslen(search_term) - 1] = L'\0'; // 去掉换行符

				system("cls");

				
				search(2, 1);

				Sleep(4000);

				system("cls");
				books_search_menu(1);
				books_search(search_term);
				books_search_menu(2);
				Sleep(5000);
				break;
			case '2':
				system("cls");
				
				search(1,2);
				if (count == 1) {
					getchar();
					count++;
				}
				gotoxy(32, 9);
				fgetws(search_term, sizeof(search_term) / sizeof(wchar_t), stdin);
				search_term[wcslen(search_term) - 1] = L'\0'; // 去掉换行符

				system("cls");
				
				search(2, 2);

				Sleep(4000);

				system("cls");
				books_search_menu(1);
				books_search(search_term);
				books_search_menu(2);
				Sleep(5000); // 暂停以便用户查看
				break;
			case '3':
				system("cls");
				
				search(1,3);
				if (count == 1) {
					getchar();
					count++;
				}
				gotoxy(30, 9);
				fgetws(search_term, sizeof(search_term) / sizeof(wchar_t), stdin);
				search_term[wcslen(search_term) - 1] = L'\0'; // 去掉换行符

				system("cls");
				

				search(2, 3);

				Sleep(4000);

				system("cls");
				books_search_menu(1);
				books_search(search_term);
				books_search_menu(2);

				Sleep(5000); // 暂停以便用户查看
				break;
			case '4':
				return; // 返回主菜单
			default:
				system("cls");
				search(3, NULL);
				
				Sleep(2000); // 暂停以便用户查看
				break;
        }
    }
	return 0;
}



void books_search_menu(const int a) {
	if (a == 1) {
		printf("*========================================================================*\n");
		printf("||                          <<·—— 查阅书籍 ——·>>                        ||\n");
		printf("||                                                                      ||\n");
		printf("||                                                                      ||\n");
		printf("||                                                                      ||\n");
		printf("*========================================================================*\n");
		
	}
	
}



void borrow_books_user_menu(const wchar_t* user_name) {
	wchar_t b_ISBN[MAX_BOOKS_ISBN];
	int found = 0;

	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\books_information.txt", L"r+, ccs=UTF-8");

	
	printf("*===========================================================*\n");
	printf("||                    <<·—— 借阅书籍 ——·>>                 ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                * 请输入ISBN：                           ||\n");
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
		
	int a = 1;
	if (a == 1) {
		getchar();
		a++;
	}
		
		gotoxy(32, 9);
		fgetws(b_ISBN, sizeof(b_ISBN) / sizeof(wchar_t), stdin);
		b_ISBN[wcslen(b_ISBN)] = L'\0'; // 去掉换行符

		if (err != 0 || file == NULL) {
			wprintf(L"无法打开文件。\n");
			return;
		}

		wchar_t line[MAX_LINE_LENGTH];
		
		int line_count = 0;
		while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {
			
			line_count++;;

			wchar_t position[MAX_BOOKS_LOCATION];
			wchar_t name[MAX_BOOKS_NAME];
			wchar_t author[MAX_BOOKS_AUTHOR];
			wchar_t ISBN[MAX_BOOKS_ISBN];
			wchar_t judgement[MAX_BOOKS_WHETHER];
			wchar_t* context = NULL;


			wchar_t* token = wcstok(line, L",", &context);
			wcsncpy_s(position, sizeof(position) / sizeof(position[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(name, sizeof(name) / sizeof(name[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(author, sizeof(author) / sizeof(author[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(ISBN, sizeof(ISBN) / sizeof(ISBN[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), token, _TRUNCATE);

			wchar_t no[] = L"NO";

			// 检查书名是否匹配
			if (wcscmp(b_ISBN, ISBN) == 0 && strstr(judgement, no) != NULL) {
				wcscpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), L"YES");
				
				wchar_t borrow_time[MAX_DATA];
				wchar_t return_time[MAX_DATA];
				

				// 获取当前时间
				time_t now = time(NULL);
				struct tm* tm_info = localtime(&now);

				// 格式化时间为字符串
				wcsftime(borrow_time, sizeof(borrow_time) / sizeof(wchar_t), L"%Y.%m.%d", tm_info);

				tm_info->tm_mon += 1; // 增加一个月
				mktime(tm_info); // 正规化时间结构
				wcsftime(return_time, sizeof(return_time) / sizeof(wchar_t), L"%Y.%m.%d", tm_info);

				wchar_t n_line[MAX_LINE_LENGTH];
				// 拼接新信息
				
				swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls\0", position, name, author, ISBN, judgement, user_name, borrow_time, return_time);
				
				fclose(file);

				wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\books_information.txt";
				
				delete_line(filename, line_count);
				
				append_line(filename, n_line);
				
				found = 1;
				system("cls"); // 清屏
				printf("*===========================================================*\n");
				printf("||                    <<·—— 借阅书籍 ——·>>                 ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                * 正在借阅中...                          ||\n");
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

				system("cls");
				printf("*===========================================================*\n");
				printf("||                    <<·—— 借阅书籍 ——·>>                 ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                                                         ||\n");
				printf("||                        * 借阅成功!                      ||\n");
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
				break; // 找到后可以选择退出
			}
		}

	if (!found) {
		system("cls");
		printf("*===========================================================*\n");
		printf("||                    <<·—— 借阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                  * 未找到匹配的书籍，请重试             ||\n");
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
		fclose(file);
		return;
	}

}



void return_books_user_menu() {
	wchar_t b_ISBN[MAX_BOOKS_ISBN];
	int found = 0;

	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\books_information.txt", L"r+, ccs=UTF-8");

	
	system("cls"); // 清屏
	printf("*===========================================================*\n");
	printf("||                    <<·—— 归还书籍 ——·>>                 ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                * 请输入ISBN：                           ||\n");
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

	getchar();
	gotoxy(32, 9);
	fgetws(b_ISBN, sizeof(b_ISBN) / sizeof(wchar_t), stdin);
	b_ISBN[wcslen(b_ISBN) ] = L'\0'; // 去掉换行符

	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n");
		return;
	}

	wchar_t line[MAX_LINE_LENGTH];


	
	int line_count = 0;
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {

		

		line_count++;;


		wchar_t position[MAX_BOOKS_LOCATION];
		wchar_t name[MAX_BOOKS_NAME];
		wchar_t author[MAX_BOOKS_AUTHOR];
		wchar_t ISBN[MAX_BOOKS_ISBN];
		wchar_t judgement[MAX_BOOKS_WHETHER];
		wchar_t* context = NULL;


		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(position, sizeof(position) / sizeof(position[0]), token, _TRUNCATE);

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(name, sizeof(name) / sizeof(name[0]), token, _TRUNCATE);

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(author, sizeof(author) / sizeof(author[0]), token, _TRUNCATE);

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(ISBN, sizeof(ISBN) / sizeof(ISBN[0]), token, _TRUNCATE);

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), token, _TRUNCATE);
		token = wcstok(NULL, L",", &context);

		wchar_t yes[] = L"YES";

		// 检查书名是否匹配
		if (wcscmp(b_ISBN, ISBN) == 0 && wcscmp(judgement, yes) == 0) {
			wcscpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), L"NO");

			wchar_t n_line[MAX_LINE_LENGTH];
			
			swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls,%ls,%ls,%ls\0", position, name, author, ISBN, judgement);
			
			fclose(file);

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\books_information.txt";

			delete_line(filename, line_count);
			
			append_line(filename, n_line);
			
			found = 1;
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                    <<·—— 归还书籍 ——·>>                 ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                * 正在归还中...                          ||\n");
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
			system("cls"); // 清屏

			printf("*===========================================================*\n");
			printf("||                    <<·—— 归还书籍 ——·>>                 ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                        * 归还成功!                      ||\n");
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
			break; // 找到后可以选择退出
		}
	}
	if (!found) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                    <<·—— 借阅书籍 ——·>>                 ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                  * 未找到匹配的书籍，请重试             ||\n");
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
		fclose(file);
		return;
	}
}

void modify_user_information_menu() {
	wchar_t original_password[PASSWORD_MAX_LENGTH];
	wchar_t new_password[PASSWORD_MAX_LENGTH];
	wchar_t name[NAME_MAX_LENGTH];
	int found = 0;

	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\user_account_information.txt", L"r+, ccs=UTF-8");

	system("cls"); // 清屏
	printf("*===========================================================*\n");
	printf("||                  <<·—— 修改个人信息 ——·>>               ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 账户：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 旧密码：                                   ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 新密码：                                   ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");

	
	
	getchar();
	
	gotoxy(22, 7);
	fgetws(name, sizeof(name) / sizeof(wchar_t), stdin);
	name[wcslen(name) - 1] = L'\0'; // 去掉换行符

	/*wprintf(L"\t                请输入原密码：");*/
	gotoxy(24, 10);
	fgetws(original_password, sizeof(original_password) / sizeof(wchar_t), stdin);
	original_password[wcslen(original_password)] = L'\0'; // 去掉换行符


	wchar_t encrypt[PASSWORD_MAX_LENGTH];
	wcscpy(encrypt, caesarEncrypt(original_password));

	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n");
		return;
	}

	wchar_t line[MAX_LINE_LENGTH];
	
	int line_count = 0;
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {
		line_count++;;

		

		wchar_t user_name[NAME_MAX_LENGTH];
		wchar_t user_password[PASSWORD_MAX_LENGTH];
		
		wchar_t* context = NULL;

		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(user_name, sizeof(user_name) / sizeof(user_name[0]), token, _TRUNCATE);


		token = wcstok(NULL, L",", &context);
		wcsncpy_s(user_password, sizeof(user_password) / sizeof(user_password[0]), token, _TRUNCATE);
		

		// 检查书名是否匹配
		if (wcscmp(encrypt, user_password) == 0 && wcscmp(user_name, name) == 0) {
			
			/*wprintf(L"\t                请输入新密码：");*/
			gotoxy(24, 13);
			fgetws(new_password, sizeof(new_password) / sizeof(wchar_t), stdin);
			new_password[wcslen(new_password) - 1] = L'\0'; // 去掉换行符



			wchar_t new_encrypt[PASSWORD_MAX_LENGTH];
			wcscpy(new_encrypt, caesarEncrypt(new_password));

			wchar_t n_line[MAX_LINE_LENGTH];
			// 拼接新信息
			
			swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls\0", user_name, new_encrypt);
			


			
			fclose(file);

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\user_account_information.txt";

			delete_line(filename, line_count);
			
			append_line(filename, n_line);
			
			found = 1;
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                  <<·—— 修改个人信息 ——·>>               ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                      * 密码修改成功!                    ||\n");
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

			

			Sleep(3000); // 暂停5秒

			break; // 找到后可以选择退出
		}
	}


	if (!found) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                  <<·—— 修改个人信息 ——·>>               ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||             * 用户名或密码错误请重试，请重试            ||\n");
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
		
		fclose(file);
		Sleep(3000);
		return;
	}

}


