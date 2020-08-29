#pragma once

#include "ArrowsError.h";
#include <iostream>
#include <string>

class FileFormatError : public ArrowsError
{
public:
	FileFormatError(string f) : ArrowsError(f) {};
};

