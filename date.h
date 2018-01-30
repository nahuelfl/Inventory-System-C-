#pragma once
#include <time.h>
#include <string>

using namespace std;

time_t DT_now();
time_t DT_secs_diff(time_t old_t);
time_t DT_days_diff(time_t old_t);
string DT_format_date(time_t t);
string DT_format_heure(time_t t);
string DT_format_date_heure(time_t t);