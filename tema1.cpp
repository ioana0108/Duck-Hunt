#include "lab_m1/Tema1/tema1.h"  
#include <vector>
#include <iostream>

#include "lab_m1/Tema1/tema1_transform2D.h"
#include "lab_m1/Tema1/tema1_object2D.h"

using namespace std;
using namespace m1;

glm::ivec2 res; 
int color;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

int ciocnit_deja = 0;
void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0); 
    float squareSide = 40;
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    Mesh* square1 = object2D_t1::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    float side = 80;
    Mesh* square2 = object2D_t1::CreateSquare("square2", corner, side, glm::vec3(0, 0, 1), true);
    AddMeshToList(square2);
    Mesh* rectangle1 = object2D_t1::CreateRectangle("rectangle1", corner, side, glm::vec3(0, 1, 0), false);
    AddMeshToList(rectangle1);

    // Hai sa facem triunchiul la pasare:
    {
        vector<VertexFormat> vertices_trunchi
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(255, 255, 0)), // A
            VertexFormat(glm::vec3(0, 120, 0), glm::vec3(255, 255, 0)), // B
            VertexFormat(glm::vec3(120, 60, 0), glm::vec3(255, 255, 0)), // C
        };

        vector<unsigned int> indices_trunchi =
        {
            0, 2, 1, 
        };

        CreateMesh("trunchi", vertices_trunchi, indices_trunchi); 
    }

    // Cap format din 2 triunghiuri
    {
        vector<VertexFormat> vertices_cap
        {
            VertexFormat(glm::vec3(90, 60, 0), glm::vec3(255, 0, 0)), // C1
            VertexFormat(glm::vec3(120, 30, 0), glm::vec3(255, 0, 0)), // C2
            VertexFormat(glm::vec3(120, 90, 0), glm::vec3(255, 0, 0)), // C4
            VertexFormat(glm::vec3(120, 90, 0), glm::vec3(255, 0, 0)), // C4
            VertexFormat(glm::vec3(120, 30, 0), glm::vec3(255, 0, 0)), // C2
            VertexFormat(glm::vec3(150, 60, 0), glm::vec3(255, 0, 0))  // C3
        };

        vector<unsigned int> indices_cap =
        {
            0, 2, 1, // first triangle
            3, 4, 5  // second triangle
        };

        CreateMesh("cap", vertices_cap, indices_cap);
    }

    // Hai sa facem cioc la rata
    {
        vector<VertexFormat> vertices_choc
        {
            VertexFormat(glm::vec3(138, 74, 0), glm::vec3(255, 255, 0)), // varf1 (cioc1)
            VertexFormat(glm::vec3(138, 46, 0), glm::vec3(255, 255, 0)), // varf2 (cioc2)
            VertexFormat(glm::vec3(155, 60, 0), glm::vec3(255, 255, 0)), // varf3 (cioc3)
        };

        vector<unsigned int> indices_choc =
        {
            0, 2, 1,
        };

        CreateMesh("choc", vertices_choc, indices_choc);
    }

    // Hai sa facem aripaSTG la pasare:
    {
        vector<VertexFormat> vertices_aripaSTG
        {
            VertexFormat(glm::vec3(57.8, 133.4, 0), glm::vec3(0, 0, 1)), // D
            VertexFormat(glm::vec3(40, 96, 0), glm::vec3(0, 0, 1)), // E
            VertexFormat(glm::vec3(83.3, 78.4, 0), glm::vec3(0, 0, 1)), // F
        };

        vector<unsigned int> indices_aripaSTG =
        {
            0, 2, 1, 
        };

        CreateMesh("aripaSTG", vertices_aripaSTG, indices_aripaSTG); // Incerc sa creez primul triunghi
    }

    // Hai sa facem aripaDRP la pasare:
    {
        vector<VertexFormat> vertices_aripaDRP
        {
            VertexFormat(glm::vec3(57.8, -13.0, 0), glm::vec3(255, 255, 0)), // D'
            VertexFormat(glm::vec3(40, 24, 0), glm::vec3(255, 255, 0)), // E'
            VertexFormat(glm::vec3(83.3, 41.6, 0), glm::vec3(255, 255, 0)), // F'
        };

        vector<unsigned int> indices_aripaDRP =
        {
            0, 2, 1,
        };

        CreateMesh("aripaDRP", vertices_aripaDRP, indices_aripaDRP); // Incerc sa creez primul triunghi
    }

    // Glontz
    {
        vector<VertexFormat> vertices_glontz
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), // A
            VertexFormat(glm::vec3(4, 10, 0), glm::vec3(0, 1, 0)), // B
            VertexFormat(glm::vec3(8, 0, 0), glm::vec3(0, 1, 0)), // C
        };

        vector<unsigned int> indices_glontz =
        {
            0, 2, 1,
        };

        CreateMesh("glontz", vertices_glontz, indices_glontz);
    }
    
    // Diverse declarari

    Fx = 83.3; // Retin coord lui F si F' (punctul superior in care se unesc aripa si trunchiul) pentru rotatia aripii
    Fy = 78.4;
    Fprimx = 83.3;
    Fprimy = 41.6;
    //glm::vec2 F = (83.3, 78.4);
    sign1 = 1; // semn care determina in ce sens se realizeaza semirotatia aripilor (ceas / trigonometric)
    sign2 = 1;
    ciocnire = 0; // marcheaza ciocnirea de perete
    ciocnire_OY = 0;
    pi = 3.1415926535;
    margineXdrp_ecran = 970; // marcheaza marginea din dreapta a ecranului

    // Initialize tx and ty (the translation steps)
    translateX = 0; 
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularSteps
    angularStep1 = 0.1;
    angularStep2 = -0.1;
    angularStep3 = 3.14159265 / 4;
    unghi_jos = 0.18;
    unghi_sus = 0.25;

    // punct de plecare rata
    startx = 0;
    starty = 0;

    impuscata = 0;
    nr_gloante = 3;
    vieti = 3;
    fara_gloante = 0;
    sens_zbor = 1;
    nr_ciocniri = 0;
    durata_prestatie = 0;
    latime_ratza = 100;
    evadare = 0;
    contor_ratze = 1;
    viteza_ratza = 300;
    nr_ratze_impuscate = 0;
}

void Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));

}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, color, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y); //1280x720
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    matriceMiscareRatza = glm::mat3(1);

    durata_prestatie += 1;
    
    // Setez variabile de miscare in functie de starea ratzei

    if (durata_prestatie > 1000)
    {
        evadare = 1;
    }

    if (impuscata == 0)
    {
        if (evadare == 0)
        {
            if (ciocnire == 1)
            {
                translateX += -sens_zbor * deltaTimeSeconds * viteza_ratza;
            }
            else
            {
                translateX += sens_zbor * deltaTimeSeconds * viteza_ratza;
            }

            if (ciocnire_OY == 1)
            {
                translateY -= deltaTimeSeconds * 100; 
            }
            else
            {
                translateY += deltaTimeSeconds * 100; //((rand() % (150 - 30)) + 30);
            }
        }
        else
        {
            translateY += deltaTimeSeconds * 300;
        }
        
    }
    else
    {
        translateY -= deltaTimeSeconds * 500; // viteza cu care cade dupa impuscare
    }

    matriceMiscareRatza *= transform2D::Translate(translateX, translateY);

    
    // Dat din aripaDRP (aripa jos) 

    if (angularStep1 >= 0.1) // cand creste de 5 grade, trebuie sa o ia inspre trunchi
    {
        sign1 = -1;

    }
    if (angularStep1 < -0.5) // cand scade de -28 de grade, trebuie sa o ia inspre cap
    {
        sign1 = 1;

    }

    angularStep1 += sign1 * deltaTimeSeconds * 1.5;
    matriceRotatieAripaDRP = glm::mat3(1);
    matriceRotatieAripaDRP *= transform2D::Translate(translateX, translateY);
    matriceRotatieAripaDRP *= transform2D::Translate(Fprimx, Fprimy);
    matriceRotatieAripaDRP *= transform2D::Rotate(angularStep1);
    matriceRotatieAripaDRP *= transform2D::Translate(-Fprimx, -Fprimy);
    

    // Dat din aripaSTG (aripa sus)  

    
    if (angularStep2 <= -0.1) // cand scade de -5 grade, trebuie sa o ia inspre trunchi  
    {
        sign2 = 1;
    }
    if (angularStep2 > 0.5) // cand creste de 28 de grade, trebuie sa o ia inspre cap
    {
        sign2 = -1;
    }
 

    angularStep2 += sign2 * deltaTimeSeconds * 1.5;
    matriceRotatieAripaSTG = glm::mat3(1);
    matriceRotatieAripaSTG *= transform2D::Translate(translateX, translateY);
    matriceRotatieAripaSTG *= transform2D::Translate(Fx, Fy);
    matriceRotatieAripaSTG *= transform2D::Rotate(angularStep2); 
    matriceRotatieAripaSTG *= transform2D::Translate(-Fx, -Fy);
    
    // Conditiile de ciocnire:
    if (sens_zbor == 1)
    {
        if (translateX >= resolution.x - 155)
        {
            ciocnire = 1;
        }
        else if (translateX <= 0)
        {
            ciocnire = 0;
        }
    }
    else if (sens_zbor == -1)
    {
        matriceMiscareRatza *= transform2D::Translate(77.5, 60);
        matriceMiscareRatza *= transform2D::Rotate(pi);
        matriceMiscareRatza *= transform2D::Translate(-77.5, -60);

        matriceRotatieAripaDRP *= transform2D::Translate(77.5, 60);
        matriceRotatieAripaDRP *= transform2D::Rotate(pi);
        matriceRotatieAripaDRP *= transform2D::Translate(-77.5, -60);

        matriceRotatieAripaSTG *= transform2D::Translate(77.5, 60);
        matriceRotatieAripaSTG *= transform2D::Rotate(pi);
        matriceRotatieAripaSTG *= transform2D::Translate(-77.5, -60);

        if (translateX <= 0)
        {
            ciocnire = 1;
        }
        else if (translateX >= resolution.x - 155)
        {
            ciocnire = 0;
        }
    }
   
    if (ciocnire == 1) 
    {
        matriceMiscareRatza *= transform2D::Translate(77.5, 60);
        matriceMiscareRatza *= transform2D::Rotate(pi);
        matriceMiscareRatza *= transform2D::Translate(-77.5, -60);

        matriceRotatieAripaDRP *= transform2D::Translate(77.5, 60);
        matriceRotatieAripaDRP *= transform2D::Rotate(pi);
        matriceRotatieAripaDRP *= transform2D::Translate(-77.5, -60);

        matriceRotatieAripaSTG *= transform2D::Translate(77.5, 60);
        matriceRotatieAripaSTG *= transform2D::Rotate(pi);
        matriceRotatieAripaSTG *= transform2D::Translate(-77.5, -60);
    }

    // In sfarsit, afisez pasarea cu toate componentele
    RenderMesh2D(meshes["choc"], shaders["VertexColor"], matriceMiscareRatza);
    RenderMesh2D(meshes["cap"], shaders["VertexColor"], matriceMiscareRatza);
    RenderMesh2D(meshes["trunchi"], shaders["VertexColor"], matriceMiscareRatza);
    RenderMesh2D(meshes["aripaDRP"], shaders["VertexColor"], matriceRotatieAripaDRP);
    RenderMesh2D(meshes["aripaSTG"], shaders["VertexColor"], matriceRotatieAripaSTG); 

    // Afisare gloante
    for (int i = 1; i <= nr_gloante && vieti != 0; i++)
    {
        matriceMiscareRatza = glm::mat3(1);
        matriceMiscareRatza *= transform2D::Translate(i * 80 - 18, resolution.y - 130); // doar asez gloantele pe ecran
        matriceMiscareRatza *= transform2D::Scale(2, 2);
        RenderMesh2D(meshes["glontz"], shaders["VertexColor"], matriceMiscareRatza);
    }

    // Afisare vieti
    for (int i = 1; i <= vieti; i++)
    {
        matriceMiscareRatza = glm::mat3(1);
        matriceMiscareRatza *= transform2D::Translate(i * 80 - 30, resolution.y - 70);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], matriceMiscareRatza);
    }
    
    // Afisare scor
    matriceMiscareRatza = glm::mat3(1);
    matriceMiscareRatza *= transform2D::Translate(resolution.x - 430, resolution.y - 100);
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], matriceMiscareRatza);
    
    for (int i = 0; i < nr_ratze_impuscate; i++)
    {
        matriceMiscareRatza = glm::mat3(1);
        //RenderMesh2D(meshes["square2"], shaders["VertexColor"], matriceMiscareRatza);
        matriceMiscareRatza *= transform2D::Translate(resolution.x - 430 + i*80, resolution.y - 100); // 80 = side
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], matriceMiscareRatza);

        if (vieti == 0) break;
    }

    if (translateY >= resolution.y - latime_ratza) 
    {
        ciocnire_OY = 1;
    }
    else if (translateY <= 0)
    {
        ciocnire_OY = 0;
    }



    ////  EVADARE si IMPUSCARE  ////

    if (translateY >= resolution.y + 400) // Ratza a scapat
    { 
        
        // Daca rata a evadat, reapare la baza ecranului - se recicleaza rata la nesfarsit
        // Ratza se translateaza la loc de unde a plecat (fundul ecranului). Este in regula ca Y sa ramana mereu acelasi (< 0), dar X ar trebui randomizat, ca sa nu plece mereu din acelasi loc

        // Setez de unde apare urmatoarea rata si sensul in care zboara
        if (((rand() % (2 - 0)) + 0) % 2 == 0)
        {
            sens_zbor = 1;
        }
        else
        {
            sens_zbor = -1;
        }
        translateX = (rand() % (800 - 600)) + 600;
        translateY = -200;  // SCHIMBA CAT DE REPEDE SA SE INTOARCA RATA DUPA CE A FOST IMPUSCATA

        // Actualizez caracteristicile ratzei
        ciocnire = 0;
        impuscata = 0;
        nr_gloante = 3;
        evadare = 0;
        durata_prestatie = 0;   
        contor_ratze++;
        vieti--; // Scade numarul de vieti, pentru ca evadat

        if (vieti == 0)
        {
            cout << "A castigat ratza" << endl;
        }

        if (contor_ratze % 5 == 0)
        {
            viteza_ratza += viteza_ratza / 3;
        }
    }
    else if (impuscata == 1 && translateY < -100) // Ratza a fost impuscata
    {
        // Setez de unde apare urmatoarea rata si sensul in care zboara
        if ( ( ( rand() % (2 - 0) ) + 0) % 2 == 0 )
        {
            sens_zbor = 1;
        }
        else
        {
            sens_zbor = -1;
        }
        translateX = (rand() % (800 - 600)) + 600;
        translateY = -200;  // SCHIMBA CAT DE REPEDE SA SE INTOARCA RATA DUPA CE A FOST IMPUSCATA

        // Actualizez caracteristicile ratzei
        ciocnire = 0;
        impuscata = 0;
        nr_gloante = 3;
        evadare = 0;
        durata_prestatie = 0;
        contor_ratze++;

        if (contor_ratze % 5 == 0)
        {
            viteza_ratza += viteza_ratza / 3;
        }
    }

} 


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();

    if ( mouseX > translateX && mouseX < (translateX + 155) && mouseY < resolution.y - translateY && mouseY > resolution.y - (translateY + 100) ) // modif + 100 ala
    {
        impuscata = 1;

        if (nr_ratze_impuscate == 5)
        {
            cout << "Ai castigat! La culcare" << endl;
        }
        else
        {
            nr_ratze_impuscate++;
        }
    }

    nr_gloante--;
    
    if (nr_gloante == 0)
    {
        evadare = 1;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}




