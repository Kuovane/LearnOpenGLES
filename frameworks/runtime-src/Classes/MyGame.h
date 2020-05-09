
#pragma once

/**
 @brief    The cocos2d Application.
 
 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  MyGame 
{
public:
	MyGame(int width, int height);
    virtual ~MyGame();
    
	void run();
    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching() ;
    
    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground() ;
    
    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground() ;

	void drawLight();
	
	void drawBox();


	int m_m;
	int m_v;
	int m_p;

	int m_ml;
	int m_vl;
	int m_pl;

	int m_lightPos;

	float xa[10];
	float ya[10];
	float za[10];
	float ra[10];
	float ratio;
	unsigned int  program;
	unsigned int programLight;

	unsigned int vertex_buffer;
	unsigned int lightVertex_buffer;
	int mvp_location;
	int vpos_location;
	int vnormal_location;
	int vpos_texCoord;
	int CC_TextureID;
	int lightPosLoc;
};
