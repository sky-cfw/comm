#include <stdio.h>
#include <unistd.h>
#include "local_seq_generator.h"

int main()
{
    const key_t SHM_KEY_UNI_BILLNO = 0x20220305;
    
    for ( int i = 0; i < 8; i++ )
    {
        if ( 0 == fork() )
        {
            local_seq_generator sg(SHM_KEY_UNI_BILLNO);
	    for ( int j = 0; j < 10000; j++ )
            {
                printf("pid[%u] seq[%u]\n", getpid(), sg.generator_seqno());
	    }
	    break;
	}
    }

    return 0;
}
