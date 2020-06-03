#!/bin/tcsh

# parse command line arguments
export RUNPERIOD=$1
if [ -z "$RUNPERIOD" ]; then
    echo Need to pass run period as first argument!
    exit 1
endif

export VERSION=$2
if [ -z "$VERSION" ]; then
    echo Need to pass data version as second argument!
    exit 1
endif

export RUN=$3
if [ -z "$RUN" ]; then
    echo Need to pass run number as third argument!
    exit 1
endif

# configure environment
export DATATYPE=recon
export INPUTDIR=/cache/halld/$RUNPERIOD/$DATATYPE
export INPUT_SMALLFILE_DIR=/work/halld2/recon/$RUNPERIOD
export OUTPUTDIR=/work/halld2/data_monitoring/${RUNPERIOD}/${DATATYPE}_ver${VERSION}
export ROOTOUTPUTDIR=/work/halld/data_monitoring/${RUNPERIOD}/${DATATYPE}_ver${VERSION}/rootfiles
export ARGS=" -R $RUN -E -v $RUNPERIOD,$VERSION --merge-trees=tree_bcal_hadronic_eff,tree_fcal_hadronic_eff,tree_sc_eff,tree_tof_eff,tree_trackeff,tree_TS_scaler --merge-skims=BCAL-LED,bigevents,FCAL-LED,sync --merged-root-output-dir=$ROOTOUTPUTDIR "


# Load standard environment for ROOT
source /home/gxproj5/env_monitoring_launch.sh

export MONITORING_HOME=/home/gxproj5/monitoring/process
source $MONITORING_HOME/monitoring_env.sh
export MONITORING_LIBDIR=$MONITORING_HOME/lib
export MONITORING_LOGDIR=$MONITORING_HOME/log

# run the script
cd $MONITORING_HOME

./process_new_offline_data.py $ARGS ver$VERSION $INPUTDIR $INPUT_SMALLFILE_DIR $OUTPUTDIR
