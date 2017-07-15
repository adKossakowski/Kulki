#pragma once
#ifndef Ball_hpp
#define Ball_hpp

#include "FlashCard.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<string.h>

using namespace std;

class DefaultBall {

protected:

	static const char defaultBallPattern = ' ';

};

class Ball: public DefaultBall {

private:

	char ballPattern;
	int vertical;
	int horizontal;

	//void meet(const int t_hor, const int t_ver, FlashCard &fc, Ball &bl);

	static void defaultInsert(Ball &b) {
		b.ballPattern = DefaultBall::defaultBallPattern;
	}

	void defaultBall(Ball &b, int i, int j) {
		b.ballPattern = DefaultBall::defaultBallPattern;
		horizontal = i;
		vertical = j;
	}

	void newBall(char c, int i, int j) {
		this->ballPattern = c;
		this->horizontal = i;
		this->vertical = j;
	}

protected:

public:

	friend class FlashCard;

	Ball() :ballPattern(DefaultBall::defaultBallPattern),horizontal(0),vertical(0) {};

	Ball(char t_ballPattern) :ballPattern(t_ballPattern), horizontal(0), vertical(0) {};

	Ball(char t_ballPattern, int t_vertical, int t_horizontal) :ballPattern(t_ballPattern), vertical(t_vertical), horizontal(t_horizontal) {};

	Ball &operator=(const Ball* v) {
		this->ballPattern = v->ballPattern;
		return *this;
	}

	Ball &operator=(const Ball& v) {
		this->ballPattern = v.ballPattern;
		return *this;
	}

	bool operator!=(const Ball& v) {
		if ((this->ballPattern != v.ballPattern))
			return true;
		else return false;
	}

	bool operator==(const Ball& v) {
		if ((this->ballPattern == v.ballPattern))
			return true;
		else return false;
	}

	/*bool negativeValue(const int t_val) {
		if (t_val != 0 && t_val != 9) return true;
		else return false;
	}*/

};

#endif