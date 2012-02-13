#include "StoppedHSCP/Analysis/interface/BadRuns.h"

bool isBadRun(unsigned long run){
  // Checks for bad runs.  Runs associated with bad fills were taken from fills.txt

  // fills 1186-1207
  if (run>=139020 && run<=139790) return true;
  // fills 1293, 1308, 1309
  if (run==143179 || run==143181 || run==143187 || run==143191 || run==143192 || run==143193) return true; // 1293
  if (run==144083 || run==144084 || run==144085 || run==144086 || run==144087 || run==144088 || run==144089) return true; // 1308
  if (run==144112 || run==144114) return true;
  //fills 1373-1376
  if (run>=146698 && run <=146807) return true;
  // fills 1393, 1394
  if (run==147195 || run==147196 || run==147202 || run==147203 || 
      run==147205 || run==147206 || run==147212 || run==147214 || 
      run==147216 || run==147217 || run==147218 || run==147219 || 
      run==147221 || run==147222) return true; // 1393
  if (run==147284) return true; // 1394
  // HBHE problem
  if (run>=176709 && run<=176795) return true;
  return false;
}

bool isBadFillOrRun(unsigned fill, unsigned run)
{
  // Explicitly checks bad fills or runs

  /*
    remove fills 1186-1207 - cosmic rate is higher than surrounding fills, reason not understood
    remove fills 1293, 1308, 1309 - all rates much lower than expected
    2010B
    remove fills 1373-1375 - all rates lower than expected
    remove fills 1393,1394 - all rates lower than expected (this is the drifting pedestal period)
    
    2011A
    remove fills 1615-1647 - 75ns fills with different backgrounds
    remove runs during fills 1743-1756 in which our triggers were prescaled (this is NOT all runs during this period)
    remove runs 176709-176795 - due to a problem in HBHE raised by Arno 
  */

  // Return True if run/fill is one of known bad runs or fills
  if (fill>=1186 && fill<=1207) return true;
  if (fill==1293 || fill==1308 || fill==1309) return true;
  if (fill>=1373 && fill<=1375) return true;
  if (fill==1393 || fill==1394) return true;
  if (fill>=1615 && fill<=1647) return true;
  if (run>=176709 && run<=176795) return true;

  if (fill==1801) return true;
  if (fill==1956) return true;
  if (fill==1958) return true;
  if (fill==2029) return true;
  if (fill==2032) return true;
  if (fill==2129) return true;
  if (fill==2151) return true;
  if (fill==2152) return true;
  if (fill==2208) return true;
  if (fill==2210) return true;
  if (fill==2215) return true;
  if (fill==2216) return true;
  if (fill==2217) return true;
  if (fill==2218) return true;
  if (fill==2219) return true;
  if (fill==2240) return true;
  if (fill==2241) return true;

  return false;
}
