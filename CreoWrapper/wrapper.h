#pragma once
#include "pch.h"

 //ProToolkit 头文件（需要时取消注释）
//#include <ProToolkit.h>
//#include <ProMdl.h>
//#include <ProParam.h>
//#include <ProView.h>

struct PartParams
{
	double Length;
	double Width;
	double Height;
	double DraftAngle;
	double FilletRadius;
};


class CreoWrapper
{
public:
	CreoWrapper();
	~CreoWrapper();


	bool InitCreo(const std::wstring& creoPath);
	void CloseCreo();


	bool CreatePart(const PartParams& params);
	bool CreatePartFromJson(const std::wstring& jsonCmd);


private:
	void WriteLog(const PartParams& params, const std::wstring& status);


	PROCESS_INFORMATION m_creoProcessInfo;
	bool m_creoStartedByWrapper;
	std::wstring m_templatePath = L"D:\\CreoDemo\\Template\\template.prt";
};