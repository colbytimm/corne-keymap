/**
 * Utilities for QMK oled animations
 *
 * Copyright (c) Marek Piechut
 * MIT License
 */
#pragma once

//-------- CONFIGURATION START --------

#ifndef ANIM_INVERT
  #define ANIM_INVERT false //Invert animation color and background
#endif
#ifndef ANIM_FRAME_TIME
  #define ANIM_FRAME_TIME 250
#endif
//-------- CONFIGURATION END--------

#define OLED_ROWS OLED_DISPLAY_HEIGHT / 4

static void oled_render_anim_frame(const char **fast_frames, const char **slow_frames, uint8_t frames_len) {

  static uint32_t anim_timer = 0;
  static uint8_t current_frame = 0;

  if (timer_elapsed32(anim_timer) > ANIM_FRAME_TIME && speed > 0) {
    oled_set_cursor(0, 0);
    anim_timer = timer_read32();

    current_frame = (current_frame + 1) % frames_len;

    for(int offset = 0; offset <= OLED_MATRIX_SIZE; offset++) {
      uint16_t col = offset % OLED_DISPLAY_WIDTH;
      oled_write_raw_byte(ANIM_INVERT ? ~col_data : col_data, offset );
    }
  }
}
