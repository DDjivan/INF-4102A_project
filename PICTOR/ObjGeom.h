/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */
#pragma once

#include "Color.h"
#include "V2.h"
#include "ObjAttr.h"
#include "Graphics.h"

class ObjGeom
{
public :
	ObjAttr drawInfo_;

	ObjGeom() {}
	ObjGeom(ObjAttr  drawInfo) : drawInfo_(drawInfo)   {  }

	virtual void draw(Graphics & G) {}

	virtual void getHitbox(V2& P, V2& size){}
};


class ObjRectangle : public ObjGeom
{
public :
	V2 P1_;
	V2 P2_;

	ObjRectangle(ObjAttr  drawInfo, V2 P1, V2 P2) : ObjGeom(drawInfo)
	{
		P1_ = P1;
		P2_ = P2;
	}

	void draw(Graphics& G) override
	{
		V2 P, size;
		getPLH(P1_, P2_, P, size);

		if ( drawInfo_.isFilled_ )
  		   G.drawRectangle(P,size, drawInfo_.interiorColor_, true);

		G.drawRectangle(P, size, drawInfo_.borderColor_, false, drawInfo_.thickness_);
	}

	void getHitbox(V2& P, V2& size) override 
	{
		getPLH(P1_, P2_, P, size);
	}
};


class ObjSegment : public ObjGeom
{
public:
	V2 P1_;
	V2 P2_;

	ObjSegment(ObjAttr  drawInfo, V2 P1, V2 P2) : ObjGeom(drawInfo)
	{
		P1_ = P1;
		P2_ = P2;
	}

	void draw(Graphics& G) override
	{
		V2 P, size;
	 
		G.drawLine(P1_, P2_, drawInfo_.borderColor_, drawInfo_.thickness_);
	}

	void getHitbox(V2& P, V2& size) override 
	{
		getPLH(P1_, P2_, P, size);
	}
};




class ObjCercle : public ObjGeom
{
public:
	V2 P1_;
	V2 P2_;

	ObjCercle(ObjAttr  drawInfo, V2 P1, V2 P2) : ObjGeom(drawInfo)
	{
		P1_ = P1;
		P2_ = P2;
	}

	void draw(Graphics& G) override
	{
		const float r = (P1_ - P2_).norm();
		G.drawCircle(P1_, r, drawInfo_.borderColor_, drawInfo_.thickness_);
	}


	void getHitbox(V2& P, V2& size) override {
		float r = (P1_ - P2_).norm();
		size = V2(2 * r, 2 * r);
		P = P1_ - V2(r, r);
	}
};