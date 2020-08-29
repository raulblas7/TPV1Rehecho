#pragma once

#include "ArrowsError.h";
#include <string>;
#include <iostream>;

class FileNotFoundError : public ArrowsError
{
public:
	FileNotFoundError(string f) : ArrowsError(f) {};
};

