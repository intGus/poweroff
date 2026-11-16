/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "screen_manager.h"

#include "poweroff_screen.h"

namespace app {

ScreenManager::ScreenManager(viewmodel::BaseViewModel& view_model, AssetManager& assets)
    : view_model_(view_model), assets_(assets) {}

ScreenManager::~ScreenManager() = default;

void ScreenManager::start() {
    if (current_screen_) {
        return;
    }

    current_screen_ = std::make_unique<screen::PowerOffScreen>(view_model_, assets_);
    lv_screen_load(current_screen_->root());
}

lv_obj_t* ScreenManager::current_screen() const {
    return current_screen_ ? current_screen_->root() : nullptr;
}

} // namespace app
