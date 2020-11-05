#ifndef RENDERLIB_IMODEL
#define RENDERLIB_IMODEL
#pragma once

#include <RenderLib/ModelDescriptor.hpp>
#include <memory>

namespace RenderLib
{
	class IGPUApi;
	class IMesh;

	class IModel
	{
		public:
			// model data
			std::vector<TextureDescriptor> textures_loaded;

			void setActiveTexture();
			//virtual void setActiveTexture() = 0;

			virtual void LoadAssets(ModelDescriptor) {};
			virtual void LoadModel(ModelDescriptor&, const IGPUApi&) = 0;
			void Draw() {};

			std::vector<std::shared_ptr<RenderLib::IMesh>> modelMeshes;
			uint16_t meshesCount = 0;
	};
}

#endif // !IMODEL_DEFINED
