#ifndef _H_I_DATABASE
#define _H_I_DATABASE

#include <string>
#include <vector>

#include "sql.h"

class IDatabase {

public:
  explicit IDatabase() {};
  virtual ~IDatabase() {};

  /*
  * All parameters are passed in a vector as strings
  * TODO: think about some better structure
  */
  virtual bool openDatabase(std::vector<std::string> inputParams = std::vector<std::string>()) = 0;
  
  virtual bool executeQuery(SQL *query) = 0;
};

#endif
