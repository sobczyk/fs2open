/*
 * Code created by Thomas Whittaker (RT) for a Freespace 2 source code project
 *
 * You may not sell or otherwise commercially exploit the source or things you 
 * created based on the source.
 *
*/ 

#ifndef _SPEECH_H_
#define _SPEECH_H_


#if FS2_SPEECH

const int MAX_SPEECH_CHAR_LEN = 10000;

bool speech_init();
void speech_deinit();
bool speech_play(char *text);
bool speech_play(unsigned short *text);
bool speech_pause();
bool speech_resume();
bool speech_stop();

bool speech_set_volume(int volume);
bool speech_set_voice(int voice);

#else

// Goober5000: see, the *real* way to do stubs (avoiding the warnings)
// is to just use #defines (c.f. NO_SOUND)
#define speech_init() (false)
#define speech_deinit()
#define speech_play(text) ((void) text)
#define speech_play(text) ((void) text)
#define speech_pause() (false)
#define speech_resume() (false)
#define speech_stop() (false)
#define speech_set_volume(volume) ((void) volume)
#define speech_set_voice(voice) ((void) voice)

#endif

#endif