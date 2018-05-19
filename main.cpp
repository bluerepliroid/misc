#include <stdint.h>
#include <math.h>
#include <memory>
#include "file.h"

using namespace Misc;

#define numof(array) (sizeof(array) / sizeof(array[0]))

static const int octave = 0;
static const int pitch = 12;

typedef enum : int {
	C_MAJOR_C = -9,
	C_MAJOR_D = -7,
	C_MAJOR_E = -5,
	C_MAJOR_F = -4,
	C_MAJOR_G = -2,
	C_MAJOR_A = 0,
	C_MAJOR_B = 2,
} CMajor;

static double frequency(double note)
{
	return 440 * pow(2, note / pitch);
}

int main(void)
{
	const unsigned fs = 48000;
	int note[7] = {
		C_MAJOR_C,
		C_MAJOR_D,
		C_MAJOR_E,
		C_MAJOR_F,
		C_MAJOR_G,
		C_MAJOR_A,
		C_MAJOR_B,
	};
	const unsigned sec = numof(note);
	const unsigned length = fs * sec;
	const double volume = 0.5;
	std::unique_ptr<int16_t[]> m(new int16_t[length]);
	for (unsigned i = 0; i < numof(note); i++) {
		note[i] += octave * pitch;
	}
	for (unsigned i = 0; i < sec; i++) {
		const double f = frequency(note[i]);
		printf("%f Hz\n", f);
		for (unsigned j = 0; j < fs; j++) {
			m[fs * i + j] = INT16_MAX * volume * sin(2 * M_PI * f / fs * j);
		}
	}
	{
		File file("out.pcm", "w");
		file.write(m.get(), sizeof(int16_t) * length);
	}
	return 0;
}
