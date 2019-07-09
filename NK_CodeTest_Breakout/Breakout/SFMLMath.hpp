//
// Created by Denis Wagner on 1/16/19.
// Edited by Callum Keddie 24/6/19

#ifndef PONG_SFMLMATH_HPP
#define PONG_SFMLMATH_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sf
{
	inline bool LineSegIntersect(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f & outValue)
	{
		// line 1
		auto a1 = p1.y - p0.y;
		auto b1 = p0.x - p1.x;
		// ax + by = c
		auto c1 = a1 * p0.x + b1 * p0.y;

		// line 2
		auto a2 = p3.y - p2.y;
		auto b2 = p2.x - p3.x;
		// ax + by = c
		auto c2 = a2 * p2.x + b2 * p2.y;

		// first eq minus second eq
		auto denom = a1 * b2 - a2 * b1;

		// check if lines are parallel
		if (denom == 0)
			return false;

		// solve for x
		float iX = (b2 * c1 - b1 * c2) / denom;
		// solve for y
		float iY = (a1 * c2 - a2 * c1) / denom;

		float rx0 = (iX - p0.x) / (p1.x - p0.x);
		float ry0 = (iY - p0.y) / (p1.y - p0.y);
		float rx1 = (iX - p2.x) / (p3.x - p2.x);
		float ry1 = (iY - p2.y) / (p3.y - p2.y);

		if (((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) &&
			((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1)))
		{
			outValue.x = iX;
			outValue.y = iY;
			return true;
		}
		else
			return false;
	}
	/*
	 * Edit: added line intersect function
	 * line intercept form using Ax+By=C
	 */
	inline bool LineIntersect(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f & outValue)
	{
		// line 1
		auto a1 = p1.y - p0.y;
		auto b1 = p0.x - p1.x;
		// ax + by = c
		auto c1 = a1 * p0.x + b1 * p0.y;

		// line 2
		auto a2 = p3.y - p2.y;
		auto b2 = p2.x - p3.x;
		// ax + by = c
		auto c2 = a2 * p2.x + b2 * p2.y;
		
		// first eq minus second eq
		auto denom = a1 * b2 - a2 * b1;

		// check if lines are parallel
		if (denom == 0)
			return false;		

		// solve for x
		outValue.x = (b2 * c1 - b1 * c2) / denom;
		// solve for y
		outValue.y = (a1 * c2 - a2 * c1) / denom;
		
		return true;
	}

	/*
	 * Edit: added cross product function
	 */
	inline sf::Vector2f Cross(sf::Vector2f v)
	{
		return sf::Vector2f(v.y, -v.x);
	}
	
	/*
	 * Edit: added clamp function
	 */
	inline float clamp(float value, float min, float max)
	{
		return std::max(min, std::min(value, max));
	}

	/*
	 * Edit: added lerp function
	 */
	inline float lerp(float v0, float v1, float t)
	{
		return v0 + t * (v1 - v0);
	}

    static const auto PI = acos( -1 );

    /*
     * Vector addition
     */
    template <typename T>
    T operator+( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x + vec2.x;
        const auto newY = vec1.y + vec2.y;

        return T( newX, newY );
    }

    /*
     * Vector subtraction
     */
    template <typename T>
    T operator-( const T& vec1, const T& vec2 )
    {
        const auto newX = vec1.x - vec2.x;
        const auto newY = vec1.y - vec2.y;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename T, typename U>
    T operator*( const T& vec, U scalar )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Scalar multiplication
     */
    template <typename U, typename T>
    T operator*( U scalar, const T& vec )
    {
        const auto newX = vec.x * scalar;
        const auto newY = vec.y * scalar;

        return T( newX, newY );
    }

    /*
     * Returns the dot product of two given vectors
     */
    template <typename T>
    double operator*( const T& vec1, const T& vec2 )
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    /*
     * Returns the square of a given value
     */
    template <typename T>
    inline T sqr( T value )
    {
        return value * value;
    }

    /*
     * Converts radians to degrees
     */
    template <typename T>
    inline double radToDeg( T radians )
    {
        return radians * 180.0 / PI;
    }

    /*
     * Converts degrees to radian
     */
    template <typename T>
    inline double degToRad( T degree )
    {
        return degree / 180.0 * PI;
    }

    /*
     * Returns the length of a given vector
     */
    template <typename T>
    inline double getLength( const T& vec )
    {
        return sqrt( sqr( vec.x ) + sqr( vec.y ) );
    }

    /*
     * Returns a inverted vector
     */
    template <typename T>
    inline T getInverted( const T& vec )
    {
        return T( -vec.x, -vec.y );
    }

    /*
     * Inverts a given vector in-place
     */
    template <typename T>
    inline T& invert( T& vec )
    {
        vec.x = -vec.x;
        vec.y = -vec.y;

        return vec;
    }

    /*
     * Returns a normalized vector
     */
    template <typename T>
    inline T getNormalized( const T& vec )
    {
        const double length = getLength( vec );
        const double newX   = vec.x / length;
        const double newY   = vec.y / length;

        return T( newX, newY );
    }

    /*
     * Normalizes a given vector in-place
     */
    template <typename T>
    inline T& normalize( T& vec )
    {
        const double length = getLength( vec );
        vec.x /= length;
        vec.y /= length;

        return vec;
    }

    /*
     * Returns the angle of a given vector from 0 to 360° depending its direction on the unit circle
     */
    template <typename T>
    inline double getRotationAngle( const T& vec )
    {
        const T      normalizedVec = getNormalized( vec );
        const double angleXRad     = acos( normalizedVec.x );
        const double angleYRad     = asin( normalizedVec.y );
        double       angleRad;

        if ( angleYRad < 0 )
            angleRad = degToRad( 360 ) - angleXRad;
        else
            angleRad = angleXRad;

        return radToDeg( angleRad );
    }

    /*
     * Returns the angle in degrees between two given vectors
     */
    template <typename T>
    inline double getAngleBetween( const T& vec1, const T& vec2 )
    {
        const double angle = acos( ( vec1 * vec2 ) / ( getLength( vec1 ) * getLength( vec2 ) ) );

        return radToDeg( angle );
    }

    /*
     * Returns a vector rotated with a given angle in degrees
     */
    template <typename T>
    inline void getRotated( const T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        const double newX     = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
        const double newY     = vec.x * sin( angleRad ) + vec.y * cos( angleRad );

        return T( newX, newY );
    }

    /*
     * Rotates a vector in-place with a given angle in degrees
     */
    template <typename T>
    inline T& rotate( T& vec, double angle )
    {
        const double angleRad = degToRad( -angle );
        const double newX     = vec.x * cos( angleRad ) - vec.y * sin( angleRad );
        const double newY     = vec.x * sin( angleRad ) + vec.y * cos( angleRad );
        vec.x = newX;
        vec.y = newY;

        return vec;
    }
}
#endif //PONG_SFMLMATH_HPP
