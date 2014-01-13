#pragma once

#include <QtCore/QObject>

#include "interpreterBase/robotModel/portInfo.h"
#include "interpreterBase/robotModel/robotParts/pluggableDevice.h"

#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace interpreterBase {
namespace robotModel {

class ROBOTS_INTERPRETER_BASE_EXPORT ConfigurationInterface : public QObject
{
	Q_OBJECT

public:
	enum PortDirection {
		defaultDirection
		, input
		, output
	};

	virtual ~ConfigurationInterface() {}

	virtual void configureDevice(robotParts::PluggableDevice const &device, PortInfo const &port) = 0;

	virtual void lockConfiguring() = 0;
	virtual void unlockConfiguring() = 0;

	/// Returns configured device on a given port or NULL if no device is configured there.
	virtual robotParts::PluggableDevice *pluggableDevice(
			PortInfo const &port
			, PortDirection direction = defaultDirection) const = 0;

	// TODO: Implement some convenience methods that cast generic PluggableDevice to desired sensor/motor type.

	virtual void clearDevice(PortInfo const &port) = 0;

signals:
	void allDevicesConfigured();
};

}
}
