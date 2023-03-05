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