
---

# 图书管理系统 / Library Management System

[English Version](#en) | [中文版本](#cn)

---

<a id="cn" name="图书管理系统-cn"></a>

## 📖 图书管理系统 (C语言版)

这是一个基于 C 语言开发的控制台图书管理系统，采用模块化设计，具备完善的用户与管理员权限体系。

### ✨ 核心功能

* **双身份系统**：区分普通用户与管理员，拥有不同的操作权限。
* **账户安全性**：
* 内置 **凯撒加密算法 (Caesar Cipher)** 对密码进行脱敏存储。
* 支持注册与登录验证，防止重复注册。


* **图书管理**：
* 书籍搜索（基于关键词）、增加、删除及修改书籍位置。
* 借阅与归还系统，实时更新书籍状态。


* **用户体验**：
* 使用 Windows API 控制光标隐藏与定位，打造整洁的 UI 界面。
* 集成 `mmsystem.h` 支持背景音乐播放（BGM）。
* 密码输入实时隐藏（以 `*` 显示）。



### 📂 项目结构

| 文件名 | 描述 |
| --- | --- |
| `main.c` | 程序入口，包含 BGM 启动与主循环逻辑。 |
| `functions.c/h` | 通用底层函数：加密、文件读写、链表操作、UI 控制。 |
| `user.c/h` | 用户侧逻辑：查阅书籍、借书、还书、修改个人信息。 |
| `manager.c/h` | 管理员侧逻辑：书籍增删改、用户管理、借阅情况监控。 |

### 🛠️ 环境要求

* **操作系统**: Windows (使用了 `windows.h` 和 `conio.h`)
* **编译器**: 支持 C99 及其以上的编译器 (推荐使用 MSVC/Visual Studio)
* **依赖库**: `Winmm.lib` (用于播放音频)

### 🚀 快速开始

1. 确保你处于 Windows 环境下。
2. 将所有 `.c` 和 `.h` 文件导入到你的集成开发环境 (IDE) 中。
3. 在链接器设置中添加 `winmm.lib`。
4. 编译并运行 `main.c`。
5. **注意**: 请确保音乐文件路径与代码中一致，或将其修改为你的本地路径。

---

<a id="en" name="library-management-system-en"></a>

## 📖 Library Management System (C Language)

A console-based Library Management System developed in C, featuring modular architecture and a robust permission system for Users and Managers.

### ✨ Key Features

* **Dual-Role System**: Separate interfaces and permissions for standard Users and Administrators.
* **Account Security**:
* Integrated **Caesar Cipher** for password encryption and secure storage.
* Registration and login validation to prevent duplicate accounts.


* **Book Management**:
* Search (keyword-based), Add, Delete, and Update book locations.
* Borrowing and Returning system with real-time status updates.


* **User Experience**:
* Utilizes Windows API for cursor manipulation (hiding/positioning) to create a clean TUI.
* Background Music (BGM) support via `mmsystem.h`.
* Masked password input (displays `*` instead of plain text).



### 📂 Project Structure

| File | Description |
| --- | --- |
| `main.c` | Entry point, handles BGM initialization and the main program loop. |
| `functions.c/h` | Core utilities: Encryption, File I/O, Linked list logic, UI control. |
| `user.c/h` | User-side logic: Search, Borrow, Return, and Profile management. |
| `manager.c/h` | Admin-side logic: Book CRUD, User management, and system monitoring. |

### 🛠️ Requirements

* **Operating System**: Windows (dependent on `windows.h` and `conio.h`).
* **Compiler**: C99 or later (Visual Studio/MSVC recommended).
* **Dependencies**: `Winmm.lib` (for audio playback).

### 🚀 Quick Start

1. Ensure you are running on Windows.
2. Import all `.c` and `.h` files into your C/C++ project.
3. Add `winmm.lib` to your linker dependencies.
4. Compile and run `main.c`.
5. **Note**: Update the music file path in `main.c` to match your local file location.

---