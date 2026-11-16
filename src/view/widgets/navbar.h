/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "base_widget.h"
#include "base_viewmodel.h"
#include "icon_button.h"

#include <array>
#include <memory>

namespace app {
class AssetManager;
}

namespace view::widgets {

// Fixed 5-button bar mapped to hardware/keyboard keys 4-8 (left to right):
// OFF (power off), three unused slots, BACK (exit without shutting down).
class NavBar : public BaseWidgets {
public:
    NavBar(lv_obj_t* parent, viewmodel::BaseViewModel& view_model, app::AssetManager& assets);
    ~NavBar() override;

    void build() override;

private:
    void create_icon_buttons();
    void update_icon_buttons();

    static void power_off_cb(lv_event_t* event);
    static void back_cb(lv_event_t* event);
    static void busy_changed_cb(lv_observer_t* observer, lv_subject_t* subject);

    viewmodel::BaseViewModel& view_model_;
    app::AssetManager& assets_;
    std::array<std::unique_ptr<IconButton>, 5> icon_buttons_;
    lv_font_t* icon_font_{nullptr};
    const lv_font_t* label_font_{nullptr};
    lv_observer_t* busy_observer_{nullptr};
};

} // namespace view::widgets
