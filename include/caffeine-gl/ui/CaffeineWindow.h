#ifndef CAFFEINEWINDOW_H
#define CAFFEINEWINDOW_H

#include <iostream>

#include <GLFW/glfw3.h>

class CaffeineWindow {
public:
	int WIDTH, HEIGHT;
	bool keys[1024], processedKeys[1024];
	bool shouldClose;

	GLFWmonitor* primaryMonitor;
	const GLFWvidmode *videoMode;

	CaffeineWindow();
	~CaffeineWindow();

	void createViewport() const;
	void setWindowTitle(const char* newTitle) const;

private:
	void initGLFW();

	GLFWwindow* window;
};

#endif //CAFFEINEWINDOW_H
