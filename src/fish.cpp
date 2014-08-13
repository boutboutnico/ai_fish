///
/// \file	fish.cpp
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///

#include "fish.h"

/// === INCLUDES	================================================================================
#include <cstdlib>

#include "SDL2_gfx/SDL2_gfxPrimitives.h"

#include "utils.h"

/// === NAMESPACES	================================================================================
using namespace sdl;

/// === PUBLIC DEFINITIONS	========================================================================

vector<SPoint> Fish::vertices_ =
{ SPoint(-1, 1), SPoint(1, 1), SPoint(1, 0), SPoint(0.25, 0), SPoint(0.25, -0.75), SPoint(0.75,
		-0.75), SPoint(0.75, -1), SPoint(-0.75, -1), SPoint(-0.75, -0.75), SPoint(-0.25, -0.75),
		SPoint(-0.25, 0), SPoint(-1, 0) };

/// === PUBLIC DEFINITIONS	========================================================================
Fish::Fish(Renderer& renderer)
{
	rgba_ =
	{	0, 0, 0, 255};

	reset();
}

/// ------------------------------------------------------------------------------------------------
void Fish::reset()
{
	rotation_ = RandFloat() * Param::TwoPi;

	direction_.x = -sin(rotation_);
	direction_.y = cos(rotation_);

	position_ = SVector2D(RandFloat() * Param::window_width, RandFloat() * Param::window_height);

	food_cpt_ = 0;
}

/// ------------------------------------------------------------------------------------------------
void Fish::update(vector<Food*>& foods)
{
	//this will store all the inputs for the NN
	vector<float> inputs;

	//get vector to closest mine
	vec_closest_food_ = ComputeClosestFood(foods);

	/// ??? Normaliser vecteur ???
	SVector2D vec = vec_closest_food_;
//	Vec2DNormalize(vec);

//add in vector to closest mine
	inputs.push_back(vec.x);
	inputs.push_back(vec.y);

	//add in sweepers
	inputs.push_back(direction_.x);
	inputs.push_back(direction_.y);

	//update the brain and get feedback
	vector<float> output = neural_net_.Update(inputs);

	// assign the outputs to the sweepers left & right tracks
	float m_lTrack = output[0];
	float m_rTrack = output[1];

	//calculate steering forces
	float RotForce = m_lTrack - m_rTrack;

	//clamp rotation
	Clamp(RotForce, -Param::turn_rate_max, Param::turn_rate_max);

	rotation_ += RotForce;

	float speed = (m_lTrack + m_rTrack);

	//update Look At
	direction_.x = -sin(rotation_);
	direction_.y = cos(rotation_);

	//update position
	position_ += (direction_ * speed);

	/// wrap around window limits
	if (position_.x > Param::window_width) position_.x = 0;
	if (position_.x < 0) position_.x = Param::window_width;
	if (position_.y > Param::window_height) position_.y = 0;
	if (position_.y < 0) position_.y = Param::window_height;
}

/// ------------------------------------------------------------------------------------------------
void Fish::display(sdl::Renderer& renderer)
{
	renderer.setDrawColor(rgba_.r_, rgba_.g_, rgba_.b_, rgba_.alpha_);

	/// Draw Fish
	vector<SPoint> vertices = vertices_;
	transform(vertices);

	for (uint16_t i = 1; i < vertices.size(); i++)
	{
		renderer.drawLine(vertices[i - 1].x, vertices[i - 1].y, vertices[i].x, vertices[i].y);
	}
	renderer.drawLine(vertices[0].x, vertices[0].y, vertices[vertices.size() - 1].x,
			vertices[vertices.size() - 1].y);

	/// Draw Circle
//	circleRGBA(renderer.get(), position_.x, position_.y, getRadius(), rgba_.r_, rgba_.g_, rgba_.b_,
//			rgba_.alpha_);

/// Draw Line to food
	renderer.drawLine(position_.x, position_.y, vec_closest_food_.x, vec_closest_food_.y);

	//	SDL_Rect rect = {};
	//	renderer.drawRect();
//	ptexture_->copyEx(NULL, &rect_, rad_to_deg(theta_), NULL, SDL_FLIP_NONE);

}

/// === PRIVATE DEFINITIONS	========================================================================

void Fish::transform(vector<SPoint>& vertices)
{
	//create the world transformation matrix
	C2DMatrix matTransform;

	//scale
	matTransform.Scale(Param::scale, Param::scale);

	//rotate
	matTransform.Rotate(rotation_);

	//and translate
	matTransform.Translate(position_.x, position_.y);

	//now transform the ships vertices
	matTransform.TransformSPoints(vertices);
}

/// ------------------------------------------------------------------------------------------------
SVector2D Fish::ComputeClosestFood(const vector<Food*>& foods)
{
	float closest = sqrt(pow(Param::window_width, 2) + pow(Param::window_height, 2));

	SVector2D vec_food;
	float lenght = 0;

	/// cycle through food to find closest
	for (uint16_t i = 0; i < foods.size(); i++)
	{
		lenght = Vec2DLength(foods.at(i)->getPosition() - position_);

		if (lenght < closest)
		{
			closest = lenght;

			vec_food = foods.at(i)->getPosition();

			index_closest_food_ = i;
		}
	}

	return vec_food;
}

/// === END OF FILES	============================================================================
