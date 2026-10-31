#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "machine_state.h"
#include "raylib.h"
#include "stopwatch.h"
#include "window_state.h"

int main (int argc, char *argv[]) {
    stopwatch_context *now = malloc(sizeof(stopwatch_context)); 
    now -> accumulated_time.tv_nsec = 0;
    now -> accumulated_time.tv_sec = 0;
    stopwatch *stopwatch_frontend = malloc(sizeof(stopwatch));
    char time_text[64];
    SetConfigFlags (FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags (FLAG_WINDOW_UNDECORATED);
    SetConfigFlags (FLAG_WINDOW_TOPMOST);
    int screen_width = 80;
    int screen_height = 50;
    InitWindow(screen_width, screen_height, "iWatchU");
    Vector2 dragOffset = {0.0f, 0.0f};
    bool isDragging = false;
    bool is_window_tracking = false;
    SetTargetFPS(30);
    while (is_window_open(argv[1]) && !WindowShouldClose()) {
        if (!is_window_tracking) {
            start_time_for_stopwatch(now);
            is_window_tracking = true;
        }
        Vector2 mousePos = GetMousePosition();
        Vector2 windowPos = GetWindowPosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDragging = true;
            dragOffset = mousePos;
        }
        if (isDragging) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                int newWinX = (int) (windowPos.x + mousePos.x - dragOffset.x);
                int newWinY = (int) (windowPos.y + mousePos.y - dragOffset.y);
                SetWindowPosition (newWinX, newWinY);
            }
            else {
                isDragging = false;
            }
        }
        if (is_window_in_foreground(argv[1])) {
            stopwatch_function(now, stopwatch_frontend);
        }
        else {
            if (is_window_tracking){
                pause_stopwatch(now);
                start_time_for_stopwatch(now);
                is_window_tracking = false;
            }
        }
        snprintf(time_text, sizeof(time_text), "%02d:%02d:%02d", stopwatch_frontend -> hours, stopwatch_frontend -> minutes, stopwatch_frontend -> seconds);
        BeginDrawing();
            ClearBackground(BLANK);
            int text_width =  MeasureText(time_text, 20);
            int x = (GetScreenWidth() - text_width) / 2;
            int y = (GetScreenHeight() - 20) / 2;
            DrawText(time_text, x, y, 20, RED);
        EndDrawing();
    }
    free (now);
    free (stopwatch_frontend);    
    return 0;
}