#include <QtGui>
#include <cstdio>
#include <assert.h>
#include "window.h"
#include "world/world.h"
#include "utilities/timer.h"

extern const uint g_hres;
extern const uint g_vres;
extern ulong g_numPrimaryRays;
extern ulong g_numLightRays;
extern Timer closestIsectTimer;
extern Timer shadowIsectTimer;

World world;

Window::Window() : nextScanline(0)
{
	this->setFixedSize(g_hres, g_vres);

	qImage = new QImage(g_hres, g_vres, QImage::Format_RGB32);
	qImage->fill(0x000000);
}


Window::~Window()
{
    delete qImage;
}


void Window::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *qImage);
}


void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Q) {
        close();
    }
}


void Window::startRender()
{
    world.screen_buffer = (uint*)qImage->bits();
	world.build();

    renderStartTime.start();
    renderScanline();
}


void Window::renderScanline()
{
    world.render_scanline(nextScanline);
	nextScanline++;
	update();

	if( nextScanline < g_vres) {
		// Fill the next scanline to render with white
		uint* startOfNextScanline = (uint*)qImage->scanLine(nextScanline);
		memset(startOfNextScanline, 0xFFFFFF, qImage->bytesPerLine());

        QTimer::singleShot(0, this, SLOT(renderScanline()));
	}
    else {
		qDebug("Primary rays: %ld  (%.1f /pixel)", g_numPrimaryRays, (double)g_numPrimaryRays/(double)(g_hres*g_vres));
		qDebug("Light rays: %ld  (%.1f /pixel)", g_numLightRays, (double)g_numLightRays/(double)(g_hres*g_vres));
		qDebug("Closest intersection time: %.2fs", closestIsectTimer.getAccumulatedMsec() / 1000.0);
		qDebug("Shadow intersection time: %.2fs", shadowIsectTimer.getAccumulatedMsec() / 1000.0);
		qDebug("Render time: %.2fs", renderStartTime.elapsed() / 1000.0);
	}
}
