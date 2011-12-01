#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H
#include <Phonon/SeekSlider>
#include <QLabel>
#include<QTimer>
namespace views
{

    class sliderWidget :public QWidget
    {
        Q_OBJECT
        public:
            sliderWidget(QWidget *parent=0);
            
        private slots:
            void updateTime();
            
        private:
            Phonon::SeekSlider *slider;
            QLabel *right;
            QLabel *left;
            QTimer timer;

    };

};

#endif