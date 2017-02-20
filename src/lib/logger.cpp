/*
 * Logger.cpp
 *
 *  Created on: 20. 2. 2017
 *      Author: martin
 */

#include "logger.h"

Logger::Logger(std::string filename, bool cout) {
	output.open(filename.c_str());
	this->cout = cout;
}

Logger::~Logger() {
	output.flush();
	output.close();
}

/*template<class TOut> Logger& Logger::operator <<(const TOut &data)
{
	output << data << std::endl;
	if(this->cout)
		std::cout << data << std::endl;

	return *this;
}*/
