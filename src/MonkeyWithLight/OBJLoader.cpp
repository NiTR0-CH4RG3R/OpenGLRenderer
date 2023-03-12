
// Local Includes
#include "OBJLoader.h"

// Standard Includes
#include <fstream>
#include <sstream>
#include <iterator>

OBJLoader::OBJLoader(const std::string & filename)
{
	LoadObjToMemory(filename);
	CreateVerticesAndIndices();
}

OBJLoader::~OBJLoader()
{
}

bool OBJLoader::LoadObjToMemory(const std::string & filename)
{
	m_positions.clear();
	m_uvs.clear();
	m_normals.clear();
	m_faces.clear();

	// open the wavefront .obj file
	std::ifstream file(filename);

	// check if the file is opened
	if (!file.is_open()) {
		err = "Can't open \"" + filename + "\" file";
		return false;
	}

	// Loop through all the lines in the file
	std::string line;
	while (std::getline(file, line)) {

		// break the line into words
		std::istringstream iss(line);
		std::vector<std::string> words(
			std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>()
		);

		if (!words.empty()) {
			if (words[0] == "v") {
				m_positions.push_back({ -std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) });
			}
			else if (words[0] == "vt") {
				m_bUVsPresent = true;
				m_uvs.push_back({ std::stof(words[1]), 1.0f - std::stof(words[2]) });
			}
			else if (words[0] == "vn") {
				m_bNormalsPresent = true;
				m_normals.push_back({ -std::stof(words[1]), std::stof(words[2]), std::stof(words[3]) });
			}
			else if (words[0] == "f") {
				Face face;
				face.VerticesPerFace = (uint32_t)words.size() - 1;
				face.Indices.resize((size_t)face.VerticesPerFace);

				for (uint32_t i = face.VerticesPerFace; i > 0; i--) {
					VertexIndex& f = face.Indices[face.VerticesPerFace - i];
					std::vector<std::string> indices = Split(words[i], '/');
					f.PosIndex = (uint32_t)std::stoi(indices[0]) - 1u;
					f.UVIndex = m_bUVsPresent ? (uint32_t)std::stoi(indices[1]) - 1u : 0u;
					f.NormalIndex = m_bNormalsPresent ? (uint32_t)std::stoi(indices[2]) - 1u : 0u;
				}

				m_faces.push_back(face);
			}
		}
	}

	// close the file
	file.close();
	return true;
}

void OBJLoader::CreateVerticesAndIndices()
{
	for (const auto& face : m_faces) {
		for (uint32_t i = 1; i < face.VerticesPerFace - 1u; i++) {

			const auto& v0 = face.Indices[0];
			const auto& v1 = face.Indices[i];
			const auto& v2 = face.Indices[i + 1];

			if (m_VertexIndices.find(v0) == m_VertexIndices.end()) {
				// a new vertex found
				Vertex v;
				v.Position = m_positions.at((size_t)v0.PosIndex);
				v.UV = m_bUVsPresent ? m_uvs.at((size_t)v0.UVIndex) : Vector2{};
				v.Normal = m_bNormalsPresent ? m_normals.at((size_t)v0.NormalIndex) : Vector3{};

				vertices.push_back(v);
				uint32_t index = (uint32_t)(vertices.size() - 1);
				m_VertexIndices.insert({ v0,index });
				indices.push_back(index);
			}
			else {
				// vertex already exists
				indices.push_back(m_VertexIndices.at(v0));
			}

			if (m_VertexIndices.find(v1) == m_VertexIndices.end()) {
				// a new vertex found
				Vertex v;
				v.Position = m_positions.at((size_t)v1.PosIndex);
				v.UV = m_bUVsPresent ? m_uvs.at((size_t)v1.UVIndex) : Vector2{};
				v.Normal = m_bNormalsPresent ? m_normals.at((size_t)v1.NormalIndex) : Vector3{};

				vertices.push_back(v);
				uint32_t index = (uint32_t)(vertices.size() - 1);
				m_VertexIndices.insert({ v1,index });
				indices.push_back(index);
			}
			else {
				// vertex already exists
				indices.push_back(m_VertexIndices.at(v1));
			}

			if (m_VertexIndices.find(v2) == m_VertexIndices.end()) {
				// a new vertex found
				Vertex v;
				v.Position = m_positions.at((size_t)v2.PosIndex);
				v.UV = m_bUVsPresent ? m_uvs.at((size_t)v2.UVIndex) : Vector2{};
				v.Normal = m_bNormalsPresent ? m_normals.at((size_t)v2.NormalIndex) : Vector3{};

				vertices.push_back(v);
				uint32_t index = (uint32_t)(vertices.size() - 1);
				m_VertexIndices.insert({ v2,index });
				indices.push_back(index);
			}
			else {
				// vertex already exists
				indices.push_back(m_VertexIndices.at(v2));
			}
		}
	}
}

std::vector<std::string> OBJLoader::Split(const std::string & str, const char & delimeter) const {
	std::stringstream ss(str);
	std::string segment;
	std::vector<std::string> segments;

	while (std::getline(ss, segment, delimeter)) {
		segments.push_back(segment);
	}
	return segments;
}
