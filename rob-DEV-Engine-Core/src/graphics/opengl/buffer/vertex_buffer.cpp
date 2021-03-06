#include "vertex_buffer.h"

#if(_ENGINE_RENDERER_OPENGL)
namespace Engine { namespace Core { namespace Graphics { namespace OpenGL { namespace Buffers {

	VertexBufferObject::VertexBufferObject()
	{
		glGenBuffers(1, &m_VBO);
	}


	VertexBufferObject::~VertexBufferObject()
	{
		glDeleteBuffers(1, &m_VBO);
	}
	void VertexBufferObject::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}

	void VertexBufferObject::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBufferObject::del()
	{
		glDeleteBuffers(1, &m_VBO);
	}

} } } } }

#endif