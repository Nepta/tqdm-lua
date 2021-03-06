#include <tuple>
#include <array>

namespace hue {
	constexpr int N = 320;

	constexpr int pct_to_idx(double pct) {
		return int(pct * (N - 1) / 100);
	}

	constexpr auto hue_to_rgb(int hue) {
		constexpr std::array<std::tuple<int, int, int>, N> rgb = {
          std::make_tuple(230, 115, 143),
          {230, 115, 143},
          {230, 115, 142},
          {230, 115, 141},
          {230, 115, 141},
          {230, 115, 140},
          {230, 115, 139},
          {230, 115, 138},
          {230, 115, 138},
          {230, 115, 137},
          {230, 115, 136},
          {230, 115, 136},
          {230, 115, 135},
          {230, 115, 134},
          {230, 115, 133},
          {230, 115, 133},
          {230, 115, 132},
          {230, 115, 131},
          {230, 115, 131},
          {230, 115, 130},
          {230, 115, 129},
          {230, 115, 128},
          {230, 115, 128},
          {230, 115, 127},
          {230, 115, 126},
          {230, 115, 126},
          {230, 115, 125},
          {230, 115, 124},
          {230, 115, 123},
          {230, 115, 123},
          {230, 115, 122},
          {230, 115, 121},
          {230, 115, 120},
          {230, 115, 120},
          {230, 115, 119},
          {230, 115, 118},
          {230, 115, 118},
          {230, 115, 117},
          {230, 115, 116},
          {230, 115, 115},
          {230, 115, 115},
          {230, 115, 115},
          {230, 116, 115},
          {230, 117, 115},
          {230, 118, 115},
          {230, 118, 115},
          {230, 119, 115},
          {230, 120, 115},
          {230, 120, 115},
          {230, 121, 115},
          {230, 122, 115},
          {230, 123, 115},
          {230, 123, 115},
          {230, 124, 115},
          {230, 125, 115},
          {230, 126, 115},
          {230, 126, 115},
          {230, 127, 115},
          {230, 128, 115},
          {230, 128, 115},
          {230, 129, 115},
          {230, 130, 115},
          {230, 131, 115},
          {230, 131, 115},
          {230, 132, 115},
          {230, 133, 115},
          {230, 133, 115},
          {230, 134, 115},
          {230, 135, 115},
          {230, 136, 115},
          {230, 136, 115},
          {230, 137, 115},
          {230, 138, 115},
          {230, 138, 115},
          {230, 139, 115},
          {230, 140, 115},
          {230, 141, 115},
          {230, 141, 115},
          {230, 142, 115},
          {230, 143, 115},
          {230, 143, 115},
          {230, 144, 115},
          {230, 145, 115},
          {230, 146, 115},
          {230, 146, 115},
          {230, 147, 115},
          {230, 148, 115},
          {230, 148, 115},
          {230, 149, 115},
          {230, 150, 115},
          {230, 151, 115},
          {230, 151, 115},
          {230, 152, 115},
          {230, 153, 115},
          {230, 153, 115},
          {230, 154, 115},
          {230, 155, 115},
          {230, 156, 115},
          {230, 156, 115},
          {230, 157, 115},
          {230, 158, 115},
          {230, 158, 115},
          {230, 159, 115},
          {230, 160, 115},
          {230, 161, 115},
          {230, 161, 115},
          {230, 162, 115},
          {230, 163, 115},
          {230, 164, 115},
          {230, 164, 115},
          {230, 165, 115},
          {230, 166, 115},
          {230, 166, 115},
          {230, 167, 115},
          {230, 168, 115},
          {230, 169, 115},
          {230, 169, 115},
          {230, 170, 115},
          {230, 171, 115},
          {230, 171, 115},
          {230, 172, 115},
          {230, 173, 115},
          {230, 174, 115},
          {230, 174, 115},
          {230, 175, 115},
          {230, 176, 115},
          {230, 176, 115},
          {230, 177, 115},
          {230, 178, 115},
          {230, 179, 115},
          {230, 179, 115},
          {230, 180, 115},
          {230, 181, 115},
          {230, 181, 115},
          {230, 182, 115},
          {230, 183, 115},
          {230, 184, 115},
          {230, 184, 115},
          {230, 185, 115},
          {230, 186, 115},
          {230, 186, 115},
          {230, 187, 115},
          {230, 188, 115},
          {230, 189, 115},
          {230, 189, 115},
          {230, 190, 115},
          {230, 191, 115},
          {230, 191, 115},
          {230, 192, 115},
          {230, 193, 115},
          {230, 194, 115},
          {230, 194, 115},
          {230, 195, 115},
          {230, 196, 115},
          {230, 197, 115},
          {230, 197, 115},
          {230, 198, 115},
          {230, 199, 115},
          {230, 199, 115},
          {230, 200, 115},
          {230, 201, 115},
          {230, 202, 115},
          {230, 202, 115},
          {230, 203, 115},
          {230, 204, 115},
          {230, 204, 115},
          {230, 205, 115},
          {230, 206, 115},
          {230, 207, 115},
          {230, 207, 115},
          {230, 208, 115},
          {230, 209, 115},
          {230, 209, 115},
          {230, 210, 115},
          {230, 211, 115},
          {230, 212, 115},
          {230, 212, 115},
          {230, 213, 115},
          {230, 214, 115},
          {230, 214, 115},
          {230, 215, 115},
          {230, 216, 115},
          {230, 217, 115},
          {230, 217, 115},
          {230, 218, 115},
          {230, 219, 115},
          {230, 219, 115},
          {230, 220, 115},
          {230, 221, 115},
          {230, 222, 115},
          {230, 222, 115},
          {230, 223, 115},
          {230, 224, 115},
          {230, 224, 115},
          {230, 225, 115},
          {230, 226, 115},
          {230, 227, 115},
          {230, 227, 115},
          {230, 228, 115},
          {230, 229, 115},
          {230, 230, 115},
          {229, 230, 115},
          {228, 230, 115},
          {227, 230, 115},
          {227, 230, 115},
          {226, 230, 115},
          {225, 230, 115},
          {224, 230, 115},
          {224, 230, 115},
          {223, 230, 115},
          {222, 230, 115},
          {222, 230, 115},
          {221, 230, 115},
          {220, 230, 115},
          {219, 230, 115},
          {219, 230, 115},
          {218, 230, 115},
          {217, 230, 115},
          {217, 230, 115},
          {216, 230, 115},
          {215, 230, 115},
          {214, 230, 115},
          {214, 230, 115},
          {213, 230, 115},
          {212, 230, 115},
          {212, 230, 115},
          {211, 230, 115},
          {210, 230, 115},
          {209, 230, 115},
          {209, 230, 115},
          {208, 230, 115},
          {207, 230, 115},
          {207, 230, 115},
          {206, 230, 115},
          {205, 230, 115},
          {204, 230, 115},
          {204, 230, 115},
          {203, 230, 115},
          {202, 230, 115},
          {202, 230, 115},
          {201, 230, 115},
          {200, 230, 115},
          {199, 230, 115},
          {199, 230, 115},
          {198, 230, 115},
          {197, 230, 115},
          {197, 230, 115},
          {196, 230, 115},
          {195, 230, 115},
          {194, 230, 115},
          {194, 230, 115},
          {193, 230, 115},
          {192, 230, 115},
          {191, 230, 115},
          {191, 230, 115},
          {190, 230, 115},
          {189, 230, 115},
          {189, 230, 115},
          {188, 230, 115},
          {187, 230, 115},
          {186, 230, 115},
          {186, 230, 115},
          {185, 230, 115},
          {184, 230, 115},
          {184, 230, 115},
          {183, 230, 115},
          {182, 230, 115},
          {181, 230, 115},
          {181, 230, 115},
          {180, 230, 115},
          {179, 230, 115},
          {179, 230, 115},
          {178, 230, 115},
          {177, 230, 115},
          {176, 230, 115},
          {176, 230, 115},
          {175, 230, 115},
          {174, 230, 115},
          {174, 230, 115},
          {173, 230, 115},
          {172, 230, 115},
          {171, 230, 115},
          {171, 230, 115},
          {170, 230, 115},
          {169, 230, 115},
          {169, 230, 115},
          {168, 230, 115},
          {167, 230, 115},
          {166, 230, 115},
          {166, 230, 115},
          {165, 230, 115},
          {164, 230, 115},
          {164, 230, 115},
          {163, 230, 115},
          {162, 230, 115},
          {161, 230, 115},
          {161, 230, 115},
          {160, 230, 115},
          {159, 230, 115},
          {158, 230, 115},
          {158, 230, 115},
          {157, 230, 115},
          {156, 230, 115},
          {156, 230, 115},
          {155, 230, 115},
          {154, 230, 115},
          {153, 230, 115},
          {153, 230, 115},
          {152, 230, 115},
          {151, 230, 115},
          {151, 230, 115},
          {150, 230, 115},
          {149, 230, 115},
          {148, 230, 115},
          {148, 230, 115},
          {147, 230, 115},
          {146, 230, 115},
          {146, 230, 115},
          {145, 230, 115},
          {144, 230, 115},
		};
		return rgb[hue];
	}

}
