
#include <stdio.h>

#include <at/display.h>

int main(void)
{
	if (at_open_simple_display(80, 24, "simple display")) {
		printf("could not open display\n");
		return -1;
	}

	while (!at_simple_display_flush()) {
		at_simple_display_key('j');

		at_simple_display_clear(0x00000000);
		at_simple_display_plot_glyphs(0, 0, 0xff, "hello");
	}

	at_close_simple_display();
	return 0;
}
