#include <algorithm>
#include "Utils.h"
std::vector<RNRgb> ColorUtil::color_array;
int ColorUtil::next_counter = 0;
RNBoolean ColorUtil::is_initialized_flag = FALSE;
std::vector<RNRgb> ColorUtil::avoided_color_list;
void ColorUtil::
Initialize(int num)
{
	color_array.clear();
	int num_per_channel = ceil(log(num) / log(3.0));
	RNScalar step = 1.0 / (num_per_channel - 1);
	for (int i=0; i<num_per_channel; i++) {
		for (int j=0; j<num_per_channel; j++) {
			for (int k=0; k<num_per_channel; k++) {
				RNRgb color(i*step, j*step, k*step);
				if (!IsColorAvoided(color))
					color_array.push_back(color);
			}
		}
	}
	// random shuffle
	srand(0);
	random_shuffle(color_array.begin(), color_array.end());
	is_initialized_flag = TRUE;
}

int ColorUtil::
NColors(void)
{
	return int(color_array.size());
}

const RNRgb ColorUtil::
KthColor(int k)
{
	if (!is_initialized_flag) Initialize(64);
//    if (k == 0) {
//        return RNRgb(0, 1, 0);
//    }
//    else if (k == 1) {
//        return RNRgb(1, 0, 0);
//    }
//    else if (k == 2) {
//        return RNRgb(0, 0, 1);
//    }
//	else
    if (k < NColors() && k >= 0) return color_array[k];
	else return RandomGeneratedColor();
}

const RNRgb ColorUtil::
NextColor(void)
{
	if (!is_initialized_flag) Initialize();
	RNRgb color = KthColor(next_counter);
	next_counter ++;
	return color;
}

void ColorUtil::
AddAvoidedColor(RNRgb color)
{
	avoided_color_list.push_back(color);
}

bool ColorUtil::
IsColorAvoided(RNRgb color)
{
	for (int i=0; i<int(avoided_color_list.size()); i++) {
		if (avoided_color_list[i] == color) return true;
	}
	return false;
}

void ColorUtil::
ResetCounter(void)
{
	next_counter = 0;
	srand(0);
}

const RNRgb ColorUtil::
RandomGeneratedColor(void)
{
	RNRgb color(0, 0, 0);
	do {
		color[0] = (rand() % 1000) / 1000.0;
		color[1] = (rand() % 1000) / 1000.0;
		color[2] = (rand() % 1000) / 1000.0;
	} while (IsColorAvoided(color));
	return color;
}