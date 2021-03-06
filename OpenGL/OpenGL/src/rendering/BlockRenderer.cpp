#include "BlockRenderer.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


const int pX = 8;
const int pY = 7;

const float t = 1.0f / 16.0f;

float yMin = (16 - (pY + 1)) * t;
float yMax = (16 - (pY)) * t;
float xMin = pX * t;
float xMax = (pX + 1) * t;


float position[] = {
-0.5f, -0.5f, -0.5f,  xMin, yMin,
 0.5f, -0.5f, -0.5f,  xMax, yMin,
 0.5f,  0.5f, -0.5f,  xMax, yMax,
 0.5f,  0.5f, -0.5f,  xMax, yMax,
-0.5f,  0.5f, -0.5f,  xMin, yMax,
-0.5f, -0.5f, -0.5f,  xMin, yMin,
/*
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
*/
};


glm::mat4 model(1.0);

BlockRenderer::BlockRenderer(const Renderer& renderer) :
	shader("res/shaders/Sprite.shader"), tex("res/textures/terrain.png"), vb(position, 5 * 36 * sizeof(float)), renderer(renderer)
{	
	
	layout.Push<float>(3);
	layout.Push<float>(2);
	shader.Bind();		
	tex.Bind();
	shader.SetUniform1i("u_Texture", 0);
	va.AddBuffer(vb, layout);
	
	
}

void BlockRenderer::drawBlock(int x, int y, int z)
{
	//va.Bind();
	model = glm::translate(glm::mat4(1.0f), glm::vec3((float)x, (float)y, (float)z));
	renderer.Draw(va, shader, model);
}
