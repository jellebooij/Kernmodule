#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"


class BlockRenderer {

private:

	VertexArray va;
	VertexBufferLayout layout;
	Shader shader;
	Texture tex;
	VertexBuffer vb;
	Renderer renderer;


public:
	BlockRenderer(const Renderer& renderer);
	void drawBlock(int x, int y, int z);

};