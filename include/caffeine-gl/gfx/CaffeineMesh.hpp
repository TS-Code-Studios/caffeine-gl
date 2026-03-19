#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <glad/glad.h>

struct Vertex2D {
	float x, y;
	float u, v;
	float r, g, b, a;
};

struct CaffeineMesh {
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;

	uint32_t indexCount = 0;

	CaffeineMesh() = default;

	CaffeineMesh(const CaffeineMesh&) = delete;
	CaffeineMesh& operator=(const CaffeineMesh&) = delete;

	CaffeineMesh(CaffeineMesh&& other) noexcept {
		vao = other.vao;
		vbo = other.vbo;
		ebo = other.ebo;
		indexCount = other.indexCount;

		other.vao = 0;
		other.vbo = 0;
		other.ebo = 0;
	}

	CaffeineMesh& operator=(CaffeineMesh&& other) noexcept {
		vao = other.vao;
		vbo = other.vbo;
		ebo = other.ebo;
		indexCount = other.indexCount;

		other.vao = 0;
		other.vbo = 0;
		other.ebo = 0;
		return *this;
	}

	CaffeineMesh(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices) {
		bufferData(vertices, indices);
	}

	~CaffeineMesh() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	void bufferData(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices) {
		// If buffers have been created before, delete old buffers before creating new ones to avoid GPU memory leaks
		if (vao != 0) {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
		}

		indexCount = static_cast<uint32_t>(indices.size());

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		// Buffer vertices in VBO
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
		// Buffer indices data in EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

		// VAO setup
		// XY is stored at position 0
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);
		// UV is stored at position 1
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void *>(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// RGBA is stored at position 2
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void *>(4 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void draw() const {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, static_cast<void*>(nullptr));
		glBindVertexArray(0);
	}
};

#endif //MESH_HPP
