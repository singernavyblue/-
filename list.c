#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



//创建一个空链表
struct fList *create_linkedlist(void)
{
	struct fList *f;
	f =(struct fList *)malloc(sizeof(struct fList));
	f->first = f->last = NULL;
}


void print_list(struct fList *f)
{
	struct fNode *p = f->first;

	while(p)
	{
		printf("%s\n", p->filename);
		p = p->next;
	}


}

//向链表中插入一个节点，节点信息为文件名(绝对路径)和文件修改时间
void add_a_filenode(struct fList* f, const char* filename, time_t mtime) 
{
	if( NULL == f)
	{
		printf("flist is NULL \n");
		return;
	}
	struct fNode *p = (struct fNode *)malloc(sizeof(struct fNode));
	strcpy(p->filename, filename);
	p->mtime = mtime;
	p->prev = NULL;
	p->next = NULL;
	
	
	//printf("add a filenode filename=%s\n",p->filename);
	if( NULL == f->first )
	{
		f->first = p;
		f->last = p;
		return;
	}
	//老的在前面，新的在后面
	struct fNode *px = f->first;
	while( px )
	{
		if( px->mtime > p->mtime )
		{
			break;
		}
		//pr = px;
		px = px->next;
	}

	if( NULL  == px ) //p比最后一个都年轻
	{
		f->last->next = p;
		p->prev = f->last;
		f->last = p;
		
	}else if( px == f->first )  //p比第一个都老
	{
		p->next = px;
		px->prev = p;
		f->first = p;
	}else //插入到px的前面
	{
		px->prev->next = px;
		p->prev = px->prev;
		p->next = px;
		px->prev = p;
	}


}

