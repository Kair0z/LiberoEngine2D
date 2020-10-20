#pragma once
#include "LiberoMacros.h"
#include "ILiberoLocator.h"

#include <iostream>
#include <fstream>
#include <vector>

//*************************************************************
// Logger (Credits to The Overlord Engine)
//*************************************************************

#define LOGBUFFER_INITSIZE 10000

namespace Libero
{
	class Logger
	{
	public:
		enum class LogType
		{
			Info,
			Warning,
			Error
		};

		Logger();
		~Logger()
		{
			m_Logbuffer.clear();

			delete m_pConsoleLogger;
			m_pConsoleLogger = nullptr;

			delete m_pFileLogger;
			m_pFileLogger = nullptr;
		}

	private:
#pragma region Nested Loggers
		class BaseLogger
		{
		protected: 
			std::ostream* m_pOS = nullptr;
			BaseLogger() = default;

		public:
			virtual void Log(const std::string& mssg);
			virtual ~BaseLogger() = default;
		};

		class ConsoleLogger : public BaseLogger
		{
		public:
			ConsoleLogger();
		};

		class FileLogger : public BaseLogger
		{
		public:
			explicit FileLogger(const std::string& filepath);
			virtual ~FileLogger();

		private:
			std::string m_Filepath;
			std::ofstream m_FOS;
		};
#pragma endregion

	public:
		// * General Logging functions *
		virtual void Log(LogType, const std::string& mssg);
		virtual void LogInfo(const std::string& mssg);
		virtual void LogWarning(const std::string& mssg);
		virtual void LogError(const std::string& mssg);

		virtual void ExplicitConsoleLog(LogType logType, const std::string& mssg);
		// VIRTUAL == So that NullLogger may exist! // Worth it?

		// * File Logging *
		virtual void StartFileLogging(const std::string& filepath);
		virtual void StopFileLogging();

		// Get buffer
		const std::vector<std::string>& GetLogBuffer() const;
		void Clear();

	private:
		void Initialize();

		std::vector<std::string> m_Logbuffer; // Current log report
		std::vector<std::string> m_Backbuffer; // Total log report

		// Loggers:
		ConsoleLogger* m_pConsoleLogger;
		FileLogger* m_pFileLogger;

	private:
		ROFDEL(Logger);
	};
}

namespace Libero
{
	// Does nothing
	class NullLogger : public Logger
	{
	public:
		virtual void Log(LogType, const std::string&) override {}
		virtual void LogInfo(const std::string&) override {}
		virtual void LogWarning(const std::string&) override {}
		virtual void LogError(const std::string&) override {}
		virtual void ExplicitConsoleLog(LogType, const std::string&) override{}
		virtual void StartFileLogging(const std::string&) override{}
		virtual void StopFileLogging() override{}
	};
	class LoggerLocator : public ILiberoLocator<Logger, NullLogger> {};
}


