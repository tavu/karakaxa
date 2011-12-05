#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H
#include <Phonon/SeekSlider>
#include <QLabel>
#include <QSlider>
namespace views
{
    /*
     * this is amarok code
    */
    class Slider : public QSlider
    {
        Q_OBJECT

        public:
            explicit Slider( Qt::Orientation, uint max = 0, QWidget* parent = 0 );

            virtual void setValue( int );

        signals:
            //we emit this when the user has specifically changed the slider
            //so connect to it if valueChanged() is too generic
            //Qt also emits valueChanged( int )
            void sliderReleased( int );

        protected:
            virtual void wheelEvent( QWheelEvent* );
            virtual void mouseMoveEvent( QMouseEvent* );
            virtual void mouseReleaseEvent( QMouseEvent* );
            virtual void mousePressEvent( QMouseEvent* );
            virtual void slideEvent( QMouseEvent* );
            QRect sliderHandleRect( const QRect &slider, qreal percent ) const;
            virtual void resizeEvent( QResizeEvent * ) { m_needsResize = true; }

            bool m_sliding;
//             bool m_usingCustomStyle;

            static const int s_borderWidth = 6;
            static const int s_borderHeight = 6;

            static const int s_sliderInsertX = 5;
            static const int s_sliderInsertY = 5;

        private:

            bool m_outside;
            int  m_prevValue;
            bool m_needsResize;

            QPixmap m_topLeft;
            QPixmap m_topRight;
            QPixmap m_top;
            QPixmap m_bottomRight;
            QPixmap m_right;
            QPixmap m_bottomLeft;
            QPixmap m_bottom;
            QPixmap m_left;

            Q_DISABLE_COPY( Slider )
    };

    

    class sliderWidget :public QWidget
    {
        Q_OBJECT
        public:
            sliderWidget(QWidget *parent=0);

        private slots:
            void totalTimeChanged(qint64 time);
            void updateTime(int);
            void seek(int );
            void setSliderValue(qint64 time);
            void trackChanged();

        private:
//             Phonon::SeekSlider *slider;
            Slider *slider;
            QLabel *right;
            QLabel *left;
    };


};

#endif