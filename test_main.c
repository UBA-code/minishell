#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

// int main(int argc, char const *argv[])
// {
// 	int f = open("werwerew", 0);
// 	perror("minishell");
// 	return 0;
// }
int main(int argc, char const *argv[])
{
	int f = open("werwerew", 0);
	char *e = strerror(errno);
	printf("%s\n", e);
	return 0;
}