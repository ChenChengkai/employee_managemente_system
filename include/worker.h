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
