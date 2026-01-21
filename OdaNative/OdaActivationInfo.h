#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// ODA SDK 授权信息读取
// 从 SDK 的 ThirdParty\activation\OdActivationInfo 文件读取授权信息

namespace OdaActivation
{
    // 移除字符串两端的引号
    inline std::string TrimQuotes(const std::string& str)
    {
        std::string result = str;
        if (!result.empty() && result.front() == '"')
        {
            result = result.substr(1);
        }
        if (!result.empty() && result.back() == '"')
        {
            result = result.substr(0, result.length() - 1);
        }
        return result;
    }

    // 从文件读取授权信息
    // 参数：activationFilePath - 授权文件路径
    // 返回：pair<userInfo, userSignature>，如果读取失败则返回空字符串
    inline std::pair<std::string, std::string> ReadActivationInfo(const std::string& activationFilePath)
    {
        std::pair<std::string, std::string> result;
        
        std::ifstream file(activationFilePath);
        if (!file.is_open())
        {
            return result; // 返回空字符串对
        }

        std::string line;
        
        // 读取第一行（授权文件通常只有一行，包含两个用逗号分隔的字符串）
        if (std::getline(file, line))
        {
            // 查找逗号位置
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos)
            {
                // 分割两个字符串
                std::string first = line.substr(0, commaPos);
                std::string second = line.substr(commaPos + 1);
                
                // 移除引号
                result.first = TrimQuotes(first);
                result.second = TrimQuotes(second);
            }
            else
            {
                // 如果没有逗号，可能是两行格式
                result.first = TrimQuotes(line);
                
                // 读取第二行
                std::string line2;
                if (std::getline(file, line2))
                {
                    result.second = TrimQuotes(line2);
                }
            }
        }

        file.close();
        return result;
    }

    // 获取默认授权文件路径（相对于 SDK 根目录）
    inline std::string GetDefaultActivationFilePath()
    {
        // SDK 根路径：E:\Code\cli\SDK_26.12
        return "E:\\Code\\cli\\SDK_26.12\\ThirdParty\\activation\\OdActivationInfo";
    }
}
