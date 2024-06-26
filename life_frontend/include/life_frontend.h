#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_rwops.h"
#include "SDL_mixer.h"
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #define GET_PROC_ADDRESS GetProcAddress
    #define LOAD_LIBRARY LoadLibrary
    #define FREE_LIBRARY FreeLibrary
    #define HANDLER HMODULE
#elif defined(__linux__)
    #include <dlfcn.h>
    #define GET_PROC_ADDRESS dlsym
    #define LOAD_LIBRARY dlopen
    #define FREE_LIBRARY dlclose
    #define HANDLER void*
#endif

namespace life_frontend {
    class life_frontend {
    public:
        explicit life_frontend(const std::string &sdlLibraryPath);

        ~life_frontend();

        int SDL_Init(Uint32 flags);

        SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);

        SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags);

        int SDL_SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        void SDL_Quit(void);

        int SDL_DestroyWindow(SDL_Window *window);

        int SDL_RenderClear(SDL_Renderer *renderer);

        void SDL_DestroyRenderer(SDL_Renderer *renderer);

        int SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect);

        void SDL_RenderPresent(SDL_Renderer *renderer);

        int SDL_PollEvent(SDL_Event *event);

        void SDL_Delay(Uint32 ms);

        void SDL_RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

        SDL_Surface *SDL_GetWindowSurface(SDL_Window *window);

        int SDL_FillRect(SDL_Surface *dst, const SDL_Rect *rect, Uint32 color);

        int SDL_UpdateWindowSurface(SDL_Window * window);

        Uint32 SDL_MapRGB(const SDL_PixelFormat * format, Uint8 r, Uint8 g, Uint8 b);

        void SDL_SetWindowTitle(SDL_Window * window, const char * title);

        Uint32 SDL_GetMouseState(int * x, int * y);

        void SDL_SetWindowGrab(SDL_Window * window, SDL_bool grabbed);

        void SDL_GetWindowSize(SDL_Window * window, int * w, int * h);

        void SDL_SetWindowSize(SDL_Window * window, int w, int h);

        SDL_bool SDL_GetWindowGrab(SDL_Window * window);

        SDL_RWops* SDL_RWFromFile(const char * file, const char * mode);

        SDL_Surface* SDL_LoadBMP_RW(SDL_RWops * src, int freesrc);

        void SDL_SetWindowIcon(SDL_Window * window, SDL_Surface * icon);

        void SDL_FreeSurface(SDL_Surface * surface);

        SDL_Surface * IMG_Load(const char *file);

        const char* SDL_GetError(void);


    private:
        std::string sdl_lib_path;
        HANDLER sdl_lib_handle;

        int (*SDL_Init_Func)(Uint32 flags) = nullptr;

        void (*SDL_Quit_Func)(void) = nullptr;

        SDL_Renderer *(*SDL_CreateRenderer_Func)(SDL_Window *window, int index, Uint32 flags) = nullptr;

        SDL_Window *(*SDL_CreateWindow_Func)(const char *title, int x, int y, int w, int h, Uint32 flags) = nullptr;

        int (*SDL_SetRenderDrawColor_Func)(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = nullptr;

        void (*SDL_DestroyRenderer_Func)(SDL_Renderer *renderer) = nullptr;

        int (*SDL_DestroyWindow_Func)(SDL_Window *window) = nullptr;

        int (*SDL_RenderClear_Func)(SDL_Renderer *renderer) = nullptr;

        int (*SDL_RenderFillRect_Func)(SDL_Renderer *renderer, const SDL_Rect *rect) = nullptr;

        void (*SDL_RenderPresent_Func)(SDL_Renderer *renderer) = nullptr;

        int (*SDL_PollEvent_Func)(SDL_Event *event) = nullptr;

        int (*SDL_RenderDrawLine_Func)(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) = nullptr;

        void (*SDL_Delay_Func)(Uint32 ms) = nullptr;

        SDL_Surface *(*SDL_GetWindowSurface_Func)(SDL_Window *window) = nullptr;

        int (*SDL_FillRect_Func)(SDL_Surface *dst, const SDL_Rect *rect, Uint32 color) = nullptr;

        int (*SDL_UpdateWindowSurface_Func)(SDL_Window * window) = nullptr;

        Uint32 (*SDL_MapRGB_Func)(const SDL_PixelFormat * format, Uint8 r, Uint8 g, Uint8 b) = nullptr;

        void (*SDL_SetWindowTitle_Func)(SDL_Window * window, const char * title) = nullptr;

        Uint32 (*SDL_GetMouseState_Func)(int * x, int * y) = nullptr;

        void (*SDL_SetWindowGrab_Func)(SDL_Window * window, SDL_bool grabbed) = nullptr;

        void (*SDL_GetWindowSize_Func)(SDL_Window * window, int * w, int * h) = nullptr;

        void (*SDL_SetWindowSize_Func)(SDL_Window * window, int w, int h) = nullptr;

        SDL_bool (*SDL_GetWindowGrab_Func)(SDL_Window * window) = nullptr;

        SDL_RWops* (*SDL_RWFromFile_Func)(const char * file, const char * mode) = nullptr;

        SDL_Surface* (*SDL_LoadBMP_RW_Func)(SDL_RWops * src, int freesrc) = nullptr;

        void (*SDL_SetWindowIcon_Func)(SDL_Window * window, SDL_Surface * icon) = nullptr;

        void (*SDL_FreeSurface_Func)(SDL_Surface * surface) = nullptr;

        SDL_Surface* (*IMG_Load_Func)(const char *file) = nullptr;

        const char* (*SDL_GetError_Func)(void) = nullptr;
    };

    class SDL_MUSIC {
    public:
        SDL_MUSIC(const std::string &sdl2mixerLibraryPath);

        ~SDL_MUSIC();

        void Mix_Quit(void);

        int Mix_Init(int flags);

        int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);

        Mix_Music * Mix_LoadMUS(const char * file);

        void Mix_FreeMusic(Mix_Music * music);

        void Mix_CloseAudio(void);

        int Mix_PlayMusic(Mix_Music *music, int loops);

        int Mix_PlayingMusic(void);

        Mix_Chunk * Mix_LoadWAV_RW(SDL_RWops * src, int freesrc);

        int Mix_VolumeMusic(int volume);

        int Mix_Volume(int channel, int volume);

    private:

        std::string sdl2mixer_lib_path;
        HANDLER sdl2mixer_lib_handle;

        int (*Mix_Init_Func)(int flags) = nullptr;

        void (*Mix_Quit_Func)(void) = nullptr;

        int (*Mix_OpenAudio_Func)(int frequency, Uint16 format, int channels, int chunksize) = nullptr;

        Mix_Music * (*Mix_LoadMUS_Func)(const char * file) = nullptr;

        void (*Mix_FreeMusic_Func)(Mix_Music * music) = nullptr;

        void (*Mix_CloseAudio_Func)(void) = nullptr;

        int (*Mix_PlayMusic_Func)(Mix_Music *music, int loops) = nullptr;

        int (*Mix_PlayingMusic_Func)(void) = nullptr;

        Mix_Chunk * (*Mix_LoadWAV_RW_Func)(SDL_RWops * src, int freesrc) = nullptr;

        int (*Mix_VolumeMusic_Func)(int volume) = nullptr;

        int (*Mix_Volume_Func)(int channel, int volume) = nullptr;
    };

}