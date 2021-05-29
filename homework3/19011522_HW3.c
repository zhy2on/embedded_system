#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void exit_parent(int signo)
{
	printf("exit parent\n");
	exit(0);
}

void exit_child(int signo)
{
	printf("exit child\n");
	exit(0);
}

int main()
{
	pid_t grandchild_pid;
	pid_t child_pid;
	pid_t parent_pid;

	parent_pid = getpid();
	child_pid = fork();

	if(child_pid == 0)
	{
		child_pid = getpid();
		grandchild_pid = fork();

		if(grandchild_pid == 0)
		{
			sleep(3);
			printf("i'm grandchild\n");
			printf("grandchild pid = %d\n\n", getpid());
			printf("exit grandchild\n");
		}
		else if(child_pid > 0)
		{
			signal(SIGCHLD, exit_child);
			sleep(1);
			printf("i'm child\n");
			printf("child pid = %d\n\n", getpid());
			while(1)
				sleep(10);

		}
	}
	else if(child_pid > 0)
	{
		signal(SIGCHLD, exit_parent);
		printf("i'm parent \n");
		printf("parent pid = %d\n\n", getpid());
		while (1)
			sleep(10);
	}
	else
		printf("fork returned error, no child \n");
}
