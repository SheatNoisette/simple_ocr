/*
      ___           ___           ___     
     /\  \         /\  \         /\  \    
    /::\  \       /::\  \       /::\  \   
   /:/\:\  \     /:/\:\  \     /:/\:\  \  
  /:/  \:\  \   /:/  \:\  \   /::\~\:\  \ 
 /:/__/ \:\__\ /:/__/ \:\__\ /:/\:\ \:\__\
 \:\  \ /:/  / \:\  \  \/__/ \/_|::\/:/  /
  \:\  /:/  /   \:\  \          |:|::/  / 
   \:\/:/  /     \:\  \         |:|\/__/  
    \::/  /       \:\__\        |:|  |    
     \/__/         \/__/         \|__|    

    SIMPLE OPTICAL CHARACTERS RECOGNITION

 */

#include <stdio.h>
#include "cli.h"
#ifdef GTK
    #include "gui_gtk.h"
#endif

int main(int argc, char **argv)
{
    //Using GTK
    #ifdef GTK

        if (argc == 1) {
            gui_run(argc, argv);
        } else {
            //Parse command
            cli_parse_commands(argc, argv);
        }

    #else
        cli_parse_commands(argc, argv);
    #endif

    return 0;
}
