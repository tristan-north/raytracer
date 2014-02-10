#include "meshdata.h"

MeshData::MeshData() {}


// this doesn't handle the vertex_faces
MeshData::MeshData(const MeshData& m) : vertices(m.vertices)
{}

MeshData::~MeshData() {}

// this doesn't handle the vertex_faces
MeshData& MeshData::operator= (const MeshData& rhs) {
	if (this == &rhs)
		return (*this);

	vertices 		= rhs.vertices;

	return (*this);
}





