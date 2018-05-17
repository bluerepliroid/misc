#include <stdint.h>
#include <math.h>
#include <memory>

int main(void)
{
	const unsigned fs = 48000;
	const unsigned sec = 5;
	const unsigned length = fs * sec;
	const unsigned f = 500;
	const double volume = 0.5;
	std::unique_ptr<int16_t[]> m(new int16_t[length]);
	for (unsigned i = 0; i < length; i++) {
		m[i] = INT16_MAX * volume * sin(2 * M_PI * f / fs * i);
	}
	{
		FILE *fp = fopen("out.pcm", "w");
		fwrite(m.get(), sizeof(int16_t) * length, 1, fp);
		fclose(fp);
	}
	return 0;
}
