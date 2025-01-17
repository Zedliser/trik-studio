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

#include "qRealFileDialog.h"

#include <qrkernel/settingsManager.h>

using namespace utils;

QString QRealFileDialog::getOpenFileName(const QString &id
		, QWidget *parent
		, const QString &caption
		, const QString &dir
		, const QString &filter
		, QString *selectedFilter
		, QFileDialog::Options options)
{
	const QString lastDir = lastSelectedDirectory(id, dir);
	QString lastSelectedFilter;
	if (selectedFilter) {
		lastSelectedFilter = *selectedFilter;
	} else {
		lastSelectedFilter = QRealFileDialog::lastSelectedFilter(id, filter.split(";;")[0]);
	}
	auto result = QFileDialog::getOpenFileName(parent, caption, lastDir, filter, &lastSelectedFilter, options);
	if (selectedFilter) {
		*selectedFilter = lastSelectedFilter;
	}
	saveState(id, directoryOf(result), lastSelectedFilter);
	return result;
}

QString QRealFileDialog::getSaveFileName(const QString &id
		, QWidget *parent
		, const QString &caption
		, const QString &dir
		, const QString &filter
		, const QString &defaultFile
		, QString *selectedFilter
		, QFileDialog::Options options)
{
	const QString lastDir = lastSelectedDirectory(id, dir) + "/" + defaultFile;
	QString lastSelectedFilter;
	if (selectedFilter) {
		lastSelectedFilter = *selectedFilter;
	} else {
		lastSelectedFilter = QRealFileDialog::lastSelectedFilter(id, filter.split(";;")[0]);
	}
	const QString result = QFileDialog::getSaveFileName(parent, caption, lastDir, filter, selectedFilter, options);
	if (selectedFilter) {
		*selectedFilter = lastSelectedFilter;
	}
	saveState(id, directoryOf(result), lastSelectedFilter);
	return result;
}

QString QRealFileDialog::getExistingDirectory(const QString &id
		, QWidget *parent
		, const QString &caption
		, const QString &dir
		, QFileDialog::Options options)
{
	const QString lastDir = lastSelectedDirectory(id, dir);
	const QString result = QFileDialog::getExistingDirectory(parent, caption, lastDir, options);
	saveState(id, result, "");
	return result;
}

QStringList QRealFileDialog::getOpenFileNames(const QString &id
		, QWidget *parent
		, const QString &caption
		, const QString &dir
		, const QString &filter
		, QString *selectedFilter
		, QFileDialog::Options options)
{
	const QString lastDir = lastSelectedDirectory(id, dir);
	QString lastSelectedFilter;
	if (selectedFilter) {
		lastSelectedFilter = *selectedFilter;
	} else {
		lastSelectedFilter = QRealFileDialog::lastSelectedFilter(id, filter.split(";;")[0]);
	}
	const QStringList result = QFileDialog::getOpenFileNames(parent, caption, lastDir, filter, selectedFilter, options);

	if (selectedFilter) {
		*selectedFilter = lastSelectedFilter;
	}

	if (!result.isEmpty()) {
		saveState(id, directoryOf(result[0]), lastSelectedFilter);
	}

	return result;
}

QString QRealFileDialog::lastSelectedDirectory(const QString &id, const QString &defaultDirectory)
{
	return qReal::SettingsManager::value(lastDirectoryKey(id), defaultDirectory).toString();
}

QString QRealFileDialog::lastSelectedFilter(const QString &id, const QString &defaultFilter)
{
	return qReal::SettingsManager::value(lastFilterKey(id), defaultFilter).toString();
}

QString QRealFileDialog::lastDirectoryKey(const QString &id)
{
	return id + "FileDialogLastDir";
}

QString QRealFileDialog::lastFilterKey(const QString &id)
{
	return id + "FileDialogLastFilter";
}

QString QRealFileDialog::directoryOf(const QString &file)
{
	if (file.isEmpty()) {
		return QString();
	}

	return QFileInfo(file).absoluteDir().absolutePath();
}

void QRealFileDialog::saveState(const QString &id, const QString &directory, const QString &selectedFilter)
{
	if (!directory.isEmpty()) {
		qReal::SettingsManager::setValue(lastDirectoryKey(id), directory);
		qReal::SettingsManager::setValue(lastFilterKey(id), selectedFilter);
	}
}
