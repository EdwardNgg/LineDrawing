#ifndef PA1_CONTEXT_H
#define PA1_CONTEXT_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


/// A singleton Context class managing all global stuff
class Context
{
public:
    const int WINDOW_WIDTH {1000};
    const int WINDOW_HEIGHT {1000};

    enum State
    {
        LINE_SEGMENT = 1,
        POLYLINE = 2,
        POLYGON = 3,
        CIRCLE = 4,
        ELLIPSE = 5,
        CUBIC_CURVE = 6,
    }
    state = LINE_SEGMENT;

public:
    static Context & getInstance();

public:
    Context(const Context &) = delete;
    Context(Context &&) = delete;
    Context & operator=(const Context &) = delete;
    Context & operator=(Context &&) = delete;

    // setup VAO, VBO, ...
    void setupVertexObjects();

    // free these resources
    void deleteVertexObjects();

    // send render commands to OpenGL server
    void render() const;

    /// Set state and clean all buffer data.
    /// \param s new state to switch to
    void setState(State s);

public:
    // frontend GUI
    double lastMouseLeftPressXPos = 0;
    double lastMouseLeftPressYPos = 0;

    double cursorXPos = 0;
    double cursorYPos = 0;

    double firstXPos = 0;
    double firstYPos = 0;

    bool showPreview {false};

    // used for OpenGL rendering commands
    GLuint VAO {0};
    GLuint VBO {0};
    std::vector<glm::vec2> vertexBufferData;

    // used for polyline
    std::size_t mouseClickCount {0};
    std::vector<glm::vec2> vertexBufferDataPolyLine;

private:
    Context();

    ~Context() = default;
};


#endif  // PA1_CONTEXT_H

