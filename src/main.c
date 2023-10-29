#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

int main() {
    Display *display;
    Window window;
    XftFont *font;
    XGlyphInfo glyph_info;
    XftDraw *draw;

    // Open a connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    // Create a window
    window = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, 400, 300, 0, 0, WhitePixel(display, 0));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Load a font with Xft
    font = XftFontOpenName(display, DefaultScreen(display), "Noto Color Emoji:style=Regular");

    // Create an Xft draw context
    draw = XftDrawCreate(display, window, DefaultVisual(display, 0), DefaultColormap(display, 0));

   // Example color
   XftColor color;
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));
    XftColorAllocName(display, DefaultVisual(display, DefaultScreen(display)),
                      colormap, "red", &color);

    // Main event loop
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Draw the emoji
            const char *emoji_text = "😀";  // Unicode representation of the emoji
            XftTextExtentsUtf8(display, font, (XftChar8 *)emoji_text, strlen(emoji_text), &glyph_info);
            XftDrawStringUtf8(draw, &color, font, 50, 150, (XftChar8 *)emoji_text, strlen(emoji_text));
        }
        if (event.type == KeyPress) {
            break; // Exit on key press
        }
    }

    // Clean up
    XftFontClose(display, font);
    XftDrawDestroy(draw);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
