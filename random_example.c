#include <libfreenect.h>
//res: http://pastebin.com/BfbJYFtw
int main(void) {
    freenect_context* ctx;
    freenect_device* dev;
    freenect_init(&ctx, NULL); // So you can use freenect/libusb functions
    freenect_open_device(ctx, &dev, 0); // Open this particular device
    freenect_set_led(dev, LED_RED); // Set the led color (see include/libfreenect.h for more info)

    int die = 0;

    while(!die && freenect_process_events(ctx) >= 0) {
        // Do stuff here, to quit, set die != 0
    }
    freenect_close_device(dev);
    freenect_shutdown(ctx);
    return 0;
}
