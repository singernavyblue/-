//条件编译的作用是避免重复定义
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <time.h>

//双向链表的节点
struct fNode
{
	unsigned char 	filename[256]; //文件的绝对路径
	time_t 			mtime; //文件的最后修改时间
	struct fNode 	*prev;
	struct fNode 	*next; 
};
struct fList
{
	struct fNode 	*first; // 链表中的第一个节点
	struct fNode 	*last; //  链表中的最后一个节点
};
//创建一个空链表
struct fList *create_linkedlist(void);
//向链表中插入一个节点，节点信息为文件名(绝对路径)和文件修改时间
void add_a_filenode(struct fList*, const char*, time_t); 
void print_list(struct fList *f);

#endif
