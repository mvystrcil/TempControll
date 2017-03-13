#ifndef _H_LOGLEVELS_
#define _H_LOGLEVELS_

#include <string>

#define LOG_LEVELS_COUNT 4

enum LogLevel {ERROR, WARNING, INFO, DEBUG};
static const char* const mapping[LOG_LEVELS_COUNT] = {"ERR", "WRN", "INFO", "DBG"};

/*std::string getPossibleLogLevels()
{
  std::string ret = "";
  
  for(int i = 0; i < LOG_LEVELS_COUNT; i++)
  {
    ret.append(mapping[i]);
    if(i < (LOG_LEVELS_COUNT - 1))
    {
      ret.append(",");
    }
  }
  
  return ret;
}*/

#endif