#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTime>

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window();
	~Window();
	void startRender();

public slots:
	void renderScanline();

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
	QImage *qImage;
	QTime renderStartTime;
	int nextScanline;
};

#endif // WINDOW_H
