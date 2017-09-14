#include <unistd.h>

#include <gpio.h>

#define GPIO_LED    67
#define GPIO_BUTTON 68

int main(int argc, char **argv) {

	/* Setting up LED */
	gpio_export(GPIO_LED);
	gpio_set_dir(GPIO_LED, 1);

	/* Setting up button */
	gpio_export(GPIO_BUTTON);
	gpio_set_dir(GPIO_BUTTON, 0);
	// FIXME: change this depending on button configuration.
	// We want to start the timer when user releases button.
	// For rising, button must be in pull-up configuration.
	gpio_set_edge(GPIO_BUTTON, "rising");

	/* Start of program */
	while(1) {
		/* Turn on LED */
		gpio_set_value(GPIO_LED, 1);
		
		sleep(1);
	}

	return 0;
}
