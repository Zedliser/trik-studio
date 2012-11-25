#include <QMessageBox>
#include "editPropertiesDialog.h"
#include "ui_editPropertiesDialog.h"

using namespace qReal;

EditPropertiesDialog::EditPropertiesDialog(QWidget *parent) :
	ManagedClosableDialog(parent, false),
	mUi(new Ui::EditPropertiesDialog)
{
	mUi->setupUi(this);
}

EditPropertiesDialog::~EditPropertiesDialog()
{
	delete mUi;
}

void EditPropertiesDialog::setupDefaultValues()
{
	mUi->attributeTypeEdit->setText(mInterperterEditorManager->getTypeName(mId, mPropertyName));
	mUi->defaultValueEdit->setText(mInterperterEditorManager->getDefaultPropertyValue(mId, mPropertyName));
	mUi->displayedNameEdit->setText(mInterperterEditorManager->propertyDisplayedName(mId, mPropertyName));
}

void EditPropertiesDialog::ok()
{
	if (mUi->attributeTypeEdit->text().isEmpty() || mUi->displayedNameEdit->text().isEmpty()) {
		QMessageBox::critical(this, tr("Error"), tr("All required properties should be filled!"));
	} else {
		mInterperterEditorManager->updateProperties(mId, mPropertyName, mUi->attributeTypeEdit->text(), mUi->defaultValueEdit->text(), mUi->displayedNameEdit->text());
		if (mSelectedItem != NULL) {
			mSelectedItem->setText(mInterperterEditorManager->propertyDisplayedName(mId, mPropertyName));
		}
		forceClose();
	}
}

void EditPropertiesDialog::init(QListWidgetItem *selectedItem, EditorManagerInterface* interperterEditorManager, Id const &id, QString const &propertyName)
{
	mInterperterEditorManager = interperterEditorManager;
	mId = id;
	mPropertyName = mInterperterEditorManager->getPropertyNameByDisplayedName(mId, propertyName);
	mSelectedItem = selectedItem;
	setWindowTitle(tr("Properties editor") + ": " + propertyName);
	setupDefaultValues();

	connect(mUi->okPushButton, SIGNAL(clicked()), this, SLOT(ok()));
}
