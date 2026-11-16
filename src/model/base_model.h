/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace model {

enum class PowerAction {
    None     = 0,
    PowerOff = 1,
    Reboot   = 2,
};

class BaseModel {
public:
    const char* app_title() const;

    bool dark_mode() const;
    void set_dark_mode(bool enabled);
    void toggle_dark_mode();

    bool info_visible() const;
    void toggle_info();

private:
    bool dark_mode_ = false;
    bool info_visible_ = false;
};

} // namespace model
