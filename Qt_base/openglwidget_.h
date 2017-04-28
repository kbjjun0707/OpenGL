#ifndef OPENGLWIDGET__H
#define OPENGLWIDGET__H


#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QOpenGLFunctions>

#include "camera_.h"
#include "object_.h"
#include "collision_.h"
#include "ray_.h"

#include <glm\fwd.hpp>

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

	std::vector<jun::Object *>			m_Objs;
	std::vector<jun::Collision_Base *>	m_Collis;
	std::vector<bool>					m_IsColli;

	jun::Ray							m_CamRay;

	QPoint								m_PressPnt;
	bool								m_MouseDown[3];

	glm::mat4	m_ProjectionMat, m_LookAtMat, m_ModelMat;
	glm::fvec4	m_Viewport;


	///////////////////////////FUNCT//////////////////////////


	///////////////////////////SLOTS//////////////////////////

};


#endif // !OPENGLWIDGET__H