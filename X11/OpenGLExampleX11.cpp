
#include "OpenGLExampleX11.h"
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include "logging.h"

void OpenGLExampleX11::StaticInitialize()
{
    int c = 0;
    gdk_gl_init_check(&c, NULL);
}

void OpenGLExampleX11::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

OpenGLExampleX11::OpenGLExampleX11()
{
}

OpenGLExampleX11::~OpenGLExampleX11()
{
}

bool OpenGLExampleX11::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowX11 *win)
{
    FBLOG_WARN("", "AttachedEvent start");
    rThread = boost::thread(&OpenGLExampleX11::renderThread, this, win);
    FBLOG_WARN("", "AttachedEvent end");
}

bool OpenGLExampleX11::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *win)
{
    FBLOG_WARN("", "DetachedEvent start");
    rThread.interrupt();
    rThread.join();
    FBLOG_WARN("", "DetachedEvent end");
}

void OpenGLExampleX11::renderThread(FB::PluginWindowX11* win)
{
    // Initialize GTK/GDK on this thread

    //boost::scoped_array<char> argv(new char[1][20]);
    int argc = 0;
    //strcpy(argv[0], "--sync");
    //gboolean initSucceeded = gtk_init_check(&argc, argv.get());

    gdk_threads_enter();
    FBLOG_WARN("", "Starting Render Thread");
    gboolean initSucceeded = gdk_gl_init_check(&argc, NULL);
    FBLOG_WARN("", "gdk_gl_init_check returned " << initSucceeded);

    GtkWidget* drawing_area;
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 500, 500);

    GdkGLConfigMode glconf = static_cast<GdkGLConfigMode>(
            GDK_GL_MODE_RGB |
            GDK_GL_MODE_DOUBLE |
            GDK_GL_MODE_DEPTH
            );
    //FBLOG_WARN("", "Trying to config");
    //glConfig = gdk_gl_config_new_by_mode(glconf);
    //FBLOG_WARN("", "Created config: " << glConfig);
    //if (!glConfig) {
        //FBLOG_WARN("", "Double-buffer didn't work. Trying single.");
        glconf = static_cast<GdkGLConfigMode>(
                GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH
                );
        glConfig = gdk_gl_config_new_by_mode(glconf);
        FBLOG_WARN("", "Created config: " << glConfig);
        if (!glConfig) {
            FBLOG_WARN("", "Couldn't initialize opengl. No idea why, sorry!");
            return;
        } else {
            FBLOG_INFO("", "Single-buffer opengl");
        }
    //} else {
        //FBLOG_INFO("", "Double-buffer opengl");
    //}

    FBLOG_WARN("", "Setting GL capability on Widget: " << drawing_area);
    gtk_widget_set_gl_capability (drawing_area,
            glConfig,
            NULL,
            TRUE,
            GDK_GL_RGBA_TYPE);

    gtk_container_add(win->getGtkContainer(), drawing_area);
    gtk_widget_show(drawing_area);

    FBLOG_WARN("", "Getting GL Context");
    GdkGLContext *glcontext = gtk_widget_get_gl_context (drawing_area);
    FBLOG_WARN("", "Got GL Context: " << glcontext << " Now getting Drawable:");
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (drawing_area);
    FBLOG_WARN("", "Got GL Drawable: " << gldrawable);

    // Attach our OpenGL context to the widget
    gdk_threads_leave();
    try {
        while (!boost::this_thread::interruption_requested()) {
            gdk_threads_enter();
            GdkGLDrawable *gld = gtk_widget_get_gl_drawable (drawing_area);
            gdk_gl_drawable_make_current(gldrawable, glcontext);
            gboolean tmp = gdk_gl_drawable_gl_begin(gldrawable, glcontext);
            FBLOG_WARN("", "Setting current context to widget. glbegin was " << tmp);
            //render();
            gdk_gl_drawable_gl_end(gldrawable);
            //FBLOG_INFO("", "Got drawable: " << gld);
            //if (gdk_gl_drawable_is_double_buffered (gld)) {
                //gdk_gl_drawable_swap_buffers (gld);
            //} else {
                //glFlush();
            //}
            gdk_flush();
            gdk_threads_leave();
            boost::this_thread::sleep(boost::posix_time::milliseconds(200));
        }
    } catch (const boost::thread_interrupted&) {
    }
    FBLOG_WARN("", "Thread stop signaled");
    // Shut down the opengl config and context objects
    if (glConfig) {
        g_object_unref(G_OBJECT(glConfig));
        glConfig = NULL;
    }
    GdkGLContext *glContext = gtk_widget_get_gl_context(drawing_area);
    if (glContext) {
        g_object_unref(G_OBJECT(glContext));
        glContext = NULL;
    }
    FBLOG_WARN("", "Thread stopping");
}
