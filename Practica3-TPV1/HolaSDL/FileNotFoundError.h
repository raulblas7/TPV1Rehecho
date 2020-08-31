#pragma once

#include "ArrowsError.h";
#include <string>;
#include <iostream>;
#include "checkML.h"

class FileNotFoundError : public ArrowsError
{
public:
	FileNotFoundError(string f) : ArrowsError(f) {};
};

