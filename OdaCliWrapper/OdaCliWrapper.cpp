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
	bool SimpleDraw::Initialize(IntPtr hostHwnd)
	{
		HWND hwnd = static_cast<HWND>(hostHwnd.ToPointer());
		return Oda_Initialize(hwnd);
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

    bool SimpleDraw::OpenDwg(String^ filePath)
    {
        if (String::IsNullOrEmpty(filePath))
            return false;

        pin_ptr<const wchar_t> pPath = PtrToStringChars(filePath);
        return Oda_LoadDwg(pPath);
    }
}
