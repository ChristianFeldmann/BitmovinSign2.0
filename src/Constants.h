#pragma once

#include <vector>

const unsigned NR_LED_TOTAL = 489;
const unsigned NR_LED_BACKGROUND = 206;
const unsigned NR_LED_PART_LEFT = 46;
const unsigned NR_LED_PART_MIDDLE = 90;
const unsigned NR_LED_PART_RIGHT = 147;

const unsigned OFFSET_PART_LEFT = NR_LED_BACKGROUND;
const unsigned OFFSET_PART_MIDDLE = OFFSET_PART_LEFT + NR_LED_PART_LEFT;
const unsigned OFFSET_PART_RIGHT = OFFSET_PART_MIDDLE + NR_LED_PART_MIDDLE;

const std::vector<int> LED_PARTS_BACKGROUND = {34, 36, 33, 34, 35, 34};
const std::vector<int> LED_PARTS_PART_LEFT = {14, 14, 2, 7, 7, 2};
const std::vector<int> LED_PARTS_PART_MIDDLE = {26, 26, 5, 14, 14, 5};
const std::vector<int> LED_PARTS_PART_RIGHT = {42, 41, 8, 24, 24, 8};

const QColor BitmovinBlue = QColor(30, 171, 226);
