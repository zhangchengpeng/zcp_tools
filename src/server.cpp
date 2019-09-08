#include "server.h"
#include "printf.h"
#include "net_utils.h"
#include <sys/wait.h>

static void signal_handle_func(int sig_no, siginfo_t *sig_info, void *data)
{
	if (sig_no == SIGCHLD)
	{
		while (true)
		{
			int status = 0;
			__pid_t pid = waitpid(-1, &status, WNOHANG);
			//设置了WNOHANG没有子进程了
			if (pid == 0)
			{
				break;
			}
			else if (pid == -1)
			{
				//设置了WNOHANG没有子进程了
				if (errno == ECHILD)
				{
					break;
				}
				else
				{
					PRINTF_ERROR();
					continue;
				}
			}
			//成功回收pid>0
			int result = WIFEXITED(status);
			if (result == 0)
			{
				//正常退出
				PRINTF_DEBUG("pid:%d normal exit return 0", pid);
			}
			else
			{
				//异常退出
				int return_result = WEXITSTATUS(status);
				PRINTF_DEBUG("pid:%d abnormal exit return %d", pid, return_result);
			}
		}
	}
	else if (sig_no == SIGINT)
	{
		
	}
	else if (sig_no == SIGTERM)
	{
		
	}
	else if (sig_no == SIGQUIT)
	{
		
	}
	else if (sig_no == SIGUSR1)
	{
		
	}
	else if (sig_no == SIGIO)
	{
		
	}
	else if (sig_no == SIGPIPE)
	{
		
	}
	else
	{
		PRINTF_DEBUG("no set signal:%d", sig_no);
	}
	
}

int init_signal()
{
	static const int sigs[] = {SIGINT, SIGTERM, SIGQUIT, SIGCHLD, SIGUSR1, SIGIO, SIGPIPE};
	const int *begin = std::begin(sigs);
	const int *end = std::end(sigs);
	for (; begin != end; begin++)
	{
		int ret = set_signal_handle(*begin, signal_handle_func);
		if (ret != 0)
		{
			PRINTF_ERROR("set_signal_handle error")
			return -1;
		}
	}
	return 0;
}

void force_exit()
{
	PRINTF_DEBUG("now force exit, killall -9(SIGKILL)");
	if (kill(0, SIGKILL) != 0)
	{
		PRINTF_ERROR("kill error")
	}
}

int fork_child()
{
	__pid_t pid = fork();
	if (pid == -1)
	{
		PRINTF_ERROR("fork error");
		return -1;
	}
	else if (pid == 0)
	{
		//子进程
		PRINTF_DEBUG("hello world");
	}
	else //pid > 0
	{
		//父进程
		PRINTF_DEBUG("fork child pid:%d", pid);
	}
	return 0;
}