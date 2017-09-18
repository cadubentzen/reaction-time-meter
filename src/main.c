#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include <gpio.h>

#define GPIO_LED    67
#define GPIO_BUTTON 68

int main(int argc, char **argv)
{
	int button_fd;
	struct pollfd pfd;
	char buf[MAX_BUF];
	int rc;
	int len;
	struct timeval start, end;
	int time_mili;
	int game_on = 0;
#ifdef LCD_DISPLAY
	int lcd_fd = open("/dev/lcd0", O_WRONLY);
	if (lcd_fd < 0) {
		perror("lcd_fd open(): ");
	}
#endif

	/* Initialize random seed */
	srand(time(NULL));

	/* Setting up LED */
	gpio_export(GPIO_LED);
	gpio_set_dir(GPIO_LED, 1);

	/* Setting up button */
	gpio_export(GPIO_BUTTON);
	gpio_set_dir(GPIO_BUTTON, 0);
	// FIXME: change this depending on button configuration.
	// We want to start the timer when user presses button.
	// For rising, button must be in pull-up configuration.
	gpio_set_edge(GPIO_BUTTON, "falling");
	button_fd = gpio_fd_open(GPIO_BUTTON);

	/* Start of program */
	while(1) {
		/* Turn on LED */
		gpio_set_value(GPIO_LED, 1);

		/* Get time_start */
		if (game_on) 
			gettimeofday(&start, NULL);

		/* Wait for rising in GPIO_BUTTON */
		memset((void*)&pfd, 0, sizeof(&pfd));

		pfd.fd = button_fd;
		pfd.events = POLLPRI;

		rc = poll(&pfd, 1, -1);

		if (rc < 0) {
			perror("poll(): ");
			exit(1);
		}

		if (pfd.revents & POLLPRI) {
			if (game_on) {
				gettimeofday(&end, NULL);
				time_mili = (start.tv_sec * 1000 + start.tv_usec / 1000)
							 - (end.tv_sec * 1000 + end.tv_usec / 1000);
			#ifdef LCD_DISPLAY
				len = snprintf(buf, sizeof(buf), "%.1fs", time_mili*0.001); 
				write(lcd_fd, buf, len);
			#endif
				printf("Time elapsed: %.1fs", time_mili*0.001);
			}
			lseek(pfd.fd, 0, SEEK_SET);
			len = read(pfd.fd, buf, MAX_BUF);
			printf("\nButton pressed!\n");
			/* When button is pressed, turn off LED */
			gpio_set_value(GPIO_LED, 0);
			/* Wait randomly between 0 and 3s to turn on LED */
			if (!game_on)
				usleep(rand()%3000000);

			game_on = game_on ? 0 : 1;
		}
	}

	exit(0);
}
