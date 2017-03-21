#ifndef _H_I_DATABASE
#define _H_I_DATABASE

#include <string>
#include <vector>

class IDatabase {

public:
  explicit IDatabase() {};
  virtual ~IDatabase() {};

  virtual bool openDatabase(std::vector<std::string> inputParams = std::vector<std::string>()) = 0;
};

#endif
