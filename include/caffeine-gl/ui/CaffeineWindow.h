#ifndef CAFFEINEWINDOW_H
#define CAFFEINEWINDOW_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CaffeineWindow {
public:
	int WIDTH, HEIGHT;
	bool keys[1024], processedKeys[1024];

	GLFWwindow* window;

	GLFWmonitor* primaryMonitor;
	const GLFWvidmode *videoMode;

	CaffeineWindow();
	~CaffeineWindow();

	void createViewport() const;
	void setWindowTitle(const char* newTitle) const;

private:
	void initGLFW();
};

#endif //CAFFEINEWINDOW_H
