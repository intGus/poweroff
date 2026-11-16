/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "poweroff_screen.h"

#include "asset_manager.h"
#include "bindings.h"
#include "theme.h"

namespace screen {

PowerOffScreen::PowerOffScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseScreen(view_model, assets) {
    init();
}

void PowerOffScreen::build_content(lv_obj_t* content) {
    auto* group = lv_obj_create(content);
    lv_obj_remove_style_all(group);
    lv_obj_set_size(group, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(group, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(group, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(group, 4, 0);
    lv_obj_set_style_pad_hor(group, 8, 0);
    lv_obj_clear_flag(group, LV_OBJ_FLAG_SCROLLABLE);

    auto* title_font = assets().load_standard_font(20);
    auto* detail_font = assets().load_standard_font(12, app::StandardFontWeight::Regular);

    auto* title = lv_label_create(group);
    lv_label_set_text(title, "Power off?");
    lv_obj_set_style_text_font(title, title_font ? title_font : &lv_font_montserrat_20, 0);
    reactive::bind_theme(title, view_model().dark_mode_subject(), reactive::ThemeRole::Text);

    auto* detail = lv_label_create(group);
    lv_label_set_text(detail,
                      "Shuts down cleanly so the SD card is not\n"
                      "damaged. When all the lights are off, it\n"
                      "is safe to flip the power switch.");
    lv_obj_set_style_text_align(detail, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(detail, detail_font ? detail_font : &lv_font_montserrat_12, 0);
    reactive::bind_theme(detail, view_model().dark_mode_subject(), reactive::ThemeRole::Text);

    auto* status = lv_label_create(group);
    lv_label_bind_text(status, view_model().status_subject(), nullptr);
    lv_label_set_long_mode(status, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(status, LV_PCT(100));
    lv_obj_set_style_text_align(status, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(status, detail_font ? detail_font : &lv_font_montserrat_12, 0);
    lv_obj_set_style_pad_top(status, 4, 0);
    reactive::bind_theme(status, view_model().dark_mode_subject(), reactive::ThemeRole::Text);
}

} // namespace screen
