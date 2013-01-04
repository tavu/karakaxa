#ifndef DELAYTIMEEDIT_H
#define DELAYTIMEEDIT_H

#include <klineedit.h>
#include<QTimer>

namespace views
{

class delayLineEdit :public KLineEdit
{
	Q_OBJECT
	public:
		delayLineEdit(QWidget *parent);
		
		void setDelay(int d)
		{
			_delay=d;
		}
		
		int delay()
		{
			return _delay;
		}
		
	private:
		QTimer timer;
		int _delay;

	public slots:
		void setText(const QString &s);
		void clear();

	private slots:
		void textChangedSlot();
		void delayReached();
		
	signals:
		void textChangedDelay(const QString &);
		
};
	
};
#endif