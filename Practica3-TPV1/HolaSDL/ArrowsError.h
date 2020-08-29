#pragma once

#include <stdexcept>
#include <string>
using namespace std;

class ArrowsError : public logic_error
{
public:
	ArrowsError(const string& f) :logic_error("ArrowsError: " + f) {};
};



