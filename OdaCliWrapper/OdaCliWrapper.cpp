#define _CLR_SAFE

#include "pch.h"
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "../OdaNative/OdaNativeApi.h"

#include "OdaCliWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

namespace OdaCliWrapper
{
	bool SimpleDraw::Initialize(String^ runtimePath, IntPtr hostHwnd)
	{
		if (runtimePath == nullptr)
			return false;

		marshal_context ctx;

		OdaInitParam param{};
		param.runtimePath = ctx.marshal_as<const wchar_t*>(runtimePath);
		param.hostHwnd = hostHwnd.ToPointer();

		return Oda_Initialize(&param);
	}

	bool SimpleDraw::CreateOrUpdateBox(
		double length,
		double width,
		double height)
	{
		OdaBoxParam param{};
		param.length = length;
		param.width = width;
		param.height = height;

		return Oda_CreateOrUpdateBox(&param);
	}

	bool SimpleDraw::CreateOrUpdateCylinder(
		double radius,
		double height)
	{
		OdaCylinderParam param{};
		param.radius = radius;
		param.height = height;

		return Oda_CreateOrUpdateCylinder(&param);
	}

	double SimpleDraw::GetHeight()
	{
		return Oda_GetHeight();
	}
}
