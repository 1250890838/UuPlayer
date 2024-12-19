#include <QtQml/qqmlregistration.h>
#include <QObject>
#include <QQuickWindow>
#include <QMouseEvent>

class UuWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    UuWindow(QWindow *parent = nullptr);
Q_INVOKABLE void applyRadius(qint32 radius);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QPointF m_lastPos;
};