#ifndef RULER_H
#define RULER_H

#include <QWidget>

//class QPaintEvent;
class Ruler : public QWidget
{
    Q_OBJECT
public:
    explicit Ruler(QWidget *parent = 0);
    ~Ruler();
    double zoom();
    int offset();

signals:
    void resized(int);
    void resetPaintRect(QRect rect);
    void changedOffset(int);

public slots:
//    void initSetup();
    void setZoom(double zoom);
    void setOffset(int offset);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    void setPixelperLine();

    unsigned int m_offset;
    double m_zoom;
    int defaultFrameSize = 10;//추후에 외부 셋팅으로 변경
    double shotLineDistance;
    double longLineDistance;
    const double tmpFrameRate = 24;//추후에 외부 셋팅으로 변경
    double longLineStartPos;
    int m_rulerEndPixel;
    int m_rulerEndFrame;
    int m_rulerDuration;

};

#endif // RULER_H
