#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#define BUFFER_SIZE 512
const char rotateChar( const char in, const int shift ) {
	if( !shift ) { return in; }
	char res = in;
	if( isupper( in ) ) {
		const char tmp2 = ((in - 'A') + shift) % 26;
		const char tmp3 = (tmp2 < 0)? tmp2 + 'Z' + 1 : tmp2 + 'A';
		res = tmp3;
	}
	if( islower( in ) ) {
		const char tmp2 = ((in - 'a')+ shift) % 26;
		const char tmp3 = (tmp2 < 0)? tmp2 + 'z' + 1 : tmp2 + 'a';
		res = tmp3;
	}
	
	return res;
}

void rotateStr( char dest[BUFFER_SIZE], const char src[BUFFER_SIZE], int fillSize, int shift ) {
	for( int i = 0; i < fillSize; ++i ) {
		if( isalpha( src[i] ) && shift ) {
			dest[i] = rotateChar( src[i], shift );
		}
		else {
			dest[i] = src[i];
		}
	}
}

void printUsage() {
	puts( 
		"	��������� �������/��������� ��������� ���� � ������� ����� ������.\n"
		"������� � �������� ����������:\n"
		"	1. ��� �����: ������ ���� text.txt\n"
		"	2. ����� ������: c - �����������, d - �����������\n"
		"	3. ����� ��� ���������: ����� �����"
	);
}

int main( int argc, char * argv[] ) {
	setlocale( LC_CTYPE, "Russian" );
	if( argc < 4 ) {
		printUsage();
		getchar();
		return 0;
	}

	const int shift = atoi( argv[3] );
	const char regime = tolower( argv[2][0] );

	printf( "%s %c %d\n", argv[1], regime, shift );

	int activeShift = (regime == 'c')? shift : ((regime == 'd')? -shift : 0); 

	if( regime != 'c' && regime != 'd' ) {
		puts( "����� ������ �� ����� �� 'c', �� 'd'" );
		return 0;
	}
	//if( activeShift == 0 ) {
	//	puts( "�������� ������ ��� ����� ����� 0, ������ �� ����� �������������" );
	//	return 0;
	//}

	FILE * pFile = fopen( argv[1], "r+" );
	if( pFile == NULL ) {
		perror( "������ �������� �����" );
		return 0;
	}

	char src[BUFFER_SIZE];
	char enc[BUFFER_SIZE];

	while( 1 ) {
		const long int startPos = ftell(pFile);

		char * fgetsRes = fgets( src, BUFFER_SIZE, pFile );

		if( ferror(pFile) ) break;

		const long int endPos = ftell(pFile) + 1;
		const long int fillSize = endPos - startPos;

		if( fillSize != 0 ) {
			memset( enc, 0, BUFFER_SIZE*sizeof(char) );
			//size_t len = strlen( src );
			//rotateStr( enc, src, len, activeShift );
			rotateStr( enc, src, fillSize, activeShift );
			
			fseek( pFile, startPos, SEEK_SET );
			fputs( enc, pFile );

			//const long int tmpPos = ftell(pFile);
			//fseek( pFile, tmpPos-1, SEEK_SET );

			fflush(pFile);
		}
		if( feof(pFile) ) break;
	}

	fclose(pFile);
	puts( "�������������� �����������. ������� Enter ��� ���������� ���������" );
	getchar();
	return 0;
}