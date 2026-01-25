# CreoManager - ODA SDK 集成项目

## 项目简介

CreoManager 是一个基于 ODA (Open Design Alliance) SDK 的 CAD 图形显示和建模演示项目。该项目展示了如何将 ODA SDK 集成到 C# WinForms 应用程序中，实现 3D 模型的创建、显示和交互。

## Git 仓库

https://github.com/fanzf-git/CreoManager

## 系统架构

### 整体架构层次

本项目采用分层架构设计，从上层到下层共分为 4 个层次：

```
┌─────────────────────────────────────────────────────────────┐
│  第 1 层：C# WinForms 应用层                                  │
│  - MainForm.cs          (主窗体，用户交互界面)                │
│  - BimViewEditor.cs     (自定义控件，ODA 绘制容器)           │
│  - Program.cs            (应用程序入口，程序集解析)            │
└─────────────────────────────────────────────────────────────┘
                            ↓ P/Invoke / C++/CLI
┌─────────────────────────────────────────────────────────────┐
│  第 2 层：C++/CLI 包装层                                      │
│  - OdaCliWrapper.dll    (托管程序集)                          │
│    └─ SimpleDraw        (静态类，提供托管接口)                 │
│       - Initialize()     (初始化 ODA 引擎)                    │
│       - CreateOrUpdateBox()     (创建/更新盒子)               │
│       - CreateOrUpdateCylinder() (创建/更新圆柱体)            │
│       - CreateCircle()   (创建圆形)                            │
│       - Redraw()         (触发重绘)                            │
│       - OpenDwg()        (打开 DWG 文件)                       │
└─────────────────────────────────────────────────────────────┘
                            ↓ C API 调用
┌─────────────────────────────────────────────────────────────┐
│  第 3 层：原生 C++ 引擎层                                    │
│  - OdaNative.dll        (原生 C++ DLL)                       │
│    ├─ OdaNativeApi      (纯 C 接口，供 C++/CLI 调用)          │
│    │  - Oda_Initialize()                                      │
│    │  - Oda_CreateOrUpdateBox()                              │
│    │  - Oda_CreateOrUpdateCylinder()                          │
│    │  - Oda_Redraw()                                          │
│    │  - Oda_LoadDwg()                                         │
│    │                                                           │
│    ├─ OdaEngine         (C++ 引擎类，单例模式)                │
│    │  - Initialize()     (初始化数据库和图形系统)              │
│    │  - CreateOrUpdateBox()    (创建 3D 盒子实体)              │
│    │  - CreateOrUpdateCylinder() (创建 3D 圆柱体实体)          │
│    │  - LoadDwg()        (从 DWG 文件加载数据库)               │
│    │  - Redraw()         (触发图形设备更新)                    │
│    │                                                           │
│    └─ OdaInitializer    (ODA SDK 初始化管理)                   │
│       - Initialize()    (初始化 ODA 运行时)                   │
│       - Cleanup()        (清理 ODA 资源)                       │
└─────────────────────────────────────────────────────────────┘
                            ↓ 直接调用
┌─────────────────────────────────────────────────────────────┐
│  第 4 层：ODA SDK 层                                         │
│  - OdDbDatabase         (CAD 数据库，存储几何实体)             │
│  - OdDb3dSolid          (3D 实体对象：Box, Cylinder 等)        │
│  - OdDbCircle           (2D 圆形实体)                          │
│  - OdGsDevice           (图形设备，负责渲染)                   │
│  - OdGiContextForDbDatabase (图形接口上下文)                  │
│  - OdDbGsManager        (图形系统管理器)                       │
└─────────────────────────────────────────────────────────────┘
```

### 详细调用流程

#### 1. 初始化流程

```
MainForm_Load()
    ↓
OdaCliWrapper.SimpleDraw.Initialize(Handle)
    ↓
OdaNativeApi::Oda_Initialize(HWND)
    ↓
OdaEngine::Initialize(HWND)
    ├─ OdaInitializer::Initialize()        [初始化 ODA SDK]
    ├─ OdDbDatabase::createObject()        [创建数据库]
    └─ OdaEngine::initGraphics(HWND)      [初始化图形系统]
        ├─ 加载 Gs 模块 (OpenGL/GDI)
        ├─ 创建 OdGsDevice
        ├─ 绑定窗口句柄 (HWND/HDC)
        └─ OdDbGsManager::setupActiveLayoutViews() [关联数据库和视图]
```

#### 2. 创建 3D 实体流程（以 Box 为例）

```
用户点击"创建盒子"按钮
    ↓
MainForm.btnCreateBox_Click()
    ↓
MainForm.CreateBox()
    ↓
OdaCliWrapper.SimpleDraw.CreateOrUpdateBox(length, width, height)
    ↓
OdaNativeApi::Oda_CreateOrUpdateBox(OdaBoxParam*)
    ↓
OdaEngine::CreateOrUpdateBox(BoxParam)
    ├─ 删除旧的 Box 实体（如果存在）
    ├─ OdDb3dSolid::createObject()
    ├─ OdDb3dSolid::createBox()            [创建几何体]
    ├─ 获取模型空间块表记录 (*Model_Space)
    ├─ BlockTableRecord::appendOdDbEntity() [添加到数据库]
    ├─ zoomExtents()                      [自动缩放视图]
    └─ Redraw()                           [触发重绘]
        └─ OdGsDevice::update()            [更新图形设备]
```

#### 3. 重绘流程

```
BimViewEditor.OnPaint()
    ↓
OdaCliWrapper.SimpleDraw.Redraw()
    ↓
OdaNativeApi::Oda_Redraw()
    ↓
OdaEngine::Redraw()
    └─ OdGsDevice::update()                [ODA SDK 渲染到窗口]
```

#### 4. 打开 DWG 文件流程

```
用户选择 DWG 文件
    ↓
MainForm.btnOpenDwg_Click()
    ↓
OdaCliWrapper.SimpleDraw.OpenDwg(filePath)
    ↓
OdaNativeApi::Oda_LoadDwg(wchar_t*)
    ↓
OdaEngine::LoadDwg(OdString)
    ├─ DbHostServices::readFile()         [读取 DWG 文件]
    ├─ 释放旧的图形设备和数据库
    ├─ 替换为新的数据库
    └─ 重新初始化图形系统
        └─ initGraphics()                 [绑定新数据库到视图]
```

### 项目结构

```
CreoManager/
├── BimDemo.csproj              # C# WinForms 主项目
├── MainForm.cs                  # 主窗体（用户界面）
├── MainForm.Designer.cs         # 主窗体设计器代码
├── BimViewEditor.cs             # 自定义控件（ODA 绘制容器）
├── BimViewEditor.Designer.cs    # 控件设计器代码
├── Program.cs                   # 程序入口（程序集解析）
│
├── OdaCliWrapper/               # C++/CLI 包装层项目
│   ├── OdaCliWrapper.vcxproj
│   ├── OdaCliWrapper.h          # 托管接口定义
│   ├── OdaCliWrapper.cpp        # 托管接口实现
│   └── AssemblyInfo.cpp         # 程序集信息
│
├── OdaNative/                   # 原生 C++ 引擎层项目
│   ├── OdaNative.vcxproj
│   ├── OdaEngine.h              # 引擎类定义
│   ├── OdaEngine.cpp            # 引擎类实现
│   ├── OdaNativeApi.h           # C API 接口定义
│   ├── OdaNativeApi.cpp         # C API 接口实现
│   ├── OdaInitilize.h           # ODA 初始化管理
│   ├── OdaInitilize.cpp
│   └── OdaDbHostServices.h      # 数据库主机服务
│
├── OdaNativeTest/               # 测试项目（控制台应用）
│   ├── OdaNativeTest.vcxproj
│   └── main.cpp                 # 测试入口
│
└── config/                      # 项目配置文件
    ├── OdaImport.props          # ODA SDK 路径配置
    └── ThirdParty.props         # 第三方库配置
```

### 关键技术点

#### 1. 程序集加载机制

由于 `OdaCliWrapper.dll` 是 C++/CLI 程序集，在运行时需要正确加载。`Program.cs` 中实现了 `AssemblyResolve` 事件处理，确保程序集能够正确加载：

```csharp
AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
```

#### 2. 窗口句柄传递

ODA SDK 需要 Windows 窗口句柄（HWND）来进行渲染。通过 `BimViewEditor.Handle` 获取 WinForms 控件的窗口句柄，传递给 ODA 引擎。

#### 3. 图形系统初始化

ODA SDK 使用图形系统（Gs）模块进行渲染，支持多种后端：
- OpenGL (`TD_GsOpenGL.txv`)
- GDI (`TD_GsGDI.txv`)
- DirectX (可选)

#### 4. 数据库和实体管理

- **OdDbDatabase**: 存储所有 CAD 实体的容器
- **模型空间**: 通过 `*Model_Space` 块表记录访问
- **实体生命周期**: 使用 `OdSmartPtr` 进行自动内存管理

#### 5. 自动缩放

创建新实体后，自动调用 `zoomExtents()` 将视图缩放到合适范围，确保用户能看到新创建的图形。

### 依赖关系

```
BimDemo (C#)
    ├─ 项目引用: OdaCliWrapper.vcxproj
    │
OdaCliWrapper (C++/CLI)
    ├─ 链接: OdaNative.lib
    ├─ 包含: OdaNativeApi.h
    │
OdaNative (C++)
    ├─ 链接: ODA SDK 库文件
    ├─ 包含: ODA SDK 头文件
    └─ 运行时依赖: ODA SDK DLL 和 .txv 模块文件
```

### 构建和部署

#### 构建顺序

1. **OdaNative** - 首先构建原生 C++ 引擎
2. **OdaCliWrapper** - 然后构建 C++/CLI 包装层
3. **BimDemo** - 最后构建 C# 主项目

#### 部署要求

- **ODA SDK**: 需要 ODA 会员授权，SDK 文件需放置在指定目录
- **运行时文件**: 
  - `OdaNative.dll`
  - `OdaCliWrapper.dll`
  - ODA SDK DLL 文件（从 `packages/Kernel_vc17_amd64dll_26.12/exe/` 复制）
  - ODA SDK 模块文件（`.txv` 文件，如 `TD_GsOpenGL.txv`）
  - ODA SDK 资源文件（`.tx` 文件）

项目已配置自动复制这些文件到输出目录（见 `BimDemo.csproj` 中的 `CopyOdaDlls` 目标）。

## 技术路线预演 Demo

本项目展示了将 ODA SDK 集成到 C# WinForms 应用的技术路线：
**C# WinForms → C++/CLI → 原生 C++ → ODA SDK**

## 其他技术路线调研

### 斯维尔 ueBIM SDK

SDK 下载地址和 API 文档都是私密的，推测是在商业调整收费模式，不提供直接使用，无法调研是否可以独立进行。

### PT Creo

模型渲染是在进程里面，单独使用 SDK 绘制模型到 WinForm 窗体展示是不支持的。必须与授权的 Creo Parametric 主程序运行，不能独立打包发布。

#### 可能技术预演路线：

1. **获取服务授权** - 成本太高，相当于给每个客户都买一套 Creo 软件
2. **独立运行 Creo 程序** - 相当于是 2 个进程，窗体上联动看起来视觉效果是一个，实际上还是 2 个进程
3. **服务端搭建 Creo 服务** - 客户端参数化传递服务端，服务端返回模型信息，延迟太高，对服务压力很大
4. **开发 Creo 的 C++ 插件** - 以 Creo 程序为主程序，附加上需要的业务算法

### ODA SDK

✅ **路线是通的** - 本项目已实现完整的集成方案，可以作为参考实现。

### Parasolid SDK

未验证。

## 使用示例

### 基本使用流程

1. **初始化 ODA 引擎**
   ```csharp
   // 在窗体加载时初始化
   bool ok = OdaCliWrapper.SimpleDraw.Initialize(this.bimViewEditor.Handle);
   ```

2. **创建 3D 实体**
   ```csharp
   // 创建盒子
   OdaCliWrapper.SimpleDraw.CreateOrUpdateBox(100, 25, 30);
   
   // 创建圆柱体
   OdaCliWrapper.SimpleDraw.CreateOrUpdateCylinder(50, 100);
   ```

3. **打开 DWG 文件**
   ```csharp
   OdaCliWrapper.SimpleDraw.OpenDwg(@"C:\path\to\file.dwg");
   ```

4. **触发重绘**
   ```csharp
   // 在控件的 OnPaint 或 OnResize 事件中调用
   OdaCliWrapper.SimpleDraw.Redraw();
   ```

### 代码示例

详细代码示例请参考：
- `MainForm.cs` - 主窗体实现
- `BimViewEditor.cs` - 自定义控件实现
- `OdaNativeTest/main.cpp` - C++ 测试示例

## 常见问题

### 1. 设计时程序集加载失败

**问题**: 在 Visual Studio 设计器中打开窗体时，提示无法加载 `OdaCliWrapper` 程序集。

**原因**: 设计器需要能够解析所有引用的类型，但设计时可能找不到 DLL。

**解决方案**: 
- 确保 `OdaCliWrapper.dll` 已构建并位于 `x64\Debug\` 或 `x64\Release\` 目录
- 重新构建整个解决方案
- 如果问题持续，可以在设计时暂时注释掉对 `OdaCliWrapper` 的直接引用

### 2. 运行时找不到 ODA SDK DLL

**问题**: 运行时提示找不到 ODA SDK 相关的 DLL 文件。

**解决方案**:
- 检查 `BimDemo.csproj` 中的 `CopyOdaDlls` 目标是否正常执行
- 确保 ODA SDK 路径配置正确（`config/OdaImport.props`）
- 手动将 ODA SDK DLL 和 `.txv` 文件复制到输出目录

### 3. 黑屏或图形不显示

**原因**:
- 视图没有缩放到合适范围，图形在视野外
- 图形设备未正确初始化
- 实体未添加到模型空间

**解决方案**:
- 确保调用 `Initialize()` 时传入有效的窗口句柄
- 创建实体后会自动调用 `zoomExtents()`，如果仍看不到，检查实体参数是否合理
- 确保控件已创建并显示（`Handle` 有效）

### 4. 初始化失败

**原因**:
- ODA Gs 模块文件（`.txv`）不在运行目录
- 窗口句柄无效
- ODA 未正确初始化

**解决方案**:
- 确保 ODA bin 目录下的 `TD_GsOpenGL.txv` 等文件复制到 exe 目录
- 确保控件已创建并显示（`Handle` 有效）
- 检查 `OdaInitializer::Initialize()` 是否成功

## 核心对比表
| 维度                      | **Creo (Parametric + SDK)**   | **ueBIM SDK**       | **ODA SDK**                | **Parasolid SDK** |
| ----------------------- | ----------------------------- | ------------------- | -------------------------- | ----------------- |
| **是否独立运行、可嵌入 WinForms** | ❌ 需安装并授权 Creo 主程序/License     | ✔ *取决是否提供嵌入支持*（需确认） | ✔ 支持嵌入 WinForms 本地运行       | ✔ 可集成，需要自实现渲染     |
| **是否需要外部授权许可**          | ✔ 需要 Creo 授权/License（开发 & 运行） | ✔ 商业授权              | ✔ ODA 会员授权                 | ✔ 商业授权            |
| **核心功能定位**              | 参数化机械 CAD (完整设计 & 特征建模)       | BIM 建模/可视化平台        | CAD/BIM 数据互操作 + Viewer SDK | 几何建模内核            |
| **可视化能力**               | ✔ 具备，但依赖主程序 UI                | ✔ 通常具备 BIM 渲染       | ✔ 可视化 SDK 支持               | ✖ 核心几何，需要外渲染      |
| **参数化建模能力**             | ✔ 强（Creo 功能）                  | ✖ 主要 BIM            | ✖ 轻量                       | ✔ 强（几何核心，但不包含 UI） |
| **CAD 格式支持**            | ✔ 原生 Creo 文件                  | ✔ BIM 格式 IFC/DWG 等  | ✔ 多 CAD/BIM 格式             | ✖ 主要 Parasolid 格式 |
| **适用场景**                | 专业机械设计                        | BIM 应用/建筑设计         | 多格式查看与轻交互                  | 构建自定义 CAD 应用      |
| **部署可打包性**              | ❌ 目标机必须有 Creo 授权              | ✔ （需确认 SDK 授权方式）    | ✔                          | ✔                 |

