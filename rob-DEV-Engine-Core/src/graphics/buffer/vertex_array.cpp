#include "vertex_array.h"

namespace Engine { namespace Core { namespace Graphics { namespace Buffers {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VAO);	
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
		glGenVertexArrays(1, &m_VAO);
	}

} } } }
