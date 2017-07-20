#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class Ruler;
class QSpinBox;
class QDoubleSpinBox;
class QLabel;

class timeline : public QWidget
{
    Q_OBJECT

public:
    timeline(QWidget *parent = 0);
    ~timeline();
    QVBoxLayout *layout;
    QHBoxLayout *controlLayout;
    Ruler *ruler;
    QSpinBox *offsetSpin;
    QDoubleSpinBox *zoomSpin;

public slots:
    void rulerRepaint(QRect rec);

private:
    QLabel *tmpLabel;
};

#endif // TIMELINE_H
