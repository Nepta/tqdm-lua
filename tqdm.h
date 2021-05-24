#pragma once

#include "hue.h"
#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

namespace lib {
namespace ansi {
constexpr auto bold = "\e[1m";
constexpr auto red = "\e[31m";
constexpr auto yellow = "\e[32m";
constexpr auto blue = "\e[34m";
constexpr auto purple = "\e[35m";
constexpr auto reset = "\e[0m";

auto rgb(int r, int g, int b) {
  return "\e[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" +
         std::to_string(b) + "m";
}
} // namespace ansi
using namespace std::chrono;

class tqdm {
  time_point<high_resolution_clock> previousTickTime_ =
      high_resolution_clock::now();
  duration<double> totalTime_;
  unsigned previousTickValue_ = 0;
  std::deque<double> deltaTimeList_;
  std::deque<unsigned> deltaTickList_;
  unsigned totalTick_ = 0;
  unsigned period_;
  const unsigned SMOOTHING_SIZE = 100;
  std::array<std::string, 9> bars_ = {" ", "▏", "▎", "▍", "▌",
                                      "▋", "▊", "▉", "█"};
  unsigned width_ = 40;
  std::unordered_map<std::string, decltype(bars_)> theme_ = {
      {"default", {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"}},
      {"line", {"─", "─", "─", "╾", "╾", "╾", "╾", "━", "═"}},
      {"circle", {" ", "◯", "◔", "◔", "◑", "◑", "◕", "◕", "⬤"}},
      {"braille", {" ", "⡀", "⡄", "⡆", "⡇", "⡏", "⡟", "⡿", "⣿"}},
      {"braille_spin", {" ", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠇", "⠿"}},
      {"vertical", {"▁", "▂", "▃", "▄", "▅", "▆", "▇", "█", "█"}},
      {"basic", {" ", " ", " ", " ", " ", " ", " ", " ", "#"}},
  };

  bool hasFinished_ = false;
  bool hasColor_ = true;

private:
  std::string update(unsigned int currentTick) {
    double averageMicroTime =
        std::accumulate(deltaTimeList_.begin(), deltaTimeList_.end(), 0.);
    double averageTick =
        std::accumulate(deltaTickList_.begin(), deltaTickList_.end(), 0.);
    double averageRate = averageTick / averageMicroTime * 1e6;

    double eta = (totalTick_ - currentTick) / averageRate;
    double percent = 100.0 * currentTick / totalTick_;

    std::stringstream oss;
    if (hasColor_) {
      oss << clean() << formatBar(percent) << ansi::red << ' '
          << formatPercent(percent) << ' '
          << formatInfo(currentTick, averageRate, eta) << ansi::reset;
    } else {
      oss << clean() << formatBar(percent) << ' '
          << formatPercent(percent) << ' '
          << formatInfo(currentTick, averageRate, eta);
    }
    return oss.str();
  }

  static std::string clean() {
    // TODO measure terminal size
    return '\r' + std::string(100, ' ') + '\r';
  }

  std::string formatInfo(int currentTick, double averageRate,
                         double eta) const {
    std::stringstream oss;
    if (hasColor_) {
      oss << ansi::yellow << "[" << ansi::blue << currentTick << ansi::yellow
          << "/" << ansi::blue << totalTick_ << ansi::yellow << " | "
          << ansi::blue << std::fixed << std::setprecision(0) << std::setw(3);
    } else {
      oss << "[" << currentTick << "/" << totalTick_ << " | " << std::fixed
          << std::setprecision(0) << std::setw(3);
    }
    if (averageRate > 1e6) {
      oss << averageRate / 1e6 << " MHz";
    } else if (averageRate > 1e3) {
      oss << averageRate / 1e3 << " kHz";
    } else {
      oss << averageRate << " Hz";
    }

    auto totalTime = duration_cast<seconds>(totalTime_).count();
    if (hasColor_) {
      oss << ansi::yellow << " | " << ansi::blue << totalTime << "s"
          << ansi::yellow << " : " << ansi::blue << eta << "s" << ansi::yellow
          << "]";
    } else {
      oss << " | " << totalTime << "s"
          << " : " << eta << "s"
          << "]";
    }
    return oss.str();
  }

  std::string formatBar(double percent) const {
    std::stringstream oss;
    double fills = percent * width_ / 100;
    unsigned ifills = static_cast<unsigned>(fills);
    unsigned hue_idx = hue::pct_to_idx(percent);
    auto rgb = hue::hue_to_rgb(hue_idx);
    auto r = std::get<0>(rgb);
    auto g = std::get<1>(rgb);
    auto b = std::get<2>(rgb);

    if (hasColor_) {
      oss << ansi::blue << "[" << ansi::rgb(r, g, b);
    } else {
      oss << "[";
    }
    for (unsigned i = 0; i < ifills; i++) {
      oss << bars_[8];
    }
    if (ifills < width_) {
      oss << bars_[8 * (fills - ifills)];
    }
    for (unsigned i = ifills + 1; i < width_; i++) {
      oss << bars_[0];
    }
    if (hasColor_) {
      oss << ansi::blue << "]";
    } else {
      oss << "]";
    }
    return oss.str();
  }

  std::string formatPercent(double percent) const {
    std::stringstream oss;
    if (hasColor_) {
      oss << std::fixed << std::setprecision(percent == 100.0 ? 0 : 1)
          << ansi::red << std::setw(4) << percent << "%";
    } else {
      oss << std::fixed << std::setprecision(percent == 100.0 ? 0 : 1)
          << std::setw(4) << percent << "%";
    }
    return oss.str();
  }

  std::string finish() {
    std::stringstream oss;

    double averageMicroTime =
        std::accumulate(deltaTimeList_.begin(), deltaTimeList_.end(), 0.);
    double averageTick =
        std::accumulate(deltaTickList_.begin(), deltaTickList_.end(), 0.);
    double averageRate = averageTick / averageMicroTime * 1e6;
    if (hasColor_) {
      oss << clean() << formatBar(100) << ansi::red << ' ' << formatPercent(100)
          << ' ' << formatInfo(totalTick_, averageRate, 0) << ansi::reset;
    } else {
      oss << clean() << formatBar(100) << ' ' << formatPercent(100) << ' '
          << formatInfo(totalTick_, averageRate, 0);
    }
    return oss.str();
  }

public:
  tqdm(unsigned totalTick) {
    totalTick_ = totalTick;
    period_ = 1 + totalTick_ / 200;
  }

  tqdm *theme(std::string themeName) {
    if (theme_.count(themeName) != 0) {
      bars_ = theme_[themeName];
      hasColor_ = themeName != "basic";
    }
    return this;
  }

  void progress(unsigned currentTick) {
    if (currentTick >= totalTick_ and not hasFinished_) {
      std::cerr << finish() << std::endl;
      hasFinished_ = true;
    } else if (currentTick < totalTick_) {
      hasFinished_ = false;
      if (currentTick % period_ == 0) {
        auto now = high_resolution_clock::now();
        auto dtime = now - previousTickTime_;
        auto dtick = currentTick - previousTickValue_;
        previousTickTime_ = now;
        previousTickValue_ = currentTick;
        totalTime_ += dtime;

        auto dtAsMicro = duration_cast<microseconds>(dtime).count();
        deltaTimeList_.push_back(dtAsMicro);
        deltaTickList_.push_back(dtick);
        if (deltaTimeList_.size() > SMOOTHING_SIZE)
          deltaTimeList_.pop_front();
        if (deltaTickList_.size() > SMOOTHING_SIZE)
          deltaTickList_.pop_front();
        std::cerr << update(currentTick);
      }
    }
  }
};
} // namespace lib
