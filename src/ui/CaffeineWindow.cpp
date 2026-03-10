#include <caffeine-gl/ui/CaffeineWindow.hpp>

#include "caffeine-gl/gfx/Renderer.hpp"


CaffeineWindow::CaffeineWindow(const char* title) {
	// GLFW initialization and basic setup
	glfwSetErrorCallback(errorCallback);

	if(!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->primaryMonitor = glfwGetPrimaryMonitor();
	this->videoMode = glfwGetVideoMode(primaryMonitor);

	windowWidth = videoMode->width;
	windowHeight = videoMode->height;

	// Set GLFW Anti-Aliasing samples to 4
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, title, primaryMonitor, nullptr);

	if(window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	glfwMakeContextCurrent(window);
}

CaffeineWindow::~CaffeineWindow() {
	glfwDestroyWindow(window);

	glfwTerminate();
}


// Utility functions
void CaffeineWindow::createViewport() const {
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	float scaleX = windowWidth  / 1920.0f;
	float scaleY = windowHeight / 1080.0f;

	float scale = std::min(scaleX, scaleY);

	int viewportWidth  = static_cast<int>(1920 * scale);
	int viewportHeight = static_cast<int>(1080 * scale);

	int viewportX = (windowWidth  - viewportWidth)  / 2;
	int viewportY = (windowHeight - viewportHeight) / 2;

	glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CaffeineWindow::update() const {
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
}


// Configuration functions
void CaffeineWindow::setWindowTitle(const char* newTitle) const {
	glfwSetWindowTitle(window, newTitle);
}



// GLFW callback functions
void errorCallback(int error_code, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	if(auto* thisWindow = static_cast<CaffeineWindow*>(glfwGetWindowUserPointer(window))) {
		const float scaleX = width  / Renderer::virtualWidth;
		const float scaleY = height / Renderer::virtualHeight;

		const float scale = std::min(scaleX, scaleY);

		const int viewportWidth  = static_cast<int>(Renderer::virtualWidth * scale);
		const int viewportHeight = static_cast<int>(Renderer::virtualHeight * scale);

		const int viewportX = (width  - viewportWidth)  / 2;
		const int viewportY = (height - viewportHeight) / 2;

		thisWindow->windowWidth = width;
		thisWindow->windowHeight = height;
		glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
	}
}

// Temporary solution, rework to make more customizable once Flappy Bird is done
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(auto* thisWindow = static_cast<CaffeineWindow*>(glfwGetWindowUserPointer(window))) {
		if (key < 0 || key >= 1024) {
			return;
		}

		if (action == GLFW_PRESS) {
			thisWindow->keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			thisWindow->keys[key] = false;
			thisWindow->processedKeys[key] = false;
		}
	}
}