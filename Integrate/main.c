#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef double (*FuncType)(const double);
typedef double (*CompositeMethodType)(const double, const double, const int, FuncType);

// ������ ��������������
double trapezComposite( const double from, const double to, const int points, FuncType func ) {
	double integral = 0.0;
	double h = (to - from) / (points-1);
	for( int i = 1; i < points-1; ++i ) {
		double x1 = i * (to - from) / (points-1) + from;

		integral += func(x1);
	}
	double x0 = from;
	double xn = to;
	integral += 0.5 * (func(x0) + func(xn));
	return integral * h;
}

double midRectComposite( const double from, const double to, const int points, FuncType func ) {
	double integral = 0.0;
	for( int i = 1; i < points-1; ++i ) {
		double x0 = (i-1) * (to - from) / (points-1) + from;
		double x1 = i * (to - from) / (points-1) + from;

		integral += func( 0.5 * (x0 + x1) ) * (x1-x0);
	}
	double x0 = (points-2) * (to - from) / (points-1) + from;
	double x1 = to;
	integral += func( 0.5 * (x0 + x1) )*(x1-x0);
	return integral;
}

double simpsonComposite( const double from, const double to, const int points, FuncType f ) {
	double tmp = f(from) + f(to);

	int N = (points % 2 == 0)? points + 1 : points; // ������ ���� ������ ���-�� ��������

	double h = (to - from) / (N-1);
	int n = N / 2;
	for( int i = 1; i < n; ++i ) {
		double x0 = (2 * i - 1) * h + from;
		double x1 = 2 * i * h + from;
		tmp += 4 * f(x0) + 2 * f(x1);
	}
	double xn = (2 * n - 1) * h + from;
	tmp += 4 * f(xn);

	return tmp * h / 3;
}

// �������
double constOne( const double a ) {
	return 1;
}

double mysin( const double a ) {
	return sin(a);
}

double myexp( const double a ) {
	return exp(a);
}

double mygauss( const double a ) {
	return exp( -(a*a) );
}

double myweird( const double a ) {
	return cos( 4*log( 1.05 - sin( 0.25 * a ) ) );
}

#define BUFLEN 256

// �������� ������������
int promptForInt( const char * str, const int fallback ) {
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

double promptForDouble( const char * str, const double fallback ) {
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
	CompositeMethodType method = NULL;
	char const text2[] =
		"�������� ����� ���������� �������������� :\n"
		"\t[1] - ����� ������� ���������������\n"
		"\t[2] - ����� ��������\n"
		"\t[3] - ����� ��������";
	userMethod = promptForInt( text2, 1 );

	switch( userMethod ) {
	case 1: method = midRectComposite; break;
	case 2: method = trapezComposite; break;
	case 3: method = simpsonComposite; break;
	default:
		puts( "������� ����� �� ��������� ���������� ��������. ������� �������� �� ��������� (����� ������� ���������������)" );
		method = &midRectComposite;
		break;
	}


	// ��������������
	double integral = 0.0;
	integral = method( from ,to, N, f );


	// ����� ����������
	printf( "�������� ���������: %lg\n������� Enter ��� ����������", integral );

	getchar();
	return 0;
}
