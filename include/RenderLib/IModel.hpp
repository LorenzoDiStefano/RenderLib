#ifndef RENDERLIB_IMODEL
#define RENDERLIB_IMODEL
#pragma once

#include <RenderLib/utils/ModelDescriptor.hpp>
#include <memory>

namespace RenderLib
{
	class IGPUApi;
	class IMesh;

	class IModel
	{
		public:
			virtual void LoadModel(Utils::ModelDescriptor&, IGPUApi&) = 0;
	};
}

#endif // !IMODEL_DEFINED
