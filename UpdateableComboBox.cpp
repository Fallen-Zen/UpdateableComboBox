#include "UpdateableComboBox.h"
#include <QStandardItemModel>
#include <QLineEdit>

UpdateableComboBox::UpdateableComboBox(QWidget *parent) :
	QComboBox{parent},
	filterProxyModel_{new QSortFilterProxyModel{this}},
	completer_{new QCompleter{this}}
{
	this->setFocusPolicy(Qt::StrongFocus);
	this->setEditable(true);
    this->completer_->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	this->filterProxyModel_->setFilterCaseSensitivity(Qt::CaseInsensitive);
	this->setCompleter(this->completer_);

	connect(
		this->lineEdit(),
		SIGNAL(textEdited(const QString&)),
		this->filterProxyModel_,
		SLOT(setFilterFixedString(const QString&))
	);

	connect(
		this->completer_,
		SIGNAL(activated(const QString&)),
		this,
		SLOT(setTextIfCompleterIsClicked(const QString&))
	);
}

void UpdateableComboBox::setItemModel(QAbstractItemModel *model)
{
	this->setModel(model);
	this->filterProxyModel_->setSourceModel(model);
	this->completer_->setModel(this->filterProxyModel_);
}

void UpdateableComboBox::setTextIfCompleterIsClicked(const QString& text)
{
	if ( ! text.isEmpty())
	{
		const auto& index = this->findText(text);
		this->setCurrentIndex(index);
	}
}
