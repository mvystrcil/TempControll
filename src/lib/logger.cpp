#include "logger.h"

#include <string>
#include <stdio.h>

LogLevel Logger::current = INFO;
std::ofstream Logger::file;
bool Logger::consoleEnabled = true;

Logger::Logger()
{

}

Logger::Logger(const Logger& other)
{

}

Logger::~Logger()
{
  str << std::endl;
  
  if(consoleEnabled)
  {
    fprintf(stdout, "%s", str.str().c_str());
    fflush(stdout);
  }
  
  if(file.is_open())
  {
    file << str.str();
  }
}

LogLevel& Logger::getReportingLevel()
{
  return current;
}

void Logger::setReportingLevel(const LogLevel& level)
{
  Logger::current = level;
}

void Logger::setLogToFile(const std::string& path)
{
  if(file.is_open())
  {
   //warn << "Log file already opened, skip it"; 
    return;
  }
  else
  {
    file.open(path);
  }
}

void Logger::setLogToConsole(const bool logToConsole)
{
  consoleEnabled = logToConsole;
}

void Logger::finishLogSession()
{
  if(file.is_open())
  {
    file.flush();
    file.close();
  }
}

std::ostringstream& Logger::get(const LogLevel& level, const std::string& file, int line)
{
  str << "[" << Logger::toString(level) << "]";
  str << "[" << file << ":" << line << "] ";
  
  return str;
}

std::string Logger::toString(const LogLevel& level)
{
  return mapping[level];
}


Logger& Logger::operator=(const Logger&)
{

}
