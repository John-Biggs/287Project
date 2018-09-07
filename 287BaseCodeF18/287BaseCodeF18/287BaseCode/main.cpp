#include <ctime>
#include <vector>
#include "defs.h"
#include "Utilities.h"
#include "FrameBuffer.h"
#include "ColorAndMaterials.h"

int main(int argc, char *argv[]) {
	std::cout << approximatelyEqual(1.0f, 1.000001f) << std::endl;

	std::cout << "Expect 0: " << normalizeDegrees(0) << std::endl;
	std::cout << "Expect 0: " << normalizeDegrees(360) << std::endl;
	std::cout << "Expect 100: " << normalizeDegrees(100) << std::endl;
	std::cout << "Expect 359: " << normalizeDegrees(-1) << std::endl;

	return 0;
}