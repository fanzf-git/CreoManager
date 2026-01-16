#include "pch.h"
#include "wrapper.h"


CreoWrapper::CreoWrapper() : m_creoStartedByWrapper(false)
{
    std::filesystem::create_directories("logs");
}

CreoWrapper::~CreoWrapper()
{
    CloseCreo();
}


bool CreoWrapper::InitCreo(const std::wstring& creoPath)
{
	HWND hwnd = FindWindow(NULL, L"Creo Parametric");
	if (hwnd)
	{
		m_creoStartedByWrapper = false;
		return true;
	}


	STARTUPINFO si = { sizeof(si) };
	ZeroMemory(&m_creoProcessInfo, sizeof(m_creoProcessInfo));
	
	// CreateProcess: 第一个参数是应用程序路径，第二个参数是命令行（可以为NULL）
	if (!CreateProcess(creoPath.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &m_creoProcessInfo))
		return false;


	m_creoStartedByWrapper = true;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return true;
}


void CreoWrapper::CloseCreo()
{
	if (m_creoStartedByWrapper)
	{
		TerminateProcess(m_creoProcessInfo.hProcess, 0);
		CloseHandle(m_creoProcessInfo.hProcess);
		CloseHandle(m_creoProcessInfo.hThread);
	}
}


void CreoWrapper::WriteLog(const PartParams& params, const std::wstring& status)
{
	try
	{
		std::ofstream logFile("logs\\GenerateLog.txt", std::ios::app);
		if (!logFile.is_open())
			return;


		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char buf[64];
		ctime_s(buf, sizeof(buf), &now);
		std::string timeStr(buf);
		timeStr.pop_back();


		logFile << timeStr
			<< " | LENGTH=" << params.Length
			<< " | WIDTH=" << params.Width
			<< " | HEIGHT=" << params.Height
			<< " | DRAFT=" << params.DraftAngle
			<< " | FILLET=" << params.FilletRadius
			<< " | ";
		
		// 使用更现代的UTF-8转换方法（避免已弃用的wstring_convert）
		std::string statusUtf8;
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, status.c_str(), -1, NULL, 0, NULL, NULL);
		if (size_needed > 0)
		{
			statusUtf8.resize(size_needed - 1);
			WideCharToMultiByte(CP_UTF8, 0, status.c_str(), -1, &statusUtf8[0], size_needed, NULL, NULL);
		}
		logFile << statusUtf8
			<< std::endl;
		logFile.close();
	}
	catch (...)
	{
	}
}


bool CreoWrapper::CreatePart(const PartParams& params)
{
	WriteLog(params, L"生成成功 (模拟)");
	return true; // TODO: Replace with ProToolkit calls
}


bool CreoWrapper::CreatePartFromJson(const std::wstring& jsonCmd)
{
	try
	{
		// 转换宽字符串到UTF-8
		std::string jsonUtf8;
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, jsonCmd.c_str(), -1, NULL, 0, NULL, NULL);
		if (size_needed > 0)
		{
			jsonUtf8.resize(size_needed - 1);
			WideCharToMultiByte(CP_UTF8, 0, jsonCmd.c_str(), -1, &jsonUtf8[0], size_needed, NULL, NULL);
		}
		auto json = nlohmann::json::parse(jsonUtf8);
		PartParams p;
		p.Length = json["length"];
		p.Width = json["width"];
		p.Height = json["height"];
		p.DraftAngle = json["draft"];
		p.FilletRadius = json["fillet"];
		return CreatePart(p);
	}
	catch (...)
	{
		PartParams empty{};
		WriteLog(empty, L"JSON解析失败");
		return false;
	}
}


extern "C"
{
	__declspec(dllexport) CreoWrapper* Wrapper_New()
	{
		return new CreoWrapper();
	}

	__declspec(dllexport) void Wrapper_Delete(CreoWrapper* w)
	{
		delete w;
	}

	__declspec(dllexport) bool InitCreo(CreoWrapper* w, const wchar_t* path)
	{
		if (!w || !path)
			return false;
		return w->InitCreo(path);
	}

	__declspec(dllexport) void CloseCreo(CreoWrapper* w)
	{
		if (!w)
			return;
		w->CloseCreo();
	}

	__declspec(dllexport) bool CreatePart(CreoWrapper* w, const PartParams* p)
	{
		if (!w || !p)
			return false;
		return w->CreatePart(*p);
	}

	__declspec(dllexport) bool CreatePartFromJson(CreoWrapper* w, const wchar_t* json)
	{
		if (!w || !json)
			return false;
		return w->CreatePartFromJson(json);
	}
}