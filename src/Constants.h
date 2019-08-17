#pragma once

#include <vector>
#include <QColor>
#include <QPointF>

#include <cstdlib>
#include <climits>
#include <memory>

#include <algorithm>    // std::fill

class AnimationInterface;

const unsigned NR_LED_TOTAL = 489;
const unsigned NR_LED_BACKGROUND = 206;
const unsigned NR_LED_PART_LEFT = 46;
const unsigned NR_LED_PART_MIDDLE = 90;
const unsigned NR_LED_PART_RIGHT = 147;

const unsigned OFFSET_PART_LEFT = NR_LED_BACKGROUND;
const unsigned OFFSET_PART_MIDDLE = OFFSET_PART_LEFT + NR_LED_PART_LEFT;
const unsigned OFFSET_PART_RIGHT = OFFSET_PART_MIDDLE + NR_LED_PART_MIDDLE;

const std::vector<unsigned> LED_PARTS_BACKGROUND = {34, 36, 33, 34, 35, 34};
const std::vector<unsigned> LED_PARTS_PART_LEFT = {14, 14, 2, 7, 7, 2};
const std::vector<unsigned> LED_PARTS_PART_MIDDLE = {26, 26, 5, 14, 14, 5};
const std::vector<unsigned> LED_PARTS_PART_RIGHT = {42, 41, 8, 24, 24, 8};

const std::vector<QPointF> POINTS_BASE = {QPointF{0.5, 0.98}, QPointF{0.03 , 0.75}, QPointF{0.03 , 0.27}, QPointF{0.5, 0.03}, QPointF{0.97, 0.27}, QPointF{0.97, 0.75}};
const std::vector<QPointF> POINTS_PART_L = {QPointF{0.09, 0.38}, QPointF{0.29, 0.5}, QPointF{0.09, 0.64}, QPointF{0.09, 0.56}, QPointF{0.17 , 0.5}, QPointF{0.09 , 0.45}};
const std::vector<QPointF> POINTS_PART_M = {QPointF{0.21, 0.27}, QPointF{0.58, 0.50}, QPointF{0.21, 0.74}, QPointF{0.21, 0.61}, QPointF{0.39 , 0.5}, QPointF{0.21 , 0.40}};
const std::vector<QPointF> POINTS_PART_R = {QPointF{0.37, 0.16}, QPointF{0.93, 0.50}, QPointF{0.37, 0.85}, QPointF{0.37, 0.69}, QPointF{0.67, 0.5}, QPointF{0.37 , 0.32}};

const std::vector<unsigned> NR_LED_LIST = {NR_LED_BACKGROUND, NR_LED_PART_LEFT, NR_LED_PART_MIDDLE, NR_LED_PART_RIGHT};

const std::vector<unsigned> OFFSET_LIST = {0, OFFSET_PART_LEFT, OFFSET_PART_MIDDLE, OFFSET_PART_RIGHT};

const QColor BITMOVIN_BLUE = QColor(30, 171, 226);

using Frame = std::vector<QColor>;

Frame getBlackFrame();

QColor interpolateColors(const QColor &c1, const QColor &c2, double ratio);

unsigned int setRangeOfLedToColor(Frame& frame, unsigned int startIdx, unsigned int nrLed, QColor color);
