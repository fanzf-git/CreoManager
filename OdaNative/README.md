# OdaNative 项目代码结构说明

## 项目概述

OdaNative 是一个 C++ 原生 DLL 项目，负责直接调用 ODA SDK 的 DLL，提供绘制图形功能。

## 项目结构

### 核心文件

#### 1. OdaInitilize.h / OdaInitilize.cpp
- **功能**：ODA SDK 的初始化和激活管理
- **类说明**：
  - `OdaSystemServices`：自定义 SystemServices 类，继承自 `RxSystemServicesImpl`，在构造函数中执行 ODA 激活
  - `OdaInitializer`：初始化管理类，提供单例模式的初始化和清理功能
- **激活信息**：使用 ODA SDK 提供的 `OdActivationInfo` 文件（位于 `$(UserOdaLib)\ThirdParty\activation\OdActivationInfo`）

#### 2. OdaEngine.h / OdaEngine.cpp
- **功能**：绘制图形功能
- **主要功能**：
  - 创建和更新 Box（长方体）
  - 创建和更新 Cylinder（圆柱体）
  - 触发重绘
  - 获取图形属性（如高度）

## 使用流程

### 1. 初始化 ODA SDK

在程序启动时，首先需要初始化 ODA SDK：

```cpp
// 初始化 ODA（会自动进行激活）
if (!OdaInitializer::Initialize())
{
    // 初始化失败，处理错误
    return false;
}
```

### 2. 使用模块1：绘制图形

```cpp
// 获取 OdaEngine 实例并初始化
OdaEngine& engine = OdaEngine::Instance();
if (!engine.Initialize(hwnd))  // hwnd 可以为 nullptr
{
    // 初始化失败
    return false;
}

// 创建 Box
BoxParam boxParam;
boxParam.length = 100.0;
boxParam.width = 50.0;
boxParam.height = 30.0;
engine.CreateOrUpdateBox(boxParam);

// 创建 Cylinder
CylinderParam cylParam;
cylParam.radius = 25.0;
cylParam.height = 50.0;
engine.CreateOrUpdateCylinder(cylParam);

// 触发重绘
engine.Redraw();
```

### 3. 清理资源

在程序退出时，清理 ODA SDK：

```cpp
// 清理 ODA SDK
OdaInitializer::Cleanup();
```

## 注意事项

1. **激活信息**：激活信息从 ODA SDK 提供的 `OdActivationInfo` 文件中读取（位于 `$(UserOdaLib)\ThirdParty\activation\OdActivationInfo`）
2. **初始化顺序**：必须先调用 `OdaInitializer::Initialize()`，然后才能使用其他模块
3. **线程安全**：当前实现使用单例模式，但不保证线程安全，如需多线程使用，请添加适当的同步机制
4. **错误处理**：所有函数都返回 bool 值表示成功/失败，调用者应检查返回值
5. **资源管理**：`OdaEngine` 使用智能指针管理 ODA 对象，无需手动释放

## 编译配置

项目已配置使用 `ThirdParty.props` 中定义的 `UserOdaLib` 宏，指向：
```
$(SolutionDir)\packages\Kernel_vc17_amd64dll_26.12
```

所有包含目录和库目录都使用该宏，便于维护和迁移。

## 依赖关系

- ODA SDK 26.12
- Windows SDK
- Visual Studio 2022 (v143 工具集)
