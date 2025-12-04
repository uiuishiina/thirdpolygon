
//------  Drow_Switch.cpp  ------
#include"Drow_Polygon.h"

using namespace PG;

namespace {
	//------  ポリゴンの構造体  ------
	// Data.Buffer_		= Vertex
	// Data.Index_		= uint6_t
	// Data.UseTopology_= D3D_PRIMITIVE_TOPOLOGY

	//三角形
	Data Triangle{
		Triangle.Buffer_ = std::vector<Vertex> {
		{{	0,	0,	0},{	1,	0,	0,	1}},
		{{	0,	0,	0},{	0,	1,	0,	1}},
		{{	0,	0,	0},{	0,	0,	1,	1}}
	},
	Triangle.Index_ = 3,
	Triangle.UseTopology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	};
}
 
[[nodiscard]] bool Drow_Polygon::createTriangle(const Device& device)noexcept
{
	if (!create(device, Triangle)) {
		assert(false && "三角形のポリゴンの作成に失敗");
		return false;
	}
	return true;
}