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

bool OdaNativeApiWrapper::Initialize(OdaInitParam param)
{
    if (String::IsNullOrWhiteSpace(param.RuntimePath))
        return false;

    marshal_context ctx;

    ::OdaInitParam native{};
    native.runtimePath = ctx.marshal_as<const wchar_t*>(param.RuntimePath);
    native.hostHwnd = param.HostWindow.ToPointer();

    return Oda_Initialize(&native);
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

bool OdaEditor::Initialize(OdaInitParam param)
{
    return OdaNativeApiWrapper::Initialize(param);
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
