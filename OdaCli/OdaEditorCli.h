#pragma once
using namespace System;

namespace OdaCliWrapper
{
    public ref class BoxParamCli
    {
    public:
        double Length;
        double Width;
        double Height;
    };

    public ref class OdaViewer
    {
    public:
        void Init(IntPtr hwnd);
        void DrawBox(BoxParamCli^ param);
        double GetHeight();
    };
}