#pragma once
#include <string>
using namespace std;

namespace Debug
{
	template <typename Type> void error(Type type, string msg = "");
}