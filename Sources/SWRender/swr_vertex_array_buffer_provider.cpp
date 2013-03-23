/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "SWRender/precomp.h"
#include "swr_vertex_array_buffer_provider.h"

namespace clan
{

/////////////////////////////////////////////////////////////////////////////
// SWRenderVertexArrayBufferProvider Construction:

SWRenderVertexArrayBufferProvider::SWRenderVertexArrayBufferProvider()
{
}

SWRenderVertexArrayBufferProvider::~SWRenderVertexArrayBufferProvider()
{
}

void SWRenderVertexArrayBufferProvider::create(int size, BufferUsage usage)
{
}

void SWRenderVertexArrayBufferProvider::create(void *data, int size, BufferUsage usage)
{
}

/////////////////////////////////////////////////////////////////////////////
// SWRenderVertexArrayBufferProvider Attributes:

void *SWRenderVertexArrayBufferProvider::get_data()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// SWRenderVertexArrayBufferProvider Operations:

void SWRenderVertexArrayBufferProvider::lock(BufferAccess access)
{
}

void SWRenderVertexArrayBufferProvider::unlock()
{
}

void SWRenderVertexArrayBufferProvider::upload_data(GraphicContext &gc, int offset, const void *data, int size)
{
}
void SWRenderVertexArrayBufferProvider::copy_from(GraphicContext &gc, TransferBuffer &buffer, int dest_pos, int src_pos, int size)
{
}
void SWRenderVertexArrayBufferProvider::copy_to(GraphicContext &gc, TransferBuffer &buffer, int dest_pos, int src_pos, int size)
{
}

/////////////////////////////////////////////////////////////////////////////
// SWRenderVertexArrayBufferProvider Implementation:

}
