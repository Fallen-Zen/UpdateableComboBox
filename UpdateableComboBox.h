#pragma once

#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QCompleter>

class UpdateableComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit UpdateableComboBox(QWidget *parent = Q_NULLPTR);
	void setItemModel(QAbstractItemModel *model);

private slots:
	void setTextIfCompleterIsClicked(const QString&);

private:
	QSortFilterProxyModel *filterProxyModel_;
	QCompleter *completer_;
};
