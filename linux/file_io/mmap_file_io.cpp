#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//关于文件I/O参考：https://app.yinxiang.com/shard/s55/nl/10870108/3bf69fe7-4268-49b4-8971-f426440be1b6/
int main(int argc, char const *argv[])
{
    if ( argc < 2 )
    {
        printf("Usage: ./mmap_file_io <1> file_name \n");
        return 0;
    }

    //file content: this is mmap file io test.
    int fd = open( argv[2], O_RDWR );
    if ( -1 == fd )
    {
        perror( "open" );
        return -1;
    }

    struct stat statbuf;
    if ( -1 == fstat( fd, &statbuf ) )
    {
        perror( "fstat" );
        return -1;
    }

    char *addr = (char *)mmap( NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    close(fd);//关闭文件，并不影响addr
    if ( addr == MAP_FAILED )
    {
        perror( "mmap" );
        return -1;
    }
    strncpy( addr, "that", 4 );

    munmap(addr, statbuf.st_size);

    return 0;
}