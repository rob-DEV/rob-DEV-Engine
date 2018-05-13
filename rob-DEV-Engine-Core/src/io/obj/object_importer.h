#pragma once
#include "../../graphics/mesh.h"

namespace Engine { namespace Core { namespace IO { namespace Importers { 
	class Obj_Importer
	{
	private:
	
	public:
		Obj_Importer();
		~Obj_Importer();
		static Obj_Importer* getObjImporterInstance();

		Engine::Core::Graphics::Mesh* ImportObj(const char* filePath);
	};
}  }  }  }
