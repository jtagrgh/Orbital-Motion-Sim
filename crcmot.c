#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define G 6.67408E-11
#define Me 5.972E24
#define PIXEL_TO_M 1000

/* CODE STANDARDS */
/* Functions take math values, return game values */

char* ftos(double num);

double getPeriodRM(double radius,double centerBodyMass, int fps);
double getPeriodRV(double radius, double velocity, int fps);

double getVelocityTR(double period, double radius);
double getVelocityRM(double radius, double centerBodyMass);

double getRadiusTM(double period, double centerBodyMass);
double getRadiusTV(double period, double velocity);

int main()
{

	//Constant

	int fps = 60;
	double period = 9.95*fps;
	double radius = 100;
	double centerBodyMass = Me;
	double orbitalMass = 0;
	double velocity = 6.31e4;

	printf("%s\n\n", ftos(velocity));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Circular motion test");

	Vector2 orbitalPos = {};
	Vector2 centerBodyPos = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
	Color color = DARKBLUE;

	SetTargetFPS(fps);
	int i = 0;
	 
	while(!WindowShouldClose()) 
	{

		BeginDrawing();

		DrawCircleV(centerBodyPos, 50, MAGENTA);

		orbitalPos.x = 
			SCREEN_WIDTH/2 + radius*cos(i * 2*(M_PI/period)); 
		orbitalPos.y = 
			SCREEN_HEIGHT/2 + radius*sin(i * 2*(M_PI/period)); 

		ClearBackground(RAYWHITE);
		DrawCircleV(orbitalPos, 20, color);

		i++;

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

double getPeriodRM(double radius, double centerBodyMass, int fps)
{
	double x = 4 * M_PI*M_PI * pow(radius, 3);
	x /= (G * centerBodyMass);
	x = sqrt(x);
	x *= fps;

	return x;
}
double getPeriodRV(double radius, double velocity, int fps)
{
	double x = (2 * M_PI * radius / velocity);
	x *= 60;

	return x;
}
double getVelocityRM(double radius, double centerBodyMass)
{
	double x = G * centerBodyMass / radius;
	x = sqrt(x);

	return x;
}
double getRadiusTM(double period, double centerBodyMass)
{
	double x = G * centerBodyMass * period*period;
	x /= 4 * M_PI * M_PI;
	x = cbrt(x);
	x /= PIXEL_TO_M;

	return x;
}
double getRadiusTV(double period, double velocity)
{
	double x = velocity * period;
	x /= 2 * M_PI;
	x /= PIXEL_TO_M;

	return x;
}
double getVelocityTR(double period, double radius)
{
	double x = 2 * M_PI * radius / period;	

	return x;
}

char* ftos(double num)
{
	char* str;
	str = (char*)malloc(sizeof(char)*100);
	sprintf(str, "%.3f", num);

	return str;
}

