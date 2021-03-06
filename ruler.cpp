#include "ruler.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QStylePainter>

/* 24*60*60*24=2073600 24fps일때 24시간의 프레임수
 * offset + (width/defaultFramePixel)*zoom_factor = totalFrameCount
 * Max_zoom_factor = (2073600-offset)/(width/defaultFramePixel)
 */

Ruler::Ruler(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(50);
//    this->setMinimumWidth(500);
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
/*  100 = defaultFrameSize/zoom
 *  zoom = defaultFrameSize/100
 */
    if(m_zoom != zoom)
    {
        double minZoomFactor = defaultFrameSize/100;
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
//        (this->width()/defaultFrameSize)
        m_offset = offset;
        m_rulerEndFrame = m_rulerDuration+m_offset;
        this->update();
        emit changedOffset(m_offset);
    }
}

void Ruler::paintEvent(QPaintEvent *event)
{
//  다시 그릴때 마다 계산하지 않도록 변경필요
//  paintEvent에서는 Draw만 하도록 변경
//  문제점 forLoop문에서 증가값이 소수점값으로 인해 불일치값이 발생함.

//  longLine은 무조건 초단위로 간다 zoom값에 의해 라인 간격이 2,3개등의로 넓어지면 longLine위에 초도 2초,3초 단위로 올라간다.

/*  ruluer와 상관없는 메모
 * 나중에 트렉에서 클립명을 검색할때 스크롤+클릭위치와 앞클립길이를 더해 가면서 forLoop를 돌린다.
 * 참고 QtTreeView에 QTreeViewPrivate::itemAtCoordinate(int coordinate)함수 참조
 * 현재 생각하는 구현 방법에서는 상위 트랙부터 앞클립의 in out을 비교해가며 forLoop
 * 속도가 느리다면 다시 구현방법 생각해본다.
 */
    setPixelperLine();
    QStylePainter p(this);
    const QRect &paintRect = event->rect();
    emit resetPaintRect(paintRect);
    p.setClipRect(paintRect);
    p.fillRect(paintRect,palette().midlight().color());
    for(double i=0-(int)m_offset;i<this->size().width()/defaultFrameSize/m_zoom;i+=shotLineDistance)
    {
        p.drawLine(i*m_zoom*defaultFrameSize,20,i*m_zoom*defaultFrameSize,30);
    }
    for(double i=0-(int)m_offset;i<this->size().width()/m_zoom/defaultFrameSize;i+=longLineDistance)
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


