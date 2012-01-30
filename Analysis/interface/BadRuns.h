#ifndef GUARD_badruns_h
#define GUARD_badruns_h


// explicitly checks for bad runs and fill numbers
bool isBadFillOrRun(unsigned fill, unsigned run);

// checks for bad runs (including those from bad fills, but 
// those runs are hard coded based on the info in fills.txt from
// 16 January 2012)
bool isBadRun(unsigned long run);

#endif
