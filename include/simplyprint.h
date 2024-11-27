#ifndef simplyprint_h
#define simplyprint_h

#include <simplyprint.h>

int arreter_impression(int printer_id);
String get_printer_state();
bool is_printer_printing();
bool is_printer_paused();
int toogle_pause_resume_impression();
int resume_impression();
int pause_impression();
#endif