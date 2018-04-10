

#include "wav.h"
#include "../sys/inc.h"
#include "../sys/utils.h"
#include "../sys/debug.h"


//Wav Header
struct wav_header_t
{
	char chunkID[4]; //"RIFF" = 0x46464952
	unsigned long chunkSize; //28 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes] + sum(sizeof(chunk.id) + sizeof(chunk.size) + chunk.size)
	char format[4]; //"WAVE" = 0x45564157
	char subchunk1ID[4]; //"fmt " = 0x20746D66
	unsigned long subchunk1Size; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	//[WORD wExtraFormatBytes;]
	//[Extra format bytes]
};

typedef struct wav_header_t wav_header_t;

//Chunks
struct chunk_t
{
	char ID[4]; //"data" = 0x61746164
	unsigned long size;  //Chunk data bytes
};

typedef struct chunk_t chunk_t;

void WavReader(const char* fileName, const char* fileToSave)
{
	FILE *fin = fopen(fileName, "rb");

	//Read WAV header
	wav_header_t header;
	fread(&header, sizeof(header), 1, fin);

	//Print WAV header
	printf("WAV File Header read:\n");
	printf("File Type: %s\n", header.chunkID);
	printf("File Size: %ld\n", header.chunkSize);
	printf("WAV Marker: %s\n", header.format);
	printf("Format Name: %s\n", header.subchunk1ID);
	printf("Format Length: %ld\n", header.subchunk1Size);
	printf("Format Type: %hd\n", header.audioFormat);
	printf("Number of Channels: %hd\n", header.numChannels);
	printf("Sample Rate: %ld\n", header.sampleRate);
	printf("Sample Rate * Bits/Sample * Channels / 8: %ld\n", header.byteRate);
	printf("Bits per Sample * Channels / 8.1: %hd\n", header.blockAlign);
	printf("Bits per Sample: %hd\n", header.bitsPerSample);

	//skip wExtraFormatBytes & extra format bytes
	//fseek(f, header.chunkSize - 16, SEEK_CUR);

	//Reading file
	chunk_t chunk;
	printf("id\t" "size\n");
	//go to data chunk
	while (dtrue)
	{
		fread(&chunk, sizeof(chunk), 1, fin);
		printf("%c%c%c%c\t" "%li\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		fseek(fin, chunk.size, SEEK_CUR);
	}

	//Number of samples
	int sample_size = header.bitsPerSample / 8;
	int samples_count = chunk.size * 8 / header.bitsPerSample;
	printf("Samples count = %i\n", samples_count);

	short int *value = (short int*)malloc(sizeof(short int)*samples_count);
	memset(value, 0, sizeof(short int) * samples_count);

	//Reading data
	for (int i = 0; i < samples_count; i++)
	{
		fread(&value[i], sample_size, 1, fin);
	}

	//Write data into the file
	FILE *fout = fopen(fileToSave, "w");
	for (int i = 0; i < samples_count; i++)
	{
		fprintf(fout, "%d\n", value[i]);
	}
	fclose(fin);
	fclose(fout);
}


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