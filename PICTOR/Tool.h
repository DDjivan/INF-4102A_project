/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */
#pragma once

#include <string>
#include "Event.h"
#include "Model.h"
#include "ObjGeom.h"

using namespace std;

enum State { WAIT, INTERACT  };

////////////////////////////////////////////////////////////////////

class Tool
{
protected :
	int currentState;

public:
	Tool() {   currentState = State::WAIT; }
	virtual void processEvent(const Event& E, Model & Data) {}

	virtual void draw(Graphics& G,const  Model& Data) {}
};

////////////////////////////////////////////////////////////////////


class ToolSegment : public Tool
{
	V2 Pstart;
public :

	ToolSegment() : Tool() {}
	void processEvent(const Event& E, Model& Data) override
	{
		if (E.Type == EventType::MouseDown && E.info == "0") // left mouse button pressed
		{
			if (currentState == State::WAIT)
			{
				// interactive drawing
				Pstart = Data.currentMousePos;
				currentState = State::INTERACT;
				return;
			}
		}

		if (E.Type == EventType::MouseUp && E.info == "0") // left mouse button released
		{
			if (currentState == State::INTERACT)
			{
				// add object in the scene
				V2 P2 = Data.currentMousePos;
				auto newObj = make_shared<ObjSegment>(Data.drawingOptions, Pstart, P2);
				Data.LObjets.push_back(newObj);
				currentState = State::WAIT;
				return;
			}
		}
	}


	void draw(Graphics& G, const Model& Data) override
	{
		if (currentState == State::INTERACT)
  		  G.drawLine(Pstart, Data.currentMousePos, Data.drawingOptions.borderColor_, Data.drawingOptions.thickness_);
	}

};



////////////////////////////////////////////////////////////////////


class ToolRectangle : public Tool
{
	V2 Pstart;

public:

	ToolRectangle() : Tool() {}


	void processEvent(const Event& E, Model& Data) override
	{
		if (E.Type == EventType::MouseDown && E.info == "0") // left mouse button pressed
		{
			if (currentState == State::WAIT)
			{
				// interactive drawing
				Pstart = Data.currentMousePos;
				currentState = State::INTERACT;
				return;
			}
		}

		if (E.Type == EventType::MouseUp && E.info == "0") // left mouse button released
		{
			if (currentState == State::INTERACT)
			{
				// add object in the scene
				V2 P2 = Data.currentMousePos;
				auto newObj = make_shared<ObjRectangle>(Data.drawingOptions, Pstart, P2);
				Data.LObjets.push_back(newObj);
				currentState = State::WAIT;
				return;
			}
		}
	}

	void draw(Graphics& G, const Model& Data) override
	{
		V2 P;
		V2 size;
			if (currentState == State::INTERACT)
				getPLH(Pstart, Data.currentMousePos,P,size );// Convertie les point diagonneaux en taille et point de depart du rectangle (utulisation prof ObjGeom.h l36)
				
			
			if (Data.drawingOptions.isFilled_)
			{
				G.drawRectangle(P, size, Data.drawingOptions.interiorColor_, true);
			}

			G.drawRectangle(P, size, Data.drawingOptions.borderColor_, false, Data.drawingOptions.thickness_);
			//G.drawRectangle(P, size, Data.drawingOptions.interiorColor_, Data.drawingOptions.thickness_);
	}
};







////////////////////////////////////////////////////////////////////




class ToolCercle : public Tool
{
	V2 Pstart;
public:

	ToolCercle() : Tool() {}
	void processEvent(const Event& E, Model& Data) override
	{
		if (E.Type == EventType::MouseDown && E.info == "0") // left mouse button pressed
		{
			if (currentState == State::WAIT)
			{
				// interactive drawing
				Pstart = Data.currentMousePos;
				currentState = State::INTERACT;
				return;
			}
		}

		if (E.Type == EventType::MouseUp && E.info == "0") // left mouse button released
		{
			if (currentState == State::INTERACT)
			{
				// add object in the scene
				V2 P2 = Data.currentMousePos;
				auto newObj = make_shared<ObjCercle>(Data.drawingOptions, Pstart, P2);
				Data.LObjets.push_back(newObj);
				currentState = State::WAIT;
				return;
			}
		}
	}


	void draw(Graphics& G, const Model& Data) override
	{
		if (currentState == State::INTERACT)
		{
			float r = (Pstart - Data.currentMousePos).norm();
			if (Data.drawingOptions.isFilled_)
			{
				G.drawCircle(Pstart, r, Data.drawingOptions.interiorColor_, true);
			}

			G.drawCircle(Pstart, r, Data.drawingOptions.borderColor_, false, Data.drawingOptions.thickness_);// L'epaisseur marche mal
			
		}
	}

};



class ToolSelection : public Tool
{
public:

	ToolSelection() : Tool() {}

	void processEvent(const Event& E, Model& Data) override
	{
		if (E.Type == EventType::MouseDown && E.info == "0")
		{
			Data.ObjSelectionne = nullptr;

			for (auto& obj : Data.LObjets)
			{
				V2 P, size;
				obj->getHitbox(P, size);

				if (Data.currentMousePos.isInside(P, size))
				{
					Data.ObjSelectionne = obj;
				}
			}
		}
	}

	void draw(Graphics& G, const Model& Data) override
	{
		// Affichage visuel de la s�lection
		if (Data.ObjSelectionne != nullptr)
		{
			V2 P, size;
			Data.ObjSelectionne->getHitbox(P, size);
			G.drawRectangle(P, size, Color::Magenta, false, 10);
		}
	}
};



class ToolLignePolygonale : public Tool
{
	std::vector<V2> points;

public:
	ToolLignePolygonale() : Tool()
	{
		return;
	}

	void processEvent(const Event& E, Model& Data) override
    {
		// commencer
        if (E.Type == EventType::MouseDown && E.info == "0")  // LMB appuyé
        {
            points.push_back(Data.currentMousePos);
			currentState = State::INTERACT;
        }

		// finaliser
        if (
			// (E.Type == EventType::KeyDown && E.info == "\n")  // Enter appuyé
			// (ne fonctionne pas, donc j'ai choisi une flèche directionnelle) ↓
			(E.Type == EventType::KeyDown && E.info == "RIGHT")  // Right appuyé
			|| (E.Type == EventType::MouseDown && E.info == "2")  // RMB appuyé
		)
        {
            if (points.size() >= 2)  // au moins deux points sont nécessaires
            {
                for (int i = 0; i < points.size() - 1; i++)
                {
                    auto newSegment = make_shared<ObjSegment>(Data.drawingOptions, points.at(i), points.at(i+1));
                    Data.LObjets.push_back(newSegment);
                }
            }
			points.clear();
			currentState = State::WAIT;
        }

		// annuler
        if (E.Type == EventType::MouseDown && E.info == "1")  // MMB appuyé
        {
            points.clear();
            // drawingStarted = false;
            currentState = State::WAIT;
        }

		return;
    }

    void draw(Graphics& G, const Model& Data) override
    {
        if (currentState == State::INTERACT) {
            for (int i = 0; i < points.size() - 1; i++)
            {
                G.drawLine(points.at(i), points.at(i+1), Data.drawingOptions.borderColor_, Data.drawingOptions.thickness_);
            }
            G.drawLine(points.back(), Data.currentMousePos, Data.drawingOptions.borderColor_, Data.drawingOptions.thickness_);
        }
		return;
    }
};
