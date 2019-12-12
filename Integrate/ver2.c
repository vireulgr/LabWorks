#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef double (*FuncType)(double);

// Методы интегрирования
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

// Функции
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

// Спросить пользователя
int promptForInt( char const * str, int const fallback ) {
	int userInput = 0;
	char buf[BUFLEN];
	memset( buf, 0, BUFLEN );
	puts( str );

	fgets( buf, BUFLEN, stdin );

	int scanRes = sscanf( buf, "%d", &userInput );
	if( scanRes == 0 || scanRes == EOF ) {
		printf( "Не удалось распознать ввод. Выбрано значение по умолчанию (%d)\n", fallback );
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
		printf( "Не удалось распознать ввод. Выбрано значение по умолчанию (%g)\n", fallback );
		return fallback;
	}
	return userInput;
}

// Точка входа
int main() {
	// для вывода кириллицы
	setlocale( LC_CTYPE, "Russian" );

	// Пользователь выбирает кол-во точек для интегрирования
	int N = 11;
	N = promptForInt( "Введите кол-во точек для интегрирования (11)", 11 );
	if( N <= 1 ) {
		puts( "Кол-во точек меньше 2 - невозможно интегрировать. Завершение программы" );
		getchar();
		return 0;
	}


	// Пользователь выбирает функцию для интегрирования
	int userFunc = 0;
	FuncType f = NULL;

	char const text1[] =
		"Выберите подынтегральную функцию:\n"
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
		puts( "Введено число за границами допустимых значений. Выбрано значение по умолчанию (f(x) = 1)" );
		f = &constOne;
		break;
	}

	// Пользователь выбирает пределы интегрирования
	double from = promptForDouble( "Введите начало интервала интегрирования:", 0.0 );
	double to = promptForDouble( "Введите конец интервала интегрирования:", 1.0 );

	// Пользователь выбирает метод интегрирования
	int userMethod = 0;
	char const text2[] =
		"Выберите метод численного интегрирования :\n"
		"\t[1] - метод средних прямоугольников\n"
		"\t[2] - метод трапеций\n"
		"\t[3] - метод Симпсона";
	userMethod = promptForInt( text2, 1 );
	if( userMethod < 1 && userMethod > 3 ) {
		puts( "Введено число за границами допустимых значений. Выбрано значение по умолчанию (метод средних прямоугольников)" );
		userMethod = 1;
	}

	double integral = 0.0;

	// Интегрирование
	switch( userMethod ) {
	case 2: { // Метод трапеций
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
	case 3: { // Метод Симпсона
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
	default: { // Метод средних прямоугоьлников
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

	// Вывод результата
	printf( "Знечение интеграла: %lg\nНажмите Enter для завершения", integral );

	getchar( );
	return 0;
}
