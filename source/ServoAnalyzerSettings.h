#ifndef SERVO_ANALYZER_SETTINGS
#define SERVO_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class ServoAnalyzerSettings : public AnalyzerSettings
{
public:
	ServoAnalyzerSettings();
	virtual ~ServoAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
};

#endif //SERVO_ANALYZER_SETTINGS
