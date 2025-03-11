#include "Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::vector<LogEntry> Logger::messages;

std::string getTime() {
    std::time_t now = std::time(nullptr);
    std::tm ltm;  // Declare a local tm structure

    // Use localtime_s for safer conversion (Windows/MSVC)
    if (localtime_s(&ltm, &now) != 0) {
        return "Error retrieving time";
    }

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << ltm.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << ltm.tm_min << ":"
        << std::setw(2) << std::setfill('0') << ltm.tm_sec;

    return oss.str();
}

std::string getDate() {
	std::time_t now = std::time(nullptr);
	std::tm ltm;  // Declare a local tm structure
	// Use localtime_s for safer conversion (Windows/MSVC)
	if (localtime_s(&ltm, &now) != 0) {
		return "Error retrieving date";
	}
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << ltm.tm_mday << "/"
		<< std::setw(2) << std::setfill('0') << 1 + ltm.tm_mon << "/"
		<< 1900 + ltm.tm_year;
	return oss.str();
}

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LogType::INFO;
	logEntry.message = "LOG: [" + getDate() + " " + getTime() + "] : " + message;
	// Add log entry to the vector
	messages.push_back(logEntry);
	std::cerr << "\033[32m" << logEntry.message << "\033[0m" << std::endl;
}

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LogType::ERROR;
	logEntry.message = "ERR: [" + getDate() + " " + getTime() + "] : " + message;
	messages.push_back(logEntry);
	std::cerr << "\033[31m" << logEntry.message << "\033[0m" << std::endl;
}

void Logger::Warn(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LogType::WARNING;
	logEntry.message = "WARN: [ " + getDate() + " " + getTime() + " ]: " + message;
	messages.push_back(logEntry);
	std::cerr << "\033[33m" << logEntry.message << "\033[0m" << std::endl;
}