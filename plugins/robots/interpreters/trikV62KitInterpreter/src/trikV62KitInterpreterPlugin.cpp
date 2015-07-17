/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "trikV62KitInterpreterPlugin.h"

//#include <QtWidgets/QApplication>
//#include <QtWidgets/QLineEdit>

//#include <twoDModel/engine/twoDModelEngineFacade.h>
//#include <qrkernel/settingsManager.h>
//#include <qrkernel/settingsListener.h>

using namespace trik;
//using namespace qReal;

//const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
//const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

#include "robotModel/real/trikV62RealRobotModel.h"
#include "robotModel/twoD/trikV62TwoDRobotModel.h"

TrikV62KitInterpreterPlugin::TrikV62KitInterpreterPlugin()
	: TrikKitInterpreterPluginBase()
{
	const auto realRobotModel = new robotModel::real::RealRobotModel(kitId(), "trikKitRobot");
	const auto twoDRobotModel = new robotModel::twoD::TwoDRobotModel(*realRobotModel);
	const auto blocksFactory = new blocks::TrikV62BlocksFactory();
	initKitInterpreterPluginBase(realRobotModel, twoDRobotModel, blocksFactory);
}

//	  mRealRobotModel(kitId(), "trikKitRobot") // todo: somewhere generate robotId for each robot
//	, mTwoDRobotModel(mRealRobotModel)
//	, mBlocksFactory(new blocks::TrikV62BlocksFactory)
//{
//	mTwoDRobotModel.setWheelPorts("M4", "M3");
//	auto modelEngine = new twoDModel::engine::TwoDModelEngineFacade(mTwoDRobotModel);

//	mTwoDRobotModel.setEngine(modelEngine->engine());
//	mTwoDModel.reset(modelEngine);

//	mAdditionalPreferences = new TrikAdditionalPreferences({ mRealRobotModel.name() });
//}

//TrikV62KitInterpreterPlugin::~TrikV62KitInterpreterPlugin()
//{
//	if (mOwnsAdditionalPreferences) {
//		delete mAdditionalPreferences;
//	}

//	if (mOwnsBlocksFactory) {
//		delete mBlocksFactory;
//	}
//}

//void TrikV62KitInterpreterPlugin::init(const kitBase::KitPluginConfigurator &configurator)
//{
//	connect(&configurator.eventsForKitPlugin()
//			, &kitBase::EventsForKitPluginInterface::robotModelChanged
//			, [this](const QString &modelName) { mCurrentlySelectedModelName = modelName; });

//	qReal::gui::MainWindowInterpretersInterface &interpretersInterface
//			= configurator.qRealConfigurator().mainWindowInterpretersInterface();

//	mTwoDModel->init(configurator.eventsForKitPlugin()
//			, configurator.qRealConfigurator().systemEvents()
//			, configurator.qRealConfigurator().logicalModelApi()
//			, interpretersInterface
//			, configurator.interpreterControl());

//	mRealRobotModel.setErrorReporter(*interpretersInterface.errorReporter());
//	mTwoDRobotModel.setErrorReporter(*interpretersInterface.errorReporter());

//	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged
//			, &mRealRobotModel, &robotModel::real::RealRobotModel::rereadSettings);
//	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged
//			, &mTwoDRobotModel, &robotModel::twoD::TwoDRobotModel::rereadSettings);
//}

//QString TrikV62KitInterpreterPlugin::kitId() const
//{
//	return "trikV62Kit";
//}

//QString TrikV62KitInterpreterPlugin::friendlyKitName() const
//{
//	return tr("TRIK (new case)");
//}

//QList<kitBase::robotModel::RobotModelInterface *> TrikV62KitInterpreterPlugin::robotModels()
//{
//	return {&mRealRobotModel, &mTwoDRobotModel};
//}

//kitBase::blocksBase::BlocksFactoryInterface *TrikV62KitInterpreterPlugin::blocksFactoryFor(
//		const kitBase::robotModel::RobotModelInterface *model)
//{
//	Q_UNUSED(model);
//	mOwnsBlocksFactory = false;
//	return mBlocksFactory;
//}

//kitBase::robotModel::RobotModelInterface *TrikV62KitInterpreterPlugin::defaultRobotModel()
//{
//	return &mTwoDRobotModel;
//}

//QList<kitBase::AdditionalPreferences *> TrikV62KitInterpreterPlugin::settingsWidgets()
//{
//	mOwnsAdditionalPreferences = false;
//	return {mAdditionalPreferences};
//}

//QWidget *TrikV62KitInterpreterPlugin::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
//{
//	return model.name().toLower().contains("twod")
//			? nullptr
//			: produceIpAddressConfigurer();
//}

//QList<qReal::ActionInfo> TrikV62KitInterpreterPlugin::customActions()
//{
//	return {};
//}

//QList<HotKeyActionInfo> TrikV62KitInterpreterPlugin::hotKeyActions()
//{
//	return {};
//}

//QString TrikV62KitInterpreterPlugin::defaultSettingsFile() const
//{
//	return ":/trikDefaultSettings.ini";
//}

//QIcon TrikV62KitInterpreterPlugin::iconForFastSelector(
//		const kitBase::robotModel::RobotModelInterface &robotModel) const
//{
//	return &robotModel == &mRealRobotModel
//			? QIcon(":/icons/switch-real-trik.svg")
//			: &robotModel == &mTwoDRobotModel
//					? QIcon(":/icons/switch-2d.svg")
//					: QIcon();
//}

//kitBase::DevicesConfigurationProvider *TrikV62KitInterpreterPlugin::devicesConfigurationProvider()
//{
//	return &mTwoDModel->devicesConfigurationProvider();
//}

//QWidget *TrikV62KitInterpreterPlugin::produceIpAddressConfigurer()
//{
//	QLineEdit * const quickPreferences = new QLineEdit;
//	quickPreferences->setPlaceholderText(tr("Enter robot`s IP-address here..."));
//	auto updateQuickPreferences = [quickPreferences]() {
//		quickPreferences->setText(qReal::SettingsManager::value("TrikTcpServer").toString());
//	};
//	updateQuickPreferences();
//	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged, updateQuickPreferences);
//	qReal::SettingsListener::listen("TrikTcpServer", updateQuickPreferences);
//	connect(quickPreferences, &QLineEdit::textChanged, [](const QString &text) {
//		qReal::SettingsManager::setValue("TrikTcpServer", text);
//	});
//	return quickPreferences;
//}