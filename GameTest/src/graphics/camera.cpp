#include "stdafx.h"
#include "camera.h"

#include "../../GameTest/App/AppSettings.h"

namespace gfx
{
	Camera::Camera()
	{
		if (Main == nullptr)
		{
			Main = this;
		}

		fov = PI * 0.5f;
	}

	Camera::~Camera()
	{
		if (Main == this)
		{
			Main = nullptr;
		}
	}

	Camera* Camera::Main = nullptr;
}
