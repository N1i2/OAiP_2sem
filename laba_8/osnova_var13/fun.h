#pragma once

struct element
{
	int numb{};
	element* next{};
};

int show(element*);

int dell(element**, int);

int clear(element**);

int minMax(element*);