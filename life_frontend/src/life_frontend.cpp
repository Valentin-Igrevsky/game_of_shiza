#include "life_frontend.h"

life_frontend::life_frontend::life_frontend(const std::string &sdlLibraryPath) {
    sdl_lib_path = sdlLibraryPath;

    #if defined(_WIN32) || defined(_WIN64)
        sdl_lib_handle = LOAD_LIBRARY(sdl_lib_path.c_str());
    #elif defined(__linux__)
        sdl_lib_handle = LOAD_LIBRARY(sdl_lib_path.c_str(), RTLD_NOW);
    #endif


    SDL_Init_Func = (int (*)(Uint32)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_Init");

    SDL_CreateWindow_Func = (SDL_Window *(*)(const char *, int, int, int, int, Uint32)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                                       "SDL_CreateWindow");
    SDL_CreateRenderer_Func = (SDL_Renderer *(*)(SDL_Window *, int, Uint32)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                            "SDL_CreateRenderer");
    SDL_SetRenderDrawColor_Func = (int (*)(SDL_Renderer *, Uint8, Uint8, Uint8, Uint8)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                                       "SDL_SetRenderDrawColor");
    SDL_Quit_Func = (void (*)(void)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_Quit");
    SDL_DestroyWindow_Func = (int (*)(SDL_Window *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_DestroyWindow");
    SDL_Delay_Func = (void (*)(Uint32)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_Delay");
    SDL_RenderDrawLine_Func = (int (*)(SDL_Renderer *, int, int, int, int)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                           "SDL_RenderDrawLine");
    SDL_RenderClear_Func = (int (*)(SDL_Renderer *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_RenderClear");
    SDL_RenderFillRect_Func = (int (*)(SDL_Renderer *, const SDL_Rect *)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                         "SDL_RenderFillRect");
    SDL_RenderPresent_Func = (void (*)(SDL_Renderer *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_RenderPresent");
    SDL_PollEvent_Func = (int (*)(SDL_Event *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_PollEvent");
    SDL_DestroyRenderer_Func = (void (*)(SDL_Renderer *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_DestroyRenderer");

    SDL_GetWindowSurface_Func = (SDL_Surface *(*)(SDL_Window *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_GetWindowSurface");

    SDL_FillRect_Func = (int (*)(SDL_Surface *, const SDL_Rect *, Uint32)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                          "SDL_FillRect");

    SDL_UpdateWindowSurface_Func = (int (*)(SDL_Window *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_UpdateWindowSurface");

    SDL_MapRGB_Func = (Uint32 (*)(const SDL_PixelFormat *, Uint8, Uint8, Uint8)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                                "SDL_MapRGB");

    SDL_SetWindowTitle_Func = (void (*)(SDL_Window *, const char *)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                    "SDL_SetWindowTitle");

    SDL_GetMouseState_Func = (Uint32 (*)(int *, int *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_GetMouseState");

    SDL_SetWindowGrab_Func = (void (*)(SDL_Window *, SDL_bool)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_SetWindowGrab");

    SDL_GetWindowSize_Func = (void (*)(SDL_Window *, int *, int *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_GetWindowSize");

    SDL_SetWindowSize_Func = (void (*)(SDL_Window *, int, int)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_SetWindowSize");

    SDL_GetWindowGrab_Func = (SDL_bool (*)(SDL_Window *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_GetWindowGrab");

    SDL_RWFromFile_Func = (SDL_RWops *(*)(const char *, const char *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_RWFromFile");

    SDL_LoadBMP_RW_Func = (SDL_Surface *(*)(SDL_RWops *, int)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_LoadBMP_RW");

    SDL_SetWindowIcon_Func = (void (*)(SDL_Window *, SDL_Surface *)) GET_PROC_ADDRESS(sdl_lib_handle,
                                                                                    "SDL_SetWindowIcon");

    SDL_FreeSurface_Func = (void (*)(SDL_Surface *)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_FreeSurface");

    IMG_Load_Func = (SDL_Surface *(*)(const char *)) GET_PROC_ADDRESS(sdl_lib_handle, "IMG_Load");

    SDL_GetError_Func = (const char* (*)(void)) GET_PROC_ADDRESS(sdl_lib_handle, "SDL_GetError");
}

life_frontend::life_frontend::~life_frontend() {
    this->SDL_Quit();
    FREE_LIBRARY(sdl_lib_handle); // Unload the SDL library
}

int life_frontend::life_frontend::SDL_Init(Uint32 flags) {
    return SDL_Init_Func(flags);

}

SDL_Window *
life_frontend::life_frontend::SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags) {
    return SDL_CreateWindow_Func(title, x, y, w, h, flags);

}

SDL_Renderer *life_frontend::life_frontend::SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags) {
    return SDL_CreateRenderer_Func(window, index, flags);

}

int life_frontend::life_frontend::SDL_SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    return SDL_SetRenderDrawColor_Func(renderer, r, g, b, a);

}

void life_frontend::life_frontend::SDL_Quit(void) {
    SDL_Quit_Func();
}

int life_frontend::life_frontend::SDL_DestroyWindow(SDL_Window *window) {
    return SDL_DestroyWindow_Func(window);

}

int life_frontend::life_frontend::SDL_RenderClear(SDL_Renderer *renderer) {
    return SDL_RenderClear_Func(renderer);

}

void life_frontend::life_frontend::SDL_DestroyRenderer(SDL_Renderer *renderer) {
    SDL_DestroyRenderer_Func(renderer);


}

int life_frontend::life_frontend::SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect) {
    return SDL_RenderFillRect_Func(renderer, rect);

}

void life_frontend::life_frontend::SDL_RenderPresent(SDL_Renderer *renderer) {
    SDL_RenderPresent_Func(renderer);


}

int life_frontend::life_frontend::SDL_PollEvent(SDL_Event *event) {
    return SDL_PollEvent_Func(event);
}

void life_frontend::life_frontend::SDL_Delay(Uint32 ms) {
    SDL_Delay_Func(ms);

}

void life_frontend::life_frontend::SDL_RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine_Func(renderer, x1, y1, x2, y2);
}

SDL_Surface *life_frontend::life_frontend::SDL_GetWindowSurface(SDL_Window *window) {
    return SDL_GetWindowSurface_Func(window);
}

int life_frontend::life_frontend::SDL_FillRect(SDL_Surface *dst, const SDL_Rect *rect, Uint32 color) {
    return SDL_FillRect_Func(dst, rect, color);
}

int life_frontend::life_frontend::SDL_UpdateWindowSurface(SDL_Window *window) {
    return SDL_UpdateWindowSurface_Func(window);
}

Uint32 life_frontend::life_frontend::SDL_MapRGB(const SDL_PixelFormat *format, Uint8 r, Uint8 g, Uint8 b) {
    return SDL_MapRGB_Func(format, r, g, b);
}

void life_frontend::life_frontend::SDL_SetWindowTitle(SDL_Window *window, const char *title) {
    SDL_SetWindowTitle_Func(window, title);
}

Uint32 life_frontend::life_frontend::SDL_GetMouseState(int *x, int *y) {
    return SDL_GetMouseState_Func(x, y);
}

void life_frontend::life_frontend::SDL_SetWindowGrab(SDL_Window *window, SDL_bool grabbed) {
    SDL_SetWindowGrab_Func(window, grabbed);
}

void life_frontend::life_frontend::SDL_GetWindowSize(SDL_Window *window, int *w, int *h) {
    SDL_GetWindowSize_Func(window, w, h);
}

void life_frontend::life_frontend::SDL_SetWindowSize(SDL_Window *window, int w, int h) {
    SDL_SetWindowSize_Func(window, w, h);
}

SDL_bool life_frontend::life_frontend::SDL_GetWindowGrab(SDL_Window *window) {
    return SDL_GetWindowGrab_Func(window);
}

SDL_RWops *life_frontend::life_frontend::SDL_RWFromFile(const char *file, const char *mode) {
    return SDL_RWFromFile_Func(file, mode);
}

SDL_Surface *life_frontend::life_frontend::SDL_LoadBMP_RW(SDL_RWops *src, int freesrc) {
    return SDL_LoadBMP_RW_Func(src, freesrc);
}

void life_frontend::life_frontend::SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon) {
    SDL_SetWindowIcon_Func(window, icon);
}

void life_frontend::life_frontend::SDL_FreeSurface(SDL_Surface *surface) {
    SDL_FreeSurface_Func(surface);
}

SDL_Surface *life_frontend::life_frontend::IMG_Load(const char *file) {
    return IMG_Load_Func(file);
}

const char* life_frontend::life_frontend::SDL_GetError() {
    return SDL_GetError_Func();
}

life_frontend::SDL_MUSIC::SDL_MUSIC(const std::string &sdl2mixerLibraryPath) {
    sdl2mixer_lib_path = sdl2mixerLibraryPath;

    #if defined(_WIN32) || defined(_WIN64)
        sdl2mixer_lib_handle = LOAD_LIBRARY(sdl2mixer_lib_path.c_str());
    #elif defined(__linux__)
        sdl2mixer_lib_handle = LOAD_LIBRARY(sdl2mixer_lib_path.c_str(), RTLD_NOW);
    #endif


    Mix_Init_Func = (int (*)(int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_Init");

    Mix_Quit_Func = (void (*)(void)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_Quit");

    Mix_OpenAudio_Func = (int (*)(int, Uint16, int, int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_OpenAudio");

    Mix_LoadMUS_Func = (Mix_Music * (*)(const char *)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_LoadMUS");

    Mix_FreeMusic_Func = (void (*)(Mix_Music *)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_FreeMusic");

    Mix_CloseAudio_Func = (void (*)(void)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_CloseAudio");

    Mix_PlayMusic_Func = (int (*)(Mix_Music *, int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_PlayMusic");

    Mix_PlayingMusic_Func = (int (*)(void)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_PlayingMusic");

    Mix_LoadWAV_RW_Func = (Mix_Chunk * (*)(SDL_RWops *, int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_LoadWAV_RW");

    Mix_VolumeMusic_Func = (int (*)(int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_VolumeMusic");

    Mix_Volume_Func = (int (*)(int, int)) GET_PROC_ADDRESS(sdl2mixer_lib_handle, "Mix_Volume");
}

life_frontend::SDL_MUSIC::~SDL_MUSIC(){
    this->Mix_Quit();
    FREE_LIBRARY(sdl2mixer_lib_handle);
}

int life_frontend::SDL_MUSIC::Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize) {
    return Mix_OpenAudio_Func(frequency, format, channels, chunksize);
}

Mix_Music * life_frontend::SDL_MUSIC::Mix_LoadMUS(const char * file) {
    return Mix_LoadMUS_Func(file);
}

void life_frontend::SDL_MUSIC::Mix_FreeMusic(Mix_Music * music) {
    Mix_FreeMusic_Func(music);
}

void life_frontend::SDL_MUSIC::Mix_CloseAudio() {
    Mix_CloseAudio_Func();
}

int life_frontend::SDL_MUSIC::Mix_PlayMusic(Mix_Music * music, int loops) {
    return Mix_PlayMusic_Func(music, loops);
}

int life_frontend::SDL_MUSIC::Mix_Init(int flags) {
    return Mix_Init_Func(flags);
}

int life_frontend::SDL_MUSIC::Mix_PlayingMusic(void) {
    return Mix_PlayingMusic_Func();
}

Mix_Chunk * life_frontend::SDL_MUSIC::Mix_LoadWAV_RW(SDL_RWops * src, int freesrc) {
    return Mix_LoadWAV_RW_Func(src, freesrc);
}

int life_frontend::SDL_MUSIC::Mix_VolumeMusic(int volume) {
    return Mix_VolumeMusic_Func(volume);
}

void life_frontend::SDL_MUSIC::Mix_Quit(void) {
    Mix_Quit_Func();
}

int life_frontend::SDL_MUSIC::Mix_Volume(int channel, int volume) {
    return Mix_Volume_Func(channel, volume);
}