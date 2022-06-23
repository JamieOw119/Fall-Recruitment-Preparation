#include	<unp.h>

void 
str_echo(int sockfd)
{
	ssize_t	n;
	char	buf[MAXLINE];

again:
	while ((n = read(sockfd, buf, sizeof(buf))) > 0)
		if (write(sockfd, buf, n) < 0)
			err_sys("write error");
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}

void
str_echo2(int sockfd)
{
	long	arg1, arg2;
	ssize_t	n;
	char	line[MAXLINE];

	while(1)
	{
		if((n = Readline(sockfd, line, MAXLINE)) == 0)
		{
			return;
		}
		if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
		{
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		}
		else
		{
			snprintf(line, sizeof(line), "input error\n");
		}
		n = strlen(line);
		Writen(sockfd, line, n);
	}
}

struct args
{
	long arg1;
	long arg2;
};

struct result
{
	long sum;
};

void str_echo3(int sockfd)
{
	ssize_t 		n;
	struct args		args;
	struct result	result;

	while(1)
	{
		if((n = Readn(sockfd, &args, sizeof(args))) == 0)
		{
			return;
		}
		result.sum = args.arg1 + args.arg2;
		Writen(sockfd, &result, sizeof(result));
	}
}