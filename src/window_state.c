#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (__unix__)
    bool is_window_in_foreground(char *target_application) {
        char *env = getenv("XDG_SESSION_TYPE");
        char *desktop_env = getenv("XDG_CURRENT_DESKTOP");
        char *bash_command = NULL;
        if (env != NULL && (env[0] == 'x' || env[0] == 'X')) { //for x11
            bash_command = "xdotool getwindowfocus getwindowname";
        }
        if (env != NULL && (env[0] == 'w' || env[0] == 'W')) { //for wayland
            if (desktop_env[0] == 'K' || desktop_env[0] == 'k') { //for kde
                bash_command = "kdotool getactivewindow getwindowname";
            }
            else if (desktop_env[0] == 'g' || desktop_env[0] == 'G') { //for gnomme
                bash_command = "gdbus call --session --dest org.gnome.Shell"
                    "--object-path /org/gnome/Shell/Extensions/Windows "
                    "--method org.gnome.Shell.Extensions.Windows.List";
            }
        }
        if (bash_command != NULL) {
            FILE *fp;
            char buffer[1024];
            fp = popen(bash_command, "r");
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                if (strcasestr(buffer, target_application) != NULL) {
                    pclose(fp);
                    return true;
                }
            }
            pclose(fp);
        }
        return false;       
    } 
#elif defined(_WIN32) || defined(_WIN64)
    //TO-DO
#endif

