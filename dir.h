#ifndef __DIR_H__
#define __DIR_H__


#include "list.h"

enum filetype
{
	FILE_BMP,
	FILE_JPEG,
	FILE_MP3,
	FILE_MP4
};

//从pathname目录中找到所有图片文件（文件名以.bmp和.jpg结尾的）
//返回：按修改时间由早到晚的顺序排序好的链表
struct fList *search_musics( const char *pathname);

//判断filename文件的类型，是bmp还是jpg格式
enum filetype get_file_type(const char *filename);
#endif

