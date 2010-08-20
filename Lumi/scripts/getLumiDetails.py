#!/usr/bin/env python
VERSION='2.00'
import os,sys
import coral
import array
from RecoLuminosity.LumiDB import argparse,nameDealer,selectionParser,hltTrgSeedMapper,connectstrParser,cacheconfigParser,tablePrinter,csvReporter,csvSelectionParser
from RecoLuminosity.LumiDB.wordWrappers import wrap_always,wrap_onspace,wrap_onspace_strict
class constants(object):
    def __init__(self):
        self.NORM=1.0
        self.LUMIVERSION='0001'
        self.NBX=3564
        self.BEAMMODE='stable' #possible choices stable,quiet,either
        self.VERBOSE=False
        self.NOWARNING=False
    def defaultfrontierConfigString(self):
        return """<frontier-connect><proxy url="http://cmst0frontier.cern.ch:3128"/><proxy url="http://cmst0frontier.cern.ch:3128"/><proxy url="http://cmst0frontier1.cern.ch:3128"/><proxy url="http://cmst0frontier2.cern.ch:3128"/><server url="http://cmsfrontier.cern.ch:8000/FrontierInt"/><server url="http://cmsfrontier.cern.ch:8000/FrontierInt"/><server url="http://cmsfrontier1.cern.ch:8000/FrontierInt"/><server url="http://cmsfrontier2.cern.ch:8000/FrontierInt"/><server url="http://cmsfrontier3.cern.ch:8000/FrontierInt"/><server url="http://cmsfrontier4.cern.ch:8000/FrontierInt"/></frontier-connect>"""
    
def lslengthsec(numorbit,numbx):
    #print numorbit, numbx
    l=numorbit*numbx*25e-09
    return l

def deliveredLumiForRunSection(dbsession,c,runnum,section):
    delivered=0.0
    totalls=0
    try:
        dbsession.transaction().start(True)
        schema=dbsession.nominalSchema()
        query=schema.newQuery()
        query.addToTableList(nameDealer.lumidetailTableName(),'lumidetail')
        query.addToTableList(nameDealer.lumisummaryTableName(),'lumisummary')
        queryCondition=coral.AttributeList()
        queryCondition.extend("runnumber","unsigned int")
        queryCondition.extend("section","unsigned int")
        queryCondition.extend("lumiversion","string")
        queryCondition["runnumber"].setData(int(runnum))
        queryCondition["section"].setData(int(section))
        queryCondition["lumiversion"].setData(c.LUMIVERSION)
        query.setCondition("lumisummary.RUNNUM=:runnumber and lumisummary.LUMIVERSION =:lumiversion AND lumisummary.LUMILSNUM=:section and lumisummary.LUMISUMMARY_ID=lumidetail.LUMISUMMARY_ID",queryCondition)
        query.addToOutputList("lumisummary.LUMILSNUM","lumils")
        query.addToOutputList("lumisummary.INSTLUMI","instlumi")
        query.addToOutputList("lumisummary.NUMORBIT","norbits")
        query.addToOutputList("lumidetail.BXLUMIVALUE","lumivalue")
        result=coral.AttributeList()
        result.extend("lumils","unsigned int")
        result.extend("instlumi","float")
        result.extend("norbits","unsigned int")
        result.extend("lumivalue","blob")
        query.defineOutput(result)
        cursor=query.execute()
        while cursor.next():
            cmsls=cursor.currentRow()["lumils"].data()
            instlumi=cursor.currentRow()["instlumi"].data()*c.NORM
            norbits=cursor.currentRow()["norbits"].data()
            lumivalue=cursor.currentRow()["lumivalue"].data()
            lumibytes=lumivalue.readline()
            print "read bytes:", len(lumibytes)
            buffer=array.array('f')
            buffer.fromstring(lumibytes)
            print "got floats :", len(buffer)
            print "deliveredLumiForRunSection", runnum, section, cmsls, instlumi, norbits, lumivalue
            for ix in range(len(buffer)):
                if buffer[ix]>1.e-4:
                    print ix, buffer[ix]
            
        cursor.close()
        del query
        dbsession.transaction().commit()
    except Exception,e:
        print str(e)
        dbsession.transaction().rollback()
        del dbsession

def main():
    c=constants()
    connectstring='frontier://LumiProd/CMS_LUMI_PROD'
    connectparser=connectstrParser.connectstrParser(connectstring)
    connectparser.parse()
    usedefaultfrontierconfig=False
    cacheconfigpath=''
    if connectparser.needsitelocalinfo():
        cacheconfigpath=os.environ['CMS_PATH']
        if cacheconfigpath:
            cacheconfigpath=os.path.join(cacheconfigpath,'SITECONF','local','JobConfig','site-local-config.xml')
        else:
            usedefaultfrontierconfig=True
        p=cacheconfigParser.cacheconfigParser()
        if usedefaultfrontierconfig:
            p.parseString(c.defaultfrontierConfigString)
        else:
            p.parse(cacheconfigpath)
        connectstring=connectparser.fullfrontierStr(connectparser.schemaname(),p.parameterdict())
    svc = coral.ConnectionService()
    session=svc.connect(connectstring,accessMode=coral.access_Update)
    session.typeConverter().setCppTypeForSqlType("unsigned int","NUMBER(10)")
    session.typeConverter().setCppTypeForSqlType("unsigned long long","NUMBER(20)")
    deliveredLumiForRunSection (session,c,140182,2)
    del session
    del svc
if __name__=='__main__':
    main()
    
