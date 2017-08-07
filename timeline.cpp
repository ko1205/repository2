#include "timeline.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include "ruler.h"
#include <QScrollBar>
#include <QPaintEvent>
#include <QStylePainter>

timeline::timeline(QWidget *parent)
    : QWidget(parent)
{
    ruler = new Ruler();
    offsetSpin = new QSpinBox();
    offsetSpin->setRange(0,999999);
    offsetSpin->setFrame(false);
    layout = new QVBoxLayout();
    QLabel *offsetLabel = new QLabel("offset",this);
    QLabel *zoomLabel = new QLabel("zoom",this);
    zoomSpin = new QDoubleSpinBox(this);
    zoomSpin->setDecimals(5);
    zoomSpin->setSingleStep(0.01);
    QLabel *widgetWidth = new QLabel("0",this);
    tmpLabel = new QLabel("0",this);

    QScrollBar *scrollbar = new QScrollBar(Qt::Horizontal);
    scrollbar->setMaximum(300);
    scrollbar->setPageStep(100);


    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    controlLayout = new QHBoxLayout;

    controlLayout->addWidget(offsetLabel);
    controlLayout->addWidget(offsetSpin);
    controlLayout->addStretch();
    controlLayout->addWidget(zoomLabel);
    controlLayout->addWidget(zoomSpin);
    controlLayout->addStretch();
    controlLayout->addWidget(widgetWidth);
    controlLayout->addWidget(tmpLabel);
    layout->addWidget(ruler);
    layout->addWidget(scrollbar);
    layout->addLayout(controlLayout);


    setLayout(layout);

    offsetSpin->setValue(ruler->offset());
    zoomSpin->setValue(ruler->zoom());

    connect(ruler,SIGNAL(resized(int)),widgetWidth,SLOT(setNum(int)));
    connect(offsetSpin,SIGNAL(valueChanged(int)),ruler,SLOT(setOffset(int)));
    connect(zoomSpin,SIGNAL(valueChanged(double)),ruler,SLOT(setZoom(double)));

    connect(ruler,SIGNAL(resetPaintRect(QRect)),this,SLOT(rulerRepaint(QRect)));
    connect(scrollbar,SIGNAL(valueChanged(int)),offsetSpin,SLOT(setValue(int)));

}

timeline::~timeline()
{

}

void timeline::rulerRepaint(QRect rec)
{
    tmpLabel->setNum(rec.left());
//    int temp = ruler->zoom();
//    tmpLabel->setNum((ruler->zoom())+10);
}

void timeline::paintEvent(QPaintEvent *event)
{
//    QStylePainter p(this);
//    const QRect &paintRect = event->rect();
//    p.drawLine(0,0,paintRect.right(),paintRect.bottom());

}
