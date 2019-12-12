#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef double (*FuncType)(double);
typedef double (*MethodType)(double, double, FuncType);
typedef double (*CompositeMethodType)(const double, const double, const int, FuncType);

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

double trapezComposite( const double from, const double to, const int points, FuncType func ) {
	double integral = 0.0;
	double h = (to - from) / (points-1);
	printf( "h %g\n", h );
	for( int i = 1; i < points-1; ++i ) {
		//double x0 = (i-1) * (to - from) / (points-1) + from;
		double x1 = i * (to - from) / (points-1) + from;
		printf( "x1 %g\n", x1 );

		integral += func(x1);
	}
	double x0 = from;
	double xn = to;
	printf( "x0 %g\t\txn %g\n", x0, xn );
	integral += 0.5 * (func(x0) + func(xn));
	return integral * h;
}

double midRectCompositeNMinus( const double from, const double to, const int points, FuncType func ) {
	double integral = 0.0;
	for( int i = 1; i < points-1; ++i ) {
		double x0 = (i-1) * (to - from) / (points-1) + from;
		double x1 = i * (to - from) / (points-1) + from;
		//printf( "x0 %g\t\tx1 %g\n", x0, x1 );

		integral += func( 0.5 * (x0 + x1) ) * (x1-x0);
	}
	double x0 = (points-2) * (to - from) / (points-1) + from;
	double x1 = to;
	//printf( "x0 %g\t\tx1 %g\n", x0, x1 );
	integral += func( 0.5 * (x0 + x1) )*(x1-x0);
	return integral;
}

//from -50		to 3
//h: 6.625			n: 4			N: 8
//x0 -43.375		x1 -36.75
//x0 -30.125		x1 -23.5
//x0 -16.875		x1 -10.25
//xn -3.625
//int: 44.5911
double simpsonCompositeN( const double from, const double to, const int points, FuncType func ) {
	double tmp = func(from) + func(to);
	//printf( "from %g\t\tto %g\n", from, to );

	int N = (points % 2 == 0)? points : points+1; // должно быть чётное кол-во отрезков

	double h = (to - from) / N;
	int n = N / 2;
	//printf( "h: %g\t\t\tn: %d\t\t\tN: %d\n", h, n, N );
	for( int i = 1; i < n; ++i ) {
		double x0 = (2 * i - 1) * h + from;
		double x1 = 2 * i * h + from;
		//printf( "x0 %g\t\tx1 %g\n", x0, x1 );
		tmp += 4 * func(x0) + 2 * func(x1);
	}
	double xn = (2 * n - 1) * h + from;
	//printf( "xn %g\n", xn);
	tmp += 4 * func(xn);

	return tmp * h / 3;
}

//from -50		to 3
//h: 6.625			n: 4			N: 9
//x0 -43.375		x1 -36.75
//x0 -30.125		x1 -23.5
//x0 -16.875		x1 -10.25
//xn -3.625
//int: 44.5911
double simpsonCompositeNMinus( const double from, const double to, const int points, FuncType f ) {
	double tmp = f(from) + f(to);
	//printf( "from %g\t\tto %g\n", from, to );

	int N = (points % 2 == 0)? points + 1 : points; // должно быть чётное кол-во отрезков

	double h = (to - from) / (N-1);
	int n = N / 2;
	//printf( "h: %g\t\t\tn: %d\t\t\tN: %d\n", h, n, N );
	for( int i = 1; i < n; ++i ) {
		double x0 = (2 * i - 1) * h + from;
		double x1 = 2 * i * h + from;
		//printf( "x0 %g\t\tx1 %g\n", x0, x1 );
		tmp += 4 * f(x0) + 2 * f(x1);
	}
	double xn = (2 * n - 1) * h + from;
	//printf( "xn %g\n", xn);
	tmp += 4 * f(xn);

	return tmp * h / 3;
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

// Общая функция для численного интегрирования
double numericIntegration( const double from, const double to, const int N, MethodType method, FuncType func ) {
	double integral = 0.0;
	for( int i = 1; i < N-1; ++i ) {
		double x0 = (i-1) * (to - from) / (N-1) + from;
		double x1 = i * (to - from) / (N-1) + from;
		integral += method( x0, x1, func );
	}
	double x0 = (N-2) * (to - from) / (N-1) + from;
	double x1 = to;
	integral += method( x0, x1, func );
	return integral;
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
	//MethodType method = NULL;
	CompositeMethodType method = NULL;
	char const text2[] =
		"Выберите метод численного интегрирования :\n"
		"\t[1] - метод средних прямоугольников\n"
		"\t[2] - метод трапеций\n"
		"\t[3] - метод Симпсона";
	userMethod = promptForInt( text2, 1 );

	switch( userMethod ) {
	//case 1: method = &midRect; break;
	//case 2: method = &trapez; break;
	//case 3: method = &simpson; break;
	case 1: method = midRectCompositeNMinus; break;
	case 2: method = trapezComposite; break;
	case 3: method = simpsonCompositeNMinus; break;
	default:
		puts( "Введено число за границами допустимых значений. Выбрано значение по умолчанию (метод средних прямоугольников)" );
		method = &midRect;
		break;
	}


	// Интегрирование
	double integral = 0.0;
	integral = method( from ,to, N, f );
	//integral = numericIntegration( from, to, N, method, f );


	// Вывод результата
	printf( "Знечение интеграла: %lg\nНажмите Enter для завершения", integral );

	getchar();
	return 0;
}
