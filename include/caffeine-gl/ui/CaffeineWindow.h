#ifndef CAFFEINEWINDOW_H
#define CAFFEINEWINDOW_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CaffeineWindow {
public:
	int WIDTH, HEIGHT;
	bool keys[1024]{}, processedKeys[1024]{};

	GLFWmonitor* primaryMonitor;
	const GLFWvidmode *videoMode;


	explicit CaffeineWindow(const char* title = "Caffeine Window");
	~CaffeineWindow();

	// Utility functions
	void createViewport() const;
	void update() const;

	// Configuration functions
	void setWindowTitle(const char* newTitle) const;

private:
	GLFWwindow* window;
};

// GLFW callback function forward declarations
void errorCallback(int error_code, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif //CAFFEINEWINDOW_H
