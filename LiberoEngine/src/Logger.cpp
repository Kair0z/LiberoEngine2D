#include "PCH.h"
#include "LiberoMacros.h"
#include "Logger.h"

//******************************
// Logger Initialization
//******************************

namespace Libero
{
	Logger::Logger()
	{
		Initialize();
	}

	void Logger::Initialize()
	{
		m_pConsoleLogger = nullptr;
		m_Logbuffer.reserve(LOGBUFFER_INITSIZE);
		m_Backbuffer.reserve(LOGBUFFER_INITSIZE);
	}

#pragma region BaseLogging & derivation functions
	void Logger::BaseLogger::Log(const std::string& mssg)
	{
		if (!m_pOS) return;

		if (m_pOS->good())
		{
			(*m_pOS) << mssg << "\n";
			m_pOS->flush();
		}
	}

	Logger::FileLogger::FileLogger(const std::string& filepath) : m_Filepath{ filepath }
	{
		//m_FOS.open(filepath, std::ofstream::out);
		m_FOS = std::ofstream(filepath);

		m_pOS = &m_FOS;
	}

	Logger::FileLogger::~FileLogger()
	{

		m_FOS.close();
	}


	Logger::ConsoleLogger::ConsoleLogger()
	{
		m_pOS = &std::cout;
	}
#pragma endregion

	//*******************************
	// General Logging Functionality
	//*******************************

#pragma region Logging

	void Logger::Log(LogType logType, const std::string& mssg)
	{
		std::string finalMessage;

		switch (logType)
		{
		case LogType::Error:
			finalMessage = "[ERROR:] ";
			break;

		case LogType::Warning:
			finalMessage = "[WARNING:] ";
			break;

		case LogType::Info:
			finalMessage = "[INFO:] ";
			break;
		}

		finalMessage += mssg;

		if (m_pConsoleLogger) m_pConsoleLogger->Log(finalMessage);
		if (m_pFileLogger) m_pFileLogger->Log(finalMessage);

		m_Logbuffer.push_back(finalMessage);
		m_Backbuffer.push_back(finalMessage);
	}
	void Logger::LogWarning(const std::string& mssg)
	{
		Log(LogType::Warning, mssg);
	}

	void Logger::LogError(const std::string& mssg)
	{
		Log(LogType::Error, mssg);
	}

	void Logger::LogInfo(const std::string& mssg)
	{
		Log(LogType::Info, mssg);
	}

	void Logger::ExplicitConsoleLog(LogType logType, const std::string& mssg)
	{
		std::string finalMessage;

		switch (logType)
		{
		case LogType::Info:
			break;

		case LogType::Warning:
			break;

		case LogType::Error:
			break;
		}

		finalMessage += mssg;

		if (m_pConsoleLogger) m_pConsoleLogger->Log(finalMessage);
	}

#pragma endregion

	const std::vector<std::string>& Logger::GetLogBuffer() const
	{
		return m_Logbuffer;
	}

	void Logger::Clear()
	{
		m_Logbuffer.clear();
	}

	//***********************
	// Enabling File Logging
	//***********************

#pragma region FileLogging

	void Logger::StartFileLogging(const std::string& filepath)
	{
		SAFEDELETE(m_pFileLogger);

		m_pFileLogger = new FileLogger("../Logs/" + filepath + ".txt");
	}

	void Logger::StopFileLogging()
	{
		SAFEDELETE(m_pFileLogger);
	}
#pragma endregion
}

