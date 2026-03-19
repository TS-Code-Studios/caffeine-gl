#include <caffeine-gl/gfx/CaffeineShader.hpp>

#include <iostream>


void CaffeineShader::activate() const {
    glUseProgram(this->ID);
}

CaffeineShader::~CaffeineShader() {
    glDeleteProgram(this->ID);
}


void CaffeineShader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
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

    glLinkProgram(this->ID);

    checkCompileErrors(this->ID, "PROGRAM");
}

void CaffeineShader::setFloat(const char *name, const float value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void CaffeineShader::setInteger(const char *name, const int value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void CaffeineShader::setVector2f(const char *name, const float x, const float y, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void CaffeineShader::setVector2f(const char *name, const glm::vec2 &value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void CaffeineShader::setVector3f(const char *name, const float x, const float y, const float z, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void CaffeineShader::setVector3f(const char *name, const glm::vec3 &value, const bool activateShader) {
    if (activateShader)
        this->activate();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void CaffeineShader::setVector4f(const char *name, const float x, const float y, const float z, const float w, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void CaffeineShader::setVector4f(const char *name, const glm::vec4 &value, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void CaffeineShader::setMatrix4(const char *name, const glm::mat4 &matrix, const bool activateShader) {
    if (activateShader) {
        this->activate();
    }

    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void CaffeineShader::checkCompileErrors(const unsigned int object, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cerr << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cerr << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}