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

//用户账户信息
struct user_information
{
	char name[NAME_MAX_LENGTH]; 
	char password[PASSWORD_MAX_LENGTH];
	struct user_information* next;
};

//管理员账户信息
struct manager_information
{
	char name[NAME_MAX_LENGTH];
	char password[PASSWORD_MAX_LENGTH];
	struct user_information* next;
};

//图书信息
struct books_information
{
	char location[MAX_BOOKS_LOCATION];
	char name[MAX_BOOKS_LOCATION];
	char author[MAX_BOOKS_AUTHOR];
	char ISBN[MAX_BOOKS_ISBN];
	char whether[MAX_BOOKS_WHETHER];
	char borrow_name[NAME_MAX_LENGTH];
	char borrow_data[MAX_DATA];
	char return_date[MAX_DATA];
	struct books_information* next;
};

// 链表头指针
struct user_information* uhead = NULL;
struct manager_information* mhead = NULL;


//管理员注册验证码
char RIGHT_AUTH_CODE[4] = { "1234" };



void append_line(const wchar_t* filename, const wchar_t* new_line) {
	// 打开指定的文件，以追加模式打开，使用UTF-8编码
	FILE* file = _wfopen(filename, L"a, ccs=UTF-8");

	// 检查文件是否成功打开
	if (!file) {
		wprintf(L"无法打开文件以追加: %ls\n", filename); // 输出错误信息
		return; // 如果文件打开失败，退出函数
	}
	// 将新行写入文件
	fputws(new_line, file);
	// 在新行后添加换行符，以保持文件格式
	fputws(L"\n", file);

	fclose(file); // 关闭文件，确保数据写入完成

	
}

void delete_line(const wchar_t* filename, int line_to_delete) {
	// 打开指定的文件，以读取模式打开，使用UTF-8编码
	FILE* file = _wfopen(filename, L"r, ccs=UTF-8");

	// 检查文件是否成功打开
	if (!file) {
		wprintf(L"无法打开文件: %ls\n", filename); // 输出错误信息
		return; // 如果文件打开失败，退出函数
	}

	// 使用动态数组存储文件内容
	wchar_t** lines = NULL; // 指向每一行的指针数组
	size_t count = 0; // 行计数器

	// 读取文件内容
	wchar_t buffer[1024]; // 缓冲区，用于存储每一行
	while (fgetws(buffer, sizeof(buffer) / sizeof(wchar_t), file)) {
		// 重新分配内存以存储新行
		lines = realloc(lines, (count + 1) * sizeof(wchar_t*));

		lines[count] = _wcsdup(buffer); // 复制当前行到动态数组

		count++; // 增加行计数
	}

	fclose(file); // 关闭文件

	// 删除指定行
	// 检查行号是否在有效范围内
	if (line_to_delete < 1 || line_to_delete > count) {
		wprintf(L"行号超出范围\n"); // 输出错误信息

		// 释放已分配的内存
		for (size_t i = 0; i < count; i++) {
			free(lines[i]);
		}
		free(lines); // 释放行指针数组
		return; // 退出函数
	}

	// 释放要删除的行的内存
	free(lines[line_to_delete - 1]);

	// 移动后面的行，覆盖被删除的行
	for (size_t i = line_to_delete; i < count; i++) {
		lines[i - 1] = lines[i]; // 将后续行向前移动
	}
	count--; // 更新行数

	// 重新打开文件以写入模式
	file = _wfopen(filename, L"w, ccs=UTF-8");

	// 检查文件是否成功打开
	if (!file) {
		wprintf(L"无法打开文件以写入: %ls\n", filename); // 输出错误信息

		// 释放内存
		for (size_t i = 0; i < count; i++) {
			free(lines[i]);
		}
		free(lines); // 释放行指针数组
		return; // 退出函数
	}

	// 写回剩余行
	for (size_t i = 0; i < count; i++) {
		fputws(lines[i], file); // 将每一行写入文件
		free(lines[i]); // 释放内存
	}
	free(lines); // 释放行指针数组
	fclose(file); // 关闭文件

	
}

//密码加密
wchar_t* caesarEncrypt(const wchar_t* password) {
	static wchar_t encrypted[256]; // 假设加密后的字符串不会超过255个字符
	int i, letter_shift = 3, digit_shift = 7;

	for (i = 0; password[i] != L'\0'; i++) {
		wchar_t c = password[i];
		// 对小写字母进行加密
		if (c >= L'a' && c <= L'z') {
			encrypted[i] = (c - L'a' + letter_shift) % 26 + L'a';
		}
		// 对大写字母进行加密
		else if (c >= L'A' && c <= L'Z') {
			encrypted[i] = (c - L'A' + letter_shift) % 26 + L'A';
		}
		// 对数字字符进行加密
		else if (c >= L'0' && c <= L'9') {
			encrypted[i] = (c - L'0' + digit_shift) % 10 + L'0';
		}
		else {
			encrypted[i] = c; // 非字母和数字字符不加密
		}
	}
	encrypted[i] = L'\0'; // 终止符

	return encrypted; // 返回加密后的字符串
}

void HideCursor(int HIDE) {
	CONSOLE_CURSOR_INFO cursor_info = { 1, HIDE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void books_search(const wchar_t* search_term) {
	int count = 0;
	FILE* file; // 文件指针，用于操作书籍信息文件
	// 尝试以读取模式打开书籍信息文件，使用UTF-8编码
	errno_t err = _wfopen_s(&file, L"C:\\Users\\swp\\Desktop\\books_information.txt", L"r, ccs=UTF-8");

	// 检查文件是否成功打开
	if (err != 0 || file == NULL) {
		printf("无法打开文件。\n"); // 提示无法打开文件
		return; // 退出函数
	}

	wchar_t line[MAX_LINE_LENGTH]; // 存储每一行的内容
	int col_width = 10;
	int found = 0; // 标志，用于标识是否找到匹配的书籍
	
	
	
	//// 逐行读取文件内容
	while (fgetws(line, sizeof(line) / sizeof(wchar_t), file)) {
		// 用逗号分割每一行，提取书籍信息
		wchar_t position[MAX_BOOKS_LOCATION]; // 存储书籍位置
		wchar_t name[MAX_BOOKS_NAME]; // 存储书籍名称
		wchar_t author[MAX_BOOKS_AUTHOR]; // 存储作者或出版社信息
		wchar_t ISBN[MAX_BOOKS_ISBN]; // 存储ISBN
		wchar_t whether[MAX_BOOKS_WHETHER]; // 存储是否被借阅信息
		wchar_t borrow_name[NAME_MAX_LENGTH]; // 存储是否被借阅信息
		wchar_t borrow_data[MAX_DATA]; // 存储是否被借阅信息
		wchar_t return_data[MAX_DATA]; // 存储是否被借阅信息
		wchar_t* context = NULL; // 用于分割字符串的上下文

		// 分割字符串，获取书籍信息
		wchar_t* token = wcstok(line, L",", &context);
		wcsncpy_s(position, sizeof(position) / sizeof(position[0]), token, _TRUNCATE); // 获取书籍位置

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(name, sizeof(name) / sizeof(name[0]), token, _TRUNCATE); // 获取书籍名称

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(author, sizeof(author) / sizeof(author[0]), token, _TRUNCATE); // 获取作者或出版社

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(ISBN, sizeof(ISBN) / sizeof(ISBN[0]), token, _TRUNCATE); // 获取ISBN

		token = wcstok(NULL, L",", &context);
		wcsncpy_s(whether, sizeof(whether) / sizeof(whether[0]), token, _TRUNCATE); // 获取是否被借阅信息

		token = wcstok(NULL, L",", &context);

		if (token != NULL) {
			wcsncpy_s(borrow_name, sizeof(borrow_name) / sizeof(borrow_name[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(borrow_data, sizeof(borrow_data) / sizeof(borrow_data[0]), token, _TRUNCATE);

			token = wcstok(NULL, L",", &context);
			wcsncpy_s(return_data, sizeof(return_data) / sizeof(return_data[0]), token, _TRUNCATE);
		}
		
		
		wchar_t yes[] = L"YES";

		// 检查ISBN是否存在
		if (ISBN != NULL) {
			// 检查搜索关键词是否与ISBN、书名或作者匹配
			
			if (wcscmp(search_term, ISBN) == 0 || strstr(search_term, name) != NULL || strstr(search_term, author) != NULL) {
				// 找到匹配的书籍，打印书籍信息
				if (wcscmp(whether, yes) != 0) {
					whether[wcslen(whether) - 1] = L'\0';
					wprintf(L"||                 书名：%ls                          \t||\n", name);// 打印书名
					wprintf(L"||                 作者or出版社：%ls                   \t||\n", author); // 打印作者或出版社
					wprintf(L"||                 ISBN：%ls                          \t||\n", ISBN); // 打印ISBN
					wprintf(L"||                 位置：%ls                           \t\t||\n", position); // 打印书籍位置
					wprintf(L"||                 是否被借阅：%ls                      \t\t\t||\n", whether); // 打印是否被借阅信息
					printf("*========================================================================*\n");
					count++;
					
				}
				else if (wcscmp(whether, yes) == 0) {
					whether[wcslen(whether)] = L'\0';
					wprintf(L"||                 书名：%ls                          \t||\n", name);// 打印书名
					wprintf(L"||                 作者or出版社：%ls                   \t||\n", author); // 打印作者或出版社
					wprintf(L"||                 ISBN：%ls                          \t||\n", ISBN); // 打印ISBN
					wprintf(L"||                 位置：%ls                           \t\t||\n", position); // 打印书籍位置
					wprintf(L"||                 是否被借阅：%ls                      \t\t||\n", whether); // 打印是否被借阅信息
					wprintf(L"||                 借阅人：%ls                          \t\t||\n", borrow_name);
					wprintf(L"||                 借阅时间：%ls                        \t\t||\n", borrow_data);
					wprintf(L"||                 归还时间：%ls                        \t\t||\n", return_data);
					printf("*========================================================================*\n");
					count++;
					
				}
				
				
				found = 1; // 标记找到书籍
			}
		}
		
	}
	printf("||                             共计找到书籍%d本                          ||\n", count);
	printf("*========================================================================*\n");
	printf("*============================按任意键返回菜单============================*\n");
	printf("*========================================================================*\n");
	// 如果未找到匹配的书籍，提示错误信息
	if (!found) {
		system("cls");
		search(4, 0);
		
		return 0; // 退出函数
	}
	_getch(); // 等待用户输入
	// 关闭文件并检查是否成功关闭
	if (fclose(file)) {
		printf("无法关闭文件。\n"); // 提示无法关闭文件
		exit(0); // 退出程序
	}

}

// 释放链表内存
void free_list(const int load) {
	if (load == 1) {
		struct user_information* current = uhead;
		struct user_information* next;
		while (current != NULL) {
			next = current->next;
			free(current);
			current = next;
		}
	}
	else if (load == 2) {
		struct manager_information* current = mhead;
		struct manager_information* next;
		while (current != NULL) {
			next = current->next;
			free(current);
			current = next;
		}
	}
}

// 添加管理员到链表
void add_manager_to_list(const char* name, const char* password) {
	struct user_information* new_manager = (struct manager_information*)malloc(sizeof(struct manager_information));
	if (new_manager == NULL) {
		printf("内存分配失败！\n");
		return;
	}
	strcpy(new_manager->name, name);
	strcpy(new_manager->password, password);
	new_manager->next = mhead; // 将管理员添加到链表头部
	mhead = new_manager; // 更新头指针
}

// 添加用户到链表
void add_user_to_list(const char* name, const char* password) {
	struct user_information* new_user = (struct user_information*)malloc(sizeof(struct user_information));
	if (new_user == NULL) {
		printf("内存分配失败！\n");
		return;
	}
	strcpy(new_user->name, name);
	strcpy(new_user->password, password);
	new_user->next = uhead; // 将新用户添加到链表头部
	uhead = new_user; // 更新头指针
}

//检查账户信息
int check_account(const char* account, const int load) {
	FILE* fp;
	char faccount[MAX_LINE_LENGTH];

	// 根据 load 参数选择文件
	if (load == 1) {
		if ((fp = fopen("C:\\Users\\swp\\Desktop\\user_account_information.txt", "r")) == NULL) {
			printf("file open error!\n");
			exit(0);
		}
	}
	else if (load == 2) {
		if ((fp = fopen("C:\\Users\\swp\\Desktop\\manager_account_information.txt", "r")) == NULL) {
			printf("file open error!\n");
			exit(0);
		}
	}
	else {
		printf("Invalid load parameter!\n");
		return -1; // 返回错误
	}

	// 逐行读取文件
	while (fgets(faccount, sizeof(faccount), fp) != NULL) {
		// 去掉换行符
		faccount[strcspn(faccount, "\n")] = '\0'; // 替换换行符为字符串结束符

		// 检查用户名和密码是否匹配
		if (strcmp(account, faccount) == 0) {
			fclose(fp);
			return 1; // 找到匹配
		}
	}

	fclose(fp);
	return 0; // 没有找到匹配
}

//密码加密
char* caesarEncrypt_char(const char* password) {
	static char encrypted[256]; // 假设加密后的字符串不会超过255个字符
	int i, letter_shift = 3, digit_shift = 7;

	for (i = 0; password[i] != '\0'; i++) {
		char c = password[i];
		// 对小写字母进行加密
		if (c >= 'a' && c <= 'z') {
			encrypted[i] = (c - 'a' + letter_shift) % 26 + 'a';
		}
		// 对大写字母进行加密
		else if (c >= 'A' && c <= 'Z') {
			encrypted[i] = (c - 'A' + letter_shift) % 26 + 'A';
		}
		// 对数字字符进行加密
		else if (c >= '0' && c <= '9') {
			encrypted[i] = (c - '0' + digit_shift) % 10 + '0';
		}
		else {
			encrypted[i] = c; // 非字母和数字字符不加密
		}
	}
	encrypted[i] = '\0'; // 终止符

	return encrypted; // 返回加密后的字符串
}

//储存账户信息
void store_account_imformation(const char* account, const int load) {
	FILE* fp;
	if (load == 1) {
		if ((fp = fopen("C:\\Users\\swp\\Desktop\\user_account_information.txt", "a")) == NULL) {
			printf("file open error!\n");
			exit(0);
		}

		fprintf(fp, "%s\n", account);

		if (fclose(fp)) {
			printf("file close error!\n");
			exit(0);
		}
	}
	else if (load == 2) {
		if ((fp = fopen("C:\\Users\\swp\\Desktop\\manager_account_information.txt", "a")) == NULL) {
			printf("file open error!\n");
			exit(0);
		}

		fprintf(fp, "%s\n", account);

		if (fclose(fp)) {
			printf("file close error!\n");
			exit(0);
		}
	}


	return 1;
}

//注册界面
int register_menu() {
	char name[NAME_MAX_LENGTH]; // 使用字符数组来存储用户名
	char password[PASSWORD_MAX_LENGTH]; // 使用字符数组来存储密码
	char auth_code[5]; // 使用字符数组来储存授权码
	char account[ACCOUNT_MAX_LENGTH];


	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                       <*- 注册 —*>                      ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 账户：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||            · 授权码：                                   ||\n");
	printf("||                                                         ||\n");
	printf("||            · 密码：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||  <* 提示：授权码填4位数为管理员注册,填0即为用户注册 *>  ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");
	
	gotoxy(22, 7);
	scanf_s("%s", name, NAME_MAX_LENGTH); // 读取用户名，确保不越界
	
	gotoxy(24, 9);
	scanf_s("%s", auth_code, 5);

	gotoxy(22, 11);
	hide_password(password, PASSWORD_MAX_LENGTH); // 隐藏密码输入

	char* encrypt = caesarEncrypt_char(password);

	snprintf(account, ACCOUNT_MAX_LENGTH, "%s,%s", name, encrypt);
	
	if (strcmp(auth_code, "0") == 0) {
		int load = 1;
		store_account_imformation(account, load);
		add_user_to_list(name, encrypt); // 将用户信息添加到链表
		return 1;
	}
	else if (strcmp(auth_code, RIGHT_AUTH_CODE) == 0) {
		int load = 2;
		store_account_imformation(account, load);
		add_user_to_list(name, encrypt); // 将管理员信息添加到链表
		return 2;
	}
	else if ((strcmp(auth_code, RIGHT_AUTH_CODE) != 0) && (strcmp(auth_code, "0") != 0)) {
		return 3;
	}
}

//管理员登陆界面
int manager_load_menu() {
	char manager_name[NAME_MAX_LENGTH]; // 使用字符数组来存储用户名
	char manager_password[PASSWORD_MAX_LENGTH]; // 使用字符数组来存储密码
	char account[ACCOUNT_MAX_LENGTH];
	int load = 2;

	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                    <*- 管理员登录 —*>                   ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 账户：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 密码：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                    <*> 最多输入三次                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");

	
	gotoxy(22, 10);
	scanf_s("%s", manager_name, NAME_MAX_LENGTH); // 读取用户名，确保不越界
	gotoxy(22, 13);
	hide_password(manager_password, PASSWORD_MAX_LENGTH); // 隐藏密码输入

	char* encrypt = caesarEncrypt_char(manager_password);
	

	snprintf(account, ACCOUNT_MAX_LENGTH, "%s,%s", manager_name, encrypt);
	if (check_account(account, load)) {
		return 1;
	}
	else {
		return 0;
	}

}

//用户登录界面
int user_load_menu() {
	
	char user_password[PASSWORD_MAX_LENGTH]; // 使用字符数组来存储密码
	char account[ACCOUNT_MAX_LENGTH];
	int load = 1;

	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                     <*- 用户登录 —*>                    ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 账户：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||            · 密码：                                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                    <*> 最多输入三次                     ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");

	gotoxy(22, 10);
	scanf_s("%s", user_name, NAME_MAX_LENGTH); // 读取用户名，确保不越界
	gotoxy(22, 13);
	hide_password(user_password, PASSWORD_MAX_LENGTH); // 隐藏密码输入

	char* encrypt = caesarEncrypt_char(user_password);
	snprintf(account, ACCOUNT_MAX_LENGTH, "%s,%s", user_name, encrypt);
	if (check_account(account, load)) {
		return 1;
	}
	else {
		return 0;
	}
}



//主菜单
void main_menu() {
	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||        <*- 用户登录 —*>       <*- 管理员登录 —*>        ||\n");
	printf("||                                                         ||\n");
	printf("||             请按 1                  请按 2              ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||          <*- 注册 —*>          <*- 退出程序 —*>         ||\n");
	printf("||                                                         ||\n");
	printf("||              请按 3                 请按 4              ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("*===========================================================*\n");
	

	
	return 0;
}

//注册失败菜单
void Landing_failed() {
	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                <*- 登陆失败，请重试 —*>                 ||\n");
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

//注册成功菜单
void enroll(const int a) {
	printf("*===========================================================*\n");
	printf("||         <<·—— 集美大学陈嘉庚图书馆管理系统 ——·>>        ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	printf("||                                                         ||\n");
	if (a == 1) {
		printf("||                <*- 用户注册成功！ —*>                   ||\n");
	}
	else if (a==2) {
		printf("||                <*- 管理员注册成功！ —*>                 ||\n");
	}
	else if (a == 3) {
		printf("||                <*- 注册失败，请重试！ —*>               ||\n");
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



