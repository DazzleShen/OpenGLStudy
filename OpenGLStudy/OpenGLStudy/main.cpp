/* //�鿴OpenGL�汾����
#include<Windows.h>
#include <stdio.h>
#include <GL/glut.h>

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Version");

	const GLubyte* name = glGetString(GL_VENDOR); //���ظ���ǰOpenGLʵ�ֳ��̵�����
	const GLubyte* biaoshifu = glGetString(GL_RENDERER); //����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //���ص�ǰOpenGLʵ�ֵİ汾��
	const GLubyte* gluVersion = gluGetString(GLU_VERSION); //���ص�ǰGLU���߿�汾

	printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
	printf("��Ⱦ����ʶ����%s\n", biaoshifu);
	printf("OpenGLʵ�ֵİ汾�ţ�%s\n", OpenGLVersion);
	printf("OGLU���߿�汾��%s\n", gluVersion);
	//�������VS��ִ�У���Ҫ��returnǰ���ϣ�system("pause");
	return 0;
}
*/

#include "DrawWindow.h"
#include "DrawTriangle.h"
#include "DrawRect.h"
#include "Shader.h"

int main()
{
	//���Ƴ�ʼ����
	//DrawWindow();

	//����������
	//DrawTriangle();

	//���ƾ���
	DrawRect();

	//��ɫ��
	//Shader();

    return 0;
}