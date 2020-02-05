#ifndef BLINK_H
#define BLINK_H

#include <OpenWallpaper/QtOpenGL/abstract_render.hpp>

#include <array>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QCursor>
#include <QScreen>
#include <QSize>

using QtRender = openWallpaper::ogl::QtRender;

class Blink : public QtRender
{
    const float SPEED_ON_START = 1.0f / 2500.0f;
    const float SPEED_DIVIDER = 5000.0f;
    const bool CHECK_FOCUS = false;

public:
    Blink();
    ~Blink();

    void init(const std::string& dir, const std::vector<std::string>& params) override;
    void data(bool focus, bool music, float volume, const std::vector<std::string>& params) override;
    void draw() override;
    void onPause() override;
    void onResume() override;

private:
    void updateSpeed(const float y);
    float normalize(const float coordinate);

private:
    QOpenGLShaderProgram* shader;
    QOpenGLFunctions* functions;
    QSize screenSize;

    float step;
    float currentSpeed;
    float lastMouseUpdate;
    std::array<float, 8> values;

    bool flip;
    bool onFocus;
};

#endif // BLINK_H
