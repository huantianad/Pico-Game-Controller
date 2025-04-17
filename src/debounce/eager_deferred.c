/**
 * Debouncing algorithm which immediately sends downstrokes,
 * but waits for DEBOUNCE_TIME of no input before sending an upstroke.
 * @author huantian
 **/

void debounce_eager_deferred() {
  for (int i = SW_GPIO_SIZE - 1; i >= 0; i--) {
    bool sw_raw_val = !gpio_get(SW_GPIO[i]);

    if (sw_cooked_val[i]) {
      if (sw_raw_val) {
        // we are outputting pressed and still are reading pressed:
        // reset debounce timer
        sw_timestamp[i] = time_us_64();
      } else if (sw_timestamp[i] != 0 && 
          time_us_64() - sw_timestamp[i] >= SW_DEBOUNCE_TIME_US) {
        // we are outputting pressed, not reading pressed,
        // and have not read pressed for DEBOUNCE_TIME:
        // output not pressed
        sw_cooked_val[i] = 0;
      }
    } else if (sw_raw_val) {
      // we aren't outputting pressed, but we read a press:
      // output pressed immediately
      sw_cooked_val[i] = 1;
      sw_timestamp[i] = time_us_64();
    }
  }
}
