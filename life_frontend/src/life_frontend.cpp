#include "life_frontend.h"
#include "SDL.h"
#include <Windows.h>

life_frontend::life_frontend::life_frontend(const std::string &sdlLibraryPath) {
    sdl_lib_path = sdlLibraryPath;
    sdl_lib_handle = LoadLibrary(sdl_lib_path.c_str());

    SDL_Init_Func = (int (*)(Uint32)) GetProcAddress(sdl_lib_handle, "SDL_Init");
    SDL_CreateWindow_Func = (SDL_Window *(*)(const char *, int, int, int, int, Uint32)) GetProcAddress(sdl_lib_handle,
                                                                                                       "SDL_CreateWindow");
    SDL_CreateRenderer_Func = (SDL_Renderer *(*)(SDL_Window *, int, Uint32)) GetProcAddress(sdl_lib_handle,
                                                                                            "SDL_CreateRenderer");
    SDL_SetRenderDrawColor_Func = (int (*)(SDL_Renderer *, Uint8, Uint8, Uint8, Uint8)) GetProcAddress(sdl_lib_handle,
                                                                                                       "SDL_SetRenderDrawColor");
    SDL_Quit_Func = (void (*)(void)) GetProcAddress(sdl_lib_handle, "SDL_Quit");
    SDL_DestroyWindow_Func = (int (*)(SDL_Window *)) GetProcAddress(sdl_lib_handle, "SDL_DestroyWindow");
    SDL_Delay_Func = (void (*)(Uint32)) GetProcAddress(sdl_lib_handle, "SDL_Delay");
    SDL_RenderDrawLine_Func = (int (*)(SDL_Renderer *, int, int, int, int)) GetProcAddress(sdl_lib_handle,
                                                                                           "SDL_RenderDrawLine");
    SDL_RenderClear_Func = (int (*)(SDL_Renderer *)) GetProcAddress(sdl_lib_handle, "SDL_RenderClear");
    SDL_RenderFillRect_Func = (int (*)(SDL_Renderer *, const SDL_Rect *)) GetProcAddress(sdl_lib_handle,
                                                                                         "SDL_RenderFillRect");
    SDL_RenderPresent_Func = (void (*)(SDL_Renderer *)) GetProcAddress(sdl_lib_handle, "SDL_RenderPresent");
    SDL_PollEvent_Func = (int (*)(SDL_Event *)) GetProcAddress(sdl_lib_handle, "SDL_PollEvent");
    SDL_DestroyRenderer_Func = (void (*)(SDL_Renderer *)) GetProcAddress(sdl_lib_handle, "SDL_DestroyRenderer");

    SDL_GetWindowSurface_Func = (SDL_Surface * (*)(SDL_Window *)) GetProcAddress(sdl_lib_handle, "SDL_GetWindowSurface");

    SDL_FillRect_Func = (int (*)(SDL_Surface *, const SDL_Rect *, Uint32)) GetProcAddress(sdl_lib_handle, "SDL_FillRect");

    SDL_UpdateWindowSurface_Func = (int (*)(SDL_Window *)) GetProcAddress(sdl_lib_handle, "SDL_UpdateWindowSurface");

    SDL_MapRGB_Func = (Uint32 (*)(const SDL_PixelFormat *, Uint8, Uint8, Uint8)) GetProcAddress(sdl_lib_handle, "SDL_MapRGB");

    SDL_SetWindowTitle_Func = (void (*)(SDL_Window *, const char *)) GetProcAddress(sdl_lib_handle, "SDL_SetWindowTitle");

    SDL_GetMouseState_Func = (Uint32 (*)(int *, int *)) GetProcAddress(sdl_lib_handle, "SDL_GetMouseState");

    SDL_SetWindowGrab_Func = (void (*)(SDL_Window *, SDL_bool)) GetProcAddress(sdl_lib_handle, "SDL_SetWindowGrab");

    SDL_GetWindowSize_Func = (void (*)(SDL_Window *, int *, int *)) GetProcAddress(sdl_lib_handle, "SDL_GetWindowSize");

    SDL_SetWindowSize_Func = (void (*)(SDL_Window *, int, int)) GetProcAddress(sdl_lib_handle, "SDL_SetWindowSize");

    SDL_GetWindowGrab_Func = (SDL_bool (*)(SDL_Window *)) GetProcAddress(sdl_lib_handle, "SDL_GetWindowGrab");
}

life_frontend::life_frontend::~life_frontend() {
    this->SDL_Quit();
    FreeLibrary(sdl_lib_handle); // Unload the SDL library
}

int life_frontend::life_frontend::SDL_Init(Uint32 flags) {
    return SDL_Init_Func(flags);

}

SDL_Window *life_frontend::life_frontend::SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags) {
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

SDL_Surface * life_frontend::life_frontend::SDL_GetWindowSurface(SDL_Window * window) {
    return SDL_GetWindowSurface_Func(window);
}

int life_frontend::life_frontend::SDL_FillRect(SDL_Surface * dst, const SDL_Rect * rect, Uint32 color) {
    return SDL_FillRect_Func(dst, rect, color);
}

int life_frontend::life_frontend::SDL_UpdateWindowSurface(SDL_Window * window) {
    return SDL_UpdateWindowSurface_Func(window);
}

Uint32 life_frontend::life_frontend::SDL_MapRGB(const SDL_PixelFormat * format, Uint8 r, Uint8 g, Uint8 b) {
    return SDL_MapRGB_Func(format, r, g, b);
}

void life_frontend::life_frontend::SDL_SetWindowTitle(SDL_Window * window, const char * title) {
    SDL_SetWindowTitle_Func(window, title);
}

Uint32 life_frontend::life_frontend::SDL_GetMouseState(int * x, int * y) {
    return SDL_GetMouseState_Func(x, y);
}

void life_frontend::life_frontend::SDL_SetWindowGrab(SDL_Window * window, SDL_bool grabbed) {
    SDL_SetWindowGrab_Func(window, grabbed);
}

void life_frontend::life_frontend::SDL_GetWindowSize(SDL_Window * window, int * w, int * h) {
    SDL_GetWindowSize_Func(window, w, h);
}

void life_frontend::life_frontend::SDL_SetWindowSize(SDL_Window * window, int w, int h) {
    SDL_SetWindowSize_Func(window, w, h);
}

SDL_bool life_frontend::life_frontend::SDL_GetWindowGrab(SDL_Window * window) {
    return SDL_GetWindowGrab_Func(window);
}