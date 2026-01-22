#include "OdaCommon.h"

#include "pch.h"
#include "OdaNativeApi.h"
#include "OdaEngine.h"

// ============================================================================
// 纯 C 接口实现
// ============================================================================
extern "C"
{
	bool Oda_Initialize(const OdaInitParam* param)
	{
		if (!param) return false;

		// 使用单例模式
		auto& engine = OdaEngine::Instance();
		HWND hwnd = param->hostHwnd ? static_cast<HWND>(param->hostHwnd) : nullptr;
		
		return engine.Initialize(hwnd);
	}

	bool Oda_CreateOrUpdateBox(const OdaBoxParam* param)
	{
		if (!param) return false;

		BoxParam box{ param->length, param->width, param->height };
		auto& engine = OdaEngine::Instance();

		bool ok = engine.CreateOrUpdateBox(box);
		if (ok) engine.Redraw();
		return ok;
	}

	bool Oda_CreateOrUpdateCylinder(const OdaCylinderParam* param)
	{
		if (!param) return false;

		CylinderParam cylinder{ param->radius, param->height };
		auto& engine = OdaEngine::Instance();

		bool ok = engine.CreateOrUpdateCylinder(cylinder);
		if (ok) engine.Redraw();
		return ok;
	}

	double Oda_GetHeight()
	{
		auto& engine = OdaEngine::Instance();
		return engine.GetHeight();
	}
}
