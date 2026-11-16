/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "base_viewmodel.h"

namespace viewmodel {

BaseViewModel::BaseViewModel()
    : title_subject_(model_.app_title()),
      dark_mode_subject_(model_.dark_mode()),
      power_request_subject_(static_cast<int>(model::PowerAction::None)),
      status_subject_("Press OFF (key 4) to shut down safely"),
      info_visible_subject_(model_.info_visible()),
      quit_requested_subject_(false) {}

BaseViewModel::~BaseViewModel() = default;

lv_subject_t* BaseViewModel::title_subject() {
    return title_subject_.native();
}

lv_subject_t* BaseViewModel::dark_mode_subject() {
    return dark_mode_subject_.native();
}

lv_subject_t* BaseViewModel::power_request_subject() {
    return power_request_subject_.native();
}

lv_subject_t* BaseViewModel::status_subject() {
    return status_subject_.native();
}

lv_subject_t* BaseViewModel::info_visible_subject() {
    return info_visible_subject_.native();
}

lv_subject_t* BaseViewModel::quit_requested_subject() {
    return quit_requested_subject_.native();
}

bool BaseViewModel::is_dark_mode() const {
    return model_.dark_mode();
}

void BaseViewModel::set_dark_mode(bool enabled) {
    model_.set_dark_mode(enabled);
    publish_all();
}

void BaseViewModel::toggle_dark_mode() {
    model_.toggle_dark_mode();
    publish_all();
}

bool BaseViewModel::is_busy() const {
    return power_request_subject_.value() != 0;
}

void BaseViewModel::request(model::PowerAction action, const char* status) {
    if (is_busy()) {
        return;
    }
    status_subject_.set(status);
    power_request_subject_.set(static_cast<int>(action));
}

void BaseViewModel::request_power_off() {
    request(model::PowerAction::PowerOff, "Shutting down... wait for the green light to go off");
}

void BaseViewModel::request_reboot() {
    request(model::PowerAction::Reboot, "Restarting...");
}

void BaseViewModel::toggle_info() {
    model_.toggle_info();
    info_visible_subject_.set(model_.info_visible());
}

void BaseViewModel::request_quit() {
    quit_requested_subject_.set(true);
}

void BaseViewModel::set_status(const char* text) {
    status_subject_.set(text);
}

void BaseViewModel::clear_power_request() {
    power_request_subject_.set(static_cast<int>(model::PowerAction::None));
}

void BaseViewModel::publish_all() {
    title_subject_.set(model_.app_title());
    dark_mode_subject_.set(model_.dark_mode());
}

} // namespace viewmodel
