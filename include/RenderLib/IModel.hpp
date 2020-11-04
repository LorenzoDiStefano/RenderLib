#ifndef RENDERLIB_IMODEL
#define RENDERLIB_IMODEL

#include <RenderLib/MeshData.hpp>
#include <RenderLib/Texture.hpp>

namespace RenderLib
{
	class IGPUApi;
	class IMesh;

	class IModel
	{
		public:

			// model data
			std::vector<Texture> textures_loaded;

			void setActiveTexture();

			virtual void LoadAssets(MeshData) {};
			virtual void LoadMeshes(MeshData&, const IGPUApi&) = 0;
			void Draw() {};

			std::vector<std::shared_ptr<RenderLib::IMesh>> modelMeshes;
			uint16_t meshesCount;
	};
}

#endif // !IMODEL_DEFINED
