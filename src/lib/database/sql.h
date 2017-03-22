#ifndef _H_SQL
#define _H_SQL

#include <string>

class SQL
{

public:
  explicit SQL() {};
  virtual ~SQL() {};

  virtual bool append(const std::string& param, const std::string& value)
  {
    query.append("param");
    return true;
  }

protected:
  std::string query = ""; 

};

#endif
