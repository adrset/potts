#pragma once
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"
#include "errors.h"
namespace GameEngine {
	class Model
	{
	public:
		/*  Functions   */
		Model(const char *path);
		~Model();
		virtual void draw(Shader& shader) = 0;
	protected:
		/*  Model Data  */
		std::vector<Mesh> meshes;
		std::string directory;
		/*  Functions   */
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
			std::string typeName);
	};
}
