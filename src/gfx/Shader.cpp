#include "Shader.h"

#include <iostream>


Shader &Shader::activate() {
    glUseProgram(this->ID);
    return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {

    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);

    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (geometrySource != nullptr) {
        const unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometrySource, nullptr);

        glCompileShader(geometryShader);
        checkCompileErrors(geometryShader, "GEOMETRY");

        glAttachShader(this->ID, geometryShader);
        glDeleteShader(geometryShader);
    }
}

void Shader::setFloat(const char *name, const float value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setInteger(const char *name, const int value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f(const char *name, const float x, const float y, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVector2f(const char *name, const glm::vec2 &value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::setVector3f(const char *name, const float x, const float y, const float z, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVector3f(const char *name, const glm::vec3 &value, const bool activateShader) {
    if (activateShader)
        this->activate();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char *name, const float x, const float y, const float z, const float w, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::setVector4f(const char *name, const glm::vec4 &value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(const unsigned int object, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}