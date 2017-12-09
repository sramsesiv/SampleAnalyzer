#include "ServoAnalyzer.h"
#include "ServoAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

ServoAnalyzer::ServoAnalyzer()
:	Analyzer2(),  
	mSettings( new ServoAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

ServoAnalyzer::~ServoAnalyzer()
{
	KillThread();
}

void ServoAnalyzer::SetupResults()
{
	mResults.reset( new ServoAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void ServoAnalyzer::WorkerThread()
{
  Frame frame;
	mSampleRateHz = GetSampleRate();

	mServo = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mServo->GetBitState() == BIT_LOW )
  {
		mServo->AdvanceToNextEdge();
  }

  for ( ; ; )
  {
    frame.mStartingSampleInclusive = mServo->GetSampleNumber();

    mServo->AdvanceToNextEdge(); //falling edge -- end of the pulse
    S64 endsample = mServo->GetSampleNumber();
    mServo->AdvanceToNextEdge(); // rising edge -- start of next pulse
    frame.mEndingSampleInclusive = mServo->GetSampleNumber();

    double pulsetime_ms = 1000.0 * (1000.0/mSampleRateHz) * (endsample - frame.mStartingSampleInclusive);
    U64 data = pulsetime_ms;

    frame.mData1 = data;
    frame.mFlags = 0;

    mResults->AddFrame( frame );
    mResults->CommitResults();
    ReportProgress( frame.mEndingSampleInclusive );
  }
}

bool ServoAnalyzer::NeedsRerun()
{
	return false;
}

U32 ServoAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 ServoAnalyzer::GetMinimumSampleRateHz()
{
	return 5000;
}

const char* ServoAnalyzer::GetAnalyzerName() const
{
	return "Servo Pulse";
}

const char* GetAnalyzerName()
{
	return "Servo Pulse";
}

Analyzer* CreateAnalyzer()
{
	return new ServoAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
