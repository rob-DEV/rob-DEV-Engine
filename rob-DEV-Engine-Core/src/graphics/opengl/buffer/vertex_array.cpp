#include "vertex_array.h"
#if(_ENGINE_RENDERER_OPENGL)
namespace Engine { namespace Core { namespace Graphics { namspace OpenGL { namespace Buffers {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VAO);	
		bind();
	}


	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_VAO);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::del()
	{
		
	}

} } } } }

#endif
