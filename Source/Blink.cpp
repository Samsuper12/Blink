#include "Blink.hpp"

Blink::Blink() 
    : shader(nullptr)
    , functions(nullptr)
    , step(0.0f)
    , flip(false)
    , onFocus(false)
{
    currentSpeed = SPEED_ON_START;
}

Blink::~Blink()
{
    delete shader;
    shader = nullptr;
}

void Blink::data(bool focus, bool music, float volume, const std::vector<std::string>& params)
{
    onFocus = focus;
    Q_UNUSED(music)
    Q_UNUSED(volume)
    Q_UNUSED(params)
}

void Blink::init(const std::string& dir, const std::vector<std::string>& params)
{
    Q_UNUSED(dir)
    Q_UNUSED(params)

    functions = QOpenGLContext::currentContext()->functions();
    screenSize = QOpenGLContext::currentContext()->screen()->size();

    shader = new QOpenGLShaderProgram();
    shader->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                             "attribute highp vec4 vertices;"
                                             "varying highp vec2 coords;"
                                             "void main() {"
                                             "    gl_Position = vertices;"
                                             "    coords = vertices.xy;"
                                             "}");

    shader->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                             "uniform lowp float t;"
                                             "varying highp vec2 coords;"
                                             "void main() {"
                                             "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                             "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                             "    i = floor(i * 20.) / 20.;"
                                             "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                             "}");

    shader->bindAttributeLocation("vertices", 0);
    shader->link();
}

void Blink::draw()
{
    float values[8] {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };

    if (onFocus && CHECK_FOCUS) {
        updateSpeed(normalize(QCursor::pos().y()));
    }

    shader->bind();
    shader->enableAttributeArray(0);

    if( step >= 1.0f || step <= 0.0f) {
        flip = !flip;
    }

    flip ? step += currentSpeed : step -= currentSpeed;

    shader->setAttributeArray(0, GL_FLOAT, values, 2);
    shader->setUniformValue("t", step);

    functions->glClearColor(0.0, 0.0, 0.0, 1.0);
    functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader->disableAttributeArray(0);
    shader->release();
}

void Blink::updateSpeed(const float y)
{
    if (lastMouseUpdate == y) {
        return;
    }

    if ( y > lastMouseUpdate) {
        currentSpeed += ( y / SPEED_DIVIDER);
    }
    else if( y < lastMouseUpdate) {
        currentSpeed -= (y / SPEED_DIVIDER);
    }

    lastMouseUpdate = y;
}

float Blink::normalize(const float coordinate)
{
    return ( coordinate / screenSize.height() );
}

void Blink::onPause()
{
}

void Blink::onResume()
{
}

extern "C" QtRender* create()
{
    return new Blink;
}

extern "C" void destroy(QtRender* p)
{
    delete p;
}
