#include <cstdlib>
#include <iostream>

#include "global/Context.h"
#include "shader/Shader.h"
#include "shape/Circle.h"
#include "shape/CubicCurve.h"
#include "shape/Ellipse.h"
#include "shape/LineSegment.h"


void cursorPosCallback(GLFWwindow *window, double, double);

void keyCallback(GLFWwindow *, int, int, int, int);

void mouseButtonCallback(GLFWwindow *, int, int, int);


// All global stuff are stored inside this context object
Context &context{Context::getInstance()};


int main() {
  // 1. Initialize OpenGL content by GLFW

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(context.WINDOW_WIDTH,
                                        context.WINDOW_HEIGHT,
                                        "PA1 - Line Segment Mode",
                                        nullptr,
                                        nullptr);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("failed to create GLFW window");
  }

  // Register all GUI callbacks here
  glfwMakeContextCurrent(window);
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  // 2. Load OpenGL functions pointers by GLAD

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    glfwTerminate();
    throw std::runtime_error("failed to initialize GLAD");
  }

  // 3. Build and compile our shader program
  Shader shader("./src/shader/vert.glsl", "./src/shader/frag.glsl");
  shader.use();

  shader.setFloat("windowWidth", static_cast<float>(context.WINDOW_WIDTH));
  shader.setFloat("windowHeight", static_cast<float>(context.WINDOW_HEIGHT));

  // 4. Set up buffer objects
  context.setupVertexObjects();

  // 6. Render loop
  glViewport(0, 0, context.WINDOW_WIDTH, context.WINDOW_HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    // send render commands to OpenGL server
    context.render();

    // Check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // De-allocate all resources once they've outlived their purpose:
  context.deleteVertexObjects();
  glDeleteProgram(shader.getShaderProgramHandle());
  glfwTerminate();

  return EXIT_SUCCESS;
}


void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_1: {
        glfwSetWindowTitle(window, "PA1 - Line Segment Mode");
        context.setState(Context::LINE_SEGMENT);
        break;
      }
      case GLFW_KEY_2: {
        glfwSetWindowTitle(window, "PA1 - Polyline Mode");
        context.setState(Context::POLYLINE);
        break;
      }
      case GLFW_KEY_3: {
        glfwSetWindowTitle(window, "PA1 - Polygon Mode");
        context.setState(Context::POLYGON);
        break;
      }
      case GLFW_KEY_4: {
        glfwSetWindowTitle(window, "PA1 - Circle Mode");
        context.setState(Context::CIRCLE);
        break;
      }
      case GLFW_KEY_5: {
        glfwSetWindowTitle(window, "PA1 - Ellipse Mode");
        context.setState(Context::ELLIPSE);
        break;
      }
      case GLFW_KEY_6: {
        glfwSetWindowTitle(window, "PA1 - Cubic Curve Mode");
        context.setState(Context::CUBIC_CURVE);
        break;
      }
      case GLFW_KEY_ESCAPE: {
        glfwSetWindowShouldClose(window, true);
        break;
      }
      default: {
        break;
      }
    }
  }
}


void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  switch (context.state) {
    case Context::LINE_SEGMENT:
    case Context::CIRCLE:
    case Context::ELLIPSE: {
      if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        context.lastMouseLeftPressXPos = context.cursorXPos;
        context.lastMouseLeftPressYPos = context.cursorYPos;
        context.showPreview = true;
      } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        context.showPreview = false;
      }

      break;
    }
    case Context::POLYLINE:
    case Context::POLYGON: {
      if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        ++context.mouseClickCount;
        // Set the first X and Y position if the first click is made
        if (context.mouseClickCount == 1) {
          context.firstXPos = context.cursorXPos;
          context.firstYPos = context.cursorYPos;
        }

        context.lastMouseLeftPressXPos = context.cursorXPos;
        context.lastMouseLeftPressYPos = context.cursorYPos;
        context.showPreview = true;

        if (context.mouseClickCount > 1) {
          context.vertexBufferDataPolyLine = context.vertexBufferData;
        }
      } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (context.state == Context::POLYGON && context.mouseClickCount >= 3) {
          // Create the final line segment connecting the last point to the
          // first point.
          LineSegment finalLineSegment = LineSegment(
              context.lastMouseLeftPressXPos,
              context.lastMouseLeftPressYPos,
              context.firstXPos,
              context.firstYPos
              );

          // Insert the final line segment into the polyline buffer.
          context.vertexBufferDataPolyLine.insert(
              context.vertexBufferDataPolyLine.end(),
              finalLineSegment.getPath().cbegin(),
              finalLineSegment.getPath().cend()
              );

          // Copy the new points to the vertex buffer.
          context.vertexBufferData = context.vertexBufferDataPolyLine;
        }

        context.vertexBufferDataPolyLine.clear();
        context.mouseClickCount = 0;
        context.showPreview = false;
      }

      break;
    }
    case Context::CUBIC_CURVE: {
      if (std::ifstream fin{"etc/parameter.txt"}) {
        double a, b, c, d;
        fin >> a >> b >> c >> d;
        context.vertexBufferData = CubicCurve(a, b, c, d,
                                              context.WINDOW_WIDTH,
                                              context.WINDOW_HEIGHT).getPath();
      } else {
        throw std::runtime_error("failed to open cubic curve parameter file");
      }

      break;
    }
    default: {
      glfwTerminate();
      throw std::invalid_argument(("unknown context state enumerator " +
                                   std::to_string(context.state)).c_str());
    }
  }
}


void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
  context.cursorXPos = xpos;
  context.cursorYPos = context.WINDOW_HEIGHT -
                       ypos;  // reverse y coordinate to facilitate debugging

  static LineSegment currentLineSegment;

  if (context.state == Context::LINE_SEGMENT ||
      context.state == Context::POLYLINE ||
      context.state == Context::POLYGON) {
    currentLineSegment = LineSegment(context.lastMouseLeftPressXPos,
                                     context.lastMouseLeftPressYPos,
                                     context.cursorXPos,
                                     context.cursorYPos);
  }

  if (context.showPreview) {
    switch (context.state) {
      case Context::LINE_SEGMENT: {
        context.vertexBufferData = currentLineSegment.getPath();
        break;
      }
      case Context::POLYLINE:
      case Context::POLYGON: {
        // Copy the previous lines and add the new line segment preview.
        std::vector<glm::vec2> currentLines =
            context.vertexBufferDataPolyLine;
        currentLines.insert(
            currentLines.end(),
            currentLineSegment.getPath().cbegin(),
            currentLineSegment.getPath().cend()
            );

        context.vertexBufferData = currentLines;
        break;
      }
      case Context::CIRCLE: {
        context.vertexBufferData = Circle(context.lastMouseLeftPressXPos,
                                          context.lastMouseLeftPressYPos,
                                          context.cursorXPos,
                                          context.cursorYPos).getPath();
        break;
      }
      case Context::ELLIPSE: {
        context.vertexBufferData = Ellipse(context.lastMouseLeftPressXPos,
                                           context.lastMouseLeftPressYPos,
                                           context.cursorXPos,
                                           context.cursorYPos).getPath();
        break;
      }
      case Context::CUBIC_CURVE: {
        break;
      }
      default: {
        glfwTerminate();
        throw std::invalid_argument(("unknown context state enumerator " +
                                     std::to_string(context.state)).c_str());
      }
    }
  }
}
