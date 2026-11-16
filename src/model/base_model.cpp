/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "base_model.h"

namespace model {

const char* BaseModel::app_title() const {
    return "Power Off";
}

bool BaseModel::dark_mode() const {
    return dark_mode_;
}

void BaseModel::set_dark_mode(bool enabled) {
    dark_mode_ = enabled;
}

void BaseModel::toggle_dark_mode() {
    dark_mode_ = !dark_mode_;
}

bool BaseModel::info_visible() const {
    return info_visible_;
}

void BaseModel::toggle_info() {
    info_visible_ = !info_visible_;
}

} // namespace model
