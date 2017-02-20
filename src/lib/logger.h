/*
 * Logger.h
 *
 *  Created on: 20. 2. 2017
 *      Author: martin
 */

#ifndef SRC_LIB_LOGGER_H_
#define SRC_LIB_LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

class Logger {
private:
	bool cout;
	std::ofstream output;

public:
	Logger(std::string filename, bool cout);
	virtual ~Logger();

	template<class TOut> Logger& operator <<(const TOut& data) {
		output << data << std::endl;
		if (this->cout)
			std::cout << data;

		return *this;
	}
};


extern Logger dbg;
extern std::string lf;

#endif /* SRC_LIB_LOGGER_H_ */
