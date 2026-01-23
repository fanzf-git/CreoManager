#include <iostream>
#include <conio.h>
#include <windows.h>
#include <shlwapi.h>
#include "../OdaNative/OdaNativeApi.h"

#pragma comment(lib, "shlwapi.lib")

int main()
{
    // 设置 ODA SDK 资源文件路径（.tx 文件）
    // 获取可执行文件所在目录
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    PathRemoveFileSpecW(exePath);
    
    // 设置环境变量，指向可执行文件目录（.tx 文件应该在这里）
    std::wstring resourcePath = exePath;
    SetEnvironmentVariableW(L"ODA_RESOURCE_PATH", resourcePath.c_str());
    
    std::wcout.imbue(std::locale(""));
    std::wcout << L"=== OdaNative 测试程序 ===" << std::endl;
    std::wcout << L"可执行文件目录: " << exePath << std::endl;
    std::wcout << std::endl;

    // 测试 1: 初始化 ODA（不使用窗口句柄）
    std::wcout << L"测试 1: 初始化 ODA..." << std::endl;
    bool initResult = Oda_Initialize(nullptr);
    if (initResult)
    {
        std::wcout << L"  [OK] ODA 初始化成功" << std::endl;
    }
    else
    {
        std::wcout << L"  [FAIL] ODA 初始化失败" << std::endl;
        std::wcout << L"按任意键退出..." << std::endl;
        _getch();
        return 1;
    }
    std::wcout << std::endl;

    // 测试 2: 创建 Box
    std::wcout << L"测试 2: 创建 Box (长度=100, 宽度=50, 高度=30)..." << std::endl;
    OdaBoxParam boxParam;
    boxParam.length = 100.0;
    boxParam.width = 50.0;
    boxParam.height = 30.0;
    
    bool boxResult = Oda_CreateOrUpdateBox(&boxParam);
    if (boxResult)
    {
        std::wcout << L"  [OK] Box 创建成功" << std::endl;
    }
    else
    {
        std::wcout << L"  [FAIL] Box 创建失败" << std::endl;
    }
    std::wcout << std::endl;

    // 测试 3: 创建 Cylinder
    std::wcout << L"测试 3: 创建 Cylinder (半径=25, 高度=50)..." << std::endl;
    OdaCylinderParam cylParam;
    cylParam.radius = 25.0;
    cylParam.height = 50.0;
    
    bool cylResult = Oda_CreateOrUpdateCylinder(&cylParam);
    if (cylResult)
    {
        std::wcout << L"  [OK] Cylinder 创建成功" << std::endl;
    }
    else
    {
        std::wcout << L"  [FAIL] Cylinder 创建失败" << std::endl;
    }
    std::wcout << std::endl;

    // 测试 4: 获取高度
    std::wcout << L"测试 4: 获取当前高度..." << std::endl;
    double height = Oda_GetHeight();
    std::wcout << L"  当前高度: " << height << std::endl;
    std::wcout << std::endl;

    std::wcout << L"=== 所有测试完成 ===" << std::endl;
    std::wcout << L"按任意键退出..." << std::endl;
    _getch();

    return 0;
}
