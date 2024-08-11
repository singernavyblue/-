#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dir.h"

//��pathnameĿ¼���ҵ�����ͼƬ�ļ����ļ�����.bmp��.jpg��β�ģ�
//���أ����޸�ʱ�����絽���˳������õ�����
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
	struct stat st; // ��ȡ�ļ����ԣ�ʱ�䣬�ļ�����
	while( ( dire = readdir(dir))!=NULL)
	{
		//printf("dire->d_name = %s\n",dire->d_name);
		if( ( 0 == strcmp(dire->d_name,".")) || 
			(0 == strcmp(dire->d_name, "..")) )
			continue;
		sprintf(filename, "%s/%s",pathname, dire->d_name);
		//printf("search pictures: filename=%s\n",filename);
		stat(filename, &st);
		if( S_ISREG(st.st_mode)) // ��� ��һ����ͨ�ļ�
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
//�ж�filename�ļ����ĺ�׺�Ƿ�����.bmp��.jpg��β
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

