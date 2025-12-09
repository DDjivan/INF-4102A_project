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

		ss << "";

		R = drawInfo_.borderColor_.R;
		G = drawInfo_.borderColor_.G;
		B = drawInfo_.borderColor_.B;
		A = drawInfo_.borderColor_.A;
		ss << "(" << R << "," << G << "," << B << "," << A << ");";

		R = drawInfo_.interiorColor_.R;
		G = drawInfo_.interiorColor_.G;
		B = drawInfo_.interiorColor_.B;
		A = drawInfo_.interiorColor_.A;
		ss << "(" << R << "," << G << "," << B << "," << A << ");";

		ss << "" << drawInfo_.thickness_ << ";";

		ss << "" << drawInfo_.isFilled_ << ";";

		ss << "";

		return ss.str();
	}



	template <typename T>
	T stringToValue(const std::string& input, const int index)
	{
		size_t posA, distB;

		posA = 0;
		distB = input.substr(posA, std::string::npos).find_first_of(';') +1;

		for (int i = 0; i < index; i++)
		{
			posA += distB;
			distB = input.substr(posA, std::string::npos).find_first_of(';') +1;
		}

		std::string value = input.substr(posA, distB-1);
		// std::cout << "index = " <<  index << ", value = " << value << "\n";

		// throw std::invalid_argument("DEBUG ! \n");



		// if constexpr (std::is_same<T, std::string>::value) {
		// 	return value;
		// }
		if constexpr (std::is_same<T, int>::value) {
			return std::stoi(value);
		}
		// if (std::is_same<T, float>::value) {
		// 	return std::stof(value);
		// }
		if constexpr (std::is_same<T, bool>::value) {
			return (value == "1");
		}
		if constexpr (std::is_same<T, Color>::value) {
			float R, G, B, A;
			// sscanf prend un const char* pour le 1er arg
    		sscanf(value.c_str(), "(%f,%f,%f,%f)", &R, &G, &B, &A);
			return Color(R, G, B, A);
		}
		if constexpr (std::is_same<T, V2>::value) {
			int x, y;
    		sscanf(value.c_str(), "(%d,%d)", &x, &y);
			return V2(x, y);
		}

		throw std::invalid_argument("Type non pris en charge ! \n");
	}

	ObjAttr extractDrawInfo(const std::string& input)
	{
		ObjAttr drawInfo;

		drawInfo.borderColor_ = stringToValue<Color>(input, 1);
		drawInfo.interiorColor_ = stringToValue<Color>(input, 2);
		drawInfo.thickness_ = stringToValue<int>(input, 3);
		drawInfo.isFilled_ = stringToValue<bool>(input, 4);

		return drawInfo;
	}

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

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "ObjRectangle;";

		ss << drawInfoSerialize() << "";

		ss << "" << P1_ << ";";
		ss << "" << P2_ << ";";
		ss << "";

        return ss.str();
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

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "ObjSegment;";

		ss << drawInfoSerialize() << "";

		ss << "" << P1_ << ";";
		ss << "" << P2_ << ";";
		ss << "";

        return ss.str();
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


	void getHitbox(V2& P, V2& size) override
	{
		float r = (P1_ - P2_).norm();
		size = V2(2 * r, 2 * r);
		P = P1_ - V2(r, r);
	}

	std::string Serialize() const override
    {
        std::stringstream ss;

        ss << "ObjCercle;";

		ss << drawInfoSerialize() << "";

		ss << "" << P1_ << ";";
		ss << "" << P2_ << ";";
		ss << "";

        return ss.str();
    }
};
