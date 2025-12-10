/* Copyright (c) 2024 Lilian Buzer - All rights reserved - */
#pragma once

#include "Color.h"
#include "V2.h"
#include "ObjAttr.h"
#include "Graphics.h"
#include <sstream>

class ObjGeom
{
public :
	V2 P1_;
	V2 P2_;
	
	ObjAttr drawInfo_;

	ObjGeom() {}
	ObjGeom(ObjAttr  drawInfo) : drawInfo_(drawInfo)   {  }

	virtual void draw(Graphics & G) {}

	virtual void getHitbox(V2& P, V2& size){}

	virtual std::string Serialize() const = 0;

	std::string drawInfoSerialize() const
	{
		float R, G, B, A;

		std::stringstream ss;

		ss << "\"drawInfo_\":{";

		R = drawInfo_.borderColor_.R;
		G = drawInfo_.borderColor_.G;
		B = drawInfo_.borderColor_.B;
		A = drawInfo_.borderColor_.A;
		ss << "\"borderColor_\":\"(" << R << "," << G << "," << B << "," << A << ")\",";

		R = drawInfo_.interiorColor_.R;
		G = drawInfo_.interiorColor_.G;
		B = drawInfo_.interiorColor_.B;
		A = drawInfo_.interiorColor_.A;
		ss << "\"interiorColor_\":\"(" << R << "," << G << "," << B << "," << A << ")\",";

		ss << "\"thickness_\":\"" << drawInfo_.thickness_ << "\",";

		ss << "\"isFilled_\":\"" << drawInfo_.isFilled_ << "\"";

		ss << "}";

		return ss.str();
	}
};


class ObjRectangle : public ObjGeom
{
public :
	//V2 P1_;
	//V2 P2_;

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

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "\"ObjRectangle\":{";

		ss << drawInfoSerialize() << ",";

		ss << "\"P1_\":\"" << P1_ << "\",";
		ss << "\"P2_\":\"" << P2_ << "\"";
		ss << "}";

        return ss.str();
    }
};


class ObjSegment : public ObjGeom
{
public:
	//V2 P1_;
	//V2 P2_;

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

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "\"ObjSegment\":{";

		ss << drawInfoSerialize() << ",";

		ss << "\"P1_\":\"" << P1_ << "\",";
		ss << "\"P2_\":\"" << P2_ << "\"";
		ss << "}";

        return ss.str();
    }
};




class ObjCercle : public ObjGeom
{
public:
	//V2 P1_;
	//V2 P2_;

	ObjCercle(ObjAttr  drawInfo, V2 P1, V2 P2) : ObjGeom(drawInfo)
	{
		P1_ = P1;
		P2_ = P2;
	}

	void draw(Graphics& G) override
	{
		const float r = (P1_ - P2_).norm();
		
		if (drawInfo_.isFilled_)
		{
			G.drawCircle(P1_, r, drawInfo_.interiorColor_, true);
		}
		G.drawCircle(P1_, r, drawInfo_.borderColor_, false, drawInfo_.thickness_); //L'epaisseur marche mal
	}


	void getHitbox(V2& P, V2& size) override
	{
		float r = (P1_ - P2_).norm();
		size = V2(2 * r, 2 * r);
		P = P1_ - V2(r, r);
	}

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "\"ObjCercle\":{";

		ss << drawInfoSerialize() << ",";

		ss << "\"P1_\":\"" << P1_ << "\",";
		ss << "\"P2_\":\"" << P2_ << "\"";
		ss << "}";

        return ss.str();
    }
};
