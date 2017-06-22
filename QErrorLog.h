#pragma once

#include <cstdio>
#include <string>
#include <time.h>

struct QErrorLog
{
	int QERROR_CODE;
	char* QERROR_MSG;
	char* QERROR_DIR;

	QErrorLog(int ERROR_CODE, char* ERROR_MSG, char* LOG_DIR) :
		QERROR_CODE(ERROR_CODE),
		QERROR_MSG(ERROR_MSG),
		QERROR_DIR(LOG_DIR)
	{};

	void OUTPUT_LOG()
	{
		time_t PT_CUR = time(0);
		struct tm * TIME_CUR = localtime(&PT_CUR);
		std::string LOG_NAME = "QERRx" + std::to_string(QERROR_CODE) + "x_" + std::to_string(TIME_CUR->tm_mday) + std::to_string(TIME_CUR->tm_hour);
			LOG_NAME += ".txt";
		std::string FULL_DIR = QERROR_DIR;
			FULL_DIR += "\\";
			FULL_DIR += LOG_NAME;

		FILE* fLOG = fopen(FULL_DIR.c_str(), "w");
		fprintf(fLOG, "%s", this->QERROR_MSG);
		fclose(fLOG);
	}
};

