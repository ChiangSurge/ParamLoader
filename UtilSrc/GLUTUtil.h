#pragma once
namespace GLUTUtil
{
	// 2D
    void Begin2D(const R3Viewer* viewer);
    void End2D(void);
	// Text
	void DrawText(const R3Point& p, const char *s);
	void DrawText(const R2Point& p, const char *s, const R3Viewer* viewer);
};
