#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <deque>
#include <numeric>
#include <iomanip>
#include <unordered_map>
#include "hue.h"

namespace lib {
	namespace ansi {
		constexpr auto bold = "\e[1m";
		constexpr auto red = "\e[31m";
		constexpr auto yellow = "\e[32m";
		constexpr auto blue = "\e[34m";
		constexpr auto purple = "\e[35m";
		constexpr auto reset = "\e[0m";

		auto rgb(int r, int g, int b) {
			return "\e[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
		}
	}
	using namespace std::chrono;

	class tqdm {
		time_point<system_clock> previousTickTime_ = system_clock::now();
		duration<double> totalTime_;
		unsigned previousTickValue_ = 0;
		std::deque<double> deltaTimeList_;
		std::deque<unsigned> deltaTickList_;
		unsigned totalTick_ = 0;
		unsigned period_;
		const unsigned SMOOTHING_SIZE = 100;
		std::array<std::string, 9> bars_ = {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};
		unsigned width_ = 40;
		std::unordered_map<std::string, decltype(bars_)> theme_ = {
				{"default", {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"}},
				{"line", {"─", "─", "─", "╾", "╾", "╾", "╾", "━", "═"}},
				{"circle", {" ", "◓", "◑", "◒", "◐", "◓", "◑", "◒", "#"}},
				{"braille", {" ", "⡀", "⡄", "⡆", "⡇", "⡏", "⡟", "⡿", "⣿"}},
				{"braille_spin", {" ", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠇", "⠿"}},
				{"vertical", {"▁", "▂", "▃", "▄", "▅", "▆", "▇", "█", "█"}},
				{"basic", {" ", " ", " ", " ", " ", " ", " ", " ", "#"}},
		};

	private:
		std::string update(unsigned int currentTick) {
			double averageMicroTime = std::accumulate(deltaTimeList_.begin(), deltaTimeList_.end(), 0.);
			double averageTick = std::accumulate(deltaTickList_.begin(), deltaTickList_.end(), 0.);
			double averageRate = averageTick / averageMicroTime * 1e6;

			double eta = (totalTick_ - currentTick) / averageRate;
			double percent = 100.0 * currentTick / totalTick_;

			std::stringstream oss;
			oss << clean() << formatBar(percent) << ansi::red << ' ' << formatPercent(percent) << ' '
			          << formatInfo(currentTick, averageRate, eta) << ansi::reset;
			return oss.str();
		}

		static std::string clean() {
			// TODO measure terminal size
			return '\r' + std::string(100, ' ') + '\r';
		}

		std::string formatInfo(int currentTick, double averageRate, double eta) const {
			std::stringstream oss;
			oss << ansi::yellow << "[" << ansi::blue << currentTick << ansi::yellow << "/" << ansi::blue << totalTick_
			    << ansi::yellow << " | " << ansi::blue << std::fixed << std::setprecision(0) << std::setw(3);
			if (averageRate > 1e6) {
				oss << averageRate / 1e6 << " MHz";
			} else if (averageRate > 1e3) {
				oss << averageRate / 1e3 << " kHz";
			} else {
				oss << averageRate << " Hz";
			}

			auto totalTime = duration_cast<seconds>(totalTime_).count();
			oss << ansi::yellow << " | "
			    << ansi::blue << totalTime << "s" << ansi::yellow << " : " << ansi::blue << eta << "s"
			    << ansi::yellow << "]";
			return oss.str();
		}

		std::string formatBar(double percent) const {
			std::stringstream oss;
			double fills = percent * width_ / 100;
			unsigned ifills = static_cast<unsigned>(fills);
			unsigned hue_idx = hue::pct_to_idx(percent);
			auto[r, g, b] = hue::hue_to_rgb(hue_idx);

			oss << ansi::blue << "[" << ansi::rgb(r, g, b);
			for (unsigned i = 0; i < ifills; i++) {
				oss << bars_[8];
			}
			if (ifills < width_) {
			    oss << bars_[static_cast<unsigned>(8.0 * (fills - ifills))];
			}
			for (unsigned i = ifills + 1; i < width_; i++) {
				oss << bars_[0];
			}
			oss << ansi::blue << "]";
			return oss.str();
		}

		std::string formatPercent(double percent) const {
			std::stringstream oss;
			oss << std::fixed << std::setprecision(percent == 100.0 ? 0 : 1)
			    << ansi::red << std::setw(4) << percent << "%";
			return oss.str();
		}

		std::string finish() {
			std::stringstream oss;

			double averageMicroTime = std::accumulate(deltaTimeList_.begin(), deltaTimeList_.end(), 0.);
			double averageTick = std::accumulate(deltaTickList_.begin(), deltaTickList_.end(), 0.);
			double averageRate = averageTick / averageMicroTime * 1e6;
			oss << clean() << formatBar(100) << ansi::red << ' ' << formatPercent(100) << ' '
			    << formatInfo(totalTick_, averageRate, 0) << ansi::reset;
			return oss.str();
		}

	public:
		tqdm(unsigned totalTick) {
			totalTick_ = totalTick;
			period_ = 1 + totalTick_ / 200;
		}

		void theme(std::string themeName) {
			if (theme_.count(themeName) != 0) {
				bars_ = theme_[themeName];
			}
		}

		void progress(unsigned currentTick) {
			if (currentTick >= totalTick_) {
				std::cerr << finish() << std::endl;
			}

			if (currentTick % period_ == 0) {
				auto now = system_clock::now();
				auto dtime = now - previousTickTime_;
				auto dtick = currentTick - previousTickValue_;
				previousTickTime_ = now;
				previousTickValue_ = currentTick;
				totalTime_ += dtime;

				auto dtAsMicro = duration_cast<microseconds>(dtime).count();
				deltaTimeList_.push_back(dtAsMicro);
				deltaTickList_.push_back(dtick);
				if (deltaTimeList_.size() > SMOOTHING_SIZE) deltaTimeList_.pop_front();
				if (deltaTickList_.size() > SMOOTHING_SIZE) deltaTickList_.pop_front();
				std::cerr << update(currentTick);
			}
		}
	};
}

