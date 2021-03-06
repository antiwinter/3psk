#pragma once
/*
	3psk - 3-pole Phase Shift Keying
	
	Copyright (c) Edward Cree, 2012
	Licensed under the GNU GPL v3+
	
	audio: AUDio Input/Output subsystem
*/

#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audioin.h>

#include <unistd.h>

#define SAMPLE_RATE	22050
#ifdef WINDOWS
#include <windef.h>
#include <winbase.h>
#define AUDIOBUFLEN	4096
#else
#define AUDIOBUFLEN	1024
#endif

#define SLEEP SDL_Delay(sleeptime)

#include "bits.h"
#ifdef WAVLIB
#include "wavlib/wavlib.h"
#endif

typedef struct
{
	unsigned int audiobuflen;
	unsigned int rp, wp;
	int16_t *buf;
	unsigned int srate;
	bool underrun;
	FILE *wav;
#ifdef WAVLIB
	wavhdr wavhdr;
#endif
}
audiobuf;

unsigned int sample_rate, sleeptime;

int init_audiorx(audiobuf *a, unsigned int audiobuflen, unsigned int sdlbuflen, FILE *wav);
void rxaudio(void *udata, Uint8 *stream, int len);
void stop_audiorx(audiobuf *a);
int rxsample(audiobuf *a, int16_t *samp); // returns 0 if we got a sample

int init_audiotx(audiobuf *a, unsigned int audiobuflen, unsigned int sdlbuflen);
void txaudio(void *udata, Uint8 *stream, int len);
void stop_audiotx(audiobuf *a);
void txsample(audiobuf *a, int16_t samp);
bool cantx(audiobuf *a);
