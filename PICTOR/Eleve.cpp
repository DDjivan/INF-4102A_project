/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */

#include <string>
#include "V2.h"
#include "Graphics.h"
#include "Event.h"
#include "Model.h"
#include "Button.h"
#include "Tool.h"

using namespace std;

// ESC : close window

///////////////////////////////////////////////////////////////////////////////
//
//		setup screen

int main(int argc, char* argv[])
{
	std::cout << "Press ESC to abort" << endl;
	Graphics::initMainWindow("Pictor", V2(1200, 800), V2(200, 200));
}

void bntToolSegmentClick(Model& Data)   { Data.currentTool = make_shared<ToolSegment>(); }
void bntToolRectangleClick(Model& Data) { Data.currentTool = make_shared<ToolRectangle>(); }
void bntToolCercleClick(Model& Data) { Data.currentTool = make_shared<ToolCercle>(); }



void bntToolRAZClick(Model& Data) {

	if (Data.ObjSelectionne == nullptr)
	{
		Data.LObjets = {};
	}
	for (int k = 0; k < Data.LObjets.size(); k++)
	{
		if (Data.LObjets[k] == Data.ObjSelectionne)
		{
			Data.LObjets.erase(Data.LObjets.begin() + k);
		}
	}
}





void bntToolSelectionClick(Model& Data){Data.currentTool = make_shared<ToolSelection>();}


void bntToolDevantClick(Model& Data)
{
	if (Data.ObjSelectionne == nullptr) return;


	for (int k = 0; k < Data.LObjets.size() - 1; k++)
	{
		if (Data.LObjets[k] == Data.ObjSelectionne)
		{
			auto x = Data.LObjets[k];
			Data.LObjets[k] = Data.LObjets[k + 1];
			Data.LObjets[k + 1] = x;
		}
	}
}


void bntToolDerriereClick(Model& Data)
{
	if (Data.ObjSelectionne == nullptr) return;


	for (int k = 1; k < Data.LObjets.size(); k++)
	{
		if (Data.LObjets[k] == Data.ObjSelectionne)
		{
			auto x = Data.LObjets[k];
			Data.LObjets[k] = Data.LObjets[k - 1];
			Data.LObjets[k - 1] = x;
		}
	}
}

void btnToolSwitchThickness(Model& Data)
{
    const int btn_index = 9;
    auto epaisseurButton = dynamic_cast<EpaisseurButton*>(
        Data.LButtons.at(btn_index).get()
    );

    if (epaisseurButton) {
        epaisseurButton->nextEpaisseur();
        Data.drawingOptions.thickness_ = epaisseurButton->getEpaisseur();

        std::cout << "Nouvelle épaisseur : ";
        std::cout << epaisseurButton->getEpaisseur() << "\n";
    }

    return;
}

void btnSwitchColorTrait(Model& Data)
{
    const int btn_index = 7;
    auto button = dynamic_cast<CouleurButton*>(
        Data.LButtons.at(btn_index).get()
    );

    if (button) {
        button->nextCouleur();
        Data.drawingOptions.borderColor_ = button->getCouleur();

        std::cout << "Nouvelle couleur de trait. \n";
    }

    return;
}

void btnSwitchColorFond(Model& Data)
{
    const int btn_index = 8;
    auto button = dynamic_cast<CouleurButton*>(
        Data.LButtons.at(btn_index).get()
    );

    if (button) {
        button->nextCouleur();
        Data.drawingOptions.interiorColor_ = button->getCouleur();

        std::cout << "Nouvelle couleur de fond. \n";
    }

    return;
}

void btnToggleFond(Model& Data)
{
    const int btn_index = 10;
    auto button = dynamic_cast<FondButton*>(
        Data.LButtons.at(btn_index).get()
    );

    if (button) {
        button->toggleFond();
        Data.drawingOptions.isFilled_ = button->getFondActivé();

        if (button->getFondActivé()) {
            std::cout << "Fond activé. \n ";
        } else {
            std::cout << "Fond désactivé. \n ";
        }
    }

    return;
}

void btnToolLignePolygonale(Model& Data)
{
    Data.currentTool = make_shared<ToolLignePolygonale>();
    return;
}



//----------------------------------------------------------------------------//

void initApp(Model& App)
{
	// choose default tool
	App.currentTool = make_shared<ToolSegment>();

	// create buttons
	int x = 0;
	int s = 80; // size

	// button Segment
	auto B1 = make_shared<Button>("Outil Segment", V2(x, 0), V2(s, s), "outil_segment.png", bntToolSegmentClick);
	App.LButtons.push_back(B1);
	x += s;

	// button Rectangle
	auto B2 = make_shared<Button>("Outil Rectangle",V2(x, 0), V2(s, s), "outil_rectangle.png", bntToolRectangleClick);
	App.LButtons.push_back(B2);
	x += s;


	// boutton cercle
	auto B3 = make_shared<Button>("Outil Cercle", V2(x, 0), V2(s, s), "outil_ellipse.png", bntToolCercleClick);
	App.LButtons.push_back(B3);
	x += s;

	// boutton suprimer
	auto B4 = make_shared<Button>("Outil RAZ", V2(x, 0), V2(s, s), "outil_delete.png", bntToolRAZClick);
	App.LButtons.push_back(B4);
	x += s;


	// boutton devant
	auto B5 = make_shared<Button>("Outil Selectionner", V2(x, 0), V2(s, s), "outil_move.png", bntToolSelectionClick);
	App.LButtons.push_back(B5);
	x += s;

	// boutton devant
	auto B6 = make_shared<Button>("Outil Selectionner", V2(x, 0), V2(s, s), "outil_up.png", bntToolDevantClick);
	App.LButtons.push_back(B6);
	x += s;

	auto B7 = make_shared<Button>("Outil Selectionner", V2(x, 0), V2(s, s), "outil_down.png", bntToolDerriereClick);
	App.LButtons.push_back(B7);
	x += s;

	// Étape 6
	auto B8 = make_shared<CouleurButton>("Choisir la couleur de trait suivante", V2(x, 0), V2(s, s), btnSwitchColorTrait, false);
	App.LButtons.push_back(B8);
	x += s;

    auto B9 = make_shared<CouleurButton>("Choisir la couleur de fond suivante", V2(x, 0), V2(s, s), btnSwitchColorFond, true);
	App.LButtons.push_back(B9);
	x += s;

    auto BA = make_shared<EpaisseurButton>("Choisir l'épaisseur suivante", V2(x, 0), V2(s, s), btnToolSwitchThickness);
	App.LButtons.push_back(BA);
	x += s;

    auto BB = make_shared<FondButton>("Basculer la présence du fond", V2(x, 0), V2(s, s), btnToggleFond);
	App.LButtons.push_back(BB);
	x += s;

    // Étape 7
    auto BC = make_shared<Button>("Outil Ligne Polygonale", V2(x, 0), V2(s, s), "outil_polygone.png", btnToolLignePolygonale);
	App.LButtons.push_back(BC);
	x += s;


	// put two objets in the scene

	ObjAttr DrawOpt1 = ObjAttr(Color::Cyan, true, Color::Green, 6);
	auto newObj1 = make_shared<ObjRectangle>(DrawOpt1, V2(100, 100), V2(300, 200));
	App.LObjets.push_back(newObj1);

	ObjAttr DrawOpt2 = ObjAttr(Color::Red, true, Color::Blue, 5);
	auto newObj2 = make_shared<ObjRectangle>(DrawOpt2, V2(500, 300), V2(600, 600));
	App.LObjets.push_back(newObj2);

	ObjAttr DrawOpt3 = ObjAttr(Color::Blue, true, Color::Red, 5);
	auto newObj3 = make_shared<ObjCercle>(DrawOpt3, V2(600, 700), V2(650, 700));
	App.LObjets.push_back(newObj3);
}

/////////////////////////////////////////////////////////////////////////
//
//		Event management


void processEvent(const Event& Ev, Model & Data)
{
	Ev.print(); // Debug

	// MouseMove event updates x,y coordinates
	if (Ev.Type == EventType::MouseMove)
	{
		Data.currentMousePos = V2(Ev.x, Ev.y);
	}


	// detect a mouse click on the tools icons

	V2 P = Data.currentMousePos;
	for (auto B : Data.LButtons)
	{
		if (Ev.Type == EventType::MouseDown && P.isInside(B->getPos(), B->getSize()))
		{
			B->manageEvent(Ev, Data);
			return;
		}
	}


	// send event to the activated tool
	Data.currentTool->processEvent(Ev,Data);


}



/////////////////////////////////////////////////////////////////////////
//
//     Drawing elements


void drawCursor(Graphics& G, const Model& D)
{


	V2 P = D.currentMousePos;
	int r = 7;

	Color c = Color::Black;
	G.drawLine(P + V2(r, 1), P + V2(-r, 1), c);
	G.drawLine(P + V2(r,-1), P + V2(-r,-1), c);
	G.drawLine(P + V2( 1,-r), P + V2( 1, r), c);
	G.drawLine(P + V2(-1,-r), P + V2(-1, r), c);

	Color cc = Color::White;
	G.drawLine(P - V2(r, 0), P + V2(r, 0), cc);
	G.drawLine(P - V2(0, r), P + V2(0, r), cc);

	G.drawStringFontMono(P + V2(20, 0), "Hello", 20, 1, Color::Yellow);
}


void drawApp(Graphics& G, const Model & D)
{
	// reset with a black background
	G.clearWindow(Color::Black);

	// draw all geometric objects
	for (auto& Obj : D.LObjets)
		Obj->draw(G);

	// draw the app menu
	for (auto& myButton : D.LButtons)
		myButton->draw(G);

	// draw current tool and interface (if active)
	D.currentTool->draw(G, D);

	// draw cursor
	drawCursor(G, D);
}






