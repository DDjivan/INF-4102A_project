/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */
#pragma once

#include "Color.h"
#include "ObjGeom.h"
#include "V2.h"
#include "ObjAttr.h"
#include <vector>
#include <memory>
using namespace std;

// declaration used to avoid cyclic dependency
class Tool;
// class Button;
class AbstractButton;
class Model;
void initApp(Model& Data);


class Model
{
  public :

	shared_ptr<Tool> currentTool;

	V2 currentMousePos;

	ObjAttr drawingOptions;

	vector< shared_ptr<ObjGeom> > LObjets;

	// vector< shared_ptr<Button> > LButtons;
	vector< shared_ptr<AbstractButton> > LButtons;

	shared_ptr<ObjGeom> ObjSelectionne = nullptr;

	Model()
	{
		initApp(*this);
	}
};
