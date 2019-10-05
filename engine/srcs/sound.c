
#include <engine.h>

#define WAV_PATH "./game/resources/sounds/gun_single_shot.wav"

void	sound_init(t_engine *eng)
{
	Mix_Chunk *sound = NULL;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		ft_putendl("Fuck1");
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		ft_putendl("Fuck2");
	sound = Mix_LoadWAV(WAV_PATH);
	if (sound == NULL)
		ft_putendl("Fuck3");
	eng->weapon[0]->shoot_sound = sound;
}

void	sound_play(t_engine *eng)
{
	if ( Mix_PlayChannel(-1, eng->weapon[0]->shoot_sound, 0) == -1 )
		ft_putendl("Fuck4");
}

void	sound_free(t_engine *eng)
{
	Mix_FreeChunk(eng->weapon[0]->shoot_sound);
//	Mix_FreeChunk(eng->weapon[1]->shoot_sound);
	Mix_CloseAudio();
}
