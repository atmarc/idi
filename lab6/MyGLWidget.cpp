#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
    scale = 1.0f;
    angle = 0.0f;
}

MyGLWidget::~MyGLWidget ()
{
    if (program != NULL)
        delete program;
}

void MyGLWidget::initializeGL ()
{
    // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)

    carregaShaders();
    
    glEnable (GL_DEPTH_TEST);
    // Carrega en homer
    m.load("../models/Patricio.obj");
    creaBuffers();
    calculaPunts();
    modelTransform();
    projTransform();
    viewTransform();
}

void MyGLWidget::paintGL ()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#endif

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    modelTransform();
    // Activem el VAO per a pintar la caseta
    glBindVertexArray (VAO);

    // pintem
    glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);
    glBindVertexArray (0);

    //TERRA
    transformTerra();
    glBindVertexArray (VAO_Terra);
    // pintem
    glDrawArrays (GL_TRIANGLES, 0, 6);
    glBindVertexArray (0);

}

void MyGLWidget::modelTransform ()
{
    // Matriu de transformació de model
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(0, puntMin.y*0.2, 0));
    transform = glm::scale(transform, glm::vec3(0.2,0.2,0.2));
    transform = glm::translate(transform, glm::vec3(-centre.x, -centre.y, -centre.z));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    
    transformacio = transform;

}

void MyGLWidget::transformTerra()
{
    // Matriu de transformació de model
    glm::mat4 transform (1.0f);
    //transform = glm::scale(transform, glm::vec3(scale));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;
    float rav = float(w)/float(h);
    if (rav < 1) {
        FOV = 2 * atan(tan(FOVini/2)/rav);
    }
    raw = rav;
    std::cout << "rav: " << rav << " FOV: " << FOV << std::endl;
    projTransform();
    viewTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
        scale += 0.05;
        break;
    }
    case Qt::Key_D: { // escalar a més petit
        scale -= 0.05;
        break;
    }
    case Qt::Key_R: { // escalar a més petit
        angle += M_PI/4;
        break;
    }
    default:
        event->ignore();
        break;
    }
    update();
}

void MyGLWidget::calculaPunts() {
    const std::vector <double> &V = m.vertices();
    int size = V.size();
    float minX = V[0];
    float minY = V[1];
    float minZ = V[2];
    float maxX = V[0];
    float maxY = V[1];
    float maxZ = V[2];

    for (int i = 0; i < size; i += 3) {
        if (V[i] < minX) minX = V[i];
        if (V[i] > maxX) maxX = V[i];
        if (V[i + 1] < minY) minY = V[i + 1];
        if (V[i + 1] > maxY) maxY = V[i + 1];
        if (V[i + 2] < minZ) minZ = V[i + 2];
        if (V[i + 2] > maxZ) maxZ = V[i + 2];
    }

    centre = glm::vec3 ((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
    puntMin = glm::vec3(minX,minY,minZ);
    OBS = glm::vec3(0,1,2);
}


void MyGLWidget::projTransform() {
    
    glm::vec4 centre2 = transformacio * glm::vec4 (centre.x, centre.y, centre.z, 1);
    glm::vec3 nouCentre = glm::vec3 (centre2.x, centre2.y, centre2.z);
    glm::vec4 puntMin2 = transformacio * glm::vec4 (puntMin.x, puntMin.y, puntMin.z, 1);
    glm::vec3 nouPuntMin = glm::vec3 (puntMin2.x, puntMin2.y, puntMin2.z);
    
    Radi = glm::distance(nouPuntMin, nouCentre);
    FOV = 2 * asin(Radi/glm::distance(OBS,nouCentre));
    zNear = glm::distance(nouCentre, OBS) - Radi;
    zFar = glm::distance(nouCentre, OBS) + Radi;
    
    // FOV, raw, zNear, zFar
    glm::mat4 Proj = glm::perspective (FOV, raw, zNear, zFar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}


void MyGLWidget::viewTransform () {
    glm::vec4 centre2 = transformacio * glm::vec4 (centre.x, centre.y, centre.z, 1);
    glm::vec3 nouCentre = glm::vec3 (centre2.x, centre2.y, centre2.z);
    
    
    
    //lookAt(OBS,VRP,UP)
    glm::mat4 View = glm::lookAt (OBS, nouCentre, glm::vec3(0,1,0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
    
}

void MyGLWidget::creaBuffers ()
{

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3,
                  m.VBO_vertices (), GL_STATIC_DRAW); // posició

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3,
                  m.VBO_matdiff (), GL_STATIC_DRAW); // color

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);


    // TERRA

    glm::vec3 posicio[6] = {
        glm::vec3(1, 0, 1),
        glm::vec3(-1, 0, 1),
        glm::vec3(-1, 0, -1),
        glm::vec3(1, 0, -1),
        glm::vec3(1, 0, 1),
        glm::vec3(-1, 0, -1)
    };
    glm::vec3 color[6] = {
        glm::vec3(1,0,0),
        glm::vec3(0,1,0),
        glm::vec3(0,0,1),
        glm::vec3(1,1,0),
        glm::vec3(1,0,0),
        glm::vec3(0,0,1)
    };

    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW); // posició

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW); // color

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);

}



void MyGLWidget::carregaShaders()
{
    // Creem els shaders per al fragment shader i el vertex shader
    QOpenGLShader fs (QOpenGLShader::Fragment, this);
    QOpenGLShader vs (QOpenGLShader::Vertex, this);
    // Carreguem el codi dels fitxers i els compilem
    fs.compileSourceFile("shaders/basicShader.frag");
    vs.compileSourceFile("shaders/basicShader.vert");
    // Creem el program
    program = new QOpenGLShaderProgram(this);
    // Li afegim els shaders corresponents
    program->addShader(&fs);
    program->addShader(&vs);
    // Linkem el program
    program->link();
    // Indiquem que aquest és el program que volem usar
    program->bind();

    // Obtenim identificador per a l'atribut “vertex” del vertex shader
    vertexLoc = glGetAttribLocation (program->programId(), "vertex");
    // Obtenim identificador per a l'atribut “color” del vertex shader
    colorLoc = glGetAttribLocation (program->programId(), "color");
    // Uniform locations
    transLoc = glGetUniformLocation(program->programId(), "TG");

    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");

}

