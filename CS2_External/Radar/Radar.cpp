#include "Radar.h"

Vec2 RevolveCoordinatesSystem(float RevolveAngle, Vec2 OriginPos, Vec2 DestPos)
{
	Vec2 ResultPos;
	if (RevolveAngle == 0)
		return DestPos;
	ResultPos.x = OriginPos.x + (DestPos.x - OriginPos.x) * cos(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * sin(RevolveAngle * M_PI / 180);
	ResultPos.y = OriginPos.y - (DestPos.x - OriginPos.x) * sin(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * cos(RevolveAngle * M_PI / 180);
	return ResultPos;
}


void Base_Radar::SetRange(const float& Range)
{
	this->RenderRange = Range;
}

void Base_Radar::SetCrossColor(const ImColor& Color)
{
	this->CrossColor = Color;
}

void Base_Radar::SetPos(const Vec2& Pos)
{
	this->Pos = Pos;
}

void Base_Radar::SetSize(const float& Size)
{
	this->Width = Size;
}

float Base_Radar::GetSize()
{
	return this->Width;
}

Vec2 Base_Radar::GetPos()
{
	return this->Pos;
}

void Base_Radar::SetProportion(const float& Proportion)
{
	this->Proportion = Proportion;
}

void Base_Radar::SetDrawList(ImDrawList* DrawList)
{
	this->DrawList = DrawList;
}

void Base_Radar::AddPoint(const Vec3& LocalPos, const float& LocalYaw, const Vec3& Pos, ImColor Color, int Type, float Yaw)
{
	Vec2 PointPos;
	float Distance;
	float Angle;

	this->LocalYaw = LocalYaw;

	Distance = sqrt(pow(LocalPos.x - Pos.x, 2) + pow(LocalPos.y - Pos.y, 2));

	Angle = atan2(Pos.y - LocalPos.y, Pos.x - LocalPos.x) * 180 / M_PI;
	Angle = (this->LocalYaw - Angle) * M_PI / 180;

	Distance = Distance / this->Proportion * this->RenderRange * 2;

	PointPos.x = this->Pos.x + Distance * sin(Angle);
	PointPos.y = this->Pos.y - Distance * cos(Angle);

	// Circle range
	//Distance = sqrt(pow(this->Pos.x - PointPos.x, 2) + pow(this->Pos.y - PointPos.y, 2));
	//if (Distance > this->RenderRange)
	//	return;

	// Rectangle range

	if (PointPos.x < this->Pos.x - RenderRange || PointPos.x > this->Pos.x + RenderRange
		|| PointPos.y > this->Pos.y + RenderRange || PointPos.y < this->Pos.y - RenderRange)
		return;

	std::tuple<Vec2, ImColor, int, float> Data(PointPos, Color, Type, Yaw);
	this->Points.push_back(Data);
}


void Base_Radar::Render()
{
	if (this->DrawList == nullptr)
		return;
	if (Width <= 0)
		return;

	// Cross
	std::pair<Vec2, Vec2> Line1;
	std::pair<Vec2, Vec2> Line2;

	Line1.first = Vec2(this->Pos.x - this->Width / 2, this->Pos.y);
	Line1.second = Vec2(this->Pos.x + this->Width / 2, this->Pos.y);
	Line2.first = Vec2(this->Pos.x, this->Pos.y - this->Width / 2);
	Line2.second = Vec2(this->Pos.x, this->Pos.y + this->Width / 2);

	if (this->Opened)
	{
		if (this->ShowCrossLine)
		{
			this->DrawList->AddLine(Line1.first.ToImVec2(), Line1.second.ToImVec2(), this->CrossColor, 1);
			this->DrawList->AddLine(Line2.first.ToImVec2(), Line2.second.ToImVec2(), this->CrossColor, 1);
		}

		for (auto PointSingle : this->Points)
		{
			Vec2	PointPos = std::get<0>(PointSingle);
			ImColor PointColor = std::get<1>(PointSingle);
			int		PointType = std::get<2>(PointSingle);
			float	PointYaw = std::get<3>(PointSingle);
			if (PointType == 0)
			{
				// 圆形样式
				this->DrawList->AddCircle(PointPos.ToImVec2(), this->CircleSize, PointColor);
				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), this->CircleSize, ImColor(0, 0, 0));
			}	
			else if (PointType==1)
			{
				// 箭头样式
				Vec2 a, b, c;
				Vec2 Re_a, Re_b, Re_c;
				Vec2 Re_Point;
				float Angle = (this->LocalYaw - PointYaw) + 180;
				Re_Point = RevolveCoordinatesSystem(Angle, this->Pos, PointPos);

				Re_a = Vec2(Re_Point.x, Re_Point.y + this->ArrowSize);
				Re_b = Vec2(Re_Point.x - this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);
				Re_c = Vec2(Re_Point.x + this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);

				a = RevolveCoordinatesSystem(-Angle, this->Pos, Re_a);
				b = RevolveCoordinatesSystem(-Angle, this->Pos, Re_b);
				c = RevolveCoordinatesSystem(-Angle, this->Pos, Re_c);

				this->DrawList->AddQuadFilled(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					PointColor
				);
				this->DrawList->AddQuad(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					ImColor(0, 0, 0, 150),
					0.1
				);
			}
			else
			{
				// 圆弧箭头
				ImVec2 TrianglePoint, TrianglePoint_1, TrianglePoint_2;
				float Angle = (this->LocalYaw - PointYaw) - 90;

				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), 0.85 * this->ArcArrowSize, PointColor, 30);
				this->DrawList->AddCircle(PointPos.ToImVec2(), 0.95 * this->ArcArrowSize, ImColor(0, 0, 0, 150), 0, 0.1);

				TrianglePoint.x = PointPos.x + (this->ArcArrowSize+ this->ArcArrowSize/3) * cos(-Angle * M_PI / 180);
				TrianglePoint.y = PointPos.y - (this->ArcArrowSize + this->ArcArrowSize / 3) * sin(-Angle * M_PI / 180);

				TrianglePoint_1.x = PointPos.x + this->ArcArrowSize * cos(-(Angle - 30) * M_PI / 180);
				TrianglePoint_1.y = PointPos.y - this->ArcArrowSize * sin(-(Angle - 30) * M_PI / 180);

				TrianglePoint_2.x = PointPos.x + this->ArcArrowSize * cos(-(Angle + 30) * M_PI / 180);
				TrianglePoint_2.y = PointPos.y - this->ArcArrowSize * sin(-(Angle + 30) * M_PI / 180);

				this->DrawList->PathLineTo(TrianglePoint);
				this->DrawList->PathLineTo(TrianglePoint_1);
				this->DrawList->PathLineTo(TrianglePoint_2);
				this->DrawList->PathFillConvex(ImColor(220, 220, 220, 240));
			}
		}
	}

	if (this->Points.size() > 0)
		this->Points.clear();
}