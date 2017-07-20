#include "ruler.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QStylePainter>

Ruler::Ruler(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(50);
    m_zoom = 1.0;
    m_offset = 0;

}

Ruler::~Ruler()
{

}

double Ruler::zoom()
{
    return m_zoom;
}

int Ruler::offset()
{
    return m_offset;
}

void Ruler::setZoom(double zoom)
{
    if(m_zoom != zoom)
    {
        if(zoom > 8)
        {
            m_zoom = 8;
        }else if(zoom <=0){
            m_zoom = 0.00001;
        }else{
            m_zoom = zoom;
        }
        this->update();
    }
}

void Ruler::setOffset(int offset)
{
    if(m_offset!=offset)
    {
        m_offset = offset;
        this->update();
    }
}

void Ruler::paintEvent(QPaintEvent *event)
{
    setPixelperLine();
    QStylePainter p(this);
    const QRect &paintRect = event->rect();
    emit resetPaintRect(paintRect);
    p.setClipRect(paintRect);
    p.fillRect(paintRect,palette().midlight().color());
    for(double i=0-m_offset;i<this->size().width()/defaultFrameSize/m_zoom;i+=shotLineDistance)
    {
        p.drawLine(i*m_zoom*defaultFrameSize,20,i*m_zoom*defaultFrameSize,30);
    }
    for(double i=0-m_offset;i<this->size().width()/m_zoom/defaultFrameSize;i+=longLineDistance)
    {
        p.drawLine(i*m_zoom*defaultFrameSize,15,i*m_zoom*defaultFrameSize,35);
    }

}

void Ruler::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    emit resized(width);
}


void Ruler::setPixelperLine()
{
    int forShortLineUnit;
    int forLongLineUnit;

    if(m_zoom >= 1)
    {
        forShortLineUnit = 1;
        forLongLineUnit = tmpFrameRate;
        longLineStartPos = (m_offset%(int)tmpFrameRate)*(defaultFrameSize*forShortLineUnit)*m_zoom;
    }else{
        forShortLineUnit = (int)(1/m_zoom);
        forLongLineUnit = (int)(forShortLineUnit*tmpFrameRate);
    }
    shotLineDistance = 1*forShortLineUnit;
    longLineDistance = shotLineDistance*24;


}


