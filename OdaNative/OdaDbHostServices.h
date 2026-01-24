#pragma once

#include "OdaCommon.h"

// ODA Drawings SDK
#include "DbHostAppServices.h"

// 一个精简版的 DbHostServices，实现 createDatabase 等基础能力，
// 用于让 OdDbDatabase 拥有完整的默认布局 / 模型空间结构，
// 以便后续调用 OdDbGsManager::setupActiveLayoutViews。

class OdaDbHostServices : public OdDbHostAppServices
{
public:
  ODRX_USING_HEAP_OPERATORS(OdDbHostAppServices);

  OdaDbHostServices() = default;
  virtual ~OdaDbHostServices() = default;

  // === 必须实现的一些纯虚函数（按最简单方式返回本地路径 / 名称） ===

  // 应用程序名称
  const OdString program() const
  {
    return OD_T("CreoManagerDemo");
  }

  // 产品名称
  const OdString product() const
  {
    return OD_T("CreoManager ODA Demo");
  }

  // 公司名称
  const OdString companyName() const
  {
    return OD_T("MC-Tech");
  }

  // 提供一个备用字体名称（当 SHX/TTF 找不到时）
  OdString getAlternateFontName() const override
  {
    // 返回空表示使用 ODA 内部默认
    return OdString::kEmpty;
  }

  // 字体目录（可以返回空，让 ODA 自己去当前目录 / 系统路径找）
  OdString getFontFolder() const
  {
    return OdString::kEmpty;
  }

  // 支持文件目录（同样返回空即可）
  OdString getSupportPath() const
  {
    return OdString::kEmpty;
  }

  // 临时目录
  OdString tempPath() const
  {
    wchar_t buf[MAX_PATH] = { 0 };
    DWORD len = ::GetTempPathW(MAX_PATH, buf);
    if (len == 0 || len > MAX_PATH)
      return OdString::kEmpty;
    return OdString(buf);
  }

  // 必须实现的抽象接口（本 Demo 不依赖，返回空指针即可）
  OdHatchPatternManager* patternManager() override
  {
    return nullptr;
  }

  OdDbKey* key() const override
  {
    return nullptr;
  }
};

