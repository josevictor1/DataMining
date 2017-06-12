#pragma once

enum Operator {EQUAL, DIFFERENT, LESS, GREATEREQUAL, N_OPERATORS};

struct Gene {
	float weight;
	Operator op;
	int value;
};
