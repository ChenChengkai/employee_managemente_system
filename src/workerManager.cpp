
#include "workerManager.h"
// 构造函数
WorkerManager::WorkerManager()
{
    this->m_EmpNum = 0;
    this->m_EmpArray = NULL;
    this->m_FileIsEmpty = true;
    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);
    // 第一种情况，文件不存在
    if (!ifs.is_open())
    {
        std::cout << "文件不存在！" << std::endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        return;
    }
    // 第二种情况，文件存在但是为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        std::cout << "文件为空！" << std::endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        return;
    }

    // 第三种情况，文件存在，且有数据记录
    int num = this->get_EmpNum();
    this->m_FileIsEmpty = false;
    std::cout << "职工人数为：" << num << std::endl;
    this->m_EmpNum = num;
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    this->init_Emp();
    std::cout << "职工初始化完毕！" << std::endl;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        this->m_EmpArray[i]->showInfo();
    }
}
// 析构函数
WorkerManager::~WorkerManager()
{
}

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

// 清屏操作
void WorkerManager::clear_window()
{
    std::string str;
    std::cout << "按回车键清屏！" << std::endl;
    system("read a");
    system("clear");
}

// 退出系统
void WorkerManager::exitSystem()
{
    std::cout << "欢迎下次再使用！" << std::endl;
    this->clear_window();
    exit(0);
}

void WorkerManager::Add_Emp()
{
    int addNum = 0;
    std::cout << "请输入要添加的职工人数：" << std::endl;
    std::cin >> addNum;

    if (addNum > 0)
    {
        // 记录更新后的空间大小
        int newNum = this->m_EmpNum + addNum;
        std::cout << newNum << std::endl;
        // 开辟新空间
        Worker **newSpace = new Worker *[newNum];
        // 将原先空间的数据先放进来
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        // 添加新的数据
        for (int i = 0; i < addNum; i++)
        {
            int id;           // 职工编号
            std::string name; // 职工姓名
            int did;          // 部门编号
            std::cout << "请输入第" << i + 1 << "个职工的编号：" << std::endl;
            std::cin >> id;
            std::cout << "请输入第" << i + 1 << "个职工的姓名：" << std::endl;
            std::cin >> name;
            std::cout << "请输入第" << i + 1 << "个职工的部门编号：" << std::endl;
            std::cout << "1.员工" << std::endl;
            std::cout << "2.经理" << std::endl;
            std::cout << "3.老板" << std::endl;
            std::cin >> did;
            Worker *worker = NULL;
            switch (did)
            {
            case 1:
                worker = new Employee(id, name, did);
                break;
            case 2:
                worker = new Manager(id, name, did);
                break;
            case 3:
                worker = new Boss(id, name, did);
                break;
            default:
            {
                std::cout << "输入的部门有误！" << std::endl;
                this->clear_window();
                return;
            }
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        // 删除原有空间
        delete[] this->m_EmpArray;
        // 更新新的空间
        this->m_EmpArray = newSpace;
        // 更新职工人数
        this->m_EmpNum = newNum;
        // 更新职工人数不为空
        this->m_FileIsEmpty = false;
        std::cout << "成功添加" << addNum << "名新职工!" << std::endl;
        this->save();
    }
    else
    {
        std::cout << "输入人数无效！" << std::endl;
        this->clear_window();
    }
    this->clear_window();
}

void WorkerManager::save()
{
    std::ofstream ofs(FILENAME, std::ios::out);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << m_EmpArray[i]->m_Name << " "
            << m_EmpArray[i]->m_DeptId << std::endl;
    }
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    std::ifstream ifs(FILENAME, std::ios::in);
    int id;
    std::string name;
    int dId;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }
    return num;
}

void WorkerManager::init_Emp()
{
    std::ifstream ifs(FILENAME, std::ios::in);
    int id;           // 员工id
    std::string name; // 员工姓名
    int dId;          // 部门号
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker *worker = NULL;
        switch (dId)
        {
        case 1:
            worker = new Employee(id, name, dId);
            break;
        case 2:
            worker = new Manager(id, name, dId);
            break;
        case 3:
            worker = new Boss(id, name, dId);
            break;
        default:
            break;
        }
        this->m_EmpArray[index++] = worker;
    }
    ifs.close();
}

void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        std::cout << "文件为空！" << std::endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            // 调用多态调用程序接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    this->clear_window();
}
int WorkerManager::IsExist(int id)
{
    int ret = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            // 找到该职工
            ret = i;
            break;
        }
    }
    return ret;
}
void WorkerManager::Del_Emp()
{
    if (!this->m_FileIsEmpty)
    {
        std::cout << "请输入要删除的职工的编号：" << std::endl;
        int del_id = 0;
        std::cin >> del_id;
        int index = this->IsExist(del_id);
        if (index != -1)
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->save();
            std::cout << "删除成功！" << std::endl;
        }
        else
        {
            std::cout << "改职工不存在，请重新确认！" << std::endl;
        }
    }
    else
    {
        std::cout << "文件不存在或文件为空！" << std::endl;
    }
    this->clear_window();
}

void WorkerManager::Mod_Emp()
{
    if (!this->m_FileIsEmpty)
    {
        std::cout << "请输入要修改的员工编号：" << std::endl;
        int mod_id = -1;
        std::cin >> mod_id;
        int ret = this->IsExist(mod_id);
        if (ret != -1)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Id == mod_id)
                {
                    delete this->m_EmpArray[i];
                    int id;
                    std::string name;
                    int dId;
                    std::cout << "请输入新的职工编号：" << std::endl;
                    std::cin >> id;
                    std::cout << "请输入新的职工姓名：" << std::endl;
                    std::cin >> name;
                    std::cout << "请输入新的职工岗位：" << std::endl;
                    std::cout << "1.员工" << std::endl;
                    std::cout << "2.经理" << std::endl;
                    std::cout << "3.老板" << std::endl;
                    std::cin >> dId;
                    switch (dId)
                    {
                    case 1:
                        this->m_EmpArray[i] = new Employee(id, name, dId);
                        break;
                    case 2:
                        this->m_EmpArray[i] = new Manager(id, name, dId);
                        break;
                    case 3:
                        this->m_EmpArray[i] = new Boss(id, name, dId);
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
            std::cout << "修改完毕！" << std::endl;
            this->save();
        }
        else
        {
            std::cout << "待修改的员工不存在！" << std::endl;
        }
    }
    else
    {
        std::cout << "文件不存在或文件为空！" << std::endl;
    }
    this->clear_window();
}

void WorkerManager::Find_Emp()
{
    if (!this->m_FileIsEmpty)
    {
        int find_mode = -1;
        std::cout << "请选择按那种方式查找：" << std::endl;
        std::cout << "1.按编号查找" << std::endl;
        std::cout << "2.按姓名查找" << std::endl;
        std::cin >> find_mode;
        if (find_mode == 1)
        {
            int id = -1;
            std::cout << "请输入要查找的编号：" << std::endl;
            std::cin >> id;
            int ret = this->IsExist(id);
            if (ret != -1)
            {
                std::cout << "查找成功！职工信息如下：" << std::endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                std::cout << "查无此人！" << std::endl;
            }
        }
        else
        {
            std::string name;
            std::cout << "请输入要查找的姓名：" << std::endl;
            std::cin >> name;
            bool find_flag = false;
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    std::cout << "查找成功！职工信息：";
                    this->m_EmpArray[i]->showInfo();
                    find_flag = true;
                }
            }
            if (!find_flag)
            {
                std::cout << "查无此人！" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "文件不存在或文件为空！" << std::endl;
    }
    this->clear_window();
}

void WorkerManager::Sort_Emp()
{
    if (!this->m_FileIsEmpty)
    {
        int sort_mode = -1;
        std::cout << "请输入排序的顺序：" << std::endl;
        std::cout << "1.顺序" << std::endl;
        std::cout << "2.逆序" << std::endl;
        std::cin >> sort_mode;
        if (sort_mode == 1) // 顺序
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                for (int j = i; j < this->m_EmpNum; j++)
                {
                    if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        Worker *worker = this->m_EmpArray[i];
                        this->m_EmpArray[i] = this->m_EmpArray[j];
                        this->m_EmpArray[j] = worker;
                    }
                }
            }
        }
        else if (sort_mode == 2)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                for (int j = i; j < this->m_EmpNum; j++)
                {
                    if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        Worker *worker = this->m_EmpArray[i];
                        this->m_EmpArray[i] = this->m_EmpArray[j];
                        this->m_EmpArray[j] = worker;
                    }
                }
            }
        }
        else
        {
            std::cout << "输入的顺序有误！" << std::endl;
            this->clear_window();
            return;
        }
        std::cout << "排序成功！" << std::endl;
    }
    else
    {
        std::cout << "文件存在或文件为空！" << std::endl;
    }
    this->save();
    this->Show_Emp();
}

void WorkerManager::Clean_File()
{
    int clean_flag = -1;
    std::cout << "确定清空？" << std::endl;
    std::cout << "1.确定" << std::endl;
    std::cout << "2.返回" << std::endl;
    std::cin >> clean_flag;
    if (clean_flag == 1)
    {
        // 清空文件
        std::ofstream ofs(FILENAME, std::ios::trunc); // 删除文件后创建
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            // 删除堆区的每个职工对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            // 删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;
            this->m_EmpNum = 0;
        }
        std::cout << "清空完成！" << std::endl;
    }
    this->clear_window();
}