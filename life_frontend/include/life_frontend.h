#include "SDL.h"
#include <Windows.h>
#include <string>

#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#elif defined(__APPLE__)
#define OS_MACOS
#elif defined(__linux__)
#define OS_LINUX
#else
#error "Unknown platform"
#endif

#ifdef OS_WINDOWS
#define SDL_LIB_PATH "SDL2.dll"
#elif defined(OS_MACOS)
#define SDL_LIB_PATH "libSDL2.dylib"
#elif defined(OS_LINUX)
#define SDL_LIB_PATH "libSDL2.so"
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

    private:
        std::string sdl_lib_path;
        HMODULE sdl_lib_handle;

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
//
//    bool isRunning;
//    SDL_Window* window;
//    SDL_Renderer* renderer;
    };
}


