#pragma once

#ifndef ENGINE_GRAPHICS_CAMERA_H
#define ENGINE_GRAPHICS_CAMERA_H

#include "../math/matrix.h"

// TODO: rewrite 2D
namespace gfx {
	class Camera
	{
		math::Vec4 position;
		math::Mat4 view;
		math::Mat4 projection;

		float fov;
		float z_near = 0.1f;
		float z_far = 1000;
	public:
		Camera();
		~Camera();

		static Camera* Main;
	};
}

#endif