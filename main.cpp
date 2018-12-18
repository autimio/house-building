#include <gl/glut.h>
#include <math.h>
#include "tgaload.h"

GLfloat ASPECTO, ANGULO;
int x_ini,y_ini, bot;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;
GLUquadricObj * quadObj = gluNewQuadric();


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

//Configurações das linhas
#define COR_JANELA 0.878, 1.000, 1.000,0.5
#define COLOR_LINE_WALL 0.555, 0.222, 0.0
#define WIDTH_LINE_WALL 50

GLfloat vetPorta[3] = {0.1, 0.1, 0.1};
GLfloat vetJanela[3] = {0.1, 0.1, 0.1};
GLfloat vetJanelaZ[3] = {0.1, 0.1, 0.1};


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
	
	texture_id[5] = 1006;
	glBindTexture (GL_TEXTURE_2D, texture_id[5]);
	image_t temp_image6;
	tgaLoad("textures/tijolinho_wall-min-frente.tga", &temp_image6, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[6] = 1007;
	glBindTexture (GL_TEXTURE_2D, texture_id[6]);
	image_t temp_image7;
	tgaLoad("textures/floor_hex.tga", &temp_image7, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[7] = 1008;
	glBindTexture (GL_TEXTURE_2D, texture_id[7]);
	image_t temp_image8;
	tgaLoad("textures/frontend-large.tga", &temp_image8, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[8] = 1009;
	glBindTexture (GL_TEXTURE_2D, texture_id[8]);
	image_t temp_image9;
	tgaLoad("textures/piscina.tga", &temp_image9, TGA_FREE | TGA_LOW_QUALITY);
	
	texture_id[9] = 1010;
	glBindTexture (GL_TEXTURE_2D, texture_id[9]);
	image_t temp_image10;
	tgaLoad("textures/cerca.tga", &temp_image10, TGA_FREE | TGA_LOW_QUALITY);
}

void LinhasPlanoCartesiano(void) {
	
	//linha 1 vertical fundo
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
		glColor3f(COLOR_LINE_WALL);
			glVertex3f(0.1, 0.0, 0.0);
			glVertex3f(0.1, 35.0, 0.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	//linha 2 vertical fundo
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
			glVertex3f(100.0, 0.0, 0.0);
			glVertex3f(100.0, 35.0, 0.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	//linha 3 vertical esquerda porta
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 50.0);
			glVertex3f(0.0, 35.0, 50.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	//linha 3 vertical direita porta
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
			glVertex3f(50.0, 0.0, 50.0);
			glVertex3f(50, 35.0, 50.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	//linha 3 vertical esqera porta principal
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
			glVertex3f(50.0, 0.0, 150.0);
			glVertex3f(50, 35.0, 150.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	//linha 3 vertical esquerda porta principal
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_LINES);
			glVertex3f(100.0, 0.0, 150.0);
			glVertex3f(100, 35.0, 150.0);
		glEnd();
		glLineWidth(WIDTH_LINE_WALL);
	glPopMatrix();
	
	
}

void buildFloorHouse(void) {	
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
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0, 100);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, 0, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, 0, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 0, 100);
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
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_PAREDE, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 50);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_PAREDE, 100);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(100, ALTURA_PAREDE, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_PAREDE, 150);
		glEnd();
	glPopMatrix();
	
	glBindTexture ( GL_TEXTURE_2D, 0 );
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
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 12, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 12, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, ALTURA_TELHADO, 50);
		glEnd();
	glPopMatrix();	
	glBindTexture(GL_TEXTURE_2D,0);
	
	glBindTexture(GL_TEXTURE_2D,texture_id[5]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(22, 0, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(22, 12, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 12, 50);
		glEnd();
	glPopMatrix();
		
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(28, 0, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, 12, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(28, 12, 50);
		glEnd();
	glPopMatrix();
	
	// Parede porta direita
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 12, 150);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 12, 150);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 150);
		glEnd();
	glPopMatrix();	
	glBindTexture(GL_TEXTURE_2D,0);
	
	glBindTexture(GL_TEXTURE_2D,texture_id[5]);	
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(71, 0, 150);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50, 0, 150);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50, 12, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(71, 12, 150);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(100, 0, 150);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(79, 0, 150);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(79, 12, 150);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 12, 150);
		glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
	
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
	glBindTexture(GL_TEXTURE_2D,0);
	
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
	glBindTexture(GL_TEXTURE_2D,0);
}

void buildDoors(void) {
	/* Porta Principal*/
	glBindTexture(GL_TEXTURE_2D,texture_id[4]);
	glPushMatrix ();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef ((TAMANHO_CASA_X / 2) - 4, 0.0, TAMANHO_CASA_Z  + 0.1);
	glRotatef (yAngle, 0, 1,0);	
	glTranslatef (-((TAMANHO_CASA_X / 2) - 4), -0.0, -((TAMANHO_CASA_Z / 2) + 0.1));
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 2) - 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 2) + 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 2) + 4, 12.0, (TAMANHO_CASA_Z / 2) + 0.1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 2) - 4, 12.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glEnd();
	glPopMatrix();
	
	//Porta 2
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef ((TAMANHO_CASA_X / 6) - 3, 0.0, 50 + 0.1);
		glRotatef (yAngle, 0, 1,0);
		glTranslatef (-((TAMANHO_CASA_X / 6) - 3), -0.0, -((TAMANHO_CASA_Z / 2) + 0.1));
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 6) - 3, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f((TAMANHO_CASA_X / 6) + 3, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 6) + 3, 12.0,(TAMANHO_CASA_Z / 2) + 0.1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f((TAMANHO_CASA_X / 6) - 3, 12.0, (TAMANHO_CASA_Z / 2) + 0.1);
		glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
}

void buildWindows(void) {

	//borda janela
	glPushMatrix();
    	glTranslatef(0,12,35);
    	glRotatef(45,0,0,1); 		// rotaciona 45º no eixo z
     	glRotatef(90,1,1,0); 		// rotaciona 90º no eixo x,y
    	glColor3f(0.47,0.53,0.42); 	//verde militar
    	glutSolidTorus(0.5,3,/*slices*/4,/*stacks*/4);
    glPopMatrix();
	    
	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanela[0], vetJanela[1], vetJanela[2]);    
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10, 10, 50);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(20 + 3, 8, 50);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(20 + 3, 8, 50);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(10, 10, 50);
		glEnd();
	glPopMatrix();

}

void buildFloorTerrace(void) {
	glBindTexture(GL_TEXTURE_2D,texture_id[6]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0, -0.01, -10.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(230, -0.01, -10.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(230, -0.01, 230);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0, -0.01, 230);
		glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
}

void buildVaranda(void){
	// Pilastra 1
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glTranslatef(2.0, 20, 100);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadObj, 1.5, 1.5, 20, 10, 10);
	glPopMatrix();

	// Pilastra 2
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glTranslatef(2.0, 20, 125);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadObj, 1.5, 1.5, 20, 10, 10);
	glPopMatrix();
	
	// Pilastra 3
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glTranslatef(2.0, 20, 150);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadObj, 1.5, 1.5, 20, 10, 10);
	glPopMatrix();
	
	//vigota principal	
	//lateral direita
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(1, 20, 97);
			glVertex3f(1, 21, 97);
			glVertex3f(1, 21, 153);
			glVertex3f(1, 20, 153);
		glEnd();
	glPopMatrix();
	
	//lateral esquerda
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(3, 20, 97);
			glVertex3f(3, 21, 97);
			glVertex3f(3, 21, 153);
			glVertex3f(3, 20, 153);
		glEnd();
	glPopMatrix();
	
	//base
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(1, 20, 97);
			glVertex3f(3, 20, 97);
			glVertex3f(3, 20, 153);
			glVertex3f(1, 20, 153);
		glEnd();
	glPopMatrix();
	
	//superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(1, 21, 97);
			glVertex3f(3, 21, 97);
			glVertex3f(3, 21, 153);
			glVertex3f(1, 21, 153);
		glEnd();
	glPopMatrix();
	
	//vigotas 2
	//vigota 2 - superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 22, 98);
			glVertex3f(50, 22, 98);
			glVertex3f(50, 22, 102);
			glVertex3f(-1, 22, 102);
		glEnd();
	glPopMatrix();
	
	//vigota 2 - inferior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 98);
			glVertex3f(50, 21, 98);
			glVertex3f(50, 21, 102);
			glVertex3f(-1, 21, 102);
		glEnd();
	glPopMatrix();
	
	//vigota 2 - frente 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 98);
			glVertex3f(50, 22, 98);
			glVertex3f(50, 22, 102);
			glVertex3f(-1, 21, 102);
		glEnd();
	glPopMatrix();
	
	//vigota 2 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 98);
			glVertex3f(50, 20.5, 98);
			glVertex3f(50, 22, 98);
			glVertex3f(-1, 22, 98);
		glEnd();
	glPopMatrix();
	
	//vigota 2 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 102);
			glVertex3f(50, 20.5, 102);
			glVertex3f(50, 22, 102);
			glVertex3f(-1, 22, 102);
		glEnd();
	glPopMatrix();
	
	//vigotas 2.1
	//vigota 2.1 - superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 22, 111);
			glVertex3f(50, 22, 111);
			glVertex3f(50, 22, 115);
			glVertex3f(-1, 22, 115);
		glEnd();
	glPopMatrix();
	
	//vigota 2.1 - inferior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 111);
			glVertex3f(50, 21, 111);
			glVertex3f(50, 21, 115);
			glVertex3f(-1, 21, 115);
		glEnd();
	glPopMatrix();
	
	//vigota 2.1 - frente 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 111);
			glVertex3f(50, 22, 111);
			glVertex3f(50, 22, 115);
			glVertex3f(-1, 21, 115);
		glEnd();
	glPopMatrix();
	
	//vigota 2.1 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 111);
			glVertex3f(50, 20.5, 111);
			glVertex3f(50, 22, 111);
			glVertex3f(-1, 22, 111);
		glEnd();
	glPopMatrix();
	
	//vigota 2.1 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 115);
			glVertex3f(50, 20.5, 115);
			glVertex3f(50, 22, 115);
			glVertex3f(-1, 22, 115);
		glEnd();
	glPopMatrix();
	
	//vigotas 3
	//vigota 3 - superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 22, 123);
			glVertex3f(50, 22, 123);
			glVertex3f(50, 22, 127);
			glVertex3f(-1, 22, 127);
		glEnd();
	glPopMatrix();
	
	//vigota 3 - inferior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 123);
			glVertex3f(50, 21, 123);
			glVertex3f(50, 21, 127);
			glVertex3f(-1, 21, 127);
		glEnd();
	glPopMatrix();
	
	//vigota 3 - frente 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 123);
			glVertex3f(50, 22, 123);
			glVertex3f(50, 22, 127);
			glVertex3f(-1, 21, 127);
		glEnd();
	glPopMatrix();
	
	//vigota 3 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 123);
			glVertex3f(50, 20.5, 123);
			glVertex3f(50, 22, 123);
			glVertex3f(-1, 22, 123);
		glEnd();
	glPopMatrix();
	
	//vigota 3 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 127);
			glVertex3f(50, 20.5, 127);
			glVertex3f(50, 22, 127);
			glVertex3f(-1, 22, 127);
		glEnd();
	glPopMatrix();
	
	//vigotas 3.1
	//vigota 3.1 - superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 22, 136);
			glVertex3f(50, 22, 136);
			glVertex3f(50, 22, 140);
			glVertex3f(-1, 22, 140);
		glEnd();
	glPopMatrix();
	
	//vigota 3.1 - inferior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 136);
			glVertex3f(50, 21, 136);
			glVertex3f(50, 21, 140);
			glVertex3f(-1, 21, 140);
		glEnd();
	glPopMatrix();
	
	//vigota 3.1 - frente 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 136);
			glVertex3f(50, 22, 136);
			glVertex3f(50, 22, 140);
			glVertex3f(-1, 21, 140);
		glEnd();
	glPopMatrix();
	
	//vigota 3.1 - lateral esquerda 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 136);
			glVertex3f(50, 20.5, 136);
			glVertex3f(50, 22, 136);
			glVertex3f(-1, 22, 136);
		glEnd();
	glPopMatrix();
	
	//vigota 3.1 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 140);
			glVertex3f(50, 20.5, 140);
			glVertex3f(50, 22, 140);
			glVertex3f(-1, 22, 140);
		glEnd();
	glPopMatrix();
	
	//vigotas 4
	//vigota 4 - superior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 22, 148);
			glVertex3f(50, 22, 148);
			glVertex3f(50, 22, 152);
			glVertex3f(-1, 22, 152);
		glEnd();
	glPopMatrix();
	
	//vigota 4 - inferior
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 148);
			glVertex3f(50, 21, 148);
			glVertex3f(50, 21, 152);
			glVertex3f(-1, 21, 152);
		glEnd();
	glPopMatrix();
	
	//vigota 4 - frente 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 21, 148);
			glVertex3f(50, 22, 148);
			glVertex3f(50, 22, 152);
			glVertex3f(-1, 21, 152);
		glEnd();
	glPopMatrix();
	
	//vigota 4 - lateral esquerda 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 148);
			glVertex3f(50, 20.5, 148);
			glVertex3f(50, 22, 148);
			glVertex3f(-1, 22, 148);
		glEnd();
	glPopMatrix();
	
	//vigota 4 - lateral direita 
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glBegin(GL_QUADS);
			glVertex3f(-1, 20.5, 152);
			glVertex3f(50, 20.5, 152);
			glVertex3f(50, 22, 152);
			glVertex3f(-1, 22, 152);
		glEnd();
	glPopMatrix();
}

void buildRoof(void) {
		
	glBindTexture(GL_TEXTURE_2D,texture_id[7]);

	//fundo
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100 / 4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100 / 6, ALTURA_TOPO_TELHADO, 100 / 4);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, ALTURA_TELHADO, 50.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 50.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100 / 4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100 / 6, ALTURA_TOPO_TELHADO, 100 / 4);
	glEnd();
	glPopMatrix();
	
	//telhado direito
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_TELHADO, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100 / 4);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50, ALTURA_TELHADO, 150);
	glEnd();
	glPopMatrix();

	//telhado esquerdo
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100 / 4);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100, ALTURA_TELHADO, 150);
	glEnd();
	glPopMatrix();

	// fim telhado
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(50, ALTURA_TELHADO, 150);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100, ALTURA_TELHADO, 150);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80, ALTURA_TOPO_TELHADO, 100);
	glEnd();
	glPopMatrix();

}

void buildBoard(void) {
	glPushMatrix();
	glTranslatef(20.0f, 5.0f, 20.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.878, 1.000, 1.000);
		glVertex2f(0.0f, 0.0f);
		int numSegments = 100;
		GLfloat angulo;
		GLfloat raio = 4.0f;
		for (int i = 0; i <= numSegments; i++)
		{
			angulo = i * 2.0f * 3.14159265f / numSegments;
			glVertex2f(cos(angulo) * raio, sin(angulo) * raio);
		}
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(20.0f, 5.0f, 20.0f);
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadObj, 2, 2, 5, 10, 5);
	glEnd();
	glPopMatrix();
	
	//base
	glPushMatrix();
		glColor3f(COLOR_LINE_WALL);
		glTranslatef(20.0, 5, 20);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(quadObj, 1.5, 1.5, 5, 10, 10);
	glPopMatrix();
}

void builfTeaPot(void) {
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(20.0f, 6.5f, 20.0f);
	glutSolidTeapot(2.0f);
	glEnd();
	glPopMatrix();
}

void buildPool(void) {
	glBindTexture(GL_TEXTURE_2D,texture_id[8]);
	glPushMatrix();
		glColor3f(1.0f,1.0f,1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(210, 0.1, 20);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(210, 0.1, 140);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(120, 0.1, 140);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(120, 0.1, 20);
		glEnd();
	glPopMatrix();
}

static void key(unsigned char key, int x, int y) {
	switch (key) {
		//	abre a porta
		case 'd' :		
			if(yAngle <= 90)
				yAngle += 15;
			break;
		//fecha a porta
		case 'e' :
			if(yAngle >= 0)
				yAngle -= 15;
			break;
	}
	glutPostRedisplay();
}

// Callback chamada para fazer o desenho
void Desenha(void) {
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LinhasPlanoCartesiano();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	buildFloorHouse();
	buildWall();
	buildDoors();
	buildVaranda();
	buildFloorTerrace();
	//buildWindows();
	buildVaranda();
	buildRoof();
	buildBoard();
	builfTeaPot();
	buildPool();
        
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

// Funçãocallback chamada quando o tamanho da janela ? alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;
	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
	// Calcula a corre??o de aspecto
	ASPECTO = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
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
    glutKeyboardFunc(key);	
	Inicializa();
	glutMainLoop();
}