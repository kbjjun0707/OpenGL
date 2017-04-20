#ifndef OPENGLWIDGET__H
#define OPENGLWIDGET__H


#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QOpenGLFunctions>

#include "camera_.h"

#include <vector>

class OpenglWidgetClass : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:

	explicit OpenglWidgetClass(QWidget* parent = nullptr);
	virtual ~OpenglWidgetClass();

	QSurfaceFormat format;

protected:

	virtual void initializeGL();

	virtual void resizeGL(int w, int h);

	virtual void paintGL();

	virtual void timerEvent(QTimerEvent *e);

	virtual void wheelEvent(QWheelEvent *e);

	virtual void mousePressEvent(QMouseEvent *e);

	virtual void mouseMoveEvent(QMouseEvent *e);

	virtual void mouseReleaseEvent(QMouseEvent *e);

private:

	int m_CamIdx;
	std::vector<jun::Camera>			m_Cams;
	QPoint								m_PressPnt;
	bool								m_MouseDown[3];


	///////////////////////////FUNCT//////////////////////////


	///////////////////////////SLOTS//////////////////////////

};


#endif // !OPENGLWIDGET__H