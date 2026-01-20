# ODA Demo 项目完整 TaskList

> 目标：构建一个 **C# WinForms → C++/CLI → Native C++ → ODA SDK** 的最小可运行 Demo，支持参数化建模与结果回传。

---

## Phase 1：ODA API 学习 & 官方 Example 学习

### 1.1 ODA SDK 整体认知
- ☑ ODA 产品线区分（Drawings / Visualize / BIM）
- ☐ 核心模块理解：
  - ☐ TD_Db / OdDb*
  - ☐ TD_Gs / OdGs*
  - ☐ Geometry / Math
- ☐ 平台服务类：
  - ☐ ExSystemServices
  - ☐ ExHostAppServices

### 1.2 官方 Example 编译与运行
- ☑ 成功编译至少 1 个官方示例
- ☑ 解决 MFC / x64 / 工具集问题
- ☑ 解决编码（C4819 / C4828）问题
  遇到问题：
  - 1. 授权文件缺失
  - 2. example 编译缺少mfc，配置mfc 143
  - 3. 缺少vc的提示信息也是mfc缺失，最终配置msvc工具集版本为14.44.35207，和vs安装一致
  - 4. 运行提示头文件编码格式不同，文件太多，cursor批处理所有文件编码：
    cd E:\Code\cli\SDK_26.12; Get-ChildItem -Path . -Recurse -Include *.h,*.hpp,*.hh,*.hxx,*.inl,*.cpp,*.c,*.cxx,*.cc -File | ForEach-Object { $c = Get-Content -LiteralPath $_.FullName -Raw; Set-Content -LiteralPath $_.FullName -Value $c -Encoding utf8 }

### 1.3 Example 结构拆解
- ☐ 初始化流程（odInitialize / Services）
- ☐ 数据库创建 / 加载流程
- ☐ 几何创建 API 调用点
- ☐ 程序退出与资源释放

---

## Phase 2：项目中引入 ODA 环境配置

### 2.1 目录与版本结构设计
- ☐ third_party/oda/include
- ☐ third_party/oda/lib/x64
- ☐ third_party/oda/bin/x64
- ☐ ODA SDK 版本号固定策略

### 2.2 C++ 工程配置
- ☐ 头文件包含路径配置
- ☐ lib 路径配置
- ☐ 链接库清单整理（core / db / gs / platform）
- ☐ Debug / Release 对应 lib 匹配

---

## Phase 3：Native C++ 引入 ODA 并跑通

### 3.1 Native 架构设计
- ☐ ODA 初始化与反初始化模块
- ☐ ODA 上下文管理（单例 / 会话对象）
- ☐ 生命周期控制（防止重复 init/shutdown）

### 3.2 最小功能闭环
- ☐ 定义参数结构体（长 / 宽 / 高 / 半径 / 角度）
- ☐ 使用 ODA API 创建简单 3D/2D 几何体
- ☐ 支持参数变更后重新计算

### 3.3 Native 对外 API 设计
- ☐ 不暴露任何 ODA 类型
- ☐ 使用 POD / struct / enum
- ☐ 错误码返回（不抛 C++ 异常）
- ☐ 初始化 / 执行 / 释放 三段式接口

---

## Phase 4：C++/CLI 桥接层设计（托管/非托管边界）

### 4.1 CLI 项目结构
- ☐ 独立 C++/CLI Class Library
- ☐ 引用 Native C++ 项目
- ☐ 不直接引用 ODA SDK

### 4.2 数据与异常转换
- ☐ 基本类型转换（double / int / bool）
- ☐ string：System::String ↔ std::wstring
- ☐ struct 映射（CLI struct ↔ Native struct）
- ☐ Native 错误码 → CLI 异常或返回值

### 4.3 CLI API 稳定性设计
- ☐ 面向 C# 的干净接口
- ☐ 不暴露 Native 生命周期复杂性

---

## Phase 5：C# WinForms 调用与验证

### 5.1 C# 调用链路打通
- ☐ 引用 C++/CLI DLL
- ☐ 初始化 ODA 会话
- ☐ 参数传入 → Native 执行
- ☐ 返回结果验证

### 5.2 UI 功能验证
- ☐ WinForms 参数输入控件
- ☐ 参数修改 → 触发重新计算
- ☐ 结果状态 / 错误信息展示

---

## Phase 6：线程、日志、错误与部署

### 6.1 线程模型设计
- ☐ ODA 是否单线程使用
- ☐ C# UI 线程 ↔ Native 工作线程隔离
- ☐ 锁与并发策略

---

## 最终交付物

- ☐ 可运行 Demo（WinForms）
- ☐ 三层工程结构清晰（C# / CLI / Native）
- ☐ 参数化建模成功
- ☐ demo练习学习记录

---

