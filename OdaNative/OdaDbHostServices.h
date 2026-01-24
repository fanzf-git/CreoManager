#pragma once

#include "OdaCommon.h"

// ODA Drawings SDK
#include "DbHostAppServices.h"

// 一个尽量贴近 OpenCAD 示例 ExDbHostAppServices 的 DbHostServices 实现，
// 主要负责：
//  - 提供应用 / 产品 / 公司名称
//  - 提供字体、支持文件、临时目录
//  - 实现 findFile / tempPath 等基础能力
//  - 复用 OdDbHostAppServices2 中对 key() 的默认实现，避免返回空指针
//
// 注意：这里是为 Demo 精简过的版本，但接口风格与 OpenCAD 基本一致，
//       已足够支撑 createDatabase / readFile / Gs 初始化等常见用法。
class OdaDbHostServices : public OdDbHostAppServices2
{
public:
  ODRX_USING_HEAP_OPERATORS(OdDbHostAppServices2);

  OdaDbHostServices() = default;
  virtual ~OdaDbHostServices() = default;

  // === 关于信息 ===

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

  // === 路径 / 资源相关 ===

  // 备用字体名称（当 SHX/TTF 找不到时）
  OdString getAlternateFontName() const
  {
    // 返回空表示使用 ODA 内部默认
    return OdString::kEmpty;
  }

  // 字体目录（可以是空；ODA 会再查找当前目录 / 系统字体目录）
  OdString getFontFolder() const
  {
    return OdString::kEmpty;
  }

  // 支持文件目录（.lin / .pat / .ctb 等）
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

  // 查找文件（字体 / XRef / PAT / TX 等）
  OdString findFile(const OdString& filename,
                    OdDbBaseDatabase* pDb = nullptr,
                    FindFileHint hint = kDefault) override
  {
    // 1. 文件名本身（绝对路径或当前目录）
    if (odrxSystemServices()->accessFile(filename, Oda::kFileRead))
      return filename;

    // 2. 如果有数据库上下文，优先在 DWG 所在目录查找
    if (pDb)
    {
      OdDbDatabase* pRealDb = OdDbDatabase::cast(pDb).get();
      if (pRealDb)
      {
        OdString dbPath = pRealDb->getFilename();
        if (!dbPath.isEmpty())
        {
          int pos = dbPath.reverseFind(L'\\');
          if (pos < 0)
            pos = dbPath.reverseFind(L'/');
          if (pos >= 0)
          {
            OdString folder = dbPath.left(pos + 1);
            OdString full = folder + filename;
            if (odrxSystemServices()->accessFile(full, Oda::kFileRead))
              return full;
          }
        }
      }
    }

    // 3. 退回到基类默认实现（会考虑 ACAD 等环境变量）
    return OdDbHostAppServices::findFile(filename, pDb, hint);
  }

  // === 进度条相关（Demo 不使用，返回空指针即可） ===

  OdDbHostAppProgressMeter* newProgressMeter() override
  {
    return nullptr;
  }

  void releaseProgressMeter(OdDbHostAppProgressMeter* /*pProgressMeter*/) override
  {
    // 无实际进度条实现，什么都不做
  }

  // 图案管理器（Demo 不使用，返回空指针）
  OdHatchPatternManager* patternManager() override
  {
    return nullptr;
  }
};

