#pragma once
#include <string>
#include <fstream>

namespace Utils
{
	std::string readTextFile(const char *fileName)
	{
		std::string fileContent;
		std::ifstream fileStream(fileName, std::ios::in);

		if (!fileStream.is_open())
		{
			printf("File %s not found\n", fileName);
			return "";
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			fileContent.append(line + "\n");
		}

		fileStream.close();
		return fileContent;
	}

}
