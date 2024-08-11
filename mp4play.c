#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#include "list.h"
#include "dir.h"

int mplayer_exited ;
void handle(int sig)
{
	if(sig==SIGCHLD)
	{
		mplayer_exited=1;
	}
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		return -1;
	
	struct fList *f = search_musics(argv[1]);
	print_list(f);
	struct fNode* p = f->first;// p 指向第一个节点
	
	pid_t pid;
	mkfifo("/tmp/mp4fifo",0666);
	int next_action;
	while(p)
	{
		pid = fork();
		if(pid == 0)//child
		{
			execlp("mplayer", "mplayer","-slave","-quiet", "-zoom","-x","800", \
				"-y","480", "-input","file=/tmp/mp4fifo", p->filename,NULL);

		}
		else //father
		{
			char buf[100];
			int fd = open("/tmp/mp4fifo",O_RDWR);
			char ch;
			mplayer_exited = 0; // 不退出
			signal(SIGCHLD,handle);
			while(!mplayer_exited)
			{
				next_action = 0;
				ch = getchar();
				scanf("%*[^\n]");
				scanf("%*c");
				switch(ch)
				{
					case 'M':  
						write(fd,"mute 1\n",strlen("mute 1\n"));
						break;
					case 'S':  
						write(fd,"seek 1\n",strlen("seek 1\n"));
						break;
					case 'B':  
						write(fd,"seek -1\n",strlen("seek -1\n"));
						break;
					case 'U':  
						write(fd,"volume 1\n",strlen("volume 1\n"));
						break;
					case 'D':  
						write(fd,"volume -1\n",strlen("volume -1\n"));
						break;
					case 'N':   //下一首
						next_action = 1;
						break;
					case 'P':  //上一首
						next_action = 2;
						break;
					case 'Q': //退出 
						next_action = 3;
						break;
										
				}
				if( next_action ) // 应该杀死 子进程
				{
					kill(pid, 9); //结束了 mplayer子进程
					mplayer_exited = 1; // 循环退出了
				}
			}
			close(fd); //关闭管道文件
			if(next_action == 1) 
			{
				if(p == f->last)
					p= f->first;
				else
					p = p->next;
			}
			else if(next_action == 2)
			{
				if(p == f->first)
					p = f->last;
				else
					p = p->prev;
			}
			else if(next_action == 3)
			{
				
				exit(0); // 父进程退出
			}
			
		}
	}
	 return 0;
}
