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

public slots:
    void setZoom(double zoom);
    void setOffset(int offset);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void setPixelperLine();

    int m_offset;
    double m_zoom;
    int defaultFrameSize = 10;
    double shotLineDistance;
    double longLineDistance;
    const double tmpFrameRate = 24;
    double longLineStartPos;
};

#endif // RULER_H
