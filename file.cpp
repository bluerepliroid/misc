#include "file.h"

namespace Misc {

File::File(const char *path, const char *mode)
	: m_fp(nullptr)
{
	m_fp = fopen(path, mode);
}

File::~File(void)
{
	if (m_fp != nullptr) {
		fclose(m_fp);
	}
}

size_t File::read(void *p, size_t size)
{
	return fread(p, size, 1, m_fp);
}

size_t File::write(const void *p, size_t size)
{
	return fwrite(p, size, 1, m_fp);
}

int File::seek(int32_t offset)
{
	return fseek(m_fp, offset, SEEK_SET);
}

}
