#include "twoDRobotModel.h"

#include "src/robotModel/twoD/parts/twoDDisplay.h"
#include "src/robotModel/twoD/parts/twoDButtons.h"
#include "src/robotModel/parts/trikInfraredSensor.h"
#include "src/robotModel/parts/trikSonarSensor.h"
#include "src/robotModel/parts/trikLed.h"

#include <interpreterBase/robotModel/robotParts/buttons.h>
#include <interpreterBase/robotModel/robotParts/speaker.h>
#include <interpreterBase/robotModel/robotParts/motor.h>
#include <interpreterBase/robotModel/robotParts/encoderSensor.h>
#include <interpreterBase/robotModel/robotParts/touchSensor.h>
#include <interpreterBase/robotModel/robotParts/rangeSensor.h>
#include <interpreterBase/robotModel/robotParts/lightSensor.h>
#include <interpreterBase/robotModel/robotParts/colorSensorBlue.h>
#include <interpreterBase/robotModel/robotParts/colorSensorFull.h>
#include <interpreterBase/robotModel/robotParts/colorSensorGreen.h>
#include <interpreterBase/robotModel/robotParts/colorSensorPassive.h>
#include <interpreterBase/robotModel/robotParts/colorSensorRed.h>

using namespace trikKitInterpreter::robotModel;
using namespace trikKitInterpreter::robotModel::twoD;
using namespace interpreterBase::robotModel;

TwoDRobotModel::TwoDRobotModel(interpreterBase::robotModel::RobotModelInterface const &realModel)
	: mRealModel(realModel)
{
	for (auto port : realModel.availablePorts()) {
		addAllowedConnection(port, realModel.allowedDevices(port));
	}
}

QString TwoDRobotModel::name() const
{
	return "TrikTwoDRobotModel" + mRealModel.name();
}

QString TwoDRobotModel::friendlyName() const
{
	QRegExp versionRegExp("\\(.*\\)");
	int const pos = versionRegExp.indexIn(mRealModel.friendlyName());
	if (pos == -1) {
		return tr("2D Model");
	}

	return tr("2D Model") + " " + versionRegExp.capturedTexts().at(0);
}

robotParts::Device *TwoDRobotModel::createDevice(PortInfo const &port, DeviceInfo const &deviceInfo)
{
	if (deviceInfo.isA<robotParts::Display>()) {
		auto display = new parts::Display(deviceInfo, port, *engine());

		/// @todo Why not do this in display constructor?!
		display->attachToPaintWidget();

		return display;
	}

	if (deviceInfo.isA<robotParts::Buttons>()) {
		return new parts::TwoDButtons(deviceInfo, port, *engine());
	}

	return twoDModel::robotModel::TwoDRobotModel::createDevice(port, deviceInfo);
}
