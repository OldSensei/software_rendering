#pragma once

namespace SFWR::Math
{

	inline const float PI = 3.141593f;

	inline float toRad( float angle )
	{
		return angle * PI / 180.0f;
	}

} // namespace SFWR::Math
