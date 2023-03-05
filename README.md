- [1.职工管理系统的C++实现介绍](#1职工管理系统的c实现介绍)
- [2.创建项目](#2创建项目)
- [3.创建管理类](#3创建管理类)
- [4.实现菜单功能](#4实现菜单功能)
  - [4.1 添加成员函数](#41-添加成员函数)
  - [4.2 菜单功能实现](#42-菜单功能实现)
  - [4.3 菜单功能验证](#43-菜单功能验证)
- [5.退出功能实现](#5退出功能实现)
  - [5.1提供功能接口](#51提供功能接口)
  - [5.2添加退出功能](#52添加退出功能)
  - [5.3退出功能测试](#53退出功能测试)
- [6.增加新职工](#6增加新职工)
  - [6.1创建职工抽象类](#61创建职工抽象类)
  - [6.2创建普通员工类](#62创建普通员工类)
  - [6.3创建经理类](#63创建经理类)
  - [6.4创建老板类](#64创建老板类)
  - [6.5测试多态](#65测试多态)


# 1.职工管理系统的C++实现介绍

&emsp;&emsp;这是根据b站的[黑马程序员](https://www.bilibili.com/video/BV1et411b73Z?p=147&vd_source=a47e14fad0ef244c0f37adf4f02401d0)视频学习的职工管理系统的项目，主要用来学习多态的相关知识。

&emsp;&emsp;职工管理系统可以用来管理公司内所有成员的信息，本教程主要利用C++来实现一个基于多态的职工管理系统。

&emsp;&emsp;公司中职工分为三类：普通员工、经理、老板，显示信息时，需要显示职工编号、职工姓名、职工岗位、以及职责。

- 普通员工职责：完成经理交给的任务；
- 经理职责：完成老板交给的任务；
- 老板职责：管理公司所有事务；

管理系统中需要实现以下功能：

- 退出管理系统：退出当前管理系统；
- 增加职工信息：实现批量添加职工信息，将信息录入到文件中，职工信息为：职工编号、姓名、部门编号；
- 显示职工信息：显示公司内部所有职工的信息；
- 删除离职职工： 按照编号删除指定的职工；
- 修改职工信息： 按照编号修改职工个人信息；
- 查找职工信息： 按照职工的编号或者职工姓名进行查找相关的人员信息；
- 按照编号排序： 按照职工编号，进行排序，排序规则由用户指定；
- 清空所有文档：清空文件中记录的所有职工信息（清空前要再次确认，防止误删）

职工管理系统界面如下：
![Image text](./pic/1_1_1_%E8%81%8C%E5%B7%A5%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F%E7%95%8C%E9%9D%A2.png)


# 2.创建项目
&emsp;&emsp;我是用CMake进行代码编译的，所以需要配置CMakeLists.txt文件，如下：

```cpp
cmake_minimum_required(VERSION 2.8)
project(CPP)
include_directories(
    include 
)
# user define
aux_source_directory(src DIR_SRCS)
add_library(SRC ${DIR_SRCS})

add_executable(main main.cpp)
target_link_libraries(main SRC)
```
创建目录文件夹如下：

```
➜  employee_managemente_system git:(master) ✗ tree
.
├── build
├── CMakeLists.txt
├── include
├── main.cpp
├── pic
├── README.md
└── src

4 directories, 4 files
```
`include`用于保存.h头文件，`src`用于保存.cpp源文件，`build`用于保存编译后的文件。

# 3.创建管理类
&emsp;&emsp;接下来开始正式的代码编写，首先创建一个管理类，起名字叫做`WorkerManager`，主要负责内容如下：

- 与用户的沟通菜单界面；
- 对职工的增删改查操作；
- 与文件的读写交互；

在`include`中创建`workerManager.h`，内容如下：

```cpp
#pragma once
#include <iostream>
class WorkerManager
{
public:
    // 构造函数
    WorkerManager();
    // 析构函数
    ~WorkerManager();
};
```
在`src`中创建`workerManager.cpp`，内容如下：

```cpp
#include "workerManager.h"
// 构造函数
WorkerManager::WorkerManager()
{
}
// 析构函数
WorkerManager::~WorkerManager()
{
}
```
# 4.实现菜单功能
功能描述：设计一个用于与用户交互的菜单。
## 4.1 添加成员函数
&emsp;&emsp;在`workerManager.h`管理类中`WorkerManager`添加一个成员函数`void Show_Menu()`:
```cpp
// 显示菜单
void Show_Menu();
```
&emsp;&emsp;在`workerManager.cpp`管理类中`WorkerManager`添加函数实现`void Show_Menu()`:
```cpp
void WorkerManager::Show_Menu()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "***********欢迎使用职工管理系统！*********" << std::endl;
    std::cout << "**************0.退出管理程序 *************" << std::endl;
    std::cout << "**************1.增加职工信息 *************" << std::endl;
    std::cout << "**************2.显示职工信息 *************" << std::endl;
    std::cout << "**************3.删除职工信息 *************" << std::endl;
    std::cout << "**************4.修改职工信息 *************" << std::endl;
    std::cout << "**************5.查找职工信息 *************" << std::endl;
    std::cout << "**************6.按照编号排序 *************" << std::endl;
    std::cout << "**************7.清空所有文档 *************" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << std::endl;
}
```
## 4.2 菜单功能实现
&emsp;&emsp;在`main.cpp`中对显示菜单功能进行测试：

```cpp
#include "workerManager.h"

int main(int argc, char const *argv[])
{
    system("clear"); // 使用前先清屏
    WorkerManager wm;
    wm.Show_Menu();
    return 0;
}
```

## 4.3 菜单功能验证
![Image test](./pic/4_1_1_菜单功能实现.png)

# 5.退出功能实现
## 5.1提供功能接口
&emsp;&emsp;在主函数中设计所有功能接口，其中包含退出功能。用switch来实现；
```cpp
int main(int argc, char const *argv[])
{
    system("clear"); // 使用前先清屏
    WorkerManager wm;
    int choice = 0; // 提供一个选择功能的接口
    while (true)
    {
        wm.Show_Menu(); // 显示一个菜单
        std::cout << "请输入您的选项：" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 0: // 退出系统
            break;
        case 1: // 添加职工
            break;
        case 2: // 显示职工
            break;
        case 3: // 删除职工
            break;
        case 4: // 修改职工
            break;
        case 5: // 查找职工
            break;
        case 6: // 职工排序
            break;
        case 7: // 清空文档
            break;
        default:
            break;
        }
    }
}
```
## 5.2添加退出功能
&emsp;&emsp;在`workerManager.h`管理类中`WorkerManager`添加函数声明`void exitSystem()`:
```cpp
// 退出系统
void exitSystem();
```
&emsp;&emsp;在`workerManager.cpp`管理类中`WorkerManager`添加函数实现`void Show_Menu()`:
```cpp
// 退出系统
void WorkerManager::exitSystem()
{
    std::cout << "欢迎下次再使用！" << std::endl;
    this->clear_window();
    exit(0);
}
```
&emsp;&emsp;其中`clear_window`函数如下：
```cpp
// 清屏操作
void WorkerManager::clear_window()
{
    std::string str;
    std::cout << "按回车键清屏！" << std::endl;
    system("read a");
    system("clear");
}
```

## 5.3退出功能测试
![Image text](./pic/5_3_1_退出功能测试.png)

# 6.增加新职工
## 6.1创建职工抽象类
&emsp;&emsp;职工的分类为普通员工、经理、老板，将三种职工抽象到一个`worker`类,利用多态管理不同职工类型；

&emsp;&emsp;职工属性分为：职工编号、职工姓名、职工所在部门编号。

&emsp;&emsp;职工的行为为：岗位职责描述，获取岗位名称；

&emsp;&emsp;首先在`include`文件夹中创建`worker.h`文件，并创建`Worker`类:

```cpp
#pragma once
#include <iostream>

// Worker是一个抽象类
class Worker
{
public:
    // 显示个人信息
    virtual void showInfo() = 0; // 纯虚函数，在基类中不做任何实现
    // 获取岗位名称
    virtual std::string getDeptName() = 0; // 纯虚函数，不做任何实现
    int m_Id;                              // 职工编号
    std::string m_Name;                    // 职工姓名
    int m_DeptId;                          // 职工所在部门名称编号
};
```

&emsp;&emsp;这里是建立了一个抽象类，里面有两个纯虚函数，在基类中不做实现，在派生类（子类）中必须去实现。这些公共的行为和属性，可以在基类中定义好。

## 6.2创建普通员工类

&emsp;&emsp;首先在`include`文件夹中创建`employee.h`文件，在`src`文件夹创建`employee.cpp`源文件。定义并实现`Employee`类，其需要公有继承`Worker`类，并实现其中的虚函数。
`employee.h`文件：
```cpp
#pragma once
#include <iostream>
#include "worker.h"

class Employee : public Worker
{
private:
    /* data */
public:
    Employee(int id, std::string name, int dId);
    // 显示个人信息
    virtual void showInfo();
    // 获取岗位名称
    virtual std::string getDeptName();
};
```
`employee.cpp`文件：
```cpp
#include "employee.h"

// 构造函数
Employee::Employee(int id, std::string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

// 显示个人信息
void Employee::showInfo()
{
    std::cout << "职工编号：" << this->m_Id
              << "\t职工姓名：" << this->m_Name
              << "\t部门编号：" << this->m_DeptId
              << "\t岗位名称：" << this->getDeptName()
              << "\t岗位职责：完成经理交给的任务" << std::endl;
}
// 获取岗位名称
std::string Employee::getDeptName()
{
    return std::string("员工");
}
```

## 6.3创建经理类

&emsp;&emsp;首先在`include`文件夹中创建`manager.h`文件，在`src`文件夹创建`manager.cpp`源文件。定义并实现`Manager`类，其需要公有继承`Worker`类，并实现其中的虚函数。
`manager.h`文件：
```cpp
#pragma once
#include <iostream>
#include "worker.h"

class Manager : public Worker
{
private:
    /* data */
public:
    Manager(int id, std::string name, int dId);
    // 显示个人信息
    virtual void showInfo();
    // 获取岗位名称
    virtual std::string getDeptName();
};
```

`manager.cpp`文件：
```cpp
#include "manager.h"

// 构造函数
Manager::Manager(int id, std::string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

// 显示个人信息
void Manager::showInfo()
{
    std::cout << "职工编号：" << this->m_Id
              << "\t职工姓名：" << this->m_Name
              << "\t部门编号：" << this->m_DeptId
              << "\t岗位名称：" << this->getDeptName()
              << "\t岗位职责：完成老板交给的任务" << std::endl;
}
// 获取岗位名称
std::string Manager::getDeptName()
{
    return std::string("经理");
}
```

## 6.4创建老板类

&emsp;&emsp;首先在`include`文件夹中创建`boss.h`文件，在`src`文件夹创建`boss.cpp`源文件。定义并实现`Boss`类，其需要公有继承`Worker`类，并实现其中的虚函数。
`boss.h`文件：
```cpp
#pragma once
#include <iostream>
#include "worker.h"

class Boss : public Worker
{
private:
    /* data */
public:
    Boss(int id, std::string name, int dId);
    // 显示个人信息
    virtual void showInfo();
    // 获取岗位名称
    virtual std::string getDeptName();
};
```

`boss.cpp`文件：

```cpp
#include "boss.h"

// 构造函数
Boss::Boss(int id, std::string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

// 显示个人信息
void Boss::showInfo()
{
    std::cout << "职工编号：" << this->m_Id
              << "\t职工姓名：" << this->m_Name
              << "\t部门编号：" << this->m_DeptId
              << "\t岗位名称：" << this->getDeptName()
              << "\t岗位职责：给经理安排任务" << std::endl;
}
// 获取岗位名称
std::string Boss::getDeptName()
{
    return std::string("老板");
}
```

## 6.5测试多态

&emsp;&emsp;测试多态代码是否正确，如下：

```cpp
    Worker *worker = NULL;
    worker = new Boss(1, "刘备", 3);
    worker->showInfo();
    delete worker;

    worker = new Manager(2, "关羽", 2);
    worker->showInfo();
    delete worker;

    worker = new Employee(3, "张飞", 1);
    worker->showInfo();
    delete worker;
```

输出结果如下：
![Image test](./pic/6_5_1_%E5%A4%9A%E6%80%81%E6%B5%8B%E8%AF%95%E7%BB%93%E6%9E%9C.png)