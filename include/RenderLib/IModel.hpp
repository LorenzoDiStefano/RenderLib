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
			virtual void LoadModel(ModelDescriptor&, const IGPUApi&) = 0;
			virtual void ActivateTextures() = 0;
	};
}

#endif // !IMODEL_DEFINED
