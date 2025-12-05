
//------  Drow_Switch.cpp  ------
#include"Drow_Polygon.h"

using namespace PG;

 
[[nodiscard]] bool Drow_Polygon::createTriangle(const Device& device)noexcept
{
	
	uint16_t I[] = { 0,1,2 };
	if (!create(device,Triangle)) {
		assert(false && "OŠpŒ`‚Ìƒ|ƒŠƒSƒ“‚Ìì¬‚É¸”s");
		return false;
	}
	return true;
}