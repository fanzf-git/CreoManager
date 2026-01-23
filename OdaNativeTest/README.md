# OdaNativeTest - ODA Native DLL 测试项目

## 项目说明

这是一个 C++ 控制台应用程序，用于测试和验证 `OdaNative.dll` 是否正常工作。

## 功能

- 测试 ODA SDK 初始化
- 测试创建 Box（长方体）
- 测试创建 Cylinder（圆柱体）
- 测试获取图形高度

## 构建要求

1. **OdaNative 项目必须先构建**，生成 `OdaNative.dll` 和 `OdaNative.lib`
2. **ODA SDK DLL** 必须可用（从 `packages\Kernel_vc17_amd64dll_26.12\exe\vc17_amd64dlldbg\` 复制）

## 关于 .tx 资源文件

如果运行时出现 "找不到 TD_DbEntities_26.12_17.tx" 等错误，说明缺少 ODA SDK 的文本资源文件。

### 解决方案

1. **查找 .tx 文件位置**：
   - 检查 ODA SDK 完整安装目录（如 `E:\Code\cli\SDK_26.12`）
   - 查找所有 `.tx` 文件
   - 将这些文件复制到可执行文件输出目录（`x64\Debug\` 或 `x64\Release\`）

2. **手动复制 .tx 文件**：
   ```powershell
   # 从 ODA SDK 安装目录复制所有 .tx 文件到输出目录
   Copy-Item "E:\Code\cli\SDK_26.12\**\*.tx" -Destination "E:\Code\cli\CreoManager\x64\Debug\" -Recurse
   ```

3. **检查 ODA SDK 文档**：
   - 查看 ODA SDK 文档，了解 `.tx` 文件的位置和用途
   - 确认这些文件是否必需，或者是否可以忽略（如果不需要本地化支持）

## 使用方法

1. 在 Visual Studio 中，右键点击 `OdaNativeTest` 项目
2. 选择"设为启动项目"
3. 按 F5 运行调试，或 Ctrl+F5 运行（不调试）
4. 查看控制台输出，确认各个测试是否通过

## 输出

程序会在控制台输出每个测试的结果：
- `[OK]` 表示测试通过
- `[FAIL]` 表示测试失败

如果所有测试通过，说明 `OdaNative.dll` 工作正常。
