#include "pch.h"
#include "OdaCliWrapper.h"

// Native C API
#include "..\OdaNative\OdaNativeApi.h"

#include <msclr/marshal.h>

using namespace msclr::interop;
using namespace OdaCliWrapper;

// ============================================================================
// OdaNativeApiWrapper 实现（专门负责转调 OdaNative 的 C API）
// ============================================================================

bool OdaNativeApiWrapper::Initialize(IntPtr hwnd)
{
    HWND nativeHwnd = static_cast<HWND>(hwnd.ToPointer());
    return Oda_Initialize(nativeHwnd);
}

bool OdaNativeApiWrapper::CreateOrUpdateBox(OdaBoxParam param)
{
    ::OdaBoxParam native{};
    native.length = param.Length;
    native.width = param.Width;
    native.height = param.Height;

    return Oda_CreateOrUpdateBox(&native);
}

bool OdaNativeApiWrapper::CreateOrUpdateCylinder(OdaCylinderParam param)
{
    ::OdaCylinderParam native{};
    native.radius = param.Radius;
    native.height = param.Height;

    return Oda_CreateOrUpdateCylinder(&native);
}

double OdaNativeApiWrapper::GetHeight()
{
    return Oda_GetHeight();
}

// ============================================================================
// OdaEditor 实现（使用 OdaNativeApiWrapper 进行转调）
// ============================================================================

bool OdaEditor::Initialize(IntPtr hwnd)
{
    return OdaNativeApiWrapper::Initialize(hwnd);
}

bool OdaEditor::CreateOrUpdateBox(OdaBoxParam param)
{
    return OdaNativeApiWrapper::CreateOrUpdateBox(param);
}

bool OdaEditor::CreateOrUpdateCylinder(OdaCylinderParam param)
{
    return OdaNativeApiWrapper::CreateOrUpdateCylinder(param);
}

double OdaEditor::GetHeight()
{
    return OdaNativeApiWrapper::GetHeight();
}
