///
/// \file	fish.h
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef FISH_H_
#define FISH_H_

/// === INCLUDES	================================================================================
#include <renderer.h>
#include <texture.h>

#include "param.h"
#include "food.h"
#include "neural_net.h"
#include "C2DMatrix.h"
#include "SVector2D.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	11 août 2014
/// \author	Nico_user
class Fish
{
public:
	/// === PUBLIC DECLARATIONS	====================================================================
	Fish(sdl::Renderer& renderer);

	void update(std::vector<Food*>& foods);
	inline SVector2D getPosition() const;
	inline uint16_t getRadius() const;
	inline uint16_t getFitness() const;
	inline void incrementFood();
	inline uint16_t getClosestFood() const;

	/// Graphics
	void display(sdl::Renderer& renderer);
	inline void setRGBA(const sdl::RGBA& rgba);

private:
	/// === PRIVATE DECLARATIONS	================================================================

	void transform(vector<SPoint>& vertices);

	SVector2D ComputeClosestFood(std::vector<Food*>& foods);

	/// === PRIVATE ATTRIBUTS	====================================================================
	sdl::Texture* ptexture_;
	SDL_Rect rect_;

	static std::vector<SPoint> vertices_;
	sdl::RGBA rgba_;

	SVector2D position_;
	SVector2D direction_;
	float rotation_;

	float x_, y_;
	float theta_;

	uint16_t food_cpt_;
	uint16_t index_closest_food_;
	SVector2D vec_closest_food_;

	NeuralNet neural_net_;
};

/// === INLINE DEFINITIONS	========================================================================

inline SVector2D Fish::getPosition() const
{
	return position_;
}

/// ------------------------------------------------------------------------------------------------
inline uint16_t Fish::getRadius() const
{
	SVector2D vec(vertices_.at(0).x, vertices_.at(0).y);

	return Vec2DLength(vec) * Param::scale;
}

/// ------------------------------------------------------------------------------------------------
inline uint16_t Fish::getFitness() const
{
	return food_cpt_;
}

/// ------------------------------------------------------------------------------------------------
inline void Fish::incrementFood()
{
	food_cpt_++;
}

/// ------------------------------------------------------------------------------------------------
inline uint16_t Fish::getClosestFood() const
{
	return index_closest_food_;
}

/// ------------------------------------------------------------------------------------------------
inline void Fish::setRGBA(const sdl::RGBA& rgba)
{
	rgba_ = rgba;
}

#endif	/// FISH_H_/// === END OF FILE	================================================================================