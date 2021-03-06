import FWCore.ParameterSet.Config as cms
from DQMServices.Core.DQMEDHarvester import DQMEDHarvester
from DQM.SiPixelPhase1Common.HistogramManager_cfi import *

SiPixelPhase1TrackClustersOnTrackCharge = DefaultHistoTrack.clone(
  name = "charge",
  title = "Corrected Cluster Charge (OnTrack)",
  range_min = 0, range_max = 200e3, range_nbins = 100,
  xlabel = "Charge (electrons)",

  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").saveAll(),
    Specification().groupBy("PXForward/PXDisk").saveAll(),
    StandardSpecification2DProfile,#what is below is only for the timing client

    Specification(OverlayCurvesForTiming).groupBy("PXBarrel/OnlineBlock")
         .groupBy("PXBarrel", "EXTEND_Y")
         .save(),
    Specification(OverlayCurvesForTiming).groupBy("PXForward/OnlineBlock")
          .groupBy("PXForward", "EXTEND_Y")
          .save(),
    
    Specification().groupBy("PXBarrel/PXLayer/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXBarrel/PXLayer", "EXTEND_X")
                   .save(),

    Specification().groupBy("PXForward/PXDisk/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXForward/PXDisk", "EXTEND_X")
                   .save(),

    Specification(PerLayer1D).groupBy("PXBarrel/Shell/PXLayer").save(),
    Specification(PerLayer1D).groupBy("PXForward/HalfCylinder/PXRing/PXDisk").save(),

    
    Specification(OverlayCurvesForTiming).groupBy("PXForward/PXDisk/OnlineBlock") # per-layer with history for online
                   .groupBy("PXForward/PXDisk", "EXTEND_Y")
                   .save(),
    Specification(OverlayCurvesForTiming).groupBy("PXBarrel/PXLayer/OnlineBlock") # per-layer with history for online
                   .groupBy("PXBarrel/PXLayer", "EXTEND_Y")
                   .save()
  )
)

SiPixelPhase1TrackClustersOnTrackSize = DefaultHistoTrack.clone(
  name = "size",
  title = "Total Cluster Size (OnTrack)",
  range_min = 0, range_max = 30, range_nbins = 30,
  xlabel = "size[pixels]",

  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").saveAll(),
    Specification().groupBy("PXForward/PXDisk").saveAll(),
    StandardSpecification2DProfile,

    Specification().groupBy("PXBarrel/PXLayer/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXBarrel/PXLayer", "EXTEND_X")
                   .save(),

    Specification().groupBy("PXForward/PXDisk/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXForward/PXDisk", "EXTEND_X")
                   .save(),

    Specification(PerLayer1D).groupBy("PXBarrel/Shell/PXLayer").save(),
    Specification(PerLayer1D).groupBy("PXForward/HalfCylinder/PXRing/PXDisk").save()

  )
)

SiPixelPhase1TrackClustersOnTrackShape = DefaultHistoTrack.clone(
  name = "shapeFilter",
  title = "Shape filter (OnTrack)",
  range_min = 0, range_max = 2, range_nbins = 2,
  xlabel = "shapeFilter",

  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").saveAll(),
    Specification().groupBy("PXForward/PXDisk").saveAll(),
    StandardSpecification2DProfile,

    Specification().groupBy("PXBarrel/PXLayer/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXBarrel/PXLayer", "EXTEND_X")
                   .save(),

    Specification().groupBy("PXForward/PXDisk/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXForward/PXDisk", "EXTEND_X")
                   .save(),

    Specification(PerLayer1D).groupBy("PXBarrel/Shell/PXLayer").save(),
    Specification(PerLayer1D).groupBy("PXForward/HalfCylinder/PXRing/PXDisk").save()

  )
)


SiPixelPhase1TrackClustersOnTrackNClusters = DefaultHistoTrack.clone(
  name = "clusters_ontrack",
  title = "Clusters_onTrack",
  range_min = 0, range_max = 30, range_nbins = 30,
  xlabel = "clusters",
  dimensions = 0,

  specs = VPSet(
 #   Specification().groupBy("PXBarrel/PXLayer" + "/DetId/Event") 
 #                  .reduce("COUNT") 
 #                  .groupBy("PXBarrel/PXLayer")
 #                  .saveAll(),
 #   Specification().groupBy("PXForward/PXDisk" + "/DetId/Event") 
 #                  .reduce("COUNT") 
 #                  .groupBy("PXForward/PXDisk")
 #                  .saveAll(),
 #   #StandardSpecificationInclusive_Num,
    StandardSpecificationTrend_Num,
    StandardSpecification2DProfile_Num,

    Specification().groupBy("PXBarrel/PXLayer/Event") #this will produce inclusive counts per Layer/Disk
                             .reduce("COUNT")    
                             .groupBy("PXBarrel/PXLayer")
                             .save(nbins=100, xmin=0, xmax=20000),

    Specification().groupBy("PXForward/PXDisk/Event")
                             .reduce("COUNT")    
                             .groupBy("PXForward/PXDisk/")
                             .save(nbins=100, xmin=0, xmax=10000),

    Specification().groupBy("PXBarrel/Event")
                   .reduce("COUNT")
                   .groupBy("PXBarrel")
                   .save(nbins=150, xmin=0, xmax=30000),

    Specification().groupBy("PXForward/Event")
                   .reduce("COUNT")
                   .groupBy("PXForward")
                   .save(nbins=150, xmin=0, xmax=30000),

    Specification().groupBy("PXAll/Event")
                   .reduce("COUNT")
                   .groupBy("PXAll")
                   .save(nbins=150, xmin=0, xmax=30000),

    Specification().groupBy("BX")
                   .groupBy("", "EXTEND_X").save(),

    Specification().groupBy("PXBarrel/PXLayer/Event")
                   .reduce("COUNT")
                   .groupBy("PXBarrel/PXLayer/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXBarrel/PXLayer","EXTEND_X")
                   .save(),

    Specification().groupBy("PXForward/PXDisk/Event")
                   .reduce("COUNT")
                   .groupBy("PXForward/PXDisk/Lumisection")
                   .reduce("MEAN")
                   .groupBy("PXForward/PXDisk","EXTEND_X")
                   .save(),

    #below is for timing client
    Specification(OverlayCurvesForTiming).groupBy("DetId/Event")
                    .reduce("COUNT")
                    .groupBy("PXForward/OnlineBlock")
                    .groupBy("PXForward", "EXTEND_Y")
                    .save(),

    Specification(OverlayCurvesForTiming).groupBy("DetId/Event")
                    .reduce("COUNT")
                    .groupBy("PXBarrel/OnlineBlock")
                    .groupBy("PXBarrel", "EXTEND_Y")
                    .save()
   
  )
)


SiPixelPhase1TrackClustersOnTrackPositionB = DefaultHistoTrack.clone(
  name = "clusterposition_zphi_ontrack",
  title = "Cluster_onTrack Positions",
  range_min   =  -60, range_max   =  60, range_nbins   = 300,
  range_y_min = -3.2, range_y_max = 3.2, range_y_nbins = 200,
  xlabel = "Global Z", ylabel = "Global \phi",
  dimensions = 2,
  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").save(),
    Specification().groupBy("").save(),
  )
)

SiPixelPhase1TrackClustersOnTrackPositionF = DefaultHistoTrack.clone(
  name = "clusterposition_xy_ontrack",
  title = "Cluster_onTrack Positions",
  xlabel = "Global X", ylabel = "Global Y",
  range_min   = -20, range_max   = 20, range_nbins   = 200,
  range_y_min = -20, range_y_max = 20, range_y_nbins = 200,
  dimensions = 2,
  specs = VPSet(
    Specification().groupBy("PXForward/PXDisk").save(),
  )
)

SiPixelPhase1TrackClustersNTracks = DefaultHistoTrack.clone(
  name = "ntracks",
  title = "Number of Tracks",
  xlabel = "All - Pixel - BPIX - FPIX",
  range_min = 1, range_max = 5, range_nbins = 4,
  dimensions = 1,
  specs = VPSet(
    Specification().groupBy("").save()
  )
)

SiPixelPhase1TrackClustersNTracksInVolume = DefaultHistoTrack.clone(
  name = "ntracksinpixvolume",
  title = "Number of Tracks in Pixel fiducial Volume",
  xlabel = "without hits - with hits",
  range_min = 0, range_max = 2, range_nbins = 2,
  dimensions = 1,
  specs = VPSet(
    Specification().groupBy("").save()
  )
)

SiPixelPhase1ClustersSizeVsEtaOnTrackOuter = DefaultHistoTrack.clone(
  name = "sizeyvseta_on_track_outer",
  title = "Cluster Size along Beamline vs. Track #eta (OnTrack) outer ladders",
  xlabel = "Track #eta",
  ylabel = "length [pixels]",
  range_min = -3.2, range_max  = 3.2, range_nbins   = 64,
  range_y_min =  0, range_y_max = 30, range_y_nbins = 30,
  dimensions = 2,
  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").save()
  )
)
SiPixelPhase1ClustersSizeVsEtaOnTrackInner = SiPixelPhase1ClustersSizeVsEtaOnTrackOuter.clone(
  name = "sizeyvseta_on_track_inner",
  title = "Cluster Size along Beamline vs. Track #eta (OnTrack) inner ladders",
)


SiPixelPhase1TrackClustersOnTrackSizeYOuter = SiPixelPhase1ClustersSizeVsEtaOnTrackOuter.clone(
  name = "sizey_on_track_outer",
  title = "Cluster Size along Beamline vs. prediction (OnTrack) outer ladders",
  xlabel = "prediction",
  ylabel = "length [pixels]",
  range_min = 0, range_max  = 30, range_nbins   = 60
)
SiPixelPhase1TrackClustersOnTrackSizeYInner = SiPixelPhase1TrackClustersOnTrackSizeYOuter.clone(
  name = "sizey_on_track_inner",
  title = "Cluster Size along Beamline vs. prediction (OnTrack) inner ladders",
)


SiPixelPhase1TrackClustersOnTrackSizeXOuter = SiPixelPhase1TrackClustersOnTrackSizeYOuter.clone(
  name = "sizex_on_track_outer",
  title = "Cluster Size along radial vs. prediction (OnTrack) outer ladders",
  range_min = 0, range_max  = 6, range_nbins   = 12,
  range_y_min =  0, range_y_max = 6, range_y_nbins = 6

)
SiPixelPhase1TrackClustersOnTrackSizeXInner = SiPixelPhase1TrackClustersOnTrackSizeXOuter.clone(
  name = "sizex_on_track_inner",
  title = "Cluster Size along radial vs. prediction (OnTrack) inner ladders",
)


SiPixelPhase1TrackClustersOnTrackSizeXYOuter = SiPixelPhase1TrackClustersOnTrackSizeYOuter.clone(
  name = "sizexy_on_track_outer",
  title = "prediction - Cluster Size x vs y (OnTrack) outer ladders",
  xlabel = "y diff",
  ylabel = "x diff",
  range_min = -6, range_max  = 6, range_nbins   = 24,
  range_y_min = -6, range_y_max = 6, range_y_nbins = 24 
)
SiPixelPhase1TrackClustersOnTrackSizeXYInner = SiPixelPhase1TrackClustersOnTrackSizeXYOuter.clone(
 name = "sizexy_on_track_inner",
 title = "prediction - Cluster Size x vs y (OnTrack) outer ladders"
)


SiPixelPhase1TrackClustersOnTrackChargeOuter = DefaultHistoTrack.clone(
  name = "chargeOuter",
  title = "Corrected Cluster Charge (OnTrack) outer ladders",
  range_min = 0, range_max = 150e3, range_nbins = 150,
  xlabel = "Charge (electrons)",

  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").save()
  )
)  
SiPixelPhase1TrackClustersOnTrackChargeInner = SiPixelPhase1TrackClustersOnTrackChargeOuter.clone(
  name = "chargeInner",
  title = "Corrected Cluster Charge (OnTrack) inner ladders"
)  

SiPixelPhase1TrackClustersOnTrackShapeOuter = DefaultHistoTrack.clone(
  name = "shapeFilterOuter",
  title = "Shape filter (OnTrack) Outer Ladders",
  range_min = 0, range_max = 2, range_nbins = 2,
  xlabel = "shapeFilter",
  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").save()
  )
)
SiPixelPhase1TrackClustersOnTrackShapeInner = SiPixelPhase1TrackClustersOnTrackShapeOuter.clone(
  name = "shapeFilterInner",
  title = "Shape filter (OnTrack) Inner Ladders",
)


SiPixelPhase1ClustersSizeVsEtaOnTrack = DefaultHistoTrack.clone(
  name = "sizeyvseta_on_track",
  title = "Cluster Size along Beamline vs. Cluster position #eta (OnTrack)",
  xlabel = "Cluster #eta",
  ylabel = "length [pixels]",
  range_min = -3.2, range_max  = 3.2, range_nbins   = 40,
  range_y_min =  0, range_y_max = 40, range_y_nbins = 40,
  dimensions = 2,
  specs = VPSet(
    Specification().groupBy("PXBarrel/PXLayer").save(),
    Specification().groupBy("PXBarrel").save()
  )
)


SiPixelPhase1TrackClustersConf = cms.VPSet(
  SiPixelPhase1TrackClustersOnTrackCharge,
  SiPixelPhase1TrackClustersOnTrackSize,
  SiPixelPhase1TrackClustersOnTrackShape,
  SiPixelPhase1TrackClustersOnTrackNClusters,
  SiPixelPhase1TrackClustersOnTrackPositionB,
  SiPixelPhase1TrackClustersOnTrackPositionF,

  SiPixelPhase1TrackClustersNTracks,
  SiPixelPhase1TrackClustersNTracksInVolume,

  SiPixelPhase1ClustersSizeVsEtaOnTrackOuter,
  SiPixelPhase1ClustersSizeVsEtaOnTrackInner,
  SiPixelPhase1TrackClustersOnTrackChargeOuter,
  SiPixelPhase1TrackClustersOnTrackChargeInner,

  SiPixelPhase1TrackClustersOnTrackShapeOuter,
  SiPixelPhase1TrackClustersOnTrackShapeInner,

  SiPixelPhase1TrackClustersOnTrackSizeXOuter,
  SiPixelPhase1TrackClustersOnTrackSizeXInner,
  SiPixelPhase1TrackClustersOnTrackSizeYOuter,
  SiPixelPhase1TrackClustersOnTrackSizeYInner,

  SiPixelPhase1TrackClustersOnTrackSizeXYOuter,
  SiPixelPhase1TrackClustersOnTrackSizeXYInner,

  SiPixelPhase1ClustersSizeVsEtaOnTrack
)


SiPixelPhase1TrackClustersAnalyzer = cms.EDAnalyzer("SiPixelPhase1TrackClusters",
        clusters = cms.InputTag("siPixelClusters"),
        tracks = cms.InputTag("generalTracks"),
        histograms = SiPixelPhase1TrackClustersConf,
        geometry = SiPixelPhase1Geometry
)

SiPixelPhase1TrackClustersHarvester = DQMEDHarvester("SiPixelPhase1Harvester",
        histograms = SiPixelPhase1TrackClustersConf,
        geometry = SiPixelPhase1Geometry
)

