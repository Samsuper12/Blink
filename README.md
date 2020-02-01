# Blink for OpenWallpaper

Blink is simple [QOpenGL][qogl_context] scene for the [OpenWallpaper Plasma][wallpaper_plasma].
Video demonstration: [YouTube][youtube_blink] | [Reddit][reddit_page]

![Blink preview image][preview_image]

## Build instructions

Unpack the downloaded package and open the terminal:

```console
# sudo ./build.sh
```

Also, you can enable mouse events: open `Source/Blink.cpp` and replace variable `const bool CHECK_FOCUS = false;` to `true`.
Don't forget to recompile sources with the command above.

## Parametres

All of the wallpaper packages must have `wallpaper.ini` file with the information below:

### Information about package and author
|  Variable    | Type           | Description               | Wallpaper Type  |  Necessary  |
|    :---:     |     :---:      |     :---:                 |     :---:       |    :---:    |
| Name         | String         | Name of current package   | ALL             | +           |
| Version      | String         | Package version           | ALL             | -           |
| Author       | String         | Author name               | ALL             | -           |
| Email        | String         | Author email              | ALL             | -           |
| AuthorLink   | String         | Author website            | ALL             | -           |
| Comment      | String         | Small text about package  | ALL             | -           |

### Settings parameters
|  Variable    | Type           | Description               | Wallpaper Type  |  Necessary  |
|    :---:     |     :---:      |     :---:                 |     :---:       |    :---:    |
| Type         | String         | One of three types        | ALL             | +           |
| Music        | Bool           | Have music or not         | OGL, Gif        | +-          |
| StartVolume  | Float          | Start volume              | ALL             | +-          |
| FillMode     | String         | Video fill mode           | Video           | -           |

### Resources

|  Variable    | Type           | Description               | Wallpaper Type  |  Necessary  |
|    :---:     |     :---:      |     :---:                 |     :---:       |    :---:    |
| Source       | String         | Path to package source    | ALL             | +           |
| MusicSource  | String         | Path to music source      | ALL             | +-          |
| PreviewImage | String         | Preview image for Manager | ALL             | +           |


About FillMode you can read in [Qt Documentation][qt_fillmode_doc].

## How to create own QtOpenGL wallpaper

### API

The OpenWallpaper Plasma install `abstract_render.hpp` class to your system by path `/usr/include/OpenWallpaper/QtOpenGL`. Now you can create own class and inherit it of `openWallpaper::ogl::QtRender`. Don't forget override follow methods:

* `void init(const std::string& dir,const std::vector<std::string>& params)` - That an "second constructor" for your class. It is called after main constructor. An basic constructor cannot have any arguments doe to architectural costs. `params` do not take any data in current release
* `void data(bool focus, bool music, float volume, const std::vector<std::string>& params)` - That method is activated first in each frame.`params` do not take any data in current release
* `void draw()` - Second method in each frame. Your render code should placed in there
* `void onPause()` - activated when user set pause for a desktop wallpaper
* `void onResume()` - activated when user set play for a desktop wallpaper

The OpenWallpaper plasma can work only with shared libraries, so your source file should have follow methods:

* `extern "C" QtRender* create() { return new **YOUR_CLASS_NAME**; }` - function for an constuctor
* `extern "C" void destroy(QtRender* p) { delete p; }` - function for an destructor

Attention: QtRender it is alias of a `openWallpaper::ogl::QtRender`.
Be careful with that type of wallpaper, check source and then run package. The library can contain any C++ code.

### Includes

For minimal build need include fallow libraries: 
* [QOpenGLContext][qogl_context]
* [QOpenGLFunctions][qogl_functions]

More information you can find in an official [Qt Documentation][qt_doc]

### Context

The `QOpenGLContext` can be taken from `QOpenGLContext::currentContext()`. See `Source/Blink.cpp` for better understanding.

## How to create the wallpaper package

* Create `wallpaper.ini` and set needed variables. See Parametres above
* Add source files (videos, gifs or shared libraries(with source))
* Share!

## Third-party

* [CMake 3.10+][cmake]
* Qt 5.10+ ([LGPL](http://doc.qt.io/qt-5/lgpl.html))

## Links

* [OpenWallpaper Plasma][wallpaper_plasma]
* [OpenWallpaper Manager][wallpaper_manager]
* [Reddit][reddit_page]

## Author

Code given from [Qt Examples][qt_example].


[//]: # (LINKS)
[cmake]: https://cmake.org/
[qogl_context]: https://doc.qt.io/qt-5/qopenglcontext.html
[qogl_functions]: https://doc.qt.io/qt-5/qopenglfunctions.html
[qt_doc]: https://doc.qt.io/qt-5/reference-overview.html
[qt_example]: https://doc.qt.io/qt-5/qtquick-scenegraph-openglunderqml-example.html
[qt_fillmode_doc]: https://doc.qt.io/qt-5/qml-qtmultimedia-video.html#fillMode-prop
[youtube_blink]: https://youtu.be/ioq54vMtm6w
[preview_image]: docs/preview_gh.png

[wallpaper_manager]: https://github.com/Samsuper12/OpenWallpaper-Manager
[wallpaper_plasma]: https://github.com/Samsuper12/OpenWallpaper-Plasma
[reddit_page]: https://www.reddit.com/r/OpenWallpaper/comments/ex78il/blink/
