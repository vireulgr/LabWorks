#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef double (*FuncType)(double);

// ������ ��������������
double midRect( double beg, double end, FuncType f ) {
	double tmp = f( 0.5 * (end + beg) );
	return tmp * (end - beg);
}

double trapez( double beg, double end, FuncType f ) {
	double tmp = f( beg ) + f( end );
	return 0.5 * tmp * (end - beg);
}

double simpson( double beg, double end, FuncType f ) {
	double tmp = f( beg ) + 4.0 * f( (beg + end) * 0.5 ) + f( end );
	return tmp * (end - beg) / 6.0;
}

// �������
double constOne( double a ) {
	return 1;
}

double mysin( double a ) {
	return sin(a);
}

double myexp( double a ) {
	return exp(a);
}

double mygauss( double a ) {
	return exp( -(a*a) );
}

double myweird( double a ) {
	return cos( 4*log( 1.05 - sin( 0.25 * a ) ) );
}

#define BUFLEN 256

// �������� ������������
int promptForInt( char const * str, int const fallback ) {
	int userInput = 0;
	char buf[BUFLEN];
	memset( buf, 0, BUFLEN );
	puts( str );

	fgets( buf, BUFLEN, stdin );

	int scanRes = sscanf( buf, "%d", &userInput );
	if( scanRes == 0 || scanRes == EOF ) {
		printf( "�� ������� ���������� ����. ������� �������� �� ��������� (%d)\n", fallback );
		return fallback;
	}
	return userInput;
}

double promptForDouble( char const * str, double const fallback ) {
	double userInput = 0;
	char buf[BUFLEN];
	memset( buf, 0, BUFLEN );
	puts( str );

	fgets( buf, BUFLEN, stdin );

	int scanRes = sscanf( buf, "%lg", &userInput );
	if( scanRes == 0 || scanRes == EOF) {
		printf( "�� ������� ���������� ����. ������� �������� �� ��������� (%g)\n", fallback );
		return fallback;
	}
	return userInput;
}

// ����� �����
int main() {
	// ��� ������ ���������
	setlocale( LC_CTYPE, "Russian" );

	// ������������ �������� ���-�� ����� ��� ��������������
	int N = 11;
	N = promptForInt( "������� ���-�� ����� ��� �������������� (11)", 11 );
	if( N <= 1 ) {
		puts( "���-�� ����� ������ 2 - ���������� �������������. ���������� ���������" );
		getchar();
		return 0;
	}


	// ������������ �������� ������� ��� ��������������
	int userFunc = 0;
	FuncType f = NULL;

	char const text1[] =
		"�������� ��������������� �������:\n"
		"\t[1] - f(x) = sin(x)\n"
		"\t[2] - f(x) = exp(x)\n"
		"\t[3] - f(x) = 1\n"
		"\t[4] - f(x) = exp( -x^2 )\n"
		"\t[5] - f(x) = cos( 4*ln( 1.05 - sin( 0.25* x ) ) )";
	userFunc = promptForInt( text1, 3 );

	switch( userFunc ) {
	case 1: f = &mysin; break;
	case 2: f = &myexp; break;
	case 3: f = &constOne; break;
	case 4: f = &mygauss; break;
	case 5: f = &myweird; break;
	default:
		puts( "������� ����� �� ��������� ���������� ��������. ������� �������� �� ��������� (f(x) = 1)" );
		f = &constOne;
		break;
	}

	// ������������ �������� ������� ��������������
	double from = promptForDouble( "������� ������ ��������� ��������������:", 0.0 );
	double to = promptForDouble( "������� ����� ��������� ��������������:", 1.0 );

	// ������������ �������� ����� ��������������
	int userMethod = 0;
	char const text2[] =
		"�������� ����� ���������� �������������� :\n"
		"\t[1] - ����� ������� ���������������\n"
		"\t[2] - ����� ��������\n"
		"\t[3] - ����� ��������";
	userMethod = promptForInt( text2, 1 );
	if( userMethod < 1 && userMethod > 3 ) {
		puts( "������� ����� �� ��������� ���������� ��������. ������� �������� �� ��������� (����� ������� ���������������)" );
		userMethod = 1;
	}

	double integral = 0.0;

	// ��������������
	switch( userMethod ) {
	case 2: { // ����� ��������
		for( int i = 1; i < N-1; ++i ) {
			double x0 = (i-1) * (to - from) / (N-1) + from;
			double x1 = i * (to - from) / (N-1) + from;
			integral += trapez( x0, x1, f );
		}
		double x0 = (N-2) * (to - from) / (N-1) + from;
		double x1 = to;
		integral += trapez( x0, x1, f );
		break;
	}
	case 3: { // ����� ��������
		for( int i = 1; i < N-1; ++i ) {
			double x0 = (i-1) * (to - from) / (N-1) + from;
			double x1 = i * (to - from) / (N-1) + from;
			integral += simpson( x0, x1, f );
		}
		double x0 = (N-2) * (to - from) / (N-1) + from;
		double x1 = to;
		integral += simpson( x0, x1, f );
		break;
	}
	case 1:
	default: { // ����� ������� ���������������
		for( int i = 1; i < N-1; ++i ) {
			double x0 = (i-1) * (to - from) / (N-1) + from;
			double x1 = i * (to - from) / (N-1) + from;
			integral += midRect( x0, x1, f );
		}
		double x0 = (N-2) * (to - from) / (N-1) + from;
		double x1 = to;
		integral += midRect( x0, x1, f );
		break;
	}
	}

	// ����� ����������
	printf( "�������� ���������: %lg\n������� Enter ��� ����������", integral );

	getchar( );
	return 0;
}
