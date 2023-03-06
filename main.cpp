#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

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
            wm.exitSystem();
            break;
        case 1: // 添加职工
            wm.Add_Emp();
            break;
        case 2: // 显示职工
            wm.Show_Emp();
            break;
        case 3: // 删除职工
            wm.Del_Emp();
            break;
        case 4: // 修改职工
            wm.Mod_Emp();
            break;
        case 5: // 查找职工
            wm.Find_Emp();
            break;
        case 6: // 职工排序
            wm.Sort_Emp();
            break;
        case 7: // 清空文档
            wm.Clean_File();
            break;
        default:
            break;
        }
    }
    return 0;
}
