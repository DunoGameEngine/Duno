#pragma once
#include "DunoGUIElement.h"
#include <iostream>
using namespace std;

struct Updater
{
	Updater(float constent, float& value, float* scaler) : 
		constent(constent), 
		value(value), 
		scaler(scaler) {}
	void update() { cout << *scaler << endl; }
	float constent;
	float& value;
	float *scaler;
};
class DunoGUIPannel : public DunoGUIElement
{
public:
	DunoGUIPannel(PlainModel* model, GLMateral* mat) : DunoGUIElement(model, mat, glm::vec2(), glm::vec2()) {}
	virtual void load(XML::Tag tag);
	virtual void update();
private:
	void setPhysical(string constent, float& value, float* scaler);

	float* width;
	float* height;
	glm::vec2 pos, size;
	vector<Updater*> toUpdate;
};