#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_

// Local Includes
#include "xxhash32.h"
#include "xxhash64.h"

// Standard Includes
#include <string>
#include <vector>
#include <unordered_map>

class OBJLoader {
private:
	union Vector3 { struct { float x, y, z; }; float element[3]; };
	union Vector2 { struct { float x, y;	}; float element[2]; };

	struct Vertex {
		Vector3 Position;
		Vector2 UV;
		Vector3 Normal;
	};

	struct VertexIndex {
		uint32_t PosIndex;
		uint32_t UVIndex;
		uint32_t NormalIndex;

		inline bool operator == (const VertexIndex& rhs) const { return (this->PosIndex == rhs.PosIndex) && (this->UVIndex == rhs.UVIndex) && (this->NormalIndex == rhs.NormalIndex); }
	};

	struct VertexIndexKeyHasher {
		std::size_t operator()(const VertexIndex& k) const {
#if defined (_WIN32)
#if defined (_WIN64)
			return XXHash64::hash(&k, (uint64_t)sizeof(VertexIndex), 0);
#else
			return XXHash32::hash(&k, (uint64_t)sizeof(VertexIndex), 0);
#endif
#endif
		}
	};

	struct Face {
		uint32_t VerticesPerFace;
		std::vector<VertexIndex> Indices;
	};

public:
	OBJLoader(const std::string& filename);
	~OBJLoader();
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

private:
	bool LoadObjToMemory(const std::string& filename);
	void CreateVerticesAndIndices();
	std::vector<std::string> Split(const std::string & str, const char & delimeter) const;
private:
	std::vector<Vector3> m_positions;
	std::vector<Vector2> m_uvs;
	std::vector<Vector3> m_normals;
	std::vector<Face> m_faces;

	
	std::unordered_map<VertexIndex, uint32_t, VertexIndexKeyHasher> m_VertexIndices;
	

	std::string err = "SUCCESS";

	bool m_bUVsPresent = false;
	bool m_bNormalsPresent = false;
};

#endif // !_OBJ_LOADER_H_
