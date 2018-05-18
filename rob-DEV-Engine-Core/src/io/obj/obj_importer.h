#pragma once
#include "../../common/singleton_instance.h"
#include "../../graphics/mesh.h"

#define OBJ_IMPORTER Obj_Importer::getInstance()

namespace Engine { namespace Core { namespace IO { namespace Importers { 
	class Obj_Importer : Singleton_Instance
	{
	private:
	
	public:
		Obj_Importer();
		~Obj_Importer();
		static Obj_Importer* getInstance();

		Engine::Core::Graphics::Mesh* ImportObj(const char* filePath);
	};
}  }  }  }
