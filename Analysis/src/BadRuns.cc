#include "StoppedHSCP/Analysis/interface/BadRuns.h"

/*

Note:  To remove a bad fill or run, you must add it to both the isBadFillOrRun and the isBadRun methods.

isBadFillOrRun is used in Cuts.cc, and can cut on either fill or run values.
isBadRun is used in RunReducedHistograms for calculating live times.  Because the live time calculation is based on a histogram
that contains live times vs runs, one must specify a run number, rather than a fill number in this method.  

The tool "convertBadFillsToBadRuns.py" in the scripts subdirectory will dump out all runs associated with user-inputted bad fills,
using the list of runs in Ntuples/data/fills.txt to make the correlation between runs and fills.  The output of this script can be 
inserted into the 'isBadRun' method to veto runs associated with a bad fill.

*/


bool isBadRun(unsigned long run){
  // Checks for bad runs. Necessary to specify by run for lumi live time calculation, which is taken from histogram with run info, but no fill info!
  // Runs associated with bad fills were taken from fills.txt

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


  // bad vacuum
  /*
    bad vacuum fills:  1801,1956,1958,2029,2032,2129,2151,2152,2208,2210,2215,2216,2217,2217,2218,2219,2240,2241

    if (fill==1801 || fill==1956 || fill==1958 || fill==2029 ||
    fill==2032 || fill==2129 || fill==2151 || fill==2152 ||
    fill==2208 || fill==2210 || fill==2215 || fill==2216 ||
    fill==2217 || fill==2218 || fill==2219 || fill==2240 || fill==2241) return true;
  */

  if ((run==165506)  ||  (run==170452)  ||  (run==170527)  ||  (run==173389)  || 
      (run==173439)  ||  (run==173438)  ||  (run==176807)  ||  (run==176805)  || 
      (run==176801)  ||  (run==176799)  ||  (run==176797)  ||  (run==176796)  || 
      (run==176795)  ||  (run==177088)  ||  (run==177095)  ||  (run==177096)  || 
      (run==178424)  ||  (run==178421)  ||  (run==178420)  ||  (run==178479)  || 
      (run==178677)  ||  (run==178675)  ||  (run==178671)  ||  (run==178670)  || 
      (run==178669)  ||  (run==178667)  ||  (run==178738)  ||  (run==178731)  || 
      (run==178724)  ||  (run==178712)  ||  (run==178708)  ||  (run==178703)  || 
      (run==178786)  ||  (run==178786)  ||  (run==178871)  ||  (run==178866)  || 
      (run==178854)  ||  (run==178840)  ||  (run==179476)  ||  (run==179452)  || 
      (run==179434)  ||  (run==179431)  ||  (run==179497)  ||  (run==178803) )
    return true;

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

  //bad vacuum fills
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
