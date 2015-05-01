#pragma once
namespace ColorUtil
{
	void Initialize(int num = 27);
	int NColors(void);
	const RNRgb KthColor(int k);
	const RNRgb NextColor(void);
	void AddAvoidedColor(RNRgb color);
	bool IsColorAvoided(RNRgb color);
	void ResetCounter(void);
	const RNRgb RandomGeneratedColor(void);
	extern std::vector<RNRgb> color_array;
	extern int next_counter;
	extern RNBoolean is_initialized_flag;
	extern std::vector<RNRgb> avoided_color_list;
};