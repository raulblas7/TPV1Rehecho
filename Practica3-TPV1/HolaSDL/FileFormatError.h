#pragma once

#include "ArrowsError.h";
#include <iostream>
#include <string>
#include "checkML.h"

class FileFormatError : public ArrowsError
{
public:
	FileFormatError(string f) : ArrowsError(f) {};
};

