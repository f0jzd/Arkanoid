#pragma once

struct Circle
{
	float x;
	float y;
	float radius;
};

void draw_circle(const Circle& circle);
bool circle_intersect(const Circle& a, const Circle& b);

struct AABB
{
	static AABB make_from_position_size(float x, float y, float w, float h); //Call it as a part of the class, similar to namespace, treats the class as a namespace.

	float x_min;
	float y_min;

	float x_max;
	float y_max;

};

void draw_box(const AABB& box);
void draw_filled_box(const AABB& box);
bool aabb_intersect(const AABB& a, const AABB& b);

bool aabb_circle_intersect(const AABB& a, const Circle& b);


