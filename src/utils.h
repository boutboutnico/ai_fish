///
/// \file	utils.h
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef UTILS_H_
#define UTILS_H_

/// === INCLUDES	================================================================================
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include <sdl.h>

#include "param.h"

/// === NAMESPACE	================================================================================
using namespace std;

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	11 août 2014
/// \author	Nico_user

/// === INLINE DEFINITIONS	========================================================================

template<typename T> string to_str(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

//returns a random integer between x and y
inline int RandInt(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

/// ------------------------------------------------------------------------------------------------
//returns a random float between zero and 1
inline float RandFloat()
{
	return (rand()) / (RAND_MAX + 1.0);
}

/// ------------------------------------------------------------------------------------------------
//returns a random float in the range -1 < n < 1
inline float RandomClamped()
{
	return RandFloat() - RandFloat();
}

/// ------------------------------------------------------------------------------------------------
inline float rad_to_deg(float rad)
{
	return rad * 180.0 / Param::Pi;
}

/// ------------------------------------------------------------------------------------------------
inline uint16_t getSurface(const SDL_Rect& r)
{
	return (r.x + r.w) * (r.y + r.h);
}

/// ------------------------------------------------------------------------------------------------
inline bool isIn(const SDL_Point& p, const SDL_Rect& r)
{
	return (p.x >= r.x && p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool isCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	SDL_Rect ra = r1, rb = r2;
	if (getSurface(r1) < getSurface(r2))
	{
		ra = r2;
		rb = r1;
	}

	SDL_Point p1 =
	{ rb.x, rb.y };
	SDL_Point p2 =
	{ rb.x + rb.w, rb.y };
	SDL_Point p3 =
	{ rb.x, rb.y + rb.h };
	SDL_Point p4 =
	{ rb.x + rb.w, rb.y + rb.h };

	return (isIn(p1, ra) || isIn(p2, ra) || isIn(p3, ra) || isIn(p4, ra)) ? true : false;
}
/// ------------------------------------------------------------------------------------------------

//	clamps the first argument between the second two
void Clamp(float& arg, float min, float max);

#endif	/// UTILS_H_/// === END OF FILE	================================================================================