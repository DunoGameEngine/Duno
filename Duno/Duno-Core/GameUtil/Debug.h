#pragma once
#include <string>
using namespace std;

namespace Debug
{
	struct NOTFOUND { string msg = "Object not found error"; };
	template <typename Type> void error(Type type, string msg = "");
}