#include "stdio.h"

#ifndef _FILE
#define _FILE

namespace Misc {

class File
{
public:
	File(const char *path, const char *mode);
	~File(void);
	size_t read(void *p, size_t size);
	size_t write(const void *p, size_t size);
	int seek(int32_t offset);
private:
	FILE *m_fp;
};

}

#endif
