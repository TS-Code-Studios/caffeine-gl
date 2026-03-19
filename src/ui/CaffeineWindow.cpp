#include <caffeine-gl/ui/CaffeineWindow.hpp>

#include "../../include/caffeine-gl/systems/CaffeineRenderingSystem.hpp"


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
	#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
	#endif

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);

	if(window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwGetWindowPos(window, &windowPositionX, &windowPositionY);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

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

	const float scaleX = static_cast<float>(windowWidth) / 1920.0f;
	const float scaleY = static_cast<float>(windowWidth) / 1080.0f;

	const float scale = std::min(scaleX, scaleY);

	const int viewportWidth  = static_cast<int>(1920 * scale);
	const int viewportHeight = static_cast<int>(1080 * scale);

	const int viewportX = (windowWidth  - viewportWidth)  / 2;
	const int viewportY = (windowHeight - viewportHeight) / 2;

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

void CaffeineWindow::enableFullscreen() {
	if (!fullscreen) {
		glfwSetWindowMonitor(window, primaryMonitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
		fullscreen = true;
	}
}

void CaffeineWindow::disableFullscreen() {
	if (fullscreen) {
		glfwSetWindowMonitor(window, nullptr, windowPositionX, windowPositionY, windowWidth, windowHeight, videoMode->refreshRate);
		fullscreen = false;
	}
}

void CaffeineWindow::toggleFullscreen() {
	if (fullscreen) {
		disableFullscreen();
	} else {
		enableFullscreen();
	}
}



// GLFW callback functions
void errorCallback(int error_code, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	if(auto* thisWindow = static_cast<CaffeineWindow*>(glfwGetWindowUserPointer(window))) {
		const float scaleX = static_cast<float>(width)  / CaffeineRenderingSystem::virtualWidth;
		const float scaleY = static_cast<float>(height) / CaffeineRenderingSystem::virtualHeight;

		const float scale = std::min(scaleX, scaleY);

		const int viewportWidth  = static_cast<int>(CaffeineRenderingSystem::virtualWidth * scale);
		const int viewportHeight = static_cast<int>(CaffeineRenderingSystem::virtualHeight * scale);

		const int viewportX = (width  - viewportWidth)  / 2;
		const int viewportY = (height - viewportHeight) / 2;

		thisWindow->framebufferWidth = width;
		thisWindow->framebufferHeight = height;
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