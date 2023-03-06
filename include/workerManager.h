#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "../empFile.txt"
class WorkerManager
{
public:
    // 构造函数
    WorkerManager();
    // 显示菜单
    void Show_Menu();
    // 退出系统
    void exitSystem();
    // 清屏操作
    void clear_window();
    // 添加职工
    void Add_Emp();
    // 保存信息
    void save();
    // 获取职工人数
    int get_EmpNum();
    // 初始化员工
    void init_Emp();
    // 显示职工
    void Show_Emp();
    // 删除职工
    void Del_Emp();
    // 职工是否存在
    int IsExist(int id);
    // 修改职工
    void Mod_Emp();
    // 查找职工
    void Find_Emp();
    // 职工排序
    void Sort_Emp();
    // 清空文档
    void Clean_File();
    // 记录职工人数
    int m_EmpNum;
    // 职工数组指针
    Worker **m_EmpArray;
    // 标志文件是否为空
    bool m_FileIsEmpty;
    // 析构函数
    ~WorkerManager();
};