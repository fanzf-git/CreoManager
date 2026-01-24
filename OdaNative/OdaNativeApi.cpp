#include "OdaCommon.h"

#include "pch.h"
#include "OdaNativeApi.h"
#include "OdaEngine.h"
#include "OdaInitilize.h"

// ============================================================================
// 纯 C 接口实现
// ============================================================================
extern "C"
{
	bool Oda_Initialize(HWND hwnd)
	{
		// 使用单例模式
		auto& engine = OdaEngine::Instance();
		return engine.Initialize(hwnd);
	}

	bool Oda_CreateOrUpdateBox(const OdaBoxParam* param)
	{
		if (!param) return false;

		BoxParam box{ param->length, param->width, param->height };
		auto& engine = OdaEngine::Instance();

		// OdaEngine::CreateOrUpdateBox 内部已经调用 Redraw，这里不再重复刷新，避免多次 update 叠加导致调试版断言。
		return engine.CreateOrUpdateBox(box);
	}

	bool Oda_CreateOrUpdateCylinder(const OdaCylinderParam* param)
	{
		if (!param) return false;

		CylinderParam cylinder{ param->radius, param->height };
		auto& engine = OdaEngine::Instance();

		// OdaEngine::CreateOrUpdateCylinder 内部已经调用 Redraw，这里不再重复刷新。
		return engine.CreateOrUpdateCylinder(cylinder);
	}

	double Oda_GetHeight()
	{
		auto& engine = OdaEngine::Instance();
		return engine.GetHeight();
	}

  void Oda_Cleanup()
  {
    // 显式清理 ODA，配合 OdaInitializerImpl::Cleanup/odUninitialize/odCleanUpStaticData
    OdaInitializer::Cleanup();
  }

  bool Oda_LoadDwg(const wchar_t* filePath)
  {
    if (!filePath)
      return false;

    auto& engine = OdaEngine::Instance();
    return engine.LoadDwg(OdString(filePath));
  }
}
