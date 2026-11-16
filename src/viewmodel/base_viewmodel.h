/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "subjects.h"
#include "base_model.h"

#include "lvgl.h"

namespace viewmodel {

class BaseViewModel {
public:
    BaseViewModel();
    ~BaseViewModel();

    BaseViewModel(const BaseViewModel&) = delete;
    BaseViewModel& operator=(const BaseViewModel&) = delete;

    lv_subject_t* title_subject();
    lv_subject_t* dark_mode_subject();
    // Non-zero while a shutdown/reboot has been requested (model::PowerAction).
    lv_subject_t* power_request_subject();
    lv_subject_t* status_subject();
    lv_subject_t* info_visible_subject();
    lv_subject_t* quit_requested_subject();

    bool is_dark_mode() const;
    void set_dark_mode(bool enabled);
    void toggle_dark_mode();

    bool is_busy() const;

    // UI-triggered actions. The actual systemctl call is made by
    // app::PowerController, which observes power_request_subject().
    void request_power_off();
    void request_reboot();
    void toggle_info();
    void request_quit();

    // Called by app::PowerController to report progress or failure.
    void set_status(const char* text);
    void clear_power_request();

private:
    void request(model::PowerAction action, const char* status);
    void publish_all();

    model::BaseModel model_;
    reactive::StringSubject<32> title_subject_;
    reactive::BoolSubject dark_mode_subject_;
    reactive::IntSubject power_request_subject_;
    reactive::StringSubject<96> status_subject_;
    reactive::BoolSubject info_visible_subject_;
    reactive::BoolSubject quit_requested_subject_;
};

} // namespace viewmodel
