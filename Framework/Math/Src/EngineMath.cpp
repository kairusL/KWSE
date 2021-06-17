#include "Precompiled.h"
#include "EngineMath.h"

using namespace KWSE;
using namespace KWSE::Math;



//Vector2
const Vector2 Vector2::Zero{ 0.0f };
const Vector2 Vector2::One{ 1.0f };
const Vector2 Vector2::XAxis{ 1.0f, 0.0f };
const Vector2 Vector2::YAxis{ 0.0f, 1.0f };

//Vector3
const Vector3 Vector3::Zero{ 0.0f };
const Vector3 Vector3::One{ 1.0f };
const Vector3 Vector3::XAxis{ 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::YAxis{ 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::ZAxis{ 0.0f, 0.0f, 1.0f };

//Quaternion
const Quaternion Quaternion::Zero = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
const Quaternion Quaternion::Identity = Quaternion(1.0f,0.0f, 0.0f, 0.0f);

//Matrix
const Matrix3 Matrix3::Identity
{
	1.0f , 0.0f , 0.0f,
	0.0f , 1.0f , 0.0f,
	0.0f , 0.0f , 1.0f
};
const Matrix4 Matrix4::Identity
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
};

//Quaternion
Quaternion Quaternion::RotationAxis(const Vector3& axis, float rad) 
{
	const float c = cos(rad * 0.5f);
	const float s = sin(rad * 0.5f);
	const Math::Vector3 a = Math::Normalize(axis);

	return Quaternion(c,a.x * s, a.y * s, a.z * s);
}
Quaternion Quaternion::RotationMatrix(const Matrix4& matrix) 
{
	Matrix4 m = Transpose(matrix);
	float qw, qx, qy, qz;

	float tr = m._11 + m._22 + m._33;

	if (tr > 0)
	{
		float w = sqrt(tr + 1.0f) * 2.0f;
		qw = 0.25f * w;
		qx = (m._32 - m._23) / w;
		qy = (m._13 - m._31) / w;
		qz = (m._21 - m._12) / w;
	}
	else if ((m._11 > m._22) & (m._11 > m._33))
	{
		float w = sqrt(1.0f + m._11 - m._22 - m._33) * 2.0f;
		qw = (m._32 - m._23) / w;
		qx = 0.25f * w;
		qy = (m._12 + m._21) / w;
		qz = (m._13 + m._31) / w;
	}
	else if (m._22 > m._33)
	{
		float w = sqrt(1.0f + m._22 - m._11 - m._33) * 2.0f;
		qw = (m._13 - m._31) / w;
		qx = (m._12 + m._21) / w;
		qy = 0.25f * w;
		qz = (m._23 + m._32) / w;
	}
	else
	{
		float w = sqrt(1.0f + m._33 - m._11 - m._22) * 2.0f;
		qw = (m._21 - m._12) / w;
		qx = (m._13 + m._31) / w;
		qy = (m._23 + m._32) / w;
		qz = 0.25f * w;
	}
	return Normalize(Quaternion(qw,qx, qy, qz));
}
Quaternion Quaternion::RotationLook(const Vector3& direction, const Vector3& up) 
{
	Vector3 z = Normalize(direction);
	Vector3 x = Normalize(Cross(up, z));
	Vector3 y = Normalize(Cross(z, x));
	Matrix4 mat
	(
		x.x, x.y, x.z, 0.0f,
		y.x, y.y, y.z, 0.0f,
		z.x, z.y, z.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return RotationMatrix(mat);
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
}
Quaternion Quaternion::RotationFromTo(const Vector3& from, const Vector3& to)
{
	Vector3 a = Cross(from, to);
	float w = sqrt(Magnitude(from) * Magnitude(from)
		* Magnitude(to) * Magnitude(to)) + Dot(from, to);
	return Normalize(Quaternion(w,a.x, a.y, a.z));
}

// RotationAxis  
Matrix4 Matrix4::RotationAxis(const Vector3& axis, float radian)
{
	const Vector3 u = Normalize(axis);
	const float x = u.x;
	const float y = u.y;
	const float z = u.z;
	const float s = sin(radian);
	const float c = cos(radian);

	return {
		c + (x * x * (1.0f - c)),
		x * y * (1.0f - c) + z * s,
		x * z * (1.0f - c) - y * s,
		0.0f,

		x * y * (1.0f - c) - z * s,
		c + (y * y * (1.0f - c)),
		y * z * (1.0f - c) + x * s,
		0.0f,

		x * z * (1.0f - c) + y * s,
		y * z * (1.0f - c) - x * s,
		c + (z * z * (1.0f - c)),
		0.0f,

		0.0f, 0.0f, 0.0f, 1.0f
	};



	
}
Matrix4 Matrix4::RotationQuaternion(const Quaternion& q)
{
	return Matrix4
	(


		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
		(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f


	);
}
KWSE::Math::Vector3 KWSE::Math::GetBarycentric(const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & point)
{
	KWSE::Math::Vector3 lambda;
	float denom = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
	lambda.x = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / denom;
	lambda.y = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / denom;
	lambda.z = 1.0f - lambda.x - lambda.y;
	return lambda;
}

bool KWSE::Math::PointInTriangle(const Vector2 & point, const Vector2 & a, const Vector2 & b, const Vector2 & c)
{
	KWSE::Math::Vector3 barycentric = GetBarycentric(a, b, c, point);
	return
		barycentric.x >= 0.0f && barycentric.x <= 1.0f &&
		barycentric.y >= 0.0f && barycentric.y <= 1.0f &&
		barycentric.z >= 0.0f && barycentric.z <= 1.0f;
}

bool KWSE::Math::PointInRect(const Vector2 & point, const Rect & rect)
{
	if (point.x > rect.right || point.x < rect.left ||
		point.y > rect.bottom || point.y < rect.top)
	{
		return false;
	}
	return true;
}

bool KWSE::Math::PointInCircle(const Vector2 & point, const Circle & circle)
{
	const Vector2 centerToPoint = point - circle.center;
	const float distSqr = Dot(centerToPoint, centerToPoint);
	const float radiusSqr = circle.radius * circle.radius;
	return distSqr < radiusSqr;
}



bool KWSE::Math::Intersect(const LineSegment & a, const LineSegment & b)
{
	// http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/

	float ua = ((a.to.x - a.from.x) * (b.from.y - a.from.y)) - ((a.to.y - a.from.y) * (b.from.x - a.from.x));
	float ub = ((b.to.x - b.from.x) * (b.from.y - a.from.y)) - ((b.to.y - b.from.y) * (b.from.x - a.from.x));
	float denom = ((a.to.y - a.from.y) * (b.to.x - b.from.x)) - ((a.to.x - a.from.x) * (b.to.y - b.from.y));

	// First check for special cases
	if (denom == 0.0f)
	{
		if (ua == 0.0f && ub == 0.0f)
		{
			// The line segments are the same
			return true;
		}
		else
		{
			// The line segments are parallel
			return false;
		}
	}

	ua /= denom;
	ub /= denom;

	if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f)
	{
		return false;
	}

	return true;
}

bool KWSE::Math::Intersect(const Circle & c0, const Circle & c1)
{
	const float fRadii = c0.radius + c1.radius;
	const float fRadiiSquared = fRadii * fRadii;
	const float fDistanceSquared = DistanceSqr(c0.center, c1.center);
	return (fDistanceSquared < fRadiiSquared);
}

bool KWSE::Math::Intersect(const Rect & r0, const Rect & r1)
{
	if (r0.left > r1.right)
		return false;
	else if (r0.top > r1.bottom)
		return false;
	else if (r0.right < r1.left)
		return false;
	else if (r0.bottom < r1.top)
		return false;
	return true;
}

bool KWSE::Math::Intersect(const LineSegment & l, const Circle & c)
{
	return Intersect(c, l);
}

bool KWSE::Math::Intersect(const Circle & c, const LineSegment & l, Vector2 * closestPoint)
{
	Vector2 startToCenter = c.center - l.from;
	Vector2 startToEnd = l.to - l.from;
	float len = Magnitude(startToEnd);
	Vector2 dir = startToEnd / len;

	// Find the closest point to the line segment
	float projection = Dot(startToCenter, dir);
	Vector2 point;
	if (projection > len)
	{
		point = l.to;
	}
	else if (projection < 0.0f)
	{
		point = l.from;
	}
	else
	{
		point = l.from + (dir * projection);
	}

	// Check if the closest point is within the circle
	if (!PointInCircle(point, c))
		return false;

	if (closestPoint)
		*closestPoint = point;

	return true;
}

bool KWSE::Math::Intersect(const Circle & c, const Rect & r)
{
	return Intersect(r, c);
}

bool KWSE::Math::Intersect(const Rect & r, const Circle & c)
{
	Vector2 closestPoint;
	closestPoint.x = Clamp(c.center.x, r.left, r.right);
	closestPoint.y = Clamp(c.center.y, r.top, r.bottom);

	const float distance = Distance(closestPoint, c.center);
	if (distance > c.radius)
	{
		return false;
	}
	return true;
}

bool KWSE::Math::Intersect(const Ray & ray, const Vector3 & a, const Vector3 & b, const Vector3 & c, float & distance)
{
	// Reference: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

	// Find vectors for two edges sharing V1
	Vector3 e1 = b - a;
	Vector3 e2 = c - a;

	// Begin calculating determinant - also used to calculate u parameter
	Vector3 P = Cross(ray.dir, e2);

	// If determinant is near zero, ray lies in plane of triangle
	float det = Dot(e1, P);
	// NOT CULLING
	if (IsZero(det))
	{
		return false;
	}

	float inv_det = 1.0f / det;

	// Calculate distance from V1 to ray origin
	Vector3 T = ray.org - a;

	// Calculate u parameter and test bound
	float u = Dot(T, P) * inv_det;

	// The intersection lies outside of the triangle
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}

	// Prepare to test v parameter
	Vector3 Q = Cross(T, e1);

	// Calculate V parameter and test bound
	float v = Dot(ray.dir, Q) * inv_det;

	// The intersection lies outside of the triangle
	if (v < 0.0f || u + v  > 1.0f)
	{
		return false;
	}

	// Ray intersection
	float t = Dot(e2, Q) * inv_det;
	if (t <= 0.0f)
	{
		// No hit, no win
		return false;
	}

	distance = t;
	return true;
}

bool KWSE::Math::Intersect(const Ray & ray, const Plane & plane, float & distance)
{
	const float orgDotN = Dot(ray.org, plane.n);
	const float dirDotN = Dot(ray.dir, plane.n);

	// Check if ray is parallel to the plane
	if (IsZero(dirDotN))
	{
		if (IsZero(orgDotN - plane.d))
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.d - orgDotN) / dirDotN;
	return true;
}

bool KWSE::Math::Intersect(const Ray & ray, const AABB & aabb, float & distEntry, float & distExit)
{
	// https://truesculpt.googlecode.com/hg-history/Release%25200.8/Doc/ray_box_intersect.pdf

	// Returns true if ray intersects bounding box
	// Sets d1 to entry distance, d2 to exit distance (along ray.dir)

	Vector3 boxMin = aabb.center - aabb.extend;
	Vector3 boxMax = aabb.center + aabb.extend;
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	float divx = 1.0f / ray.dir.x;
	float divy = 1.0f / ray.dir.y;
	float divz = 1.0f / ray.dir.z;

	if (divx >= 0.0f)
	{
		tmin = (boxMin.x - ray.org.x) * divx;
		tmax = (boxMax.x - ray.org.x) * divx;
	}
	else
	{
		tmin = (boxMax.x - ray.org.x) * divx;
		tmax = (boxMin.x - ray.org.x) * divx;
	}
	if (divy >= 0.0f)
	{
		tymin = (boxMin.y - ray.org.y) * divy;
		tymax = (boxMax.y - ray.org.y) * divy;
	}
	else
	{
		tymin = (boxMax.y - ray.org.y) * divy;
		tymax = (boxMin.y - ray.org.y) * divy;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	if (divz >= 0.0f)
	{
		tzmin = (boxMin.z - ray.org.z) * divz;
		tzmax = (boxMax.z - ray.org.z) * divz;
	}
	else
	{
		tzmin = (boxMax.z - ray.org.z) * divz;
		tzmax = (boxMin.z - ray.org.z) * divz;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	distEntry = tmin;
	distExit = tmax;
	return true;
}

bool KWSE::Math::Intersect(const Ray& ray, const Sphere& sphere, float& distance)
{
	// https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
	Vector3 oc = ray.org - sphere.center;
	float a = Dot(ray.dir, ray.dir);
	float b = 2.0f * Dot(oc, ray.dir);
	float c = Dot(oc, oc) - sphere.radius * sphere.radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		distance = -1.0f;
	else
		distance = (-b - sqrt(discriminant)) / (2.0f * a);

	return (discriminant > 0);
}
bool KWSE::Math::Intersect(const Vector3 & point, const AABB & aabb)
{
	const Vector3 test = point - aabb.center;
	if (abs(test.x) > aabb.extend.x) return false;
	if (abs(test.y) > aabb.extend.y) return false;
	if (abs(test.z) > aabb.extend.z) return false;
	return true;
}

Quaternion KWSE::Math::Slerp(Quaternion q0, Quaternion q1, float t)
{
	// Find the dot product
	float dot = (q0.w * q1.w)+ (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) ;

	// Determine the direction of the rotation.
	if (dot < 0.0f)
	{
		dot = -dot;
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;

	}
	else if (dot > 0.999f)
	{
		return Normalize(Lerp(q0, q1, t));
	}

	float theta = acosf(dot);
	float sintheta = sinf(theta);
	float scale0 = sinf(theta * (1.0f - t)) / sintheta;
	float scale1 = sinf(theta * t) / sintheta;

	// Perform the slerp
	return Quaternion
	(
		(q0.w * scale0) + (q1.w * scale1),
		(q0.x * scale0) + (q1.x * scale1),
		(q0.y * scale0) + (q1.y * scale1),
		(q0.z * scale0) + (q1.z * scale1)
		
	);
}

int KWSE::Math::Random()
{
	return std::uniform_int_distribution<>{ 0, (std::numeric_limits<int>::max)() }(myRandomEngine);
}

int KWSE::Math::Random(int min, int max)
{
	return std::uniform_int_distribution<>{ min, max }(myRandomEngine);
}

float KWSE::Math::RandomFloat()
{
	return std::uniform_real_distribution<float>{ 0, 1.0f }(myRandomEngine);
}

float KWSE::Math::RandomFloat(float min, float max)
{
	return std::uniform_real_distribution<float>{ min, max }(myRandomEngine);
}
double KWSE::Math::RandomDouble()
{
	return std::uniform_real_distribution<double>{ 0, 1 }(myRandomEngine);
}
double KWSE::Math::RandomDouble(double min, double max)
{
	return std::uniform_real_distribution<double>{ min, max }(myRandomEngine);
}

Vector2 KWSE::Math::RandomVector2()
{
	return Vector2
	(
		RandomFloat(),
		RandomFloat()
	);
}

Vector2 KWSE::Math::RandomVector2(const Vector2& min, const Vector2& max)
{
	return Vector2
	(
		RandomFloat(min.x, max.x),
		RandomFloat(min.y, max.y)
	);
}


Vector2 KWSE::Math::RandomUnitCircle(bool normalized)
{
	Vector2 randVal{
		RandomFloat(-1.0f, 1.0f) + 0.001f,
		RandomFloat(-1.0f, 1.0f)
	};
	if (normalized)

		return Normalize(randVal);
	return randVal;
}

Vector3 KWSE::Math::RandomVector3()
{
	return Vector3
	(
		RandomFloat(),
		RandomFloat(),
		RandomFloat()
	);
}

Vector3 KWSE::Math::RandomVector3(const Vector3& min, const Vector3& max)
{
	return Vector3
	(
		RandomFloat(min.x, max.x),
		RandomFloat(min.y, max.y),
		RandomFloat(min.z, max.z)
	);
}

Vector3 KWSE::Math::RandomUnitSphere()
{
	return Normalize(Vector3(
		RandomFloat(-1.0f, 1.0f) + 0.001f,
		RandomFloat(-1.0f, 1.0f),
		RandomFloat(-1.0f, 1.0f))
	);
}