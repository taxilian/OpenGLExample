
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
    rThread = boost::thread(&OpenGLExampleX11::renderThread, this, win);
}

bool OpenGLExampleX11::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowX11 *win)
{
    rThread.interrupt();
    rThread.join();
}

void OpenGLExampleX11::renderThread(FB::PluginWindowX11* win)
{
    gdk_threads_enter();
    FBLOG_WARN("", "Starting Render Thread");

    GtkWidget* drawing_area;
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, win->getWindowWidth(), win->getWindowHeight());

    GdkGLConfigMode glconf = static_cast<GdkGLConfigMode>(
            GDK_GL_MODE_RGB |
            GDK_GL_MODE_DOUBLE |
            GDK_GL_MODE_DEPTH
            );
    FBLOG_WARN("", "Trying to config");
    glConfig = gdk_gl_config_new_by_mode(glconf);
    FBLOG_WARN("", "Created config: " << glConfig);
    if (!glConfig) {
        FBLOG_WARN("", "Double-buffer didn't work. Trying single.");
        glconf = static_cast<GdkGLConfigMode>(
                GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH
                );
        glConfig = gdk_gl_config_new_by_mode(glconf);
        FBLOG_WARN("", "Created config: " << glConfig);
        if (!glConfig) {
            FBLOG_WARN("", "Couldn't initialize opengl. No idea why, sorry!");
            return;
        } else {
            FBLOG_INFO("", "Double-buffer opengl");
        }
    } else {
        FBLOG_INFO("", "Double-buffer opengl");
    }

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
    FBLOG_WARN("", "Setting current context to widget");
    gdk_gl_drawable_make_current(gldrawable, glcontext);
    gdk_threads_leave();
    try {
        while (!boost::this_thread::interruption_requested()) {
            gdk_threads_enter();
            render();
            GdkGLDrawable *gld = gtk_widget_get_gl_drawable (drawing_area);
            FBLOG_INFO("", "Got drawable: " << gld);
            if (gdk_gl_drawable_is_double_buffered (gld)) {
                gdk_gl_drawable_swap_buffers (gld);
            } else {
                glFlush();
            }
            gdk_threads_leave();
            boost::this_thread::sleep(boost::posix_time::milliseconds(20));
        }
    } catch (const boost::thread_interrupted&) {
    }
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
}
