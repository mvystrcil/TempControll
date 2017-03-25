#ifndef _H_I_DATABASE
#define _H_I_DATABASE

#include <string>
#include <vector>

#include "sql.h"
#include <unordered_map>

class IDatabase {

public:
  explicit IDatabase() {};
  virtual ~IDatabase() {};

  /*
  * All parameters are passed in a vector as strings
  */
  virtual bool openDatabase(const std::unordered_map< std::string, std::string >& params) = 0;
  virtual bool closeDatabase() = 0;
  
  virtual bool executeQuery(SQL *query) = 0;
};

#endif
