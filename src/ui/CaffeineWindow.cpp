#include <caffeine-gl/ui/CaffeineWindow.h>
#include <glad/glad.h>

void errorCallback(int error_code, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

CaffeineWindow::CaffeineWindow() {
	this->initGLFW();

	// Set all keys to false
	std::fill(std::begin(this->keys), std::end(this->keys), false);
	std::fill(std::begin(this->processedKeys), std::end(this->processedKeys), false);
}

CaffeineWindow::~CaffeineWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


void CaffeineWindow::initGLFW() {
	glfwSetErrorCallback(errorCallback);

	if(!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->primaryMonitor = glfwGetPrimaryMonitor();
	this->videoMode = glfwGetVideoMode(primaryMonitor);

	WIDTH = videoMode->width;
	HEIGHT = videoMode->height;

	// Set GLFW AA samples to 4
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "CaffeineGL Window", primaryMonitor, nullptr);

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

void CaffeineWindow::createViewport() const {
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CaffeineWindow::setWindowTitle(const char* newTitle) const {
	glfwSetWindowTitle(window, newTitle);
}

void errorCallback(int error_code, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	if(auto* thisWindow = static_cast<CaffeineWindow*>(glfwGetWindowUserPointer(window))) {
		thisWindow->WIDTH = width;
		thisWindow->HEIGHT = height;
	}
}

// Temporary solution, rework to make more customizable once Flappy Bird is done
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(auto* thisWindow = static_cast<CaffeineWindow*>(glfwGetWindowUserPointer(window))) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
			thisWindow->shouldClose = true;
		}

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