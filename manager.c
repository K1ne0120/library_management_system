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
#include "manager.h"
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


void manager_menu() {
	while (1) { // 无限循环，直到用户选择返回登录界面
		system("cls"); // 清屏
		int HIDE = 0; // 控制光标可见性
		HideCursor(HIDE); // 隐藏光标

		// 打印管理员操作界面菜单
		printf("*===========================================================*\n");
		printf("||                  <<·—— 管理员操作界面 ——·>>             ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||       <*- 增删改书籍 —*>         <*- 用户管理 —*>       ||\n");
		printf("||                                                         ||\n");
		printf("||            请按 1                    请按 2             ||\n");
		printf("||                                                         ||\n");
		printf("||        <*- 借阅管理 —*>       <*- 修改管理员信息 —*>    ||\n");
		printf("||                                                         ||\n");
		printf("||            请按 3                    请按 4             ||\n");
		printf("||                                                         ||\n");
		printf("||                   <*- 返回登陆界面 —*>                  ||\n");
		printf("||                                                         ||\n");
		printf("||                         请按 5                          ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");

		
		char choice = _getch(); // 获取用户输入的选项

		HIDE = 1; // 设置光标为可见
		HideCursor(HIDE);

		switch (choice) {
		case '1': // 用户选择增删改书籍
			system("cls"); // 清屏
			modify_books_manager_menu(); // 调用修改书籍管理菜单
			break;
		case '2': // 用户选择用户管理
			system("cls"); // 清屏
			manage_user_manager_menu(); // 调用用户管理菜单
			break;
		case '3': // 用户选择借阅管理
			system("cls"); // 清屏
			search_books_manager_menu(); // 调用书籍搜索管理菜单
			break;
		case '4': // 用户选择修改管理员信息
			system("cls"); // 清屏
			modify_manager_information_menu();
			break;
		case '5': // 用户选择返回登录界面
			system("cls"); // 清屏
			return;
		default: // 用户输入无效
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                  <<·—— 管理员操作界面 ——·>>             ||\n");
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

			
			Sleep(2000); // 暂停2秒以便用户阅读消息
			break;
		}
	}
	return 0;
}


void search_books_manager_menu() {
	wchar_t search_term[MAX_BOOKS_NAME];
	int choice;
	int count = 1;
	while (1) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                    <<·—— 借阅管理 ——·>>                 ||\n");
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
			search(1, 1);
			/*books_search_menu();
			printf("\t                请输入书名:");*/
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
			search(1, 2);
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
			search(1, 3);
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









void manage_user_manager_menu() {
	wchar_t name[NAME_MAX_LENGTH]; // 存储用户输入的用户名
	int found = 0; // 标志，用于标识是否找到匹配的用户

	// 打开用户账户信息文件，以读取和写入模式打开，使用UTF-8编码
	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\user_account_information.txt", L"r+, ccs=UTF-8");

	system("cls"); // 清屏
	printf("*===========================================================*\n");
	printf("||                     <<·—— 用户管理 ——·>>                ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 账户：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
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
	// 读取用户输入的用户名
	gotoxy(22, 7);
	fgetws(name, sizeof(name) / sizeof(wchar_t), stdin);
	name[wcslen(name) - 1] = L'\0'; // 去掉换行符
	
	

	// 检查文件是否成功打开
	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n"); // 提示无法打开文件
		return; // 退出函数
	}

	wchar_t line[MAX_LINE_LENGTH]; // 存储每一行内容

	

	int line_count = 0; // 行计数器

	// 逐行读取文件内容
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {

		line_count++; // 行数递增

		if (wcscmp(line, L"\n") == 0) {
			continue; // 如果是换行符，跳过当前循环
		}

		// 定义用于存储用户信息的变量
		wchar_t user_password[PASSWORD_MAX_LENGTH]; // 存储用户密码
		wchar_t user_name[NAME_MAX_LENGTH]; // 存储用户名
		wchar_t* context = NULL; // 用于分割字符串的上下文

		// 分割字符串，获取用户名和密码
		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(user_name, sizeof(user_name) / sizeof(user_name[0]), token, _TRUNCATE); // 获取用户名

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(user_password, sizeof(user_password) / sizeof(user_password[0]), token, _TRUNCATE); // 获取密码

		// 检查用户名是否匹配
		if (wcscmp(user_name, name) == 0) {
			wchar_t n_line[MAX_LINE_LENGTH]; // 存储修改后的行内容
			wchar_t new_password[PASSWORD_MAX_LENGTH]; // 存储新密码

			//wprintf(L"\t                请输入新密码："); // 提示用户输入新密码
			gotoxy(24, 13);
			fgetws(new_password, sizeof(new_password) / sizeof(wchar_t), stdin);
			new_password[wcslen(new_password) - 1] = L'\0'; // 去掉换行符

			// 加密新密码
			wchar_t new_encrypt[PASSWORD_MAX_LENGTH];
			wcscpy(new_encrypt, caesarEncrypt(new_password));

			// 拼接新信息
			swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls\0", user_name, new_encrypt);

			fclose(file); // 关闭文件

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\user_account_information.txt";
			// 删除原行并将新行追加到文件中
			delete_line(filename, line_count); // 删除原来的用户信息行

			append_line(filename, n_line); // 追加新的用户信息行

			found = 1; // 标记找到用户
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                     <<·—— 用户管理 ——·>>                ||\n");
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

			
			Sleep(3000); // 暂停以便用户查看
			break; // 找到后退出循环
		}
	}

	// 如果未找到匹配的用户，提示错误信息
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
		printf("||              * 未找到匹配的用户名，请重试               ||\n");
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
		
		fclose(file); // 确保文件关闭
		Sleep(3000);
		return; // 退出函数
	}
}


void modify_books_manager_menu() {
	int choice; // 存储用户选择的菜单项

	while (1) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                    <<·—— 增删改书籍 ——·>>               ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                1. 添加书籍                              ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                2. 删除书籍                              ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                3. 修改书籍位置                          ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                4. 返回主菜单                            ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("||                                                         ||\n");
		printf("*===========================================================*\n");

		

		int HIDE = 0; // 控制光标显示
		HideCursor(HIDE); // 隐藏光标

		choice = _getch(); // 获取用户输入，等待用户按下键

		HIDE = 1; // 设置为1以显示光标
		HideCursor(HIDE); // 显示光标

		// 根据用户输入的选项进行相应操作
		switch (choice) {
		case '1':
			system("cls");  // 清屏
			add_books_menu(); // 调用添加书籍的函数
			break;
		case '2':
			system("cls"); // 清屏
			delete_books(); // 调用删除书籍的函数
			break;
		case '3':
			system("cls"); // 清屏
			Modify_books_location(); // 调用修改书籍位置的函数
			break;
		case '4':
			return; // 返回主菜单，结束当前循环
		default:
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                    <<·—— 增删改书籍 ——·>>               ||\n");
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
			
			Sleep(2000); // 暂停2秒以便用户查看错误信息
			break; 
		}
	}
	return 0; // 函数结束
}

void Modify_books_location() {
	wchar_t location[MAX_BOOKS_LOCATION]; // 存储用户输入的书籍位置
	wchar_t new_location[MAX_BOOKS_LOCATION]; // 存储用户输入的新位置
	int found = 0; // 标志，用于标识是否找到匹配的书籍

	// 打开书籍信息文件，以读取和写入模式打开，使用UTF-8编码
	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\books_information.txt", L"r+, ccs=UTF-8");

	system("cls"); // 清屏

	printf("*===========================================================*\n");
	printf("||                    <<·—— 增删改书籍 ——·>>               ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入书籍位置：                      ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入新位置:                         ||\n");
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
	// 读取用户输入的书籍位置
	gotoxy(37, 6);
	fgetws(location, sizeof(location) / sizeof(wchar_t), stdin);
	location[wcslen(location)] = L'\0'; // 去掉换行符
	
	getchar();
	// 读取用户输入的新位置
	gotoxy(35,9);
	fgetws(new_location, sizeof(new_location) / sizeof(wchar_t), stdin);
	new_location[wcslen(new_location)] = L'\0'; // 去掉换行符

	

	// 检查文件是否成功打开
	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n");
		return; // 如果文件打开失败，退出函数
	}

	wchar_t line[MAX_LINE_LENGTH]; // 存储每一行内容


	
	int line_count = 0; // 行计数器

	// 逐行读取文件内容
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {

		line_count++; // 行数递增

		
		if (wcscmp(line, L"\n") == 0) {
			continue; // 如果是换行符，跳过当前循环
		}

		// 定义用于存储书籍信息的变量
		wchar_t position[MAX_BOOKS_LOCATION];
		wchar_t name[MAX_BOOKS_NAME];
		wchar_t author[MAX_BOOKS_AUTHOR];
		wchar_t ISBN[MAX_BOOKS_ISBN];
		wchar_t judgement[MAX_BOOKS_WHETHER];
		wchar_t* context = NULL; // 用于分割字符串的上下文

		// 分割字符串，获取书籍信息
		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(position, sizeof(position) / sizeof(position[0]), token, _TRUNCATE); // 获取位置

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(name, sizeof(name) / sizeof(name[0]), token, _TRUNCATE); // 获取书名

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(author, sizeof(author) / sizeof(author[0]), token, _TRUNCATE); // 获取作者

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(ISBN, sizeof(ISBN) / sizeof(ISBN[0]), token, _TRUNCATE); // 获取ISBN

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), token, _TRUNCATE); // 获取借阅情况

		wchar_t no[] = L"NO"; // 定义“NO”字符串，用于判断书籍状态

		// 检查用户输入的位置是否匹配且书籍状态为“NO”
		if (wcscmp(location, position) == 0 && strstr(judgement,no) != NULL) {
			wchar_t n_line[MAX_LINE_LENGTH]; // 存储修改后的行内容

			swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls,%ls,%ls,%ls\0", new_location, name, author, ISBN, judgement);

			n_line[wcslen(n_line) - 1] = L'\0'; // 去掉换行符

			fclose(file); // 关闭文件

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\books_information.txt"; // 文件名

			// 删除原行并将新行追加到文件中
			delete_line(filename, line_count);
			append_line(filename, n_line);

			found = 1; // 标记找到书籍

			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                    <<·—— 增删改书籍 ——·>>               ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                        * 修改成功!                      ||\n");
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
			break; // 找到后退出循环
		}
	}

	// 如果未找到匹配的书籍，提示错误信息
	if (!found) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                    <<·—— 增删改书籍 ——·>>               ||\n");
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
		fclose(file); // 确保文件关闭
		Sleep(3000);
		return; // 退出函数
	}
}

void add_books_menu(){
	// 定义用于存储书籍信息的变量
	wchar_t position[MAX_BOOKS_LOCATION]; // 存储书籍位置
	wchar_t name[MAX_BOOKS_NAME]; // 存储书籍名称
	wchar_t author[MAX_BOOKS_AUTHOR]; // 存储作者或出版社
	wchar_t ISBN[MAX_BOOKS_ISBN]; // 存储ISBN
	wchar_t judgement[MAX_BOOKS_WHETHER]; // 存储借阅情况

	// 打印菜单标题
	printf("*===========================================================*\n");
	printf("||                     <<·—— 添加书籍 ——·>>                ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入书籍位置：                      ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入书名:                           ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入出版社:                         ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入ISBN:                           ||\n");
	printf("||                                                         ||\n");
	printf("||                 * 请输入借阅情况:                       ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");

	
	getchar();
	// 读取用户输入的书籍位置
	gotoxy(37, 6);
	fgetws(position, sizeof(position) / sizeof(wchar_t), stdin);
	position[wcslen(position)] = L'\0'; // 去掉换行符
	getchar(); // 清除输入缓冲区中的换行

	

	// 读取用户输入的书名
	gotoxy(33, 8);
	fgetws(name, sizeof(name) / sizeof(wchar_t), stdin);
	name[wcslen(name) - 1] = L'\0'; // 去掉换行符

	

	// 读取用户输入的作者或出版社
	gotoxy(34, 10);
	fgetws(author, sizeof(author) / sizeof(wchar_t), stdin);
	author[wcslen(author) - 1] = L'\0'; // 去掉换行符

	

	// 读取用户输入的ISBN
	gotoxy(34, 12);
	fgetws(ISBN, sizeof(ISBN) / sizeof(wchar_t), stdin);
	ISBN[wcslen(ISBN)] = L'\0'; // 去掉换行符
	getchar(); // 清除输入缓冲区中的换行符

	

	// 读取用户输入的借阅情况
	gotoxy(38, 14);
	fgetws(judgement, sizeof(judgement) / sizeof(wchar_t), stdin);
	judgement[wcslen(judgement) ] = L'\0'; // 去掉换行符

	// 将所有书籍信息格式化为一行字符串
	wchar_t line[MAX_LINE_LENGTH];
	swprintf(line, MAX_LINE_LENGTH, L"%ls,%ls,%ls,%ls,%ls\0", position, name, author, ISBN, judgement);

	// 定义文件名
	wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\books_information.txt";

	// 调用函数将新书籍信息追加到文件中
	append_line(filename, line);

	// 提示用户录入成功
	system("cls");
	printf("*===========================================================*\n");
	printf("||                     <<·—— 添加书籍 ——·>>                ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                        * 添加成功!                      ||\n");
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
}

void delete_books() {
	wchar_t b_ISBN[MAX_BOOKS_ISBN]; // 存储用户输入的ISBN
	int found = 0; // 标志，用于标识是否找到匹配的书籍

	// 打开书籍信息文件，以读取和写入模式打开，使用UTF-8编码
	FILE* file;
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\books_information.txt", L"r+, ccs=UTF-8");

	system("cls"); // 清屏
	printf("*===========================================================*\n");
	printf("||                    <<·—— 删除书籍 ——·>>                 ||\n");
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
	// 读取用户输入的ISBN
	gotoxy(32, 9);
	fgetws(b_ISBN, sizeof(b_ISBN) / sizeof(wchar_t), stdin);
	b_ISBN[wcslen(b_ISBN)] = L'\0'; // 去掉换行符

	

	// 检查文件是否成功打开
	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n");
		return; // 如果文件打开失败，退出函数
	}

	wchar_t line[MAX_LINE_LENGTH]; // 存储每一行内容


	

	int line_count = 0; // 行计数器

	// 逐行读取文件内容
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {

		line_count++;; // 行数递增

		// 定义用于存储书籍信息的变量
		wchar_t position[MAX_BOOKS_LOCATION];
		wchar_t name[MAX_BOOKS_NAME];
		wchar_t author[MAX_BOOKS_AUTHOR];
		wchar_t ISBN[MAX_BOOKS_ISBN];
		wchar_t judgement[MAX_BOOKS_WHETHER];
		wchar_t* context = NULL; // 用于分割字符串的上下文

		// 分割字符串，获取书籍信息
		wchar_t* token = wcstok(line, L",", &context);
		token = wcstok(NULL, L",", &context);
		token = wcstok(NULL, L",", &context);	
		token = wcstok(NULL, L",", &context);
		wcsncpy_s(ISBN, sizeof(ISBN) / sizeof(ISBN[0]), token, _TRUNCATE);// 获取ISBN

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(judgement, sizeof(judgement) / sizeof(judgement[0]), token, _TRUNCATE); // 获取书籍状态
		token = wcstok(NULL, L",", &context);

		wchar_t no[] = L"NO"; // 定义“NO”字符串，用于判断书籍状态

		// 检查用户输入的ISBN是否匹配且书籍状态为“NO”
		if (wcscmp(b_ISBN, ISBN) == 0 && strstr(judgement, no) != NULL) {

			fclose(file); // 关闭文件

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\books_information.txt"; // 文件名

			// 调用删除函数，删除指定行
			delete_line(filename, line_count);

			found = 1; // 标记找到书籍
			system("cls"); // 清屏
			printf("*===========================================================*\n");
			printf("||                     <<·—— 删除书籍 ——·>>                ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                                                         ||\n");
			printf("||                        * 删除成功!                      ||\n");
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
			break; // 找到后退出循环
		}
	}

	// 如果未找到匹配的书籍，提示错误信息
	if (!found) {
		system("cls"); // 清屏
		printf("*===========================================================*\n");
		printf("||                     <<·—— 删除书籍 ——·>>                ||\n");
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
		fclose(file); // 确保文件关闭
		Sleep(3000);
		return; // 退出函数
	}
}



void modify_manager_information_menu() {
	wchar_t original_password[PASSWORD_MAX_LENGTH]; // 存储原密码
	wchar_t new_password[PASSWORD_MAX_LENGTH]; // 存储新密码
	wchar_t name[NAME_MAX_LENGTH]; // 存储用户名
	int found = 0; // 标志，用于标识是否找到用户

	FILE* file; // 文件指针
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\manager_account_information.txt", L"r+, ccs=UTF-8"); // 打开文件

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
	// 读取用户名
	gotoxy(22, 7);
	fgetws(name, sizeof(name) / sizeof(wchar_t), stdin);
	name[wcslen(name) - 1] = L'\0'; // 去掉换行符

	/*wprintf(L"\t                请输入原密码：");*/

	// 读取原密码
	gotoxy(24, 10);
	fgetws(original_password, sizeof(original_password) / sizeof(wchar_t), stdin);
	original_password[wcslen(original_password)] = L'\0'; // 去掉换行符

	// 加密原密码
	wchar_t encrypt[PASSWORD_MAX_LENGTH];
	wcscpy(encrypt, caesarEncrypt(original_password));

	// 检查文件是否成功打开
	if (err != 0 || file == NULL) {
		wprintf(L"无法打开文件。\n");
		return; // 如果文件打开失败，退出函数
	}

	wchar_t line[MAX_LINE_LENGTH]; // 存储每一行内容

	int line_count = 0; // 行计数器

	// 逐行读取文件内容
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {

		line_count++;; // 行数递增

		wchar_t manager_name[NAME_MAX_LENGTH]; // 存储管理者用户名
		wchar_t manager_password[PASSWORD_MAX_LENGTH]; // 存储管理者密码

		wchar_t* context = NULL; // 用于分割字符串的上下文

		// 分割字符串，获取用户名和密码
		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(manager_name, sizeof(manager_name) / sizeof(manager_name[0]), token, _TRUNCATE);

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(manager_password, sizeof(manager_password) / sizeof(manager_password[0]), token, _TRUNCATE);


		// 检查用户名和密码是否匹配
		if (wcscmp(encrypt, manager_password) == 0 && wcscmp(manager_name, name) == 0) {

			/*wprintf(L"\t                请输入新密码：");*/

			// 读取新密码
			gotoxy(24, 13);
			fgetws(new_password, sizeof(new_password) / sizeof(wchar_t), stdin);
			new_password[wcslen(new_password) - 1] = L'\0'; // 去掉换行符

			// 加密新密码
			wchar_t new_encrypt[PASSWORD_MAX_LENGTH];
			wcscpy(new_encrypt, caesarEncrypt(new_password));

			wchar_t n_line[MAX_LINE_LENGTH]; // 存储新信息行
			
			// 拼接新信息
			swprintf(n_line, MAX_LINE_LENGTH, L"%ls,%ls\0", manager_name, new_encrypt);

			fclose(file); // 关闭文件

			wchar_t filename[] = L"C:\\Users\\swp\\Desktop\\manager_account_information.txt"; // 文件名

			// 删除原有行并添加新行
			delete_line(filename, line_count);
			append_line(filename, n_line);

			found = 1; // 标记找到用户
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

			break; // 找到后退出循环
		}
	}
	
	// 如果未找到用户，提示错误信息
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

		

		fclose(file); // 确保文件关闭
		Sleep(3000); // 暂停3秒
		return; // 退出函数
	}
}

