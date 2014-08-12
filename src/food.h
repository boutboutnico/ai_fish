///
/// \file	food.h
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef FOOD_H_
#define FOOD_H_

/// === INCLUDES	================================================================================
#include <renderer.h>

#include "param.h"
#include "SVector2D.h"
#include "C2DMatrix.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	11 août 2014
/// \author	Nico_user
class Food
{
public:

	static const float SIZE;

	/// === PUBLIC DECLARATIONS	====================================================================
	Food();

	void display(sdl::Renderer& renderer);

	inline SVector2D getPosition() const;
	inline uint16_t getRadius() const;

	inline bool isEaten() const;
	inline void setEaten();

private:
	/// === PRIVATE DECLARATIONS	================================================================
//	void transform(std::vector<SPoint>& vertices);

	/// === PRIVATE ATTRIBUTS	====================================================================
	SDL_Rect rect_;
//	static std::vector<SPoint> vertices_pattern_;
//	std::vector<SPoint> vertices_;
//	SVector2D position_;

	sdl::RGBA rgba_;

	bool b_is_eaten;
};

/// === INLINE DEFINITIONS	========================================================================

inline SVector2D Food::getPosition() const
{
	return SVector2D(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2);
}

/// ------------------------------------------------------------------------------------------------
inline uint16_t Food::getRadius() const
{
//	SVector2D vec(vertices_pattern_.at(0).x, vertices_pattern_.at(0).y);
//
//	return Vec2DLength(vec) * Param::scale;

	return sqrt(SIZE * Param::scale * SIZE * Param::scale) / 2;
}
/// ------------------------------------------------------------------------------------------------
inline bool Food::isEaten() const
{
	return b_is_eaten;
}

/// ------------------------------------------------------------------------------------------------
inline void Food::setEaten()
{
	b_is_eaten = true;
}

#endif	/// FOOD_H_/// === END OF FILE	================================================================================
