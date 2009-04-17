
import FWCore.ParameterSet.Config as cms

process = cms.Process("FilterData")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(2000) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
         '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/0CB6380F-6BF1-DD11-82EF-0013D32281CF.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/24A284BE-6BF1-DD11-850C-00161725E467.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/3A1B7948-6DF1-DD11-832A-0013D3228229.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/3C15D623-6BF1-DD11-8CEC-0013D32281D3.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/42384449-6DF1-DD11-99FE-0013D3541FA6.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/4A35896A-70F1-DD11-B307-0015170AB27C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/4E9EBE3D-69F1-DD11-AF17-00151715BB28.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/54450F73-68F1-DD11-8E56-00151715BB28.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/5C336180-68F1-DD11-B925-00161725E51C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/68045780-68F1-DD11-8628-00161725E502.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/6E87B00E-6BF1-DD11-88EE-0013D3228131.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/9656DB44-6DF1-DD11-8ED0-0013D3542066.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/9CDF8724-6BF1-DD11-993B-0013D3228213.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/9EB75048-6DF1-DD11-92F0-0013D322820B.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/A4BD0525-6BF1-DD11-961E-00161725E491.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/A8D21FBF-6BF1-DD11-BC4E-0013D3228143.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/AE5C05BD-6BF1-DD11-94B7-0013D3542030.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/B0D0C621-6BF1-DD11-AFCE-0013D322813B.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/B22B5E80-68F1-DD11-87F0-0013D32281C7.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/C82BFABB-6BF1-DD11-84DF-0013D3228139.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/E2B549EC-6AF1-DD11-94CF-00161725E504.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/EA6C47BB-6BF1-DD11-9986-0013D3541FDC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/F214E9B9-6BF1-DD11-9BD7-0013D3541F40.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/FE9B58BC-6BF1-DD11-AE0C-0013D3228191.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/00E1721B-ABF1-DD11-8BB6-0030486709FE.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0246D06C-B3F1-DD11-86E4-0015170AE4D8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/02CBE2FB-AFF1-DD11-851E-001A64789358.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/04232271-9CF1-DD11-83AF-001A6478946C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/04B86B9C-92F1-DD11-AD9D-00151715C690.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/04FAC2F4-AAF1-DD11-B949-0013D3541F8E.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/06494A3D-B2F1-DD11-A276-001A6478ABA8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/068E0C81-B2F1-DD11-A543-00161725E479.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/081C60A1-B8F1-DD11-BFAB-001A64787070.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0867C8B3-ACF1-DD11-8029-003048635E08.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0AE6059E-BDF1-DD11-A1D9-001A64787064.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0AFDB5FC-ABF1-DD11-B35F-00E081791747.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0C48DEC8-97F1-DD11-BA2A-0013D322820D.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0C68AAB7-B7F1-DD11-8ECC-001A64789D40.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0C7A8A7F-ADF1-DD11-87FA-00E081791747.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0CF40171-B1F1-DD11-BA82-0013D3228191.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0E51D7E6-93F1-DD11-9906-001A6478ABA8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0E5A6365-A8F1-DD11-9E1E-001A64789D7C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0EC3B782-A0F1-DD11-8EB5-00E0817917B3.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0EE76129-A4F1-DD11-AC20-0013D32281E5.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/0EFDCB4D-B4F1-DD11-8E0F-00304863623C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/107E3F92-9CF1-DD11-8A3A-0015170AC428.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/108D921D-AFF1-DD11-903F-00304863623C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/10BCBB8A-ADF1-DD11-B4BA-003048673E82.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/120B49C6-ACF1-DD11-8497-00E081791761.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1298650B-91F1-DD11-B7BC-00E08178C085.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/12EC83BB-A5F1-DD11-8892-0015170AA798.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/14664D67-B4F1-DD11-9DE0-001A64789DD8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/14D04B15-9EF1-DD11-A3B5-001A6478705C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/16515ABE-9FF1-DD11-9113-001A64789E4C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/169DD369-B1F1-DD11-8C63-0013D32281F9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/16D40A34-ABF1-DD11-9C4D-001A64789D10.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/16ED7DF6-BBF1-DD11-90AC-00E0817917BD.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/18387281-B3F1-DD11-AEB1-003048635DDA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/18667861-95F1-DD11-BADA-003048673F88.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1898C521-BAF1-DD11-8508-001A647894A0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1A3C38B5-9AF1-DD11-B39A-0013D322820D.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1A533B58-9CF1-DD11-AC90-001A64789D54.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1A5BB284-AAF1-DD11-B29F-003048635E2C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1A96F4D4-8CF1-DD11-A583-00E08178C159.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1AFF3283-BEF1-DD11-A57F-0013D3DE2685.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C326364-B4F1-DD11-B054-0015170AAD90.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C44CD92-A0F1-DD11-BCB3-00304866C674.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C683CF8-B1F1-DD11-BA8B-0013D3228229.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C8EABDD-8CF1-DD11-BBAE-003048673FEA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C95FE67-A8F1-DD11-B952-003048635E0C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1E3D1F5E-A1F1-DD11-B49F-0015170AE344.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1E6625BD-9FF1-DD11-91FE-001A647894A4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1EDAB064-A8F1-DD11-AA08-0013D3228143.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/20098B89-A0F1-DD11-8BE5-00E08178C037.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/201DBCCC-A4F1-DD11-9E2C-003048326676.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2060CD51-A8F1-DD11-A1A8-00E081791833.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/20E4814D-BFF1-DD11-9505-001A64789DE4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/22024145-9DF1-DD11-A134-001A6478933C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2253F4BD-ACF1-DD11-90A8-00E08178C0FB.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/22A02925-96F1-DD11-AF91-00151715C58C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/24329C04-B0F1-DD11-8E86-00E08178C0EF.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2457BA4D-BFF1-DD11-A1B5-00E081791757.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/24A97C87-ADF1-DD11-A683-001A6478944C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/26474C93-A0F1-DD11-9A16-001A6478944C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2667F1FB-90F1-DD11-A531-00E08178C169.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2891DF18-A5F1-DD11-A15E-0013D3541F74.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2A2F0092-98F1-DD11-83C3-00161725E4DB.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2A3B5AF4-98F1-DD11-86DD-00E08179186F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2A5DF0E6-98F1-DD11-8E7C-00161725E481.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2AABBC01-A5F1-DD11-93EE-0013D3228171.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2ADA86E0-9FF1-DD11-A713-00E0817918D9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2C25435C-B1F1-DD11-8466-001A64789DB4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2C8E1164-95F1-DD11-913C-00E081B08D91.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2CB9FA36-A4F1-DD11-8494-0013D3541F4E.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2E16FE00-91F1-DD11-94DE-00E08178C0D7.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2EAF3301-B3F1-DD11-AEB4-00151715C670.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2EB6120C-8BF1-DD11-AA1E-0015170AA798.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/30150172-B2F1-DD11-AECF-001A64789D84.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/304502FD-8CF1-DD11-87C5-0030483268DA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/307A8A48-9DF1-DD11-BF66-003048635E02.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/307D4AAC-BCF1-DD11-A7A3-00E0817917EB.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/30F55C74-9CF1-DD11-89C7-003048673F2C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/32C9349B-BDF1-DD11-8583-00E08178C0CB.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/32DDEBFD-B2F1-DD11-AD96-001A64789DE0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/32F2B010-9EF1-DD11-8656-00E08178C119.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/348C3CBF-9FF1-DD11-9611-00E081791833.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/34FA09EC-AFF1-DD11-87BB-00E08178C015.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3627A507-BBF1-DD11-BB61-0013D3542064.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/364B3382-A7F1-DD11-921F-001A64789DA0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/36DD665F-B9F1-DD11-AEFB-001A6478AB7C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3883AEF9-BBF1-DD11-8367-001A64789D60.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/38E2E962-95F1-DD11-A12F-00E081791867.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/38EC770E-B6F1-DD11-A44E-00E08178C18D.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3A11D4BA-9FF1-DD11-BADD-0015170AE3F8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3A5131B1-A7F1-DD11-829D-0015170AD278.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3A9A995D-95F1-DD11-91C8-001A64789DCC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3AB2E0F5-BBF1-DD11-9354-001A64789DA0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3ADDA57D-ADF1-DD11-87C1-001A64789CE8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3C0122C7-B7F1-DD11-B8A6-001A64789498.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3C9930F4-BBF1-DD11-AF2E-0015170ACBB8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3E0DD090-A0F1-DD11-B8C6-003048670B66.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3E2D5F65-A9F1-DD11-80F4-0013D3541F72.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3ED032E8-8CF1-DD11-9DF6-001A64789458.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4451A44F-A5F1-DD11-AE2D-0015170AE41C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/44C4B7F2-9EF1-DD11-AF70-001A64789D3C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/46B3E595-A0F1-DD11-B976-001A64789D64.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/486E3F13-B7F1-DD11-9E4C-00E0817918C1.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/48A12A53-AEF1-DD11-8FC7-001A64789E54.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4A9B9C4C-BAF1-DD11-BEE1-003048635CE2.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4CC16C92-B3F1-DD11-8817-0030486709FE.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4CF0D21F-AFF1-DD11-9228-00E08178C159.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4E233956-9CF1-DD11-91E2-00E08178C01B.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4E2DED74-97F1-DD11-B947-0015170AE510.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/4EBD21AE-BCF1-DD11-A31E-001A6478A824.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5091EF0B-C0F1-DD11-80D4-003048670ADA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/50E5B4FA-99F1-DD11-8AB0-001A6478AB74.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/50FDEC71-B9F1-DD11-BB1A-00E0817917D9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/52010982-AAF1-DD11-8804-0013D3228199.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/52E64E94-B8F1-DD11-8A46-0015170ACA88.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/540C50DC-97F1-DD11-823E-0013D3228177.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/544552A0-ACF1-DD11-8EE9-00E08178C16D.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5668A1E5-93F1-DD11-9ACA-00E08179183F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/56876266-97F1-DD11-9C97-00151715C58C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/58371C48-A4F1-DD11-A822-0015170AE404.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5849E179-B9F1-DD11-8DF1-003048673FEA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5851640F-9EF1-DD11-8EC2-001A64789DA0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/58E37DDA-A4F1-DD11-BD18-00E08179188F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5A37A2E3-C6F1-DD11-ABCC-0030483268CC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5A7A8F9E-BDF1-DD11-949C-0013D32281A3.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5AF46F14-8EF1-DD11-AD54-003048673F88.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5C3AC62B-BAF1-DD11-B5A9-0015170AAD90.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5C9B4AC0-9FF1-DD11-A5D7-00E08178C135.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5CB6F2DB-98F1-DD11-84C2-0013D32281FD.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5E6CD109-B6F1-DD11-860F-0015170AE608.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5EB5E990-A0F1-DD11-9477-001A64789334.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/5ECCA2CE-97F1-DD11-9FAA-00E08178C0E9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6004A7E9-B6F1-DD11-A17A-0013D3228197.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/62C6AB8C-A0F1-DD11-A0AD-001A647894E0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/62CE7F0A-ABF1-DD11-B9C1-00E081791761.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/62FD4BE4-99F1-DD11-8CD0-00E081791847.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/66AFC5A4-BDF1-DD11-ADB9-0013D3228219.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/66CE6336-B5F1-DD11-8EE1-0015170AE2E8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/66CF53F8-B1F1-DD11-A6A6-0013D3DE2665.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6837C378-ADF1-DD11-9B64-00E0817917B9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/68CE7611-B1F1-DD11-A907-001A64789500.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6A3C1435-A8F1-DD11-B726-0015170ACBD4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6A425036-B5F1-DD11-8E67-00E08178C059.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6A814605-BBF1-DD11-9065-001A64789334.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6AD21C94-A0F1-DD11-BF36-001A64789334.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6C1431D6-ABF1-DD11-8D6D-0013D3228201.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6C1A17A4-92F1-DD11-AD66-00304832691A.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6C9FA1C1-97F1-DD11-8886-003048326732.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6E13A35B-A9F1-DD11-BE61-0015170AE54C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/6E56CB9F-BDF1-DD11-BFDF-00E081791885.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/70C5A007-B0F1-DD11-8D5C-00161725E4DD.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/70DDBC69-97F1-DD11-A39D-00161725E461.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/723B6C1E-ABF1-DD11-B11F-001A64789508.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/724F4579-A9F1-DD11-8935-0015170AE298.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/72557C4D-B1F1-DD11-A66E-003048673FFC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/725A62C9-A4F1-DD11-84A4-001A64789D6C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/72ACF2A9-9BF1-DD11-B7E0-001A64789460.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/72EA06F3-8CF1-DD11-9060-0015170AE3B8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/74771FF1-AFF1-DD11-864A-00151715BB94.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/748EA8F4-BBF1-DD11-97E8-001A6478A824.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/74A1D914-9EF1-DD11-B2EA-0013D322813F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7662881B-B2F1-DD11-B680-00304863623E.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7697E880-ADF1-DD11-B7EC-0015170AE650.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/76BC6493-B8F1-DD11-9172-001A64789DE0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/78502C3F-AAF1-DD11-B0F7-001A64789D14.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/78734C1A-A5F1-DD11-BF1E-001A64789D08.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7A40BBFB-9EF1-DD11-8756-00E0817917E1.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7C078415-9EF1-DD11-BC47-003048326974.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7C362377-BEF1-DD11-A006-001A64787064.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7C8F4A0B-A5F1-DD11-B4AB-003048635E34.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7CD88CB2-9AF1-DD11-A62E-001A64789DE4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7E0A516D-BFF1-DD11-B4C1-001A64789460.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7EC02211-BCF1-DD11-A62C-00E08178C0C1.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/803F0DF6-BBF1-DD11-9DA8-00151715C5D4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/80586F81-A6F1-DD11-8B8A-001A64789D44.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/80D0A733-99F1-DD11-8E5F-003048635E34.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8202BBB2-A0F1-DD11-B152-0013D3541FE1.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/823A82FE-AAF1-DD11-9943-0013D32281E5.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/82A398BD-B7F1-DD11-859C-00304867402A.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8425F6E4-90F1-DD11-B348-0015170AE518.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/84513368-95F1-DD11-905C-001A64789334.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/86E96288-97F1-DD11-86A3-00E08178C08F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/882D89ED-93F1-DD11-AB49-0013D3228167.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/88F18A89-A0F1-DD11-82F3-001A6478A824.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8A5C3C5E-B2F1-DD11-9CB7-003048673F2C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8A905960-96F1-DD11-9935-0013D322820B.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8A9DF39E-92F1-DD11-A64F-00E08178C169.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8AB8EA0E-B6F1-DD11-A497-001A64789CF8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8C882D5B-AAF1-DD11-9068-001A64789358.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8C96AB7E-BEF1-DD11-997D-0013D3DE2683.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8C9992C1-A5F1-DD11-95CC-00E081791829.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8E46AD9C-92F1-DD11-AC32-003048673F88.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/8EBF8C51-A8F1-DD11-B5EC-0015170AAEC0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/900A1099-B3F1-DD11-81D9-00304867402A.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/901A2FF3-B1F1-DD11-8767-0013D3541EFC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/9078FE3C-B3F1-DD11-ACD3-001A64789CF8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/90F00DF3-98F1-DD11-96A7-001A64789D14.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/92ABD881-BEF1-DD11-86E8-00E0817918AB.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/92E0F398-A7F1-DD11-A473-001A6478946C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/92EAC62E-99F1-DD11-99E4-0015170AE340.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/92FAE211-9EF1-DD11-BE2D-0015170AE650.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/942EFE7E-ADF1-DD11-82A9-003048673E82.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/94414C21-AFF1-DD11-B3E2-00E0817917DD.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/94A999E2-ABF1-DD11-AFAC-003048635E40.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/94D43218-9EF1-DD11-8BB9-003048636234.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/965B29BB-ADF1-DD11-939C-0013D3DE265B.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/9692942A-BAF1-DD11-A713-001A64789DD8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/96E73679-9CF1-DD11-8FDB-001A64789D04.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/981297BA-A5F1-DD11-8A56-001A64789DB8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/98498488-A9F1-DD11-A8A9-00E08178C053.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/98A65FA0-BDF1-DD11-848E-001A64789DE0.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/9A2482B1-A0F1-DD11-B196-003048673E7A.root'
       
   
    )
)


process.load('Configuration.StandardSequences.L1Emulator_cff')

process.load('FastSimulation.L1CaloTriggerProducer.fastl1calosim_cfi')

process.load('L1Trigger.Skimmer.l1Filter_cfi')



# output module
#
process.load("Configuration.EventContent.EventContentCosmics_cff")

process.FEVT = cms.OutputModule("PoolOutputModule",
    process.FEVTEventContent,
    dataset = cms.untracked.PSet(dataTier = cms.untracked.string('RECO')),
    fileName = cms.untracked.string('Filter_Data_Output.root'),
    SelectEvents = cms.untracked.PSet(
       SelectEvents = cms.vstring("allPath")
       )
)

process.FEVT.outputCommands.append('keep CaloTowersSorted_calotoweroptmaker_*_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCALCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCALCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCLCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCComparatorDigiMuonDigiCollection_muonCSCDigis_MuonCSCComparatorDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCorrelatedLCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCRPCDigiMuonDigiCollection_muonCSCDigis_MuonCSCRPCDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCStripDigiMuonDigiCollection_muonCSCDigis_MuonCSCStripDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCWireDigiMuonDigiCollection_muonCSCDigis_MuonCSCWireDigi_*')
process.FEVT.outputCommands.append('keep cscL1TrackCSCDetIdCSCCorrelatedLCTDigiMuonDigiCollectionstdpairs_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep DTChamberIdDTLocalTriggerMuonDigiCollection_muonDTDigis_*_*')
process.FEVT.outputCommands.append('keep DTLayerIdDTDigiMuonDigiCollection_muonDTDigis_*_*')
process.FEVT.outputCommands.append('keep intL1CSCSPStatusDigisstdpair_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTChambPhContainer_dttfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTChambThContainer_dttfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTTrackContainer_dttfDigis_DATA_*')
process.FEVT.outputCommands.append('keep HBHEDataFramesSorted_*_*_*')
process.FEVT.outputCommands.append('keep PixelDigiedmDetSetVector_siPixelDigis_*_*')
process.FEVT.outputCommands.append('keep recoCandidatesOwned_caloTowersOpt_*_*')
process.FEVT.outputCommands.append('keep RPCDetIdRPCDigiMuonDigiCollection_muonRPCDigis_*_*')



# Conditions (Global Tag is used here):
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.connect = "frontier://PromptProd/CMS_COND_21X_GLOBALTAG"
process.GlobalTag.globaltag = "CRAFT_ALL_V4::All"
process.prefer("GlobalTag")

# Magnetic fiuld: force mag field to be 0 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

# Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

# reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

# offline DQM
process.load("DQMOffline.Configuration.DQMOfflineCosmics_cff")
process.load("DQMServices.Components.MEtoEDMConverter_cff")

#L1 trigger validation
#process.load("L1Trigger.HardwareValidation.L1HardwareValidation_cff")
process.load("L1Trigger.Configuration.L1Config_cff")
process.load("L1TriggerConfig.CSCTFConfigProducers.CSCTFConfigProducer_cfi")
process.load("L1TriggerConfig.CSCTFConfigProducers.L1MuCSCTFConfigurationRcdSrc_cfi")


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Filter_Data_Histos.root')
)





# Analyzers
#########

process.an_L1 = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                   
)                                      


process.an_HLT = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)

process.an_All = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)









# Trigger tools
#########


process.bitfilter = cms.EDFilter("RecoFilter",
    FilterCondition = cms.untracked.string('OneBit'),
    Bit1 = cms.untracked.int32(16)
)


process.l1jetfilter = cms.EDFilter("L1JetFltr",
    EMinCut = cms.untracked.double(0.0),
    EMaxCut = cms.untracked.double(10000.0),
    ETMinCut = cms.untracked.double(10.0),
    ETMaxCut = cms.untracked.double(10000.0),
    BranchTag = cms.untracked.string("hltL1extraParticles"),
    EtaMinCut = cms.untracked.double(-3.0),
    EtaMaxCut = cms.untracked.double(3.0)
)

process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup2_v2_Unprescaled_cff")

process.l1Filter.algorithms = cms.vstring("L1_SingleJet10_00001")

process.MessageLogger.cerr.FwkReport.reportEvery = 100





# Filters and cuts
#########


                  

process.hltenergycut = cms.EDFilter("CaloFilter",
                   
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(20.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-3.3),
    EtaMaxThreshold=cms.untracked.double(3.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
    CentralEta=cms.untracked.double(3.0)                         
                                  
)

process.noisefilter = cms.EDFilter("HLTHPDFilter",
    inputTag = cms.InputTag("hbhereco"),
    energy = cms.double(-99.0),
    hpdSpikeEnergy = cms.double(10.0),
    hpdSpikeIsolationEnergy = cms.double(1.0),
    rbxSpikeEnergy = cms.double(50.0),                               
    rbxSpikeUnbalance = cms.double(0.2)
)





# Paths
#########


process.allPath = cms.Path( process.RawToDigi_woGCT*
                            process.an_All *
                            process.l1Filter*
                            process.an_L1 *
                            process.noisefilter*
                            process.hltenergycut*
                            process.an_HLT
 )

