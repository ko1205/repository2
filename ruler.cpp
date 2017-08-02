#include "ruler.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QStylePainter>

Ruler::Ruler(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(50);
    this->setMinimumWidth(500);
    m_zoom = 1.0;
    m_offset = 0;
    setFocusPolicy(Qt::ClickFocus);
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
        m_rulerEndFrame = m_rulerDuration+m_offset;
        this->update();
    }
}

void Ruler::paintEvent(QPaintEvent *event)
{
//  다시 그릴때 마다 계산하지 않도록 변경필요
//  paintEvent에서는 Draw만 하도록 변경
//  문제점 forLoop문에서 증가값이 소수점값으로 인해 불일치값이 발생함.

//  longLine은 무조건 초단위로 간다 zoom값에 의해 라인 간격이 2,3개등의로 넓어지면 longLine위에 초도 2초,3초 단위로 올라간다.

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
    QString tmpText("00:00:00:00");
    int fontWidth = p.fontMetrics().width(tmpText);
    p.drawText(0,fontMetrics().ascent(),"00:00:00:00");
    p.drawText(24*m_zoom*defaultFrameSize-fontWidth/2,fontMetrics().ascent(),"00:00:01:00");
    p.drawText(this->size().width()-fontWidth,fontMetrics().ascent(),"23:59:59:23");

}

void Ruler::resizeEvent(QResizeEvent *event)
{
    m_rulerEndPixel = event->size().width();
    m_rulerDuration = m_rulerEndPixel/defaultFrameSize/m_zoom;

    emit resized(m_rulerEndPixel);
}

void Ruler::focusInEvent(QFocusEvent *event)
{
    QStylePainter p(this);
    QPalette tmp = palette();
    tmp.setColor(QPalette::Midlight,Qt::blue);
    this->setPalette(tmp);
}

void Ruler::focusOutEvent(QFocusEvent *event)
{
    QStylePainter p(this);
    QPalette tmp = palette();
    tmp.setColor(QPalette::Midlight,Qt::white);
    this->setPalette(tmp);

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


