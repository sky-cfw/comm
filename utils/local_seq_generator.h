#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <string>

class local_seq_generator
{
public:
    local_seq_generator( const key_t &key ):
    shm_key(key),
    inited(false),
    shmid(0),
    pseq(NULL),
    errmsg("")
    {
        if ( (shmid = shmget(shm_key, sizeof(unsigned int), (IPC_CREAT|0666))) == -1) 
        {
            errmsg = "shmget (" + shm_key + std::string(") error:") + std::string( strerror(errno) );
            return ;
        }
        
        //
        if ( (pseq = (unsigned int *)shmat(shmid, NULL, 0)) == (unsigned int *)-1 )
        {
            errmsg = "shmat (" + shm_key + std::string(") error:") + std::string( strerror(errno) );
            return ;
        }

        inited = true;
    }

    ~local_seq_generator()
    {
        if ( pseq != (unsigned int *)-1
        && -1 == shmdt((void *)pseq) )
        {
            errmsg = "shmdt (" + shm_key + std::string(") error:") + std::string( strerror(errno) );
            return ;
        }
    }

    bool is_inited()
    {
        return inited;
    }

    //
    unsigned int generator_seqno()
    {
        return __sync_fetch_and_add( pseq, 1 ); 
    }

    //
    std::string get_last_errmsg()
    {
        return errmsg;
    }
private:
    key_t shm_key;
    bool inited;
    int shmid;
    volatile unsigned int *pseq; 
    std::string errmsg;
};

