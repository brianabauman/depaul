#include "assign2Headers.h"

int shouldRun = 1;

void timeOverHandler(int signum) {
	printf("Oh no! The time is up!\n");
	shouldRun = 0;
}

void winHandler(int signum) {
	printf("Congratulations! You found it!\n");
	shouldRun = 0;
}

void correctHandler(int signum) {
	printf("Yay! That was right!\n");
}

void incorrectHandler(int signum) {
	printf("Oops! That was wrong. Please restart from the beginning.\n");
}

int main(int argc, char* argv[]) {
	if (argc != 2) return(EXIT_FAILURE);
	int answererPid = strtol(argv[1], NULL, 10);	

	struct sigaction timeOverAct;
	memset(&timeOverAct, '\0', sizeof(timeOverAct));
	timeOverAct.sa_handler = timeOverHandler;
	sigaction(TIME_OVER_SIGNAL, &timeOverAct, NULL);

	struct sigaction winAct;
	memset(&winAct, '\0', sizeof(winAct));
	winAct.sa_handler = winHandler;
	sigaction(WIN_SIGNAL, &winAct, NULL);

	struct sigaction correctAct;
	memset(&correctAct, '\0', sizeof(correctAct));
	correctAct.sa_handler = correctHandler;
	sigaction(CORRECT_SIGNAL, &correctAct, NULL);

	struct sigaction incorrectAct;
	memset(&incorrectAct, '\0', sizeof(incorrectAct));
	incorrectAct.sa_handler = incorrectHandler;
	sigaction(INCORRECT_SIGNAL, &incorrectAct, NULL);

	while (shouldRun) {
		printf("What would you like your next guess to be: 0 or 1? ");
		char line[LINE_LEN];
		fgets(line, LINE_LEN, stdin);
		
		if (strcmp(line, "0\n")) { kill(answererPid, ZERO_SIGNAL); }
		else if (strcmp(line, "1\n")) { kill(answererPid, ONE_SIGNAL); }

		sleep(1);
	}

	printf("guesser finished\n");
	return(EXIT_SUCCESS);
}
