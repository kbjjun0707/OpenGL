# OpenGL
OpenGL 프로젝트들

glut 윈도우 환경의 GL을 만들 때, 기본적으로 사용할 프로젝트

나름대로 공부한 ray 구현 
ray와 충돌체의 충돌을 통하여 object picking 및 이동

화면의 점 x는 세상좌표(glVertex3f(1.f, 1.f, 1.f)와 같은 좌표)에 
그린 점 X를 이동, 회전, 투영 등의 변형 과정을 거쳐 표시되는 점.
x = viewport * projection matrix * modelview matrix * X 의 과정을 거친다.

perspective 투영 된 물체를 마우스가 화면에서 움직인 만큼 이동시킬 때,
카메라 위치를 c, 물체위치를 o, 화면의 점(near 평면 위의 점)을 n1에서 n2로
이동시킬 때 삼각형(c n1 n2)의 넓이 : 삼각형(o n1 n2)의 넓이 비가 
c와 near평면의 거리 : near평면과 near평면에 평행하고 점 o를 포함하는 평면의 거리 
비가 같다는 성질로 n1->n2 : o->p 로 이동될 p점을 구하였다.

여기서의 충돌검사는 충돌여부만 판단하였고,
깊이에 따라 맨 앞의 물체만 선택하는 충돌이 아니다.
