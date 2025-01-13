#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void HideCursor(int HIDE); //隐藏光标
void hide_password(char* password, int max_length); //隐藏密码
wchar_t* caesarEncrypt(const wchar_t* password); //凯撒加密——wchar
void append_line(const wchar_t* filename, const wchar_t* new_line); //追加新行
void delete_line(const wchar_t* filename, int line_to_delete); //删除当前行
void books_search(const wchar_t* search_term); //搜索书籍信息

void add_user_to_list(const char* name, const char* password); //添加用户到链表
void add_manager_to_list(const char* name, const char* password); //添加管理员到链表
void free_list(const int load); //释放链表内存
void main_menu(); //主菜单
int register_menu(); //注册系统
void store_account_imformation(const char* account, const int load); //储存账户信息
int check_account(const char* account, const int load); //检查账户
int user_load_menu(); //用户登录系统
int manager_load_menu(); //管理员登陆系统
char* caesarEncrypt_char(const char* password); //凯撒加密——char
void gotoxy(int x, int y);
void Landing_failed();
void enroll(const int a);
void search(const int b, const int a);
//aaaaa
#endif