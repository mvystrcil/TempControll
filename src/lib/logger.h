#ifndef _H_LOGGER
#define _H_LOGGER

#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>

enum LogLevel {ERROR, WARNING, INFO, DEBUG};
static const char* const mapping[] = {"ERR", "WRN", "INFO", "DBG"};

#define log(level) \
  if(level > Logger::getReportingLevel()) \
    ; \
  else \
    Logger().get(level)
  
#define err \
  log(ERROR)
  
#define warn \
  log(WARNING)
  
#define info \
  log(INFO)
  
#define dbg \
  log(DEBUG)
  

class Logger {

private:
  static LogLevel current;
  static std::ofstream file;
  
  Logger(const Logger& other);
  Logger& operator =(const Logger&);
  static std::string toString(const LogLevel& level);

public:
  Logger();
  virtual ~Logger();
  std::ostringstream& get(const LogLevel& level = INFO);
  
  static LogLevel& getReportingLevel();
  static void setReportingLevel(const LogLevel& level = INFO);
  static void setLogToFile(const std::string& path);
  static void finishLogSession();
  
protected:
  std::ostringstream str;
  
};

#endif
