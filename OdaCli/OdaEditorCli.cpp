#include "pch.h"
#include "OdaWrapper.h"
#include "../OdaNative/OdaEngine.h"

using namespace OdaCliWrapper;

void OdaViewer::Init(IntPtr hwnd)
{
    HWND h = static_cast<HWND>(hwnd.ToPointer());
    OdaEngine::Instance().Initialize(h);
}

void OdaViewer::DrawBox(BoxParamCli^ p)
{
    BoxParam native;
    native.length = p->Length;
    native.width = p->Width;
    native.height = p->Height;

    OdaEngine::Instance().CreateOrUpdateBox(native);
    OdaEngine::Instance().Redraw();
}

double OdaViewer::GetHeight()
{
    return OdaEngine::Instance().GetCurrentHeight();
}