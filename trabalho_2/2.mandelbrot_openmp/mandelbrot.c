/* Sequential Mandlebrot program */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define X_RESN 1000 /* x resolution */
#define Y_RESN 1000 /* y resolution */
#define MAX_ITER (2000)
#define CHUNK 256

// ref: https://stackoverflow.com/questions/6749621/how-to-create-a-high-resolution-timer-in-linux-to-measure-program-performance
// call this function to start a nanosecond-resolution timer
struct timespec timer_start() {
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
    return diffInNanos;
}

typedef struct complextype {
    double real, imag;
} Compl;

// Color conversion functions
// ref: https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

// maps a value from one interval to another
double map(double t, double s0, double e0, double s1, double e1)
{
    return (t - s0)/(e0 - s0)*(e1 - s1) + s1;
}

// Converts a linear double value to a color
rgb colormap1(double t) {
    double u, v;
    hsv c;
    c.h = fmod(fmod(t*1000, 360.0) + 360.0, 360.0);
    c.s = 1.0;
    c.v = 0.5;
    return hsv2rgb(c);
}

rgb colormap2(double t) {
    double u, v;
    hsv c;
    c.h = map(sin(t*10), -1, 1, 0+150, 60+150);
    c.s = 1.0;
    c.v = map(sin(t*1), -1, 1, 0, 1);
    return hsv2rgb(c);
}

int dtoi(double d) {
    int i = d * 256;
    if (i < 0) i = 0;
    if (i > 255) i = 255;
    return i;
}

// converts a rgb color to a long
unsigned long _RGB(rgb c)
{
    return dtoi(c.b) + (dtoi(c.g)<<8) + (dtoi(c.r)<<16);
}

int main(int argc, char *argv[])
{
    Window win; /* initialization for a window */
    GC gc;
    Display *display;

    // criando a janela
    {
        unsigned int width, height,        /* window size */
            x, y,                          /* window position */
            border_width,                  /*border width in pixels */
            display_width, display_height, /* size of screen */
            screen;                        /* which screen */

        char *window_name = "Mandelbrot Set", *display_name = NULL;
        unsigned long valuemask = 0;
        XGCValues values;
        XSizeHints size_hints;
        Pixmap bitmap;
        XPoint points[800];
        FILE *fp, *fopen();
        char str[100];

        XSetWindowAttributes attr[1];

        /* connect to Xserver */

        if ((display = XOpenDisplay(display_name)) == NULL)
        {
            fprintf(stderr, "drawon: cannot connect to X server %s\n",
                    XDisplayName(display_name));
            exit(-1);
        }

        /* get screen size */

        screen = DefaultScreen(display);
        display_width = DisplayWidth(display, screen);
        display_height = DisplayHeight(display, screen);

        /* set window size */

        width = X_RESN;
        height = Y_RESN;

        /* set window position */

        x = 0;
        y = 0;

        /* create opaque window */

        border_width = 4;
        win = XCreateSimpleWindow(display, RootWindow(display, screen),
                                  x, y, width, height, border_width,
                                  BlackPixel(display, screen), WhitePixel(display, screen));

        XSelectInput(display, win, StructureNotifyMask);

        size_hints.flags = USPosition | USSize;
        size_hints.x = x;
        size_hints.y = y;
        size_hints.width = width;
        size_hints.height = height;
        size_hints.min_width = 300;
        size_hints.min_height = 300;

        XSetNormalHints(display, win, &size_hints);
        XStoreName(display, win, window_name);

        /* create graphics context */

        attr[0].backing_store = Always;
        attr[0].backing_planes = 1;
        attr[0].backing_pixel = BlackPixel(display, screen);

        XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);

        XMapWindow(display, win);

        gc = XCreateGC(display, win, valuemask, &values);
        XSetBackground(display, gc, WhitePixel(display, screen));
        XSetForeground(display, gc, BlackPixel(display, screen));
        XSetLineAttributes(display, gc, 1, LineSolid, CapRound, JoinRound);

        // bug fix: must wait for the Map event to start drawing
        // otherwise, not all pixels will be drawn to screen
        for (;;)
        {
            XEvent e;
            XNextEvent(display, &e);
            if (e.type == MapNotify)
                break;
        }

        XSync(display, 0);
    }

    struct timespec vartime = timer_start();

    /* Mandlebrot variables */
    int *ks;
    ks = (int *)malloc((X_RESN*Y_RESN) * sizeof(int));

    double *ds;
    ds = (double *)malloc((X_RESN*Y_RESN) * sizeof(double));

    /* Calculate and draw points */
    #pragma omp parallel default(shared)
    {
        int num_threads = omp_get_num_threads();
        // printf("num_threads = %d\n", num_threads);
        #pragma omp for schedule(dynamic, CHUNK)
        for (int it = 0; it < X_RESN*Y_RESN; it++)
        {
            int i = it / Y_RESN;
            int j = it % Y_RESN;

            // mandelbrot set is defined in the region of x = [-2, +2] and y = [-2, +2]
            double u = ((double)i - (X_RESN / 2.0)) / (X_RESN / 4.0);
            double v = ((double)j - (Y_RESN / 2.0)) / (Y_RESN / 4.0);

            Compl z, c, t;

            z.real = z.imag = 0.0;
            c.real = v;
            c.imag = u;

            int k = 0;
            double d = 0.0;

            double lengthsq, temp;
            do
            { /* iterate for pixel color */
                t = z;
                z.imag = 2.0 * t.real * t.imag + c.imag;
                z.real = t.real * t.real - t.imag * t.imag + c.real;
                lengthsq = z.real * z.real + z.imag * z.imag;
                d += pow(pow(z.imag - t.imag, 2.0) + pow(z.real - t.real, 2.0), 0.5);
                k++;
            } while (lengthsq < 4.0 && k < MAX_ITER);

            ks[it] = k;
            ds[it] = d;
        }
    }

    {
        int i, j, k;
        double d;
        for (int it_pixel = 0; it_pixel < (X_RESN * Y_RESN); it_pixel++)
        {
            int i = it_pixel / Y_RESN;
            int j = it_pixel % Y_RESN;

            k = ks[it_pixel];
            d = ds[it_pixel];
            // if (k == MAX_ITER)
            {
                rgb c;
                c.r = 1.0;
                c.g = 0.8;
                c.b = 0;
                XSetForeground(display, gc, k == MAX_ITER ? _RGB(colormap2(sin(d))) : _RGB(colormap1(k/(double)MAX_ITER)));
                // XSetForeground(display, gc, _RGB(colormap1(d)));
                // XSetForeground(display, gc, _RGB(c));
                // XSetForeground(display, gc, 0xFFD000);
                XDrawPoint(display, win, gc, j, i);
            }
        }

        XFlush(display);

        free(ks);
        free(ds);

        long time_elapsed_nanos = timer_end(vartime);
        double elapsed = time_elapsed_nanos*0.000000001;
        printf("%lf\n", elapsed);

        sleep(30);
    }

    /* Program Finished */
    return 0;
}