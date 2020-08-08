#include "vector2.hpp"

namespace SFWR::Math
{
	float crossProduct(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.y - b.x * a.y);
	}

} // namespace SFWR::Math
