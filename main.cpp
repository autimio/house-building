#include <gl/glut.h>
#include "tgaload.h"

GLfloat ASPECTO, ANGULO;
int x_ini,y_ini, bot;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;

#define MAX_NO_TEXTURES 50

#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0 

#define ALTURA_PAREDE 15.0f
#define ALTURA_TELHADO 35.0f
#define ALTURA_TOPO_TELHADO 50.0f
#define TAMANHO_CASA_X 150.0f
#define TAMANHO_CASA_Z 150.0f
#define TAMANHO_GARAGEM_Z 60.0f
#define TAMANHO_JANELA_XY 5.0f

GLuint texture_id[MAX_NO_TEXTURES];

void initializeTexture(void) {
	// Habilita o uso de textura 
	glEnable (GL_TEXTURE_2D);
	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	// Define quantas texturas serï¿½o usadas no programa 
	glGenTextures (MAX_NO_TEXTURES, texture_id);  // Quantidade de texturas, vetor de texturas
	
	texture_id[0] = 1001;
	glBindTexture (GL_TEXTURE_2D, texture_id[0]);
	image_t temp_image1;
	tgaLoad("textures/wood_floor.tga", &temp_image1, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[1] = 1002;
	glBindTexture (GL_TEXTURE_2D, texture_id[1]);
	image_t temp_image2;
	tgaLoad("textures/auxiliar.tga", &temp_image2, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[2] = 1003;
	glBindTexture (GL_TEXTURE_2D, texture_id[2]);
	image_t temp_image3;
	tgaLoad("textures/tijolinho_wall-min.tga", &temp_image3, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[3] = 1004;
	glBindTexture (GL_TEXTURE_2D, texture_id[3]);
	image_t temp_image4;
	tgaLoad("textures/tijolinho_wall_rotate90-min.tga", &temp_image4, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[4] = 1005;
	glBindTexture (GL_TEXTURE_2D, texture_id[4]);
	image_t temp_image5;
	tgaLoad("textures/door.tga", &temp_image5, TGA_FREE | TGA_LOW_QUALITY);
}

void LinhasPlanoCartesiano(void) {
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
}

void buildFloor(void) {	
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	
	//Térreo
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, 0.0, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, 0, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, 0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, 0, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0, 100); // B , x, x
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, 0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0, 100); // B , x, x
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, 0, 150);
		glEnd();
	glPopMatrix();
	
	//andar superior
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, ALTURA_PAREDE, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, ALTURA_PAREDE, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, ALTURA_PAREDE, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(100, ALTURA_PAREDE, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 100); // B , x, x
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_PAREDE, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 100); // B , x, x
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_PAREDE, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 150);
		glEnd();
	glPopMatrix();
}

void buildWall(void){
	glBindTexture(GL_TEXTURE_2D,texture_id[2]);
	// Parede fundo
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, ALTURA_TELHADO, 0.0);
		glEnd();
	glPopMatrix();
	
	// Parede porta esquerda
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, ALTURA_TELHADO, 50);
		glEnd();
	glPopMatrix();
	
	// Parede porta direita
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0, 150);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 150);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 150);
		glEnd();
	glPopMatrix();
	
	//parede lateral esquerda - 1
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, ALTURA_TELHADO, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, ALTURA_TELHADO, 50);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(0.0, 0.0, 50);
		glEnd();
	glPopMatrix();	
	
	//parede lateral esquerda - 2
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0.0, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, ALTURA_TELHADO, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 100);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(50, 0.0, 100);
		glEnd();
	glPopMatrix();	

	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0.0,100);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, ALTURA_TELHADO, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 150);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(50, 0.0, 150);
		glEnd();
	glPopMatrix();	
	
	//parede lateral direita	
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0.0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 50);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(100, 0.0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0.0, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 100);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(100, 0.0, 100);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0.0, 100);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 150);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(100, 0.0, 150);
		glEnd();
	glPopMatrix();
}

void buildDoors(void)
{
	/* Porta Principal*/
	glBindTexture(GL_TEXTURE_2D,texture_id[4]);
	glPushMatrix ();
	glTranslatef ((TAMANHO_CASA_X / 2) - 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glRotatef (yAngle, 0, 1,0);	
	glTranslatef (-((TAMANHO_CASA_X / 2) - 4), -0.0, -((TAMANHO_CASA_Z / 2) + 0.1));
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 2) - 4, 0.0, TAMANHO_CASA_Z + 0.1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 2) + 4, 0.0, TAMANHO_CASA_Z + 0.1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 2) + 4, 12.0, TAMANHO_CASA_Z + 0.1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 2) - 4, 12.0, TAMANHO_CASA_Z + 0.1);
	glEnd();
	glPopMatrix();
	
	// Porta 2
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef ((TAMANHO_CASA_X / 6) - 3, 0.0, TAMANHO_CASA_Z + 0.1);
		glRotatef (yAngle, 0, 1,0);
		glTranslatef (-((TAMANHO_CASA_X / 6) - 3), -0.0, -(TAMANHO_CASA_Z + 0.1));
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 6) - 3, 0.0, 50 + 0.1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 6) + 3, 0.0, 50 + 0.1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 6) + 3, 10.0, 50 + 0.1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 6) - 3, 10.0, 50 + 0.1);
		glEnd();
	glPopMatrix();
}

// Callback chamada para fazer o desenho
void Desenha(void) {
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LinhasPlanoCartesiano();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	buildFloor();
	buildWall();
	buildDoors();
        
	glutSwapBuffers();
}

// Inicializa par?metros de rendering
void Inicializa (void) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLfloat luzAmbiente[4] = {0.5,0.5,0.5,1.0}; 
	GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4] = {0.0, 0.0, 10.0, 0.0};
	GLfloat especularidade[4] = {1.0,1.0,1.0,1.0}; // Capacidade de brilho do material
	GLint especMaterial = 0;
	
 	// Especifica que a cor de fundo da janela ser? preta
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	// Habilita o modelo de colorizaï¿½ï¿½o de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletï¿½ncia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentraï¿½ï¿½o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	
	// Define os par?metros da luz de n?mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	
	// Habilita a definiï¿½ï¿½o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminaï¿½ï¿½o
	glEnable(GL_LIGHTING);
	// Habilita a luz de nï¿½mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    ANGULO = 45;
    rotX = rotY = 0;
    obsX = obsY = 0;
    obsZ = 10;
    escalaX = escalaY = escalaZ = 1;
}

// Funï¿½ï¿½o usada para especificar o volume de visualizaï¿½ï¿½o
void EspecificaParametrosVisualizacao(void) {  //equivalente ao posiciona observador
	// Especifica sistema de coordenadas de projeï¿½ï¿½o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeï¿½ï¿½o
	glLoadIdentity();

	// Especifica a projeï¿½ï¿½o perspectiva
	//gluPerspective(angle,fAspect,0.4,500);
	gluPerspective(ANGULO, ASPECTO, 0.4, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posiï¿½ï¿½o do observador e do alvo
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	glTranslatef(-obsX, -obsY, -obsZ);/*Translada a cï¿½mera para essas variï¿½veis*/
	glRotatef(rotX, 1, 0, 0); /*Rotacionar a cï¿½mera para essas coordenadas*/
	glRotatef(rotY, 0, 1, 0);
}

// Fun??o callback chamada quando o tamanho da janela ? alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a corre??o de aspecto
	ASPECTO = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

// Fun??o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
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
	if (bot == GLUT_LEFT_BUTTON) { //Rotaï¿½ï¿½o
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
	glutInitWindowPosition(250, 100);
	glutCreateWindow("House Build 3D - Computação Gráfica - Autímio Brito");
	initializeTexture();
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(motion);
	Inicializa();
	glutMainLoop();
}