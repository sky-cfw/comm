#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


unsigned max = 0;

int main()
{
	unsigned blocksize[] = { 1024*1024, 1024, 1 };
	int i, cnt;
	for ( int i = 0;  i < 3; i++ )
	{
		for ( int cnt = 1; ; cnt++ )
		{
			void *mem = malloc( max + blocksize[i] * cnt );
			if ( mem != NULL )
			{
				mem += blocksize[i] * cnt;
				free(mem);
			}
			else
			{
				break;
			}
		}
	}

	printf("max malloc size = %u bytes\n", max);
	return 0;
}
