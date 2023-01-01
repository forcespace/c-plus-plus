//Вложенность скобок - int main
#include <fstream>
#include <string.h>

#define MAX_STACK_SIZE 1000

int main( int argc, char* argv[] )
{
	FILE* pFile = NULL;
	char buffer[MAX_STACK_SIZE];
	char stack[MAX_STACK_SIZE];
	int stackPointer = -1;
	char open[3] = { '(', '[', '{' };
	char close[3] = { ')', ']', '}' };
	char ch;
	int i, j;
	int len;
	int res;


	if ( argc > 1 )
	{
		pFile = fopen( argv[1], "r" );
		if ( pFile == NULL )
		{
			printf( "\nCan not open file %s", argv[1] );
			return 0;
		}
	}
	else
	{
		printf( "\nUsage: test1 <filename>" );
		return 0;
	}
	fgets( buffer, MAX_STACK_SIZE, pFile );
	//printf( "%s", buffer );
	fclose( pFile );
	len = strlen( buffer );

	for( i = 0; i < len; i++ )
	{
		ch = buffer[i];
		if ( ch == open[0] || ch == open[1] || ch == open[2] )
		{
			stack[++stackPointer] = ch;
		}
		else if ( ch == close[0] || ch == close[1] || ch == close[2] )
		{
			res = 0;
			for( j =0; j < 3; j++ )
			{
				if( stack[stackPointer] == open[j] && ch == close[j] )
				{
					stackPointer--;
					res = 1;
				}
			}
			if ( res == 0 )
			{
				printf( "\nError in string %s in position %d", buffer, i + 1 );
					return 0;
			}

		}
	}

	if ( stackPointer == -1 )
	{
		printf( "\nString %s is correct", buffer );
	}
	else
	{
		printf( "\nString %s has error", buffer );
	}

}
