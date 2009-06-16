import FWCore.ParameterSet.Config as cms

basicKinematicLeaves = cms.PSet(
    status = cms.string('status'),
    phi = cms.string('phi'),
    pt = cms.string('pt'),
    pz = cms.string('pz'),
    px = cms.string('px'),
    py = cms.string('py'),
    eta = cms.string('eta'),
    theta = cms.string('theta'),
    et = cms.string('et')
    )

TriggerPSets = cms.PSet(
    HLT_StoppedHSCP_8E29 = cms.PSet(
        src = cms.InputTag("TriggerResults","","HLT"),
        method = cms.string('HLTBitVariable')
        ),
    HLT_StoppedHSCP_1E31 = cms.PSet(
        src = cms.InputTag("TriggerResults","","HLT"),
        method = cms.string('HLTBitVariable')
        )
    )

isoAxis = cms.PSet(
    nBins = cms.uint32(100),
    Max = cms.double(20.0),
    Min = cms.double(0.0)
)
eTaxis = cms.PSet(
    nBins = cms.uint32(600),
    Max = cms.double(1200.0),
    Min = cms.double(0.0)
)
#Main module to create the two trees and histograms (these histograms are not from the trees)
configurableAnalysis = cms.EDFilter(
    "ConfigurableAnalysis",
    Selections = cms.PSet(
        filters = cms.PSet(
            leadingMuon = cms.PSet(
                src = cms.string('muons'),
                #                cut = cms.vstring('pt > 20.0 & abs(eta) < 3.0'),
                cut = cms.vstring(''),
                selector = cms.string('patMuonSEventSelector')
                #                selector = cms.string('')
                )#,
            #            leadingElectron = cms.PSet(
            #                src = cms.string('electrons'),
            #                cut = cms.vstring('pt > 20.0 & abs(eta) < 3.0'),
            #                selector = cms.string('patElectronSEventSelector')
            #            )
            ),
        selections = cms.PSet(
            minSelection = cms.PSet(
                #                                vstring filterOrder = { "leadingElectron" }
                filterOrder = cms.vstring(''),
                makeFinalPlots = cms.bool(True),
                makeSummaryTable = cms.bool(True),
                makeContentPlots = cms.bool(True),
                makeAllButOnePlots = cms.bool(True),
                ntuplize = cms.bool(True),
                nMonitor = cms.uint32(1000),
                makeCumulativePlots = cms.bool(True)
                )
            )
        ),
    Plotter = cms.PSet(
        TH1s = cms.PSet(
            
            ),
        ComponentName = cms.string('VariablePlotter'),
        TProfiles = cms.PSet(
            
            ),
        TH2s = cms.PSet(
            
            )
        ),
    Variables = cms.PSet(
        TriggerPSets,
        
        L1Bit = cms.PSet(
            src = cms.InputTag("hltGtDigis"),
            method = cms.string('ComputedVariable'),
            computer = cms.string('L1BitComputer')
            )#,

     #   csaWeight = cms.PSet(
     #       src = cms.InputTag("csaweightproducer","weight"),
     #       method = cms.string('DoubleVar')
     #   ),
    #    procIDSplit = cms.PSet(
    #        weightLabel = cms.string('csaweightproducer'),
    #        maxID = cms.uint32(70),
    #        method = cms.string('ProcessIdSplitter'),
    #        lumi = cms.double(1000.0)
    #    )
    ),
    workAsASelector = cms.bool(True),
    flows = cms.vstring('minSelection'),
    InputTags = cms.PSet(
        genParticles = cms.InputTag("genParticles"),
        mets = cms.InputTag("selectedLayer1METs"),
        genMuons = cms.InputTag("genMuons"),
        ccjets = cms.InputTag("patcrosscleaner","ccJets"),
        genElectrons = cms.InputTag("genElectrons"),
        electrons = cms.InputTag("selectedLayer1Electrons"),
        ccmets = cms.InputTag("patcrosscleaner","ccMETs"),
        muons = cms.InputTag("selectedLayer1Muons"),
        jets = cms.InputTag("selectedLayer1Jets"),
        ccmuons = cms.InputTag("patcrosscleaner","ccMuons"),
        ccelectrons = cms.InputTag("patcrosscleaner","ccElectrons"),
        genJets = cms.InputTag("iterativeCone5GenJetsNoNuBSM")
    ),
    Ntupler = cms.PSet(
        branchesPSet = cms.PSet(
            treeName = cms.string('eventB'),
            mus = cms.PSet(
                src = cms.string('muons'),
                leaves = cms.PSet(
                    basicKinematicLeaves,
                    vars = cms.vstring(
                        'gen_id:genLepton.pdgId',
                        'gen_phi:genLepton.phi',
                        'gen_pt:genLepton.pt',
                        'gen_pz:genLepton.pz',
                        'gen_px:genLepton.px',
                        'gen_py:genLepton.py',
                        'gen_eta:genLepton.eta',
                        'gen_theta:genLepton.theta',
                        'gen_et:genLepton.et',                       
                        'gen_mother_id:genLepton.mother.pdgId',
                        'gen_mother_phi:genLepton.mother.phi',
                        'gen_mother_pt:genLepton.mother.pt',
                        'gen_mother_pz:genLepton.mother.pz',
                        'gen_mother_px:genLepton.mother.px',
                        'gen_mother_py:genLepton.mother.py',
                        'gen_mother_eta:genLepton.mother.eta',
                        'gen_mother_theta:genLepton.mother.theta',
                        'gen_mother_et:genLepton.mother.et',                       
                        'tkHits:track.hitPattern.numberOfValidHits', 
                        'cIso:caloIso', 
                        'tIso:trackIso',
                        'ecalIso:ecalIso',
                        'hcalIso:hcalIso',
#                        'ecalvetoDep:ecalIsoDeposit.candEnergy',
#                        'hcalvetoDep:hcalIsoDeposit.candEnergy',
#                        'id:leptonID', 
                        'calEnergyEm:calEnergy.em',
                        'calEnergyHad:calEnergy.had',
                        'calEnergyHo:calEnergy.ho',
                        'calEnergyEmS9:calEnergy.emS9',
                        'calEnergyHadS9:calEnergy.hadS9',
                        'calEnergyHoS9:calEnergy.hoS9',
                        'iso03_sumPt:isolationR03.sumPt',
                        'iso03_emEt:isolationR03.emEt',
                        'iso03_hadEt:isolationR03.hadEt',
                        'iso03_hoEt:isolationR03.hoEt',
                        'iso03_nTracks:isolationR03.nTracks',
                        'iso05_sumPt:isolationR05.sumPt',
                        'iso05_emEt:isolationR05.emEt',
                        'iso05_hadEt:isolationR05.hadEt',
                        'iso05_hoEt:isolationR05.hoEt',
                        'iso05_nTracks:isolationR05.nTracks',
                        'charge:charge', 
                        'cm_chi2:combinedMuon.chi2', 
                        'cm_ndof:combinedMuon.ndof', 
                        'cm_chg:combinedMuon.charge', 
                        'cm_pt:combinedMuon.pt', 
                        'cm_px:combinedMuon.px', 
                        'cm_py:combinedMuon.py', 
                        'cm_pz:combinedMuon.pz', 
                        'cm_eta:combinedMuon.eta', 
                        'cm_phi:combinedMuon.phi', 
                        'cm_theta:combinedMuon.theta', 
                        'cm_d0:combinedMuon.d0', 
                        'cm_dz:combinedMuon.dz', 
                        'cm_vx:combinedMuon.vx', 
                        'cm_vy:combinedMuon.vy', 
                        'cm_vz:combinedMuon.vz', 
                        'cm_numvalhits:combinedMuon.numberOfValidHits', 
                        'cm_numlosthits:combinedMuon.numberOfLostHits', 
                        'cm_d0Err:combinedMuon.d0Error', 
                        'cm_dzErr:combinedMuon.dzError', 
                        'cm_ptErr:combinedMuon.ptError', 
                        'cm_etaErr:combinedMuon.etaError', 
                        'cm_phiErr:combinedMuon.phiError', 
                        'tk_chi2:track.chi2',
                        'tk_ndof:track.ndof', 
                        'tk_chg:track.charge', 
                        'tk_pt:track.pt', 
                        'tk_px:track.px', 
                        'tk_py:track.py', 
                        'tk_pz:track.pz', 
                        'tk_eta:track.eta', 
                        'tk_phi:track.phi', 
                        'tk_theta:track.theta', 
                        'tk_d0:track.d0', 
                        'tk_dz:track.dz', 
                        'tk_vx:track.vx', 
                        'tk_vy:track.vy', 
                        'tk_vz:track.vz', 
                        'tk_numvalhits:track.numberOfValidHits', 
                        'tk_numlosthits:track.numberOfLostHits', 
                        'tk_d0Err:track.d0Error', 
                        'tk_dzErr:track.dzError', 
                        'tk_ptErr:track.ptError', 
                        'tk_etaErr:track.etaError', 
                        'tk_phiErr:track.phiError', 
                        'stamu_chi2:standAloneMuon.chi2', 
                        'stamu_ndof:standAloneMuon.ndof', 
                        'stamu_chg:standAloneMuon.charge', 
                        'stamu_pt:standAloneMuon.pt', 
                        'stamu_px:standAloneMuon.px', 
                        'stamu_py:standAloneMuon.py', 
                        'stamu_pz:standAloneMuon.pz', 
                        'stamu_eta:standAloneMuon.eta', 
                        'stamu_phi:standAloneMuon.phi', 
                        'stamu_theta:standAloneMuon.theta', 
                        'stamu_d0:standAloneMuon.d0',
                        'stamu_dz:standAloneMuon.dz', 
                        'stamu_vx:standAloneMuon.vx', 
                        'stamu_vy:standAloneMuon.vy', 
                        'stamu_vz:standAloneMuon.vz', 
                        'stamu_numvalhits:standAloneMuon.numberOfValidHits', 
                        'stamu_numlosthits:standAloneMuon.numberOfLostHits', 
                        'stamu_d0Err:standAloneMuon.d0Error', 
                        'stamu_dzErr:standAloneMuon.dzError', 
                        'stamu_ptErr:standAloneMuon.ptError', 
                        'stamu_etaErr:standAloneMuon.etaError', 
                        'stamu_phiErr:standAloneMuon.phiError', 
                        'num_matches:numberOfMatches',
                        'id_All:isGood("All")',
                        'id_AllGlobalMuons:isGood("AllGlobalMuons")',
                        'id_AllStandAloneMuons:isGood("AllStandAloneMuons")',
                        'id_AllTrackerMuons:isGood("AllTrackerMuons")',
                        'id_TrackerMuonArbitrated:isGood("TrackerMuonArbitrated")',
                        'id_AllArbitrated:isGood("AllArbitrated")',
                        'id_GlobalMuonPromptTight:isGood("GlobalMuonPromptTight")',
                        'id_TMLastStationLoose:isGood("TMLastStationLoose")',                        
                        'id_TMLastStationTight:isGood("TMLastStationTight")',
                        'id_TM2DCompatibilityLoose:isGood("TM2DCompatibilityLoose")',
                        'id_TM2DCompatibilityTight:isGood("TM2DCompatibilityTight")',                        
                        'id_TMOneStationLoose:isGood("TMOneStationLoose")',
                        'id_TMOneStationTight:isGood("TMOneStationTight")',
                        'id_TMLastStationOptimizedLowPtLoose:isGood("TMLastStationOptimizedLowPtLoose")',
                        'id_TMLastStationOptimizedLowPtTight:isGood("TMLastStationOptimizedLowPtTight")'                                                                                                                                       )
                ),
                Class = cms.string('pat::Muon')
            ),
            mets = cms.PSet(
                src = cms.InputTag("selectedLayer1METs"),
                leaves = cms.PSet(
                    vars = cms.vstring('et:et', 
                        'phi:phi', 
                        'ex:px', 
                        'ey:py', 
                        'gen_et:genMET.et', 
                        'gen_phi:genMET.phi', 
                        'sumEt:sumEt', 
                        'unCPhi:uncorrectedPhi', 
                        'unCPt:uncorrectedPt')
                ),
                Class = cms.string('pat::MET')
            ),
            ccjets = cms.PSet(
                src = cms.string('ccjets'),
                leaves = cms.PSet(
                    basicKinematicLeaves,

                    vars = cms.vstring('energy:energy', 
                        'mass:mass')
                ),
                Class = cms.string('pat::Jet')
            ),
            photons = cms.PSet(
                src = cms.InputTag("selectedLayer1Photons"),
                leaves = cms.PSet(
                    basicKinematicLeaves
                ),
                Class = cms.string('pat::Photon')
            ),
            mc_doc = cms.PSet(
                src = cms.InputTag("genParticles"),
                leaves = cms.PSet(
                    vars = cms.vstring('id:pdgId', 
                        'pt:pt', 
                        'px:px', 
                        'py:py', 
                        'pz:pz',
                        'eta:eta',
                        'phi:phi',
                        'theta:theta', 
                        'status:status', 
                        'mother_id:mother.pdgId',
                        'grandmother_id:mother.mother.pdgId', 
                        'ggrandmother_id:mother.mother.mother.pdgId', 
                        'mother_pt:mother.pt',           
                        'vertex_x:vertex.x', 
                        'vertex_y:vertex.y', 
                        'vertex_z:vertex.z', 
                        'mass:mass', 
                        'numOfDaughters:numberOfDaughters',
                        'numOfMothers:numberOfMothers'
                                       )
                ),
#                selection = cms.string('status = 3&&numberOfMothers!=0'),
                selection = cms.string('status=3'),
                Class = cms.string('reco::GenParticle')
            ),
            mc_mus = cms.PSet(
                src = cms.InputTag("genParticles"),
                leaves = cms.PSet(
                    vars = cms.vstring('id:pdgId', 
                        'pt:pt', 
                        'px:px', 
                        'py:py', 
                        'pz:pz',
                        'eta:eta', 
                        'phi:phi',
                        'theta:theta', 
                        'status:status', 
                        'mother_id:mother.pdgId',
                        'mother_pt:mother.pt', 
                        'grandmother_id:mother.mother.pdgId',
                        'ggrandmother_id:mother.mother.mother.pdgId',                                        
                        'vertex_x:vertex.x', 
                        'vertex_y:vertex.y', 
                        'vertex_z:vertex.z', 
                        'mass:mass', 
                        'numOfDaughters:numberOfDaughters')
                ),
                selection = cms.string('status!=3 & (pdgId=13 | pdgId=-13) & pt>10'),
                Class = cms.string('reco::GenParticle')
            ),
            mc_electrons = cms.PSet(
                src = cms.InputTag("genParticles"),
                leaves = cms.PSet(
                    vars = cms.vstring('id:pdgId', 
                        'pt:pt', 
                        'px:px', 
                        'py:py', 
                        'pz:pz', 
                        'eta:eta',
                        'phi:phi',
                        'theta:theta',
                        'status:status', 
                        'mother_id:mother.pdgId',
                        'mother_pt:mother.pt', 
                        'grandmother_id:mother.mother.pdgId',
                        'ggrandmother_id:mother.mother.mother.pdgId',                                        
                        'vertex_x:vertex.x', 
                        'vertex_y:vertex.y', 
                        'vertex_z:vertex.z', 
                        'mass:mass', 
                        'numOfDaughters:numberOfDaughters')
                ),
                selection = cms.string('status!=3 & (pdgId=11 | pdgId=-11) & pt>10'),
                Class = cms.string('reco::GenParticle')
            ),
#            L1Triggerbits = cms.PSet(
#                src = cms.InputTag("gtDigis"),
#                leaves = cms.PSet(
#                    vars = cms.vstring('pass:decision' 
#                        )
#                ),
#                Class = cms.string('L1GlobalTriggerReadoutRecord')
#            ),
            tracks = cms.PSet(
#                src = cms.InputTag("ctfWithMaterialTracks"),
                src = cms.InputTag("generalTracks"),
                leaves = cms.PSet(
                    vars = cms.vstring('chi2:chi2', 
                        'ndof:ndof', 
                       'chg:charge', 
                        'pt:pt', 
                        'px:px', 
                        'py:py', 
                        'pz:pz', 
                        'eta:eta', 
                        'phi:phi', 
                        'theta:theta', 
                        'd0:d0', 
                        'dz:dz', 
                        'vx:vx', 
                        'vy:vy', 
                        'vz:vz', 
                        'numvalhits:numberOfValidHits', 
                        'numlosthits:numberOfLostHits', 
                        'd0Err:d0Error', 
                        'dzErr:dzError', 
                        'ptErr:ptError', 
                        'etaErr:etaError', 
                        'phiErr:phiError', 
                        'Nrechits:recHitsSize', 
                        'innerHitX:innerPosition.x', 
                        'innerHitY:innerPosition.y', 
                        'innerHitZ:innerPosition.z', 
                        'outerHitX:outerPosition.x', 
                        'outerHitY:outerPosition.y', 
                        'outerHitZ:outerPosition.z'
                                       )
                ),
                Class = cms.string('reco::Track')
            ),
            els = cms.PSet(
                src = cms.string('electrons'),
                leaves = cms.PSet(
                    basicKinematicLeaves,
                    vars = cms.vstring(#'id:leptonID', 
                        'gen_id:genLepton.pdgId',
                        'gen_phi:genLepton.phi',
                        'gen_pt:genLepton.pt',
                        'gen_pz:genLepton.pz',
                        'gen_px:genLepton.px',
                        'gen_py:genLepton.py',
                        'gen_eta:genLepton.eta',
                        'gen_theta:genLepton.theta',
                        'gen_et:genLepton.et',                       
                        'gen_mother_id:genLepton.mother.pdgId',
                        'gen_mother_phi:genLepton.mother.phi',
                        'gen_mother_pt:genLepton.mother.pt',
                        'gen_mother_pz:genLepton.mother.pz',
                        'gen_mother_px:genLepton.mother.px',
                        'gen_mother_py:genLepton.mother.py',
                        'gen_mother_eta:genLepton.mother.eta',
                        'gen_mother_theta:genLepton.mother.theta',
                        'gen_mother_et:genLepton.mother.et',                       
                        'tightId:electronID("eidTight")',
                        'looseId:electronID("eidLoose")',
                        'robustTightId:electronID("eidRobustTight")',
                        'robustLooseId:electronID("eidRobustLoose")',
                        'robustHighEnergyId:electronID("eidRobustHighEnergy")',
                        'cIso:caloIso', 
                        'tIso:trackIso', 
                        'ecalIso:ecalIso',
                        'hcalIso:hcalIso',
                        'chi2:gsfTrack.chi2', 
                        'class:classification', 
                        'charge:charge', 
                        'e:caloEnergy', 
                        'e_hadOverEm:hadronicOverEm', 
                        'eOverPIn:eSuperClusterOverP', 
                        'eSeedOverPOut:eSeedClusterOverPout', 
                        'eSCraw:superCluster.rawEnergy', 
                        'eSeed:superCluster.seed.energy', 
                        'sigmaEtaEta:scSigmaEtaEta',
                        'sigmaIEtaIEta:scSigmaIEtaIEta',
                        'scE1x5:scE1x5',
                        'scE2x5Max:scE2x5Max',
                        'scE5x5:scE5x5',
                        'dEtaIn:deltaEtaSuperClusterTrackAtVtx', 
                        'dPhiIn:deltaPhiSuperClusterTrackAtVtx', 
                        'dEtaOut:deltaEtaSeedClusterTrackAtCalo', 
                        'dPhiOut:deltaPhiSeedClusterTrackAtCalo', 
                        'numvalhits:gsfTrack.numberOfValidHits', 
                        'numlosthits:gsfTrack.numberOfLostHits', 
                        'numCluster:numberOfClusters', 
                        'tk_pt:gsfTrack.pt', 
                        'tk_phi:gsfTrack.phi', 
                        'tk_eta:gsfTrack.eta', 
                        'd0:gsfTrack.d0', 
                        'dz:gsfTrack.dz', 
                        'vx:gsfTrack.vx', 
                        'vy:gsfTrack.vy', 
                        'vz:gsfTrack.vz', 
                        'ndof:gsfTrack.ndof', 
                        'ptError:gsfTrack.ptError', 
                        'd0Error:gsfTrack.d0Error', 
                        'dzError:gsfTrack.dzError', 
                        'etaError:gsfTrack.etaError', 
                        'phiError:gsfTrack.phiError', 
                        'cpx:trackMomentumAtCalo.x', 
                        'cpy:trackMomentumAtCalo.y', 
                        'cpz:trackMomentumAtCalo.z', 
                        'vpx:trackMomentumAtVtx.x', 
                        'vpy:trackMomentumAtVtx.y', 
                        'vpz:trackMomentumAtVtx.z', 
                        'cx:TrackPositionAtCalo.x', 
                        'cy:TrackPositionAtCalo.y', 
                        'cz:TrackPositionAtCalo.z'#, 
                        #'IDRobust:electronIDRobust'
                        )
                ),
                Class = cms.string('pat::Electron')
            ),
            jets = cms.PSet(
                src = cms.string('jets'),
                leaves = cms.PSet(
                    basicKinematicLeaves,
                    vars = cms.vstring('parton_Id:genParton.pdgId',
                        'parton_motherId:genParton.mother.pdgId', 
                        'parton_pt:genParton.pt', 
                        'parton_phi:genParton.phi', 
                        'parton_eta:genParton.eta', 
                        'parton_Energy:genParton.energy', 
                        'parton_mass:genParton.mass', 
                        'gen_et:genJet.et', 
                        'gen_pt:genJet.pt', 
                        'gen_eta:genJet.eta', 
                        'gen_phi:genJet.phi', 
                        'gen_mass:genJet.mass', 
                        'gen_Energy:genJet.energy', 
#                        'gen_Id:genJet.pdgId', 
#                        'gen_motherID:genJet.mother.pdgId', 
                        'chgEmE:chargedEmEnergy', 
                        'chgHadE:chargedHadronEnergy', 
                        'chgMuE:chargedMuEnergy', 
                        'chg_Mult:chargedMultiplicity', 
                        'neutralEmE:neutralEmEnergy', 
                        'neutralHadE:neutralHadronEnergy', 
                        'neutral_Mult:neutralMultiplicity', 
                        'mu_Mult:muonMultiplicity', 
##                        'corr_fctr_def:correctionFactor(1)', 
##                        'corr_fctr_b:correctionFactor(4)', 
                        'emf:emEnergyFraction', 
                        'ehf:energyFractionHadronic', 
                        'n60:n60', 
                        'n90:n90', 
                        'area:towersArea', 
#                        'max_em:maxEInEmTowers#', 
#                        'max_had:maxEInHadTowers', 
                        'Energy:energy', 
                        'mass:mass'#,
#                        'nC_Energy:noCorrJet.energy',
#			'nC_mass:noCorrJet.mass',
#			'nC_et:noCorrJet.et',
#			'nC_pt:noCorrJet.pt',
#			'nC_px:noCorrJet.px',
#			'nC_py:noCorrJet.py',	
#			'nC_pz:noCorrJet.pz',	
#			'nC_eta:noCorrJet.eta',	
#			'nC_phi:noCorrJet.phi'#,	
			#'nC_theta:noCorrJet.theta'
			#'nC_emf:noCorrJet.emEnergyFraction',
                        #'nC_ehf:noCorrJet.energyFractionHadronic',
                        #'nC_n60:noCorrJet.n60',
                        #'nC_n90:noCorrJet.n90',
                        #'nC_area:noCorrJet.towersArea',
                        #'nC_max_em:noCorrJet.maxEInEmTowers',
                        #'nC_max_had:noCorrJet.maxEInHadTowers'               
                                       )
                ),
                Class = cms.string('pat::Jet')
            ),
            ccmuons = cms.PSet(
                src = cms.string('ccmuons'),
                leaves = cms.PSet(
                    basicKinematicLeaves
                ),
                Class = cms.string('pat::Muon')
            ),
            ccelectrons = cms.PSet(
                src = cms.string('ccelectrons'),
                leaves = cms.PSet(
                    basicKinematicLeaves
                ),
                Class = cms.string('pat::Electron')
            ),
            ccmets = cms.PSet(
                src = cms.string('ccmets'),
                leaves = cms.PSet(
                    vars = cms.vstring('et:et', 
                        'phi:phi', 
                        'px:px', 
                        'py:py', 
                        'status:status')
                ),
                Class = cms.string('pat::MET')
            )
         ),
        ComponentName = cms.string('CompleteNTupler'),
        useTFileService = cms.bool(True), ## false for EDM; true for non EDM

        #                string treeName="event"
        variablesPSet = cms.PSet(
            #use all the variables from the PSet above
            allVariables = cms.bool(True),
            treeName = cms.string('eventV')
        )
    )
)




