#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dir.h"

//从pathname目录中找到所有图片文件（文件名以.bmp和.jpg结尾的）
//返回：按修改时间由早到晚的顺序排序好的链表
struct fList *search_musics( const char *pathname)
{
	struct dirent *dire;
	char filename[256];

	DIR *dir = opendir(pathname);	
	if( NULL == dir)
	{
		perror("opendir error");
		return NULL;
	}
	struct fList *f = create_linkedlist();
	struct stat st; // 获取文件属性：时间，文件类型
	while( ( dire = readdir(dir))!=NULL)
	{
		//printf("dire->d_name = %s\n",dire->d_name);
		if( ( 0 == strcmp(dire->d_name,".")) || 
			(0 == strcmp(dire->d_name, "..")) )
			continue;
		sprintf(filename, "%s/%s",pathname, dire->d_name);
		//printf("search pictures: filename=%s\n",filename);
		stat(filename, &st);
		if( S_ISREG(st.st_mode)) // 如果 是一个普通文件
		{
			if( FILE_MP4 == get_file_type(filename) )
			{
				add_a_filenode(f, filename, st.st_mtime);
			}
		}
	}
//	printf("search pictures return!\n");
	closedir(dir);
	return f;
}
//判断filename文件名的后缀是否是以.bmp或.jpg结尾
enum filetype get_file_type(const char *filename)
{
	if ( 0 == strcmp(filename+strlen(filename)-4, ".bmp") )
		return FILE_BMP;
	else if(  0 == strcmp(filename+strlen(filename)-4, ".jpg") )
		return FILE_JPEG;
	else if(  0 == strcmp(filename+strlen(filename)-4, ".mp3") )
		return FILE_MP3;
	else if(  0 == strcmp(filename+strlen(filename)-4, ".mp4") )
		return FILE_MP4;
}

