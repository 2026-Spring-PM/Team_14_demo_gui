#pragma once
#include "UIBase.hpp"

class MainUI : public UIBase {
public:
    MainUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        ImGui::SetNextWindowSize({1280.0f, 720.0f});
        ImGui::SetNextWindowPos({0.0f, 0.0f});
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        
        ImGui::Begin("MainMenu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

        if (gs->mainMenuBgTexture.getSize().x > 0) {
            sf::Sprite bgSprite(gs->mainMenuBgTexture);
            float scaleX = 1280.0f / gs->mainMenuBgTexture.getSize().x;
            float scaleY = 720.0f / gs->mainMenuBgTexture.getSize().y;
            bgSprite.setScale({scaleX, scaleY});
            ImGui::Image(bgSprite);
        }

        float boardStartX = 490.0f;  
        float boardStartY = 310.0f;  
        float btnWidth = 300.0f;     
        float btnHeight = 125.0f;   
        float btnSpacing = 135.0f;  

        if (gs->newGameBtnTexture.getSize().x > 0) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.15f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));

            sf::Sprite btnSprite(gs->newGameBtnTexture);
            btnSprite.setScale({btnWidth / gs->newGameBtnTexture.getSize().x, btnHeight / gs->newGameBtnTexture.getSize().y});
            
            ImGui::SetCursorPos({boardStartX, boardStartY});
            ImVec2 clickPos = ImGui::GetCursorPos();
            ImGui::Image(btnSprite);
            
            ImGui::SetCursorPos(clickPos);
            if (ImGui::Button("##newGameClick", {btnWidth, btnHeight})) {
                const_cast<GameState*>(gs)->status = Status::AM;
                
            }
            ImGui::PopStyleColor(3);
        } else {
            ImGui::SetCursorPos({boardStartX, boardStartY});
            if (ImGui::Button("새 게임 (New Game)", {btnWidth, btnHeight})) {
                const_cast<GameState*>(gs)->status = Status::AM;
            }
        }

        if (gs->exitBtnTexture.getSize().x > 0) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.15f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));

            sf::Sprite btnSprite(gs->exitBtnTexture);
            btnSprite.setScale({btnWidth / gs->exitBtnTexture.getSize().x, btnHeight / gs->exitBtnTexture.getSize().y});
            
            ImGui::SetCursorPos({boardStartX, boardStartY + btnSpacing});
            ImVec2 clickPos = ImGui::GetCursorPos();
            ImGui::Image(btnSprite);
            
            ImGui::SetCursorPos(clickPos);
            if (ImGui::Button("##exitClick", {btnWidth, btnHeight})) {
                std::exit(0);
            }
            ImGui::PopStyleColor(3);
        } else {
            ImGui::SetCursorPos({boardStartX, boardStartY + btnSpacing});
            if (ImGui::Button("게임 종료 (Exit)", {btnWidth, btnHeight})) {
                std::exit(0);
            }
        }

        ImGui::End();
        ImGui::PopStyleVar(2);
    }
};
