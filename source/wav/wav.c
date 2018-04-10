

#include "wav.h"
#include "../sys/inc.h"
#include "../sys/utils.h"
#include "../sys/debug.h"

void dowav()
{

}

void tone()
{
	// start SDL with audio support
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		char msg[1280];
		sprintf(msg, "SDL_Init: %s\n", SDL_GetError());
		errm("Error", msg);
		// handle error
		//exit(1);
	}
	// show 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		char msg[1280];
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		errm("Error", msg);
		// handle error
		//exit(2);
	}

#if 0
	Mix_AllocateChannels(SOUND_CHANNELS);

	//chunks.assign(channelnum, (Mix_Chunk*)0);

//void play_stereo(const vector<short int>& v, int volume = 128)

	const short int *p = &(v[0]);
	//        short int * p = new short int[v.size()];
	//        for (size_t i=0;i<v.size();i++) {
	//            p[i]=v[i];
	//        }
	Mix_Chunk * ownsample = new Mix_Chunk;
	ownsample->alen = v.size() * 2;
	ownsample->abuf = (Uint8*)p;
	ownsample->allocated = 1;
	ownsample->volume = volume;
	int playchannel = Mix_PlayChannel(-1, ownsample, 0);
	if (playchannel != -1 && chunks[playchannel])
	{
		delete[] chunks[playchannel]->abuf;
		Mix_FreeChunk(chunks[playchannel]);
	}
	if (playchannel != -1)
		chunks[playchannel] = ownsample;

Mix_Chunk *ownsample = 0;
Mix_Chunk *samples = 0;

//hang

	if (Mix_OpenAudio(48000, AUDIO_S16, 2, 1024) == -1)
	{
		cerr << "audio hiba" << endl;
		exit(1);
	}
	vector<short> s(48000 * 2, 0);
	for (int i = 0; i<s.size() / 2; i++)
	{
		s[i * 2] = sin(i / 10.0 + i*i / 10000.0) * 32000 * (1 / sqrt(i / 100.0));
		s[i * 2 + 1] = sin(i / 10.0) * 32000 * (1 / sqrt(i / 100.0));
	}
	samples = Mix_LoadWAV("ding.wav");
	ownsample = new Mix_Chunk;
	ownsample->alen = s.size() * 2;
	ownsample->abuf = (unsigned char*) &(s[0]);
	ownsample->allocated = 0;
	ownsample->volume = 128;
	cout << samples->alen << endl;
	if (!samples)
	{
		cerr << "wav 'ding.wav' open error" << endl;
		exit(1);
	}
	int channelnum = Mix_AllocateChannels(64);

	if (channelnum != 64)
	{
		cerr << "warning: not as many channels are reserved as attended" << endl;
	}
	if (Mix_PlayChannel(-1, ownsample, 0) == -1)
	{
		cerr << "error on play" << endl;
	}
	//    if (Mix_PlayChannel(-1, samples, 0)==-1 ) {
	//        cerr << "error on play" << endl;
	//    }

#if 0
	vector<short> s(48000 * 2, 0);
	for (int i = 0; i<s.size() / 2; i++)
	{
		s[i * 2] = sin(i / 10.0 + i*i / 10000.0) * 32000 * (1 / sqrt(i / 100.0));

		s[i * 2 + 1] = sin(i / 10.0) * 32000 * (1 / sqrt(i / 100.0));
	}
	sm.play_stereo(s);

	SoundManager sm(16);
	sm.init();
	vector<short> s(48000 * 2, 0);
	for (int i = 0; i<s.size() / 2; i++)
	{
		s[i * 2] = sin(i / 10.0 + i*i / 10000.0) * 32000 * (1 / sqrt(i / 100.0));

		s[i * 2 + 1] = sin(i / 10.0) * 32000 * (1 / sqrt(i / 100.0));
	}
#endif
#endif
}