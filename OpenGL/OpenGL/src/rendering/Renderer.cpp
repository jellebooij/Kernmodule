#include "Renderer.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer(const glm::mat4& proj, glm::mat4* view)
{
	this->proj = proj;
	this->view = view;
}



void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform)
{
	glm::mat4 mvp = proj * (*view) * modelTransform;
	
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);

	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
