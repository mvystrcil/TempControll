#include "logger.h"

#include <string>
#include <stdio.h>

LogLevel Logger::current = INFO;
std::ofstream Logger::file;

Logger::Logger()
{

}

Logger::Logger(const Logger& other)
{

}

Logger::~Logger()
{
  str << std::endl;
  
  fprintf(stdout, "%s", str.str().c_str());
  fflush(stdout);
  
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

void Logger::finishLogSession()
{
  if(file.is_open())
  {
    file.flush();
    file.close();
  }
}

std::ostringstream& Logger::get(const LogLevel& level)
{
  str << "[" << Logger::toString(level) << "] ";
  
  return str;
}

std::string Logger::toString(const LogLevel& level)
{
  return mapping[level];
}


Logger& Logger::operator=(const Logger&)
{

}
