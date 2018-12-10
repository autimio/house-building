#include <gl/glut.h>

GLfloat ASPECTO, ANGULO;
int x_ini,y_ini, bot;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;

#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0   

// Callback chamada para fazer o desenho
void Desenha(void) {
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 300.0, 0.0);
		glEnd(); 
	glPopMatrix();
     
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(300.0, 0.0, 0.0);
		glEnd(); 
	glPopMatrix();
		
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 300.0);
		glEnd(); 
	glPopMatrix();
	    
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(20.0,0.0,0.0);
		glutSolidSphere(1.0,50.0,50.0);
	glPopMatrix();
        
	glutSwapBuffers();
}

// Inicializa par�metros de rendering
void Inicializa (void) { 
	GLfloat luzAmbiente[4] = {0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};		  // "cor" 
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho" 
	GLfloat posicaoLuz[4] = {0.0, 20.0, 20.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4] = {1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela ser� preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    //angle=45;
    ANGULO = 45;
    rotX = rotY = 0;
    obsX = obsY = 0;
    obsZ = 60;//Voltar para 10
    escalaX = escalaY = escalaZ = 1;
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void) { //equivalente ao posiciona observador
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
    // gluPerspective(angle,fAspect,0.4,500);
    gluPerspective(ANGULO, ASPECTO, 0.4, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
    // gluLookAt(0,80,200, 0,0,0, 0,1,0);
    // gluLookAt(obsX, obsY, obsZ, 0,0,0, 0,1,0);
    glTranslatef(-obsX, -obsY, -obsZ); /*Translata a câmera para essas variáveis*/
    glRotatef(rotX,1,0,0); /*Rotacionar a câmera para essas coordenadas*/
    glRotatef(rotY,0,1,0); 
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	//fAspect = (GLfloat)w/(GLfloat)h;
	ASPECTO = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	/*if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}*/
	if (state == GLUT_DOWN) {
		x_ini = x;
        y_ini = y;
        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;
        rotX_ini = rotX;
        rotY_ini = rotY;
		bot = button;
	} else bot = -1;

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void motion(int x, int y) {
	if (bot == GLUT_LEFT_BUTTON) { //Rotação
		int deltaX = x_ini - x;
		int deltaY = y_ini - y; 
		rotX = rotX_ini - deltaY/ SENS_ROT;
		rotY = rotY_ini - deltaX/ SENS_ROT;
	} else if (bot == GLUT_RIGHT_BUTTON) { //Zoom
		int deltaZ = y_ini - y;
		obsZ = obsZ_ini + deltaZ/ SENS_OBS;
	} else if (bot == GLUT_MIDDLE_BUTTON) { //Correr
		int deltaX = x_ini - x;
		int deltaY = y_ini - y;
		obsX = obsX_ini + deltaX/ SENS_TRANS;
		obsY = obsY_ini + deltaY/ SENS_TRANS;
	}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutCreateWindow("House Build 3D");
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(motion);
	Inicializa();
	glutMainLoop();
}

