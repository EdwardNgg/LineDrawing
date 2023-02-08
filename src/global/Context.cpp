#include "global/Context.h"


Context::Context()
{
    vertexBufferData.clear();
}


Context & Context::getInstance()
{
    static Context instance;
    return instance;
}


void Context::setupVertexObjects()
{
    glGenVertexArrays(1, &VAO);  // generate 1 vertex array object, bind to handle VAO
    glBindVertexArray(VAO);      // bind VAO to OpenGL context

    glGenBuffers(1, &VBO);               // generate 1 buffer object, bind to handle VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // bind VBO to OpenGL context "GL_ARRAY_BUFFER"

    // Configure generic vertex attribute arrays and store configuration in currently-bound VAO.
    // When using currently-bound VAO,
    // the generic vertex attribute array "layout (position = 0) in vec2" will fetch data from currently-bound VBO.
    // The interpretation of VBO data specified as follows.
    glVertexAttribPointer(0,                             // index: corresponds to "0" in "layout (position = 0)"
                          2,                             // size: each "vec2" generic vertex attribute has 2 values
                          GL_FLOAT,                      // data type: "vec2" generic vertex attributes are GL_FLOAT
                          GL_FALSE,                      // do not normalize data
                          sizeof(glm::vec2),             // stride between attributes in VBO data
                          reinterpret_cast<void *>(0));  // offset of 1st attribute in VBO data

    // Enable generic vertex attribute array "layout (position = 0) in vec2"
    // to be called by rendering commands (e.g. glDrawArray).
    // Generic vertex attribute array are disabled by default
    // and aren't accessed by rendering commands like glDrawArray!
    // This generic vertex attribute array will take data from currently-bound VAO.
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);                // bind buffers to context only when you are using them
    glBindBuffer(GL_ARRAY_BUFFER, 0);    // unbind whatever you are not using
}


void Context::deleteVertexObjects()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Context::render() const
{
    // Background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);              // bind VAO because drawing commands fetch data from current VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // also bind VBO because we are modifying its data!
                                         // (NOT needed if no changes to its data)

    // Update VBO
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizei>(vertexBufferData.size() * sizeof(glm::vec2)),
                 vertexBufferData.data(),
                 GL_DYNAMIC_DRAW);

    // Draw
    // This function will take configuration of generic vertex attribute arrays from currently-bound VAO
    // and render shape w.r.t. using generic vertex attribute arrays
    glDrawArrays(GL_POINTS,
                 0,                                               // start from index 0 in current VBO
                 static_cast<GLsizei>(vertexBufferData.size()));  // draw these number of GL_POINTS elements

    glBindVertexArray(0);              // unbind whatever objects
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // not currently in use
}


void Context::setState(State s)
{
    state = s;
    showPreview = false;

    vertexBufferData.clear();

    mouseClickCount = 0;
    vertexBufferDataPolyLine.clear();
}

