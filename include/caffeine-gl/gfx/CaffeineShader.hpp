#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class CaffeineShader {
public:
	unsigned int ID;

	CaffeineShader(): ID(0) {
	} ;

	~CaffeineShader();

	CaffeineShader(const CaffeineShader&) = delete;
	CaffeineShader& operator=(const CaffeineShader&) = delete;

	CaffeineShader(CaffeineShader&& other) noexcept {
		ID = other.ID;
		other.ID = 0;
	}

	CaffeineShader& operator=(CaffeineShader&& other) noexcept {
		if (this != &other) {
			glDeleteProgram(ID);
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}


	void activate() const;

	void compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);

	void setFloat(const char *name, float value, bool activateShader = false);

	void setInteger(const char *name, int value, bool activateShader = false);

	void setVector2f(const char *name, float x, float y, bool activateShader = false);
	void setVector2f(const char *name, const glm::vec2 &value, bool activateShader = false);

	void setVector3f(const char *name, float x, float y, float z, bool activateShader = false);
	void setVector3f(const char *name, const glm::vec3 &value, bool activateShader = false);

	void setVector4f(const char *name, float x, float y, float z, float w, bool activateShader = false);
	void setVector4f(const char *name, const glm::vec4 &value, bool activateShader = false);

	void setMatrix4(const char *name, const glm::mat4 &matrix, bool activateShader = false);

private:
	static void checkCompileErrors(unsigned int object, const std::string& type);
};

#endif //SHADER_H