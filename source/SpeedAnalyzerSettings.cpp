#include "SpeedAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


SpeedAnalyzerSettings::SpeedAnalyzerSettings()
: mInputChannel( UNDEFINED_CHANNEL )
{
  mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
  mInputChannelInterface->SetTitleAndTooltip( "Speed", "Standard Speed Pulse" );
  mInputChannelInterface->SetChannel( mInputChannel );

  AddInterface( mInputChannelInterface.get() );

  AddExportOption( 0, "Export as text/csv file" );
  AddExportExtension( 0, "text", "txt" );
  AddExportExtension( 0, "csv", "csv" );

  ClearChannels();
  AddChannel( mInputChannel, "Speed", false );
}

SpeedAnalyzerSettings::~SpeedAnalyzerSettings()
{
}

bool SpeedAnalyzerSettings::SetSettingsFromInterfaces()
{
  mInputChannel = mInputChannelInterface->GetChannel();

  ClearChannels();
  AddChannel( mInputChannel, "Speed Pulse", true );

  return true;
}

void SpeedAnalyzerSettings::UpdateInterfacesFromSettings()
{
  mInputChannelInterface->SetChannel( mInputChannel );
}

void SpeedAnalyzerSettings::LoadSettings( const char* settings )
{
  SimpleArchive text_archive;
  text_archive.SetString( settings );

  text_archive >> mInputChannel;

  ClearChannels();
  AddChannel( mInputChannel, "Speed Pulse", true );

  UpdateInterfacesFromSettings();
}

const char* SpeedAnalyzerSettings::SaveSettings()
{
  SimpleArchive text_archive;

  text_archive << mInputChannel;

  return SetReturnString( text_archive.GetString() );
}
