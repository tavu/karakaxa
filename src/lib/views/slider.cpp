#include"slider.h"
#include<QHBoxLayout>
#include"viewsFunc.h"
#include"../core/core.h"
#include <Phonon/MediaObject>
#include<QMouseEvent>

views::sliderWidget::sliderWidget(QWidget* parent): QWidget(parent)
{
//     slider = new Phonon::SeekSlider(this);
//     slider->setMediaObject(core::engine->getMediaObject() );
//     slider->setIconVisible(false);

    slider=new Slider(Qt::Horizontal,0,this);
    connect(slider,SIGNAL(sliderReleased(int)),this,SLOT(seek(int)) );
    
    left=new QLabel(this);
    right=new QLabel(this);    
    left->setText("     ");
    right->setText("     ");

    core::engine->getMediaObject()->setTickInterval(500);    
    
    connect(core::engine->getMediaObject(),SIGNAL(totalTimeChanged(qint64)),this,SLOT(totalTimeChanged(qint64)) );
    connect(core::engine->getMediaObject(),SIGNAL(tick(qint64)),this,SLOT(setSliderValue(qint64)) );
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(updateTime(int)));
    connect(core::engine,SIGNAL(trackChanged(QString)),this,SLOT(trackChanged()));
    
    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->addWidget(left);
    layout->addWidget(slider);
    layout->addWidget(right);    
}

void views::sliderWidget::trackChanged()
{
    slider->setValue( 0 );
}


void views::sliderWidget::setSliderValue(qint64 time)
{
    if(slider->maximum()!=0)
    {
        slider->setValue( (int)time );
    }
    else
    {
        updateTime((int)time );
    }
}


void views::sliderWidget::totalTimeChanged(qint64 time)
{
    slider->setMaximum((int) (time) );
    slider->setValue(0);
    updateTime(0);
}


void views::sliderWidget::updateTime(int currentTime)
{
//     Phonon::MediaObject *m=core::engine->getMediaObject();
    int totalTime=(int)( slider->maximum()/1000 );
    currentTime /=1000;
    left->setText(views::prettyLength(currentTime));
    if(totalTime!=0)
    {
        totalTime -=currentTime;
    }

    QString s=views::prettyLength(totalTime);
    s.prepend('-');
    
    right->setText(s);

    
}

void views::sliderWidget::seek(int pos)
{    
    Phonon::MediaObject *m=core::engine->getMediaObject();

    if(m->isSeekable() )
    {
        m->seek(pos);
    }
}


views::Slider::Slider( Qt::Orientation orientation, uint max, QWidget *parent )
    : QSlider( orientation, parent )
    , m_sliding( false )
    , m_outside( false )
    , m_prevValue( 0 )
    , m_needsResize( true )
{
    setMouseTracking( true );
    setRange( 0, max );
    setAttribute( Qt::WA_NoMousePropagation, true );
    setAttribute( Qt::WA_Hover, true );
    if ( orientation == Qt::Vertical )
    {
        setInvertedAppearance( true );
        setInvertedControls( true );
    }
}

QRect views::Slider::sliderHandleRect( const QRect &slider, qreal percent ) const
{
    QRect rect;
    const bool inverse = ( orientation() == Qt::Horizontal ) ?
                         ( invertedAppearance() != (layoutDirection() == Qt::RightToLeft) ) :
                         ( !invertedAppearance() );

    if ( inverse )
    {
            percent = 1.0 - percent;
    }
    const int handleSize = style()->pixelMetric( QStyle::PM_SliderControlThickness );
    rect = QRect( 0, 0, handleSize, handleSize );
    rect.moveTo( slider.x() + qRound( ( slider.width() - handleSize ) * percent ), slider.y() + 1 );
    

    return rect;
}

void views::Slider::wheelEvent( QWheelEvent *e )
{    
    if( orientation() == Qt::Vertical )
    {
        // Will be handled by the parent widget
        e->ignore();
        return;
    }

    // Position Slider (horizontal)
    // only used for progress slider now!
    int step = e->delta() * 24;
    int nval = value() + step;
    nval = qMax(nval, minimum());
    nval = qMin(nval, maximum());

    QSlider::setValue( nval );

    emit sliderReleased( value() );
}

void views::Slider::mouseMoveEvent( QMouseEvent *e )
{
    if ( m_sliding )
    {
        //feels better, but using set value of 20 is bad of course
        QRect rect( -20, -20, width()+40, height()+40 );

        if ( orientation() == Qt::Horizontal && !rect.contains( e->pos() ) )
        {
            if ( !m_outside )
            {
                QSlider::setValue( m_prevValue );
                //if mouse released outside of slider, emit sliderMoved to previous value
                emit sliderMoved( m_prevValue );
            }
            m_outside = true;
        }
        else
        {
            m_outside = false;
            slideEvent( e );
            emit sliderMoved( value() );
        }
    }
    else
        QSlider::mouseMoveEvent( e );
}

void views::Slider::slideEvent( QMouseEvent *e )
{
    QRect knob;
    if ( maximum() > minimum() )
        knob = sliderHandleRect( rect(), ((qreal)value()) / ( maximum() - minimum() ) );

    int position;
    int span;

    if( orientation() == Qt::Horizontal )
    {
        position = e->pos().x() - knob.width() / 2;
        span = width() - knob.width();
    }
    else
    {
        position = e->pos().y() - knob.height() / 2;
        span = height() - knob.height();
    }

    const bool inverse = ( orientation() == Qt::Horizontal ) ?
                         ( invertedAppearance() != (layoutDirection() == Qt::RightToLeft) ) :
                         ( !invertedAppearance() );
    const int val = QStyle::sliderValueFromPosition( minimum(), maximum(), position, span, inverse );
    QSlider::setValue( val );
}

void views::Slider::mousePressEvent( QMouseEvent *e )
{
    m_sliding   = true;
    m_prevValue = value();

    QRect knob;
    if ( maximum() > minimum() )
        knob = sliderHandleRect( rect(), ((qreal)value()) / ( maximum() - minimum() ) );
    if ( !knob.contains( e->pos() ) )
        mouseMoveEvent( e );
}

void views::Slider::mouseReleaseEvent( QMouseEvent* )
{
    if( !m_outside && value() != m_prevValue )
       emit sliderReleased( value() );

    m_sliding = false;
    m_outside = false;
}

void views::Slider::setValue( int newValue )
{
    //don't adjust the slider while the user is dragging it!
    if ( !m_sliding || m_outside )
        QSlider::setValue( newValue );
    else
        m_prevValue = newValue;
}


