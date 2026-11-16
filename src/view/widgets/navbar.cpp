/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "navbar.h"

#include "asset_manager.h"
#include "bindings.h"
#include "linux_input.h"
#include "theme.h"
#include "ui_const.h"

namespace view::widgets {
namespace {

// Buttons are 40px wide so 4-letter labels ("MODE", "STOP") are not clipped.
// Offsets were tuned for 32px buttons; they are adjusted here so each
// button's centre stays above the same physical key.
constexpr int32_t kNavButtonWidth = 40;
constexpr std::array<int32_t, 5> kNavButtonXOffsets = {26, 15, 2, -13, -26};

} // namespace

NavBar::NavBar(lv_obj_t* parent, viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseWidgets(parent), view_model_(view_model), assets_(assets) {}

NavBar::~NavBar() {
    for (size_t i = 0; i < icon_buttons_.size(); ++i) {
        if (icon_buttons_[i]) {
            platform::unregister_nav_button(i, icon_buttons_[i]->root());
        }
    }

    if (busy_observer_) {
        lv_observer_remove(busy_observer_);
        busy_observer_ = nullptr;
    }
}

void NavBar::build() {
    if (core_obj_) {
        return;
    }

    core_obj_ = lv_obj_create(parent_);
    lv_obj_remove_style_all(core_obj_);
    lv_obj_set_size(core_obj_, LV_PCT(100), kNavBarHeight);
    lv_obj_align(core_obj_, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(core_obj_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(core_obj_, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(core_obj_, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_left(core_obj_, 8, 0);
    lv_obj_set_style_pad_right(core_obj_, 8, 0);
    reactive::bind_theme(core_obj_, view_model_.dark_mode_subject(), reactive::ThemeRole::Bar);

    create_icon_buttons();
    busy_observer_ = reactive::observe_obj(core_obj_, view_model_.power_request_subject(), busy_changed_cb, this);
    update_icon_buttons();
}

void NavBar::create_icon_buttons() {
    const auto light_color = view::palette(false).text;
    const auto dark_color = view::palette(true).text;
    icon_font_ = assets_.load_font("Phosphor-Fill.ttf", 22);
    // Deliberately not routed through assets_.load_standard_font(): that
    // resolves to a device-only Noto Sans CJK file and always falls back on
    // desktop builds, so its fallback size (14px) does not reliably fit
    // 4-letter labels ("BACK") in a narrow nav button. This
    // built-in bitmap font is guaranteed present on both targets and small
    // enough to fit reliably.
    label_font_ = &lv_font_montserrat_12;

    struct ButtonSpec {
        const char* text;
        lv_event_cb_t click_cb;
        bool use_icon_font;
    };
    const std::array<ButtonSpec, 5> specs = {{
        {"OFF", power_off_cb, false},
        {"", nullptr, false},
        {"", nullptr, false},
        {"", nullptr, false},
        {"BACK", back_cb, false},
    }};

    for (size_t i = 0; i < icon_buttons_.size(); ++i) {
        const auto& spec = specs[i];
        const lv_font_t* font = spec.use_icon_font ? icon_font_ : label_font_;
        icon_buttons_[i] = std::make_unique<IconButton>(core_obj_,
                                                        view_model_,
                                                        kNavButtonWidth,
                                                        24,
                                                        spec.text,
                                                        font ? font : &lv_font_montserrat_14,
                                                        light_color,
                                                        dark_color,
                                                        spec.click_cb,
                                                        &view_model_,
                                                        true);
        icon_buttons_[i]->build();
        lv_obj_set_style_translate_x(icon_buttons_[i]->root(), kNavButtonXOffsets[i], 0);
        platform::register_nav_button(i, icon_buttons_[i]->root());
    }
}

void NavBar::update_icon_buttons() {
    if (!icon_buttons_[0]) {
        return;
    }
    // Once a shutdown is under way there is nothing left to press.
    const bool busy = view_model_.is_busy();
    icon_buttons_[0]->set_text(busy ? "" : "OFF");
    if (icon_buttons_[4]) {
        icon_buttons_[4]->set_text(busy ? "" : "BACK");
    }
}

void NavBar::power_off_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model) {
        view_model->request_power_off();
    }
}

void NavBar::back_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model && !view_model->is_busy()) {
        view_model->request_quit();
    }
}

void NavBar::busy_changed_cb(lv_observer_t* observer, lv_subject_t* subject) {
    LV_UNUSED(subject);

    auto* nav_bar = static_cast<NavBar*>(lv_observer_get_user_data(observer));
    if (nav_bar) {
        nav_bar->update_icon_buttons();
    }
}

} // namespace view::widgets
