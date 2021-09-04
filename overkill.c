#include "shell.h"

void overkill()
{
    for (int i = 0; i < k_number_of_bg; i++) 
    {
        if(s[i].running==0)
            continue;

        kill(s[i].pid, 9);
    }
}