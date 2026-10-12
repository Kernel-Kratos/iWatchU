#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "machine_state.h"
#include "raylib.h"
#include "stopwatch.h"

int main (void) {

    stopwatch_context *now2 = malloc(sizeof(stopwatch_context)); 
    now2 -> accumulated_time.tv_nsec = 0;
    now2 -> accumulated_time.tv_sec = 0;
    stopwatch *stopwatch_frontend = malloc(sizeof(stopwatch));
    start_time_for_stopwatch(now2);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    //SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(80, 50, "iWatchU");
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        stopwatch_function(now2, stopwatch_frontend);
        char time_text[64];
        snprintf(time_text, sizeof(time_text), "%02d:%02d:%02d", stopwatch_frontend -> hours, stopwatch_frontend -> minutes, stopwatch_frontend -> seconds);
        BeginDrawing();
            ClearBackground(BLANK);
            int text_width =  MeasureText(time_text, 20);
            int x = (GetScreenWidth() - text_width) / 2;
            int y = (GetScreenWidth() - 20) / 2;
            DrawText(time_text, x, y, 20, RED);
        EndDrawing();
   }    
    return 0;
}