/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */
#pragma once

#include <string>
#include "V2.h"
#include "Graphics.h"
#include "Event.h"
#include "Model.h"
#include <functional>

using namespace std;

// button component in the GUI


// class Button
// {
// 	string imageFile_;
// 	string myName_;
// 	V2 pos_;
// 	V2 size_;
// 	function<void(Model&)> storedFunction_; // when the button is clicked, call this function



// public:

// 	V2 getPos()  { return pos_;  }
// 	V2 getSize() { return size_; }

// 	Button(string myName, V2 pos, V2 size, string imageFile, function<void(Model&)> callBack) :
// 		myName_(myName), pos_(pos), size_(size), imageFile_(imageFile), storedFunction_(callBack) {  }

// 	void manageEvent(const Event& Ev, Model& Ap)
// 	{
// 		if (Ev.Type == EventType::MouseDown)
// 		{
// 			cout << ">> Clic sur le bouton " << myName_ << endl;
// 			storedFunction_(Ap);
// 		}
// 	}

// 	void draw(Graphics & G)
// 	{
// 		G.drawRectWithTexture(imageFile_, pos_, size_);
// 		G.drawRectangle(pos_, size_, Color::Gray, false,2);
// 		G.drawRectangle(pos_ + V2(2,2), size_-V2(4,4), Color::Black, false,2);
// 	}


// };


class AbstractButton
{
	string myName_;
	V2 pos_;
	V2 size_;
	function<void(Model&)> storedFunction_;

public:
    AbstractButton(string myName, V2 pos, V2 size, function<void(Model&)> callBack) :
        myName_(myName), pos_(pos), size_(size), storedFunction_(callBack) {
		return;
	}

	V2 getPos()  { return pos_;  }
	V2 getSize() { return size_; }
	string getName() { return myName_; }

	void manageEvent(const Event& Ev, Model& Ap)
	{
		if (Ev.Type == EventType::MouseDown)
		{
			cout << ">> Clic sur le bouton " << myName_ << endl;
			storedFunction_(Ap);
		}
		return;
	}

	virtual void draw(Graphics & G) = 0;
};



class Button : public AbstractButton
{
	string imageFile_;

public:

    Button(string myName, V2 pos, V2 size, string imageFile, function<void(Model&)> callBack) :
        AbstractButton(myName, pos, size, callBack), imageFile_(imageFile) {
		return;
	}

	void draw(Graphics & G) override
	{
		G.drawRectWithTexture(imageFile_, getPos(), getSize());

		G.drawRectangle(getPos(), getSize(), Color::Gray, false,2);
		G.drawRectangle(getPos() + V2(2,2), getSize()-V2(4,4), Color::Black, false,2);
		return;
	}
};

class EpaisseurButton : public AbstractButton
{
	int index = 1;
	const std::array<int, 4> epaisseurs = {1, 3, 5, 9};

	V2 start = V2(getPos().x			   +8, getPos().y + getSize().y/2);
	V2 end   = V2(getPos().x + getSize().x -8, getPos().y + getSize().y/2);

public:
	EpaisseurButton(string myName, V2 pos, V2 size, function<void(Model&)> callBack) :
		AbstractButton(myName, pos, size, callBack) {
		return;
	}

	const int getEpaisseur() {
		return epaisseurs.at(index);
	}

	void nextEpaisseur()
	{
		index = (index+1) % epaisseurs.size();
		return;
	}

	void draw(Graphics & G) override
	{
		G.drawRectangle(getPos(), getSize(), Color::White, true,2);

		G.drawRectangle(getPos(), getSize(), Color::Gray, false,2);
		G.drawRectangle(getPos() + V2(2,2), getSize()-V2(4,4), Color::Black, false,2);

		G.drawLine(start, end, Color::Gray, getEpaisseur());
		return;
	}
};

class TemplateButton : public AbstractButton
{
public:
	TemplateButton(string myName, V2 pos, V2 size, function<void(Model&)> callBack) :
		AbstractButton(myName, pos, size, callBack) {
		return;
	}

	void draw(Graphics & G) override
	{
		G.drawRectangle(getPos(), getSize(), Color::Green, true,2);

		G.drawRectangle(getPos(), getSize(), Color::Gray, false,2);
		G.drawRectangle(getPos() + V2(2,2), getSize()-V2(4,4), Color::Black, false,2);

		return;
	}
};
