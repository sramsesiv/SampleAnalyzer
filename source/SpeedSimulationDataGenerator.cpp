#include "SpeedSimulationDataGenerator.h"
#include "SpeedAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

SpeedSimulationDataGenerator::SpeedSimulationDataGenerator()
:	mSpeedText( "My first analyzer, woo hoo!" ),
	mStringIndex( 0 )
{
}

SpeedSimulationDataGenerator::~SpeedSimulationDataGenerator()
{
}

void SpeedSimulationDataGenerator::Initialize( U32 simulation_sample_rate, SpeedAnalyzerSettings* settings )
{
	mSimulationSampleRateHz = simulation_sample_rate;
	mSettings = settings;

	mSpeedSimulationData.SetChannel( mSettings->mInputChannel );
	mSpeedSimulationData.SetSampleRate( simulation_sample_rate );
	mSpeedSimulationData.SetInitialBitState( BIT_LOW );
}

U32 SpeedSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mSpeedSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateSpeedByte();
	}

	*simulation_channel = &mSpeedSimulationData;
	return 1;
}

void SpeedSimulationDataGenerator::CreateSpeedByte()
{
	U8 byte = mSpeedText[ mStringIndex ];
  double speedRPM_Hz = ((double)byte * 10.0) / 60.0;
  U32 periodsamples = ((double)mSimulationSampleRateHz) / speedRPM_Hz;
  U32 pulsesamples = ((double)mSimulationSampleRateHz / 200.0); // Hard-code to 200 Hz
	mStringIndex++;
	if( mStringIndex == mSpeedText.size() )
		mStringIndex = 0;

  mSpeedSimulationData.TransitionIfNeeded( BIT_HIGH ); //high-going edge for start of pulse

	mSpeedSimulationData.Advance( pulsesamples );

  mSpeedSimulationData.TransitionIfNeeded( BIT_LOW ); //low-going edge for end of pulse
	mSpeedSimulationData.Advance( periodsamples-pulsesamples ); // end of period
}
