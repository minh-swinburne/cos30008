#include "include/splashkit/splashkit.h"

int main()
{
    open_window("House Drawing", 800, 600);

    clear_screen(COLOR_WHITE);
    refresh_screen();
    delay(1000);
    fill_ellipse(COLOR_BRIGHT_GREEN, 0, 400, 800, 400);
    refresh_screen();
    delay(1000);
    fill_rectangle(COLOR_GRAY, 300, 300, 200, 200);
    refresh_screen();
    delay(1000);
    fill_triangle(COLOR_RED, 250, 300, 400, 150, 550, 300);
    refresh_screen();
    delay(5000);

    close_all_windows();

    return 0;
}
