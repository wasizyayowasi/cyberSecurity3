#include <DxLib.h>
#include <cassert>
#include "DrawFunctions.h"

namespace My {
	int MyLoadGraph(const TCHAR* path) {
		int handle = LoadGraph(path);
		assert(handle >= 0);
		return handle;
	}
}
