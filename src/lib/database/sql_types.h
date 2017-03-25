#ifndef _H_SQL_TYPES
#define _H_SQL_TYPES

#include <string>

class SQLTypes {

public:
  enum ColumnType {INT, DOUBLE, STRING};
  //std::string mapping[] = {"INT", "DOUBLE", "STRING"};
  
  static std::string getColumnType(const SQLTypes::ColumnType& type)
  {
    switch (type)
    {
      case SQLTypes::INT:
	return "INT";
	break;
	
      case SQLTypes::DOUBLE:
	return "DOUBLE";
	break;
	
      case SQLTypes::STRING:
	return "STRING";
	break;
	
      default:
	return "";
	break;
    }
  }
};

#endif
