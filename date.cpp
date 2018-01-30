#include <sstream>
#include <iomanip>
#include "date.h"

using namespace std;


#define DT_day_in_secs 60  // le nombre de secondes pour simuler un jour complet


time_t DT_now() { return time(NULL); }

time_t DT_secs_diff(time_t old_t) { return time(NULL) - old_t; }

time_t DT_days_diff(time_t old_t) { return DT_secs_diff(old_t) / DT_day_in_secs; }


string DT_format_date(time_t t)
{ 
	string ft;
	tm d;
	localtime_s(&d, &t);
	stringstream ss;
	//ss << resetiosflags(ios_base::skipws);
	ss << d.tm_mday << "/" << d.tm_mon+1 << "/" << d.tm_year-100;
	ft += ss.str();
	return ft;
}

string DT_format_heure(time_t t)
{ 
	string ft;
	tm d;
	localtime_s(&d, &t);
	stringstream ss;
	ss << setfill('0');
	ss << setw(2) << d.tm_hour << ":" << setw(2) << d.tm_min << ":" << setw(2) << d.tm_sec;
	ft += ss.str();
	return ft;
}

string DT_format_date_heure(time_t t)
{ 
	string ft;
	tm d;
	localtime_s(&d, &t);
	stringstream ss;
	ss << DT_format_date(t) << " - " << DT_format_heure(t);
	ft += ss.str();
	return ft;
}