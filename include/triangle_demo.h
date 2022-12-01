#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include "vector.h"
#include <math.h>
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <ctime>


#define SPECTRUM_SIZE 64

class TriangleDemo : public DemoBase
{

private:

	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel* m_musicChannel;
	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];
	float m_colour1;
	float m_colour2;
	float m_colour3;
	float m_rotate;
	float m_colourAssign;
	float m_rotation;


public:
	void init()
	{
		m_colour1 = 0.3f;
		m_colour2 = 1.0f;
		m_colour3 = 0.3f;
		initFmod();
	}

	void initFmod()
	{
		FMOD_RESULT result;
		unsigned int version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRORCHECK(result);

		result = m_fmodSystem->getVersion(&version);


		if (version < FMOD_VERSION)
			printf("FMOD Error! You are using an old version of FMOD.", version, FMOD_VERSION);

			//initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRORCHECK(result);

		//load and setup music
		result = m_fmodSystem->createStream("../media/bensound-funnysong.mp3",FMOD_SOFTWARE,0,&m_music);
		ERRORCHECK(result);

		//play the loaded mp3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRORCHECK(result);

	}

	void deinit()
	{

	}

	void ERRORCHECK(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s \n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	void updateSound()
	{
		m_fmodSystem->update();

		//Get spectrum for left and right stero channels
		// temp disable, testinng
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		std::cout << "1st bass level (left channel) :" << (m_spectrumLeft[0]) << std::endl;
	}

	/*void blendClass()
	{
		glEnable(GL_ALPHA_TEST);

		glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE); // additive blend
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // alpha blend
														   // glBlendFunc(GL_ZERO, GL_SRC_COLOR); // multiply blend

		drawCube();
		glDepthMask(false);

		drawCircle();
		glDepthMask(true);
	}*/

	void drawAxis(const Matrix& viewMatrix)
	{

		updateSound();
	// ============draw axis.
		/*glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.3f, 0.3f); //red x
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.3f, 1.0f, 0.3f); //green y
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.3f, 0.3f, 1.0f);//blue z
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();*/
		// ============================
	}
	

	void drawCubeArray()
	{
		
		static GLfloat vertices[] =
		{
			-1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,-1.0f,1.0f,

			1.0f,-1.0f,-1.0f,
			1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,1.0f,
			-1.0f,-1.0f,-1.0f,

			-1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,-1.0f,
			1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,1.0f,1.0f,

			1.0f,-1.0f,-1.0f,
			1.0f,1.0f,-1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,1.0f,

		
		};

		static GLfloat texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f
		};

		static GLubyte colors[] =
		{
			/*255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,*/

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255,

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255,

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255,

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255,

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255,

			255,255,255,
			0,0,0,
			0,255,255,
			0,255,255,
			0,0,0,
			255,255,255
		};
		
		/*static GLubyte colors[] =
		{
			//front
			m_colour1,255,255,
			255,0,255,
			0,255,m_colour2,
			0,255,255,
			m_colour3,0,255,
			255,255,255,
			//back
			255,m_colour3,255,
			255,0,255,
			0,255,m_colour1,
			0,255,255,
			m_colour2,0,255,
			255,255,255,
			//btm
			255,m_colour3,255,
			255,0,255,
			0,255,m_colour1,
			0,255,255,
			m_colour2,0,255,
			255,255,255,
			//top
			m_colour1,255,255,
			255,0,255,
			0,255,m_colour2,
			0,255,255,
			m_colour3,0,255,
			255,255,255,
			//right
			m_colour1,255,255,
			255,0,255,
			0,255,m_colour2,
			0,255,255,
			m_colour3,0,255,
			255,255,255,
			//left
			255,m_colour3,255,
			255,0,255,
			0,255,m_colour1,
			0,255,255,
			m_colour2,0,255,
			255,255,255
		};*/
		//activate and specify pointer to vertex array
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
			glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

			//draw rectangle
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//deactive vertex array after drawing
			glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawCircleArray()
	{
		float radius = 0.5f;
		float x = 0.0f, y = 1.0f, z = 0.0f;
		float twoPi = 2.0f * 3.14159265358979;
		const int numberOfTriangles = 64;
		const int vertices = 3;
		const int verticesCoor = 9;

		static GLfloat coorArray[numberOfTriangles][verticesCoor];
		static GLubyte colors[numberOfTriangles][verticesCoor];

		for (int i = 0; i < numberOfTriangles; i++)
		{
			coorArray[i][0] = x;
			coorArray[i][1] = y;
			coorArray[i][2] = z;

			coorArray[i][3] = x + (radius * sin(i * twoPi / numberOfTriangles));
			coorArray[i][4] = y;
			coorArray[i][5] = z + (radius * cos(i * twoPi / numberOfTriangles));

			coorArray[i][6] = x + (radius * sin((i+1) * twoPi / numberOfTriangles));
			coorArray[i][7] = y;
			coorArray[i][8] = z + (radius * cos((i+1) * twoPi / numberOfTriangles));

			colors[i][0] = 255;
			colors[i][1] = 255;
			colors[i][2] = 255;
			colors[i][3] = 255;
			colors[i][4] = 255;
			colors[i][5] = 255;
			colors[i][6] = 255;
			colors[i][7] = 255;
			colors[i][8] = 255;
		}

		
		
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, coorArray);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, numberOfTriangles * verticesCoor);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);
		float radius = 10.0f;
		float x = 0.0f, y = 0.0f, z = 0.0f;
		float twoPi = 2 * 3.14159265358979;
		
		m_rotate += 0.5f;
		m_rotation += 0.1f;
		
		/*drawCubeArray();
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);*/
		for (int i = 0; i < 64; i++)
		{
			
			x = (radius * sin(i * twoPi / 64));
			z = (radius * cos(i * twoPi / 64));
			Matrix scale1 = Matrix::makeScaleMatrix(0.1f,(3.0f * m_spectrumLeft[i]), 0.1f);
			//Matrix translate1 = Matrix::makeTranslationMatrix(i + 1.0f - 16.0f, 0.0f, 0.0f);
			Matrix translate1 = Matrix::makeTranslationMatrix(x, y, z);
			Matrix rotate1 = Matrix::makeRotateMatrix(m_rotate, Vector(1.0f, 0.0f, 0.0f));
			Matrix selfRotate = Matrix::makeRotateMatrix(m_rotation, Vector(0.0f, 1.0f, 0.0f));
			Matrix modelMatrix = scale1* selfRotate * translate1 * rotate1;
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			//glLoadMatrixf((GLfloat*)viewMatrix.mVal);
			drawCubeArray();
		}
		//drawCubeArray();
		/*static GLfloat vertices[] =
		{
			-1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,-1.0f,1.0f,

			1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f,1.0f,-1.0f,

			1.0f,-1.0f,1.0f,
			1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,

			-1.0f,1.0f,-1.0f,
			-1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,-1.0f,
			-1.0f,1.0f,-1.0f,

			1.0f,1.0f,1.0f,
			1.0f,1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,1.0f,
			1.0f,1.0f,1.0f,

			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,
			-1.0f,1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f
		};

		static GLfloat texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f,

			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			1.0f,1.0f,
			0.0f,1.0f,
			0.0f,0.0f
		};

		static GLubyte colors[] =
		{
			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,

			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,

			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,

			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,

			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255,

			255,255,255,
			255,0,255,
			0,255,255,
			0,255,255,
			255,0,255,
			255,255,255
		};
		*/

		/*glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		//activate and specify pointer to vertex array
		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);

		//draw rectangle
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//deactive vertex array after drawing
		glDisableClientState(GL_VERTEX_ARRAY);
		*/

		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//wireframe mode
		

	}

};

#endif
