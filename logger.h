#pragma once

#include <stdio.h>
#include <mutex>
#include <ctime>

enum LogPriority
{
	TracePriority,
	DebugPriority,
	InfoPriority,
	WarnPriority,
	ErrorPriority,
	CriticalPriority
};

class Logger
{
private:
	static LogPriority priority;
	static std::mutex log_mutex;
	static const char *filepath;
	static FILE *file;

public:
	static void SetPriority(LogPriority new_priority)
	{
		priority = new_priority;
	}

	static void EnableFileOutput()
	{
		filepath = "log.txt";
		enable_file_output();
	}

	static void EnableFileOutput(const char *new_filepath)
	{
		filepath = new_filepath;
		enable_file_output();
	}

	static void CloseFileOutput()
	{
		free_file();
	}

	template <typename... Args>
	static void Trace(int line, const char* source_file,const char *message, Args... args)
	{
		log(line,source_file,"[Trace]\t", TracePriority, message, args...);
	}

	template <typename... Args>
	static void Debug(int line, const char* source_file,const char *message, Args... args)
	{
		log(line, source_file,"[Debug]\t", DebugPriority, message, args...);
	}

	template <typename... Args>
	static void Info(int line, const char* source_file,const char *message, Args... args)
	{
		log(line, source_file,"[Info]\t", InfoPriority, message, args...);
	}

	template <typename... Args>
	static void Warn(int line, const char* source_file,const char *message, Args... args)
	{
		log(line, source_file,"[Warn]\t", WarnPriority, message, args...);
	}

	template <typename... Args>
	static void Error(int line, const char* source_file,const char *message, Args... args)
	{
		log(line, source_file,"[Error]\t", ErrorPriority, message, args...);
	}

	template <typename... Args>
	static void Critical(int line, const char* source_file,const char *message, Args... args)
	{
		log(line,source_file,"[Critical]\t", CriticalPriority, message, args...);
	}

private:
	// template<typename... Args>
	// static void log(const char* message_priority_str, LogPriority message_priority, const char* message, Args... args)
	// {
	// 	if (priority <= message_priority)
	// 	{
	// 		std::time_t current_time = std::time(0);
	// 		std::tm* timestamp = std::localtime(&current_time);
	// 		char buffer[80];
	// 		strftime(buffer, 80, "%c", timestamp);

	// 		std::scoped_lock lock(log_mutex);
	// 		printf("%s\t", buffer);
	// 		printf(message_priority_str);
	// 		printf(message, args...);
	// 		printf("\n");

	// 		if (file)
	// 		{
	// 			fprintf(file, "%s\t", buffer);
	// 			fprintf(file, message_priority_str);
	// 			fprintf(file, message, args...);
	// 			fprintf(file, "\n");
	// 		}
	// 	}
	// }
    template<typename... Args>	
	static void log(int line_number, const char *source_file, const char *message_priority_str, LogPriority message_priority, const char *message, Args... args)
	{
		if (priority <= message_priority)
		{
			std::time_t current_time = std::time(0);
			std::tm *timestamp = std::localtime(&current_time);
			char buffer[80];
			strftime(buffer, 80, "%c", timestamp);

			std::scoped_lock lock(log_mutex);
			printf("%s\t", buffer);
			printf(message_priority_str);
			printf(message, args...);
			printf(" on line %d in %s", line_number, source_file);
			printf("\n");

			if (file)
			{
				fprintf(file, "%s\t", buffer);
				fprintf(file, message_priority_str);
				fprintf(file, message, args...);
				fprintf(file, " on line %d in %s", line_number, source_file);
				fprintf(file, "\n");
			}
		}
	}

	static void enable_file_output()
	{
		if (file != 0)
		{
			fclose(file);
		}

		file = fopen(filepath, "a");

		if (file == 0)
		{
			printf("Logger: Failed to open file at %s", filepath);
		}
	}

	static void free_file()
	{
		fclose(file);
		file = 0;
	}
};

LogPriority Logger::priority = InfoPriority;
std::mutex Logger::log_mutex;
const char *Logger::filepath = 0;
FILE *Logger::file = 0;