
# 基于 RSA 和 AES 的加密通信实验

## 简介
本仓库是一个简化的加密通信系统，结合了 RSA 和 AES 两种经典加密算法。RSA 用于密钥分发，AES 用于高效地对数据加密。通过本项目，可以学习并实践加密通信的基本原理和实现。需要注意的是，本仓库是实现的是简单的RSA和AES，没有包括所有的步骤，且RSA密钥位数仅为16位，仅供学习使用。

主要功能包括：
- 使用 RSA 算法生成密钥对并加密 AES 密钥。
- 使用 AES 算法对数据进行加密与解密，支持 CBC 模式和 PKCS#7 填充。
- 完整实现从客户端到服务端的加密通信过程。

## 配置与运行

### 环境需求
- 编译器：支持 C++17 或以上版本的编译器（如 GCC、Clang 或 MSVC）。
- 开发环境：Visual Studio 2022（推荐）或其他支持 C++ 的 IDE。
- 操作系统：Windows/Linux/MacOS。

### 项目依赖
- 无需额外依赖，仅需标准 C++ 库。

### 运行步骤
1. 克隆仓库：
   ```bash
   git clone <仓库地址>
   cd <项目目录>

2. 打开项目：
   使用 vs2022 打开项目文件夹
3. 编译项目：
   在 vs2022 中直接点击“生成解决方案”
4. 运行程序：
   点击 ide 中的调试或执行均可，程序将生成密钥并模拟加密通信，结果在控制台中输出。
5. 输入输出：
   不需要输入，测试代码写在test/main.cpp中；运行结果输出在控制台上。

## 仓库结构
```
EzCryptoCpp/
├── include/                      # 头文件目录
│   ├── crypto_helper.h           # 加密算法辅助函数的声明
│   ├── EzClient.h                # 客户端类声明
│   ├── EzServer.h                # 服务端类声明
├── src/                          # 源文件目录
│   ├── crypto_helper.cpp         # 加密算法辅助函数的实现
│   ├── EzClient.cpp              # 客户端类实现
│   ├── EzServer.cpp              # 服务端类实现
├── tests/                        # 测试目录
│   └── main.cpp
├── .gitignore                    # Git 忽略规则
├── CMakeLists.txt                # CMake 构建配置文件
├── README.md                     # 项目说明文件
```




# Encryption Communication Experiment Based on RSA and AES

## Introduction
This repository provides a simplified encrypted communication system combining the RSA and AES cryptographic algorithms. RSA is used for secure key distribution, and AES is used for efficient data encryption. This project aims to help users understand and practice the basic principles and implementation of encrypted communication. 

Note: This repository implements a simplified version of RSA and AES. The RSA key size is only 16 bits and is intended for learning purposes only.

Key features include:
- Generating key pairs using the RSA algorithm and encrypting AES keys.
- Encrypting and decrypting data using the AES algorithm with CBC mode and PKCS#7 padding.
- Fully implementing the encryption communication process from client to server.

## Configuration and Execution

### Requirements
- Compiler: A C++17 or later compliant compiler (e.g., GCC, Clang, or MSVC).
- Development Environment: Visual Studio 2022 (recommended) or any C++ IDE.
- Operating System: Windows/Linux/MacOS.

### Dependencies
- No external dependencies are required; only the standard C++ library is used.

### Steps to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <project-directory>


2. Open the project:
   Open the project folder in Visual Studio 2022.

3. Build the project:
   In Visual Studio 2022, click "Build Solution."

4. Run the program:
   Use the IDE to debug or execute the program. The application will generate keys and simulate encrypted communication. Results will be displayed in the console.

5. Input/Output:
   - No user input is required; test code is written in `tests/main.cpp`.
   - The execution results will be printed to the console.

## Repository Structure
```
EzCryptoCpp/
├── include/                      # Header files directory
│   ├── crypto_helper.h           # Declarations for cryptographic utility functions
│   ├── EzClient.h                # Client class declarations
│   ├── EzServer.h                # Server class declarations
├── src/                          # Source files directory
│   ├── crypto_helper.cpp         # Implementation of cryptographic utility functions
│   ├── EzClient.cpp              # Client class implementation
│   ├── EzServer.cpp              # Server class implementation
├── tests/                        # Tests directory
│   └── main.cpp                  # Test code for encryption and decryption
├── .gitignore                    # Git ignore rules
├── CMakeLists.txt                # CMake build configuration file
├── README.md                     # Project documentation
```