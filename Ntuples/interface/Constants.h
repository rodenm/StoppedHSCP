#ifndef Constants_h
#define Constants_h

const unsigned NBX_PER_ORBIT = 3564;
const double TIME_PER_BX     = 24.95097e-9;
const unsigned NORBIT_PER_LS = 262144;

const double TIME_PER_LS     = TIME_PER_BX * NBX_PER_ORBIT * NORBIT_PER_LS;
//const double TIME_PER_LS     = 23.3570304;

const double TIME_WINDOW     = 1.256;

const int BX_VETO_MINUS = -1;
const int BX_VETO_PLUS = 1;

const int BX_ABORTGAP = 3485;
const int BX_L1GAP = 3529;

#endif
