# 第三方库说明

## nlohmann/json

这是一个 header-only 的 JSON 库，用于 C++ 项目。

### 使用方法

在代码中直接包含：

```cpp
#include <nlohmann/json.hpp>
```

### 文档

- GitHub: https://github.com/nlohmann/json
- 在线文档: https://json.nlohmann.me/

### 更新方法

如果需要更新到最新版本，可以运行：

```powershell
Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp' -OutFile 'third_party\nlohmann\json.hpp'
```

### 使用示例

```cpp
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// 解析 JSON
std::string jsonStr = R"({"name":"test","value":42})";
auto j = json::parse(jsonStr);

// 访问值
std::string name = j["name"];
int value = j["value"];

// 创建 JSON
json j2;
j2["name"] = "test";
j2["value"] = 42;
std::string output = j2.dump();
```
