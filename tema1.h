#pragma once

#include <vector>
#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices); // ???
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 matriceMiscareRatza;
        glm::mat3 matriceRotatieAripaSTG;
        glm::mat3 matriceRotatieAripaDRP;
        float cx, cy;
        float translateX, translateY;
        float scaleX, scaleY;

        double angularStep1, angularStep2, angularStep3;
        int sign1, sign2;
        float Fx, Fy, Fprimx, Fprimy;

        float startx, starty;
        double unghi_jos, unghi_sus;

        int ciocnire;
        int ciocnire_OY;
        double pi;

        int margineXdrp_ecran;

        int impuscata;
        int nr_gloante;
        int vieti;
        int fara_gloante;
        int sens_zbor;
        int nr_ciocniri;
        int durata_prestatie;
        int latime_ratza;
        int evadare;
        int contor_ratze;
        int viteza_ratza;
        int nr_ratze_impuscate;
    };
}   // namespace m1
