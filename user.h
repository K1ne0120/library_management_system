#ifndef USER_H
#define USER_H

#define NAME_MAX_LENGTH 30 //账户最大长度
extern char user_name[NAME_MAX_LENGTH]; // 声明共享变量

void user_menu(); //用户菜单
void search_books_user_menu(); //查阅书籍
void borrow_books_user_menu(const wchar_t* user_name); //借阅书籍
void return_books_user_menu(); //归还书籍
void modify_user_information_menu();  //修改用户信息
void books_search_menu(const int a); //书籍搜索菜单

#endif
