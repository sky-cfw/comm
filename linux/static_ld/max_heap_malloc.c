#include <stdio.h>
#include <stdlib.h>


unsigned max = 0;

int main()
{
	unsigned blocksize[] = { 1024*1024, 1024, 1 };
	int i, cnt;
	for ( i = 0;  i < 3; i++ )
	{
		for ( cnt = 1; ; cnt++ )
		{
			void *mem = malloc( max + blocksize[i] * cnt );
			if ( mem != NULL )
			{
				max += blocksize[i] * cnt;
				printf("i[%d] cnt[%d] max[%u]\n", i, cnt , max);
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
