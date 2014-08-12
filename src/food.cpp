///
/// \file	food.cpp
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///

#include "food.h"

/// === INCLUDES	================================================================================
#include "SDL2_gfx/SDL2_gfxPrimitives.h"

#include "utils.h"

/// === NAMESPACES	================================================================================

/// === PUBLIC DEFINITIONS	========================================================================

const float Food::SIZE = 0.5;

//vector<SPoint> Food::vertices_pattern_ =
//{ SPoint(-0.25, -0.25), SPoint(-0.25, 0.25), SPoint(0.25, 0.25), SPoint(0.25, -0.25) };

/// === PUBLIC DEFINITIONS	========================================================================
Food::Food() :
		b_is_eaten(false)
{
//	position_ = SVector2D(RandFloat() * Param::window_width, RandFloat() * Param::window_height);
	rect_.x = RandInt(0, Param::window_width);
	rect_.y = RandInt(0, Param::window_height);
	rect_.w = SIZE * Param::scale;
	rect_.h = SIZE * Param::scale;

	rgba_ =
	{	0,255,0,255};

//	vertices_ = vertices_pattern_;
//	transform(vertices_);

//	rect_.x = RandInt(0, Param::window_width);
//	rect_.y = RandInt(0, Param::window_height);
//	rect_.w = getSize();
//	rect_.h = getSize();
}

/// ------------------------------------------------------------------------------------------------
void Food::display(sdl::Renderer& renderer)
{
	renderer.setDrawColor(rgba_.r_, rgba_.g_, rgba_.b_, rgba_.alpha_);
	renderer.fillRect(&rect_);

//	for (uint16_t i = 1; i < vertices_.size(); i++)
//	{
//		renderer.drawLine(vertices_[i - 1].x, vertices_[i - 1].y, vertices_[i].x, vertices_[i].y);
//	}
//	renderer.drawLine(vertices_[0].x, vertices_[0].y, vertices_[vertices_.size() - 1].x,
//			vertices_[vertices_.size() - 1].y);

//	circleRGBA(renderer.get(), getPosition().x, getPosition().y, getRadius(), 0, 0, 0, 255);
}

/// === PRIVATE DEFINITIONS	========================================================================
//void Food::transform(vector<SPoint>& vertices)
//{
//	//create the world transformation matrix
//	C2DMatrix matTransform;
//
//	//scale
//	matTransform.Scale(Param::scale, Param::scale);
//
//	//rotate
////	matTransform.Rotate(0);
//
////and translate
//	matTransform.Translate(position_.x, position_.y);
//
//	//now transform the ships vertices
//	matTransform.TransformSPoints(vertices);
//}
/// === END OF FILES	============================================================================
