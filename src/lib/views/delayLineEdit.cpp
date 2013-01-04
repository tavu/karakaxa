#include"delayLineEdit.h"
#include <QTimer>
#define DEFAULT_DELAY 300

views::delayLineEdit::delayLineEdit(QWidget* parent): KLineEdit(parent)
{
	timer.setSingleShot(true);
	setDelay(DEFAULT_DELAY);
	connect(&timer, SIGNAL(timeout()), this, SLOT(delayReached()));
	connect(this,SIGNAL(textEdited(const QString &) ),this,SLOT(textChangedSlot()) );
	connect(this,SIGNAL(returnPressed() ),this,SLOT(delayReached()) );
	connect(this,SIGNAL(clearButtonClicked()),this,SLOT(delayReached()) );
}

void views::delayLineEdit::delayReached()
{	
	timer.stop();
	QString t=text();
	emit textChangedDelay(t);
}

void views::delayLineEdit::textChangedSlot()
{
	timer.start(_delay);
}

void views::delayLineEdit::setText(const QString& s)
{
    KLineEdit::setText(s);
	if(_delay>0)
	{
		delayReached();
	}
}

void views::delayLineEdit::clear()
{
    KLineEdit::clear();
	if(_delay>0)
	{
		delayReached();
	}
}

