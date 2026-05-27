#pragma once
#include "UIBase.hpp"

class BottomUI : public UIBase {
public:
    BottomUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        ImGui::SetNextWindowSize({1280, 100});
        ImGui::SetNextWindowPos({0, 620});

        bool isNight = (gs->farm.Hour >= 18 || gs->farm.Hour < 6);
        ImVec4 bgCol = isNight ? ImVec4(0.15f, 0.15f, 0.22f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 textCol = isNight ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
        ImGui::PushStyleColor(ImGuiCol_Text, textCol);

        ImGui::Begin("BottomBar", nullptr, flgs);
        
        if (!gs->showInv) renderStat(); else renderInv();

        ImGui::End();
        
        ImGui::PopStyleColor(2);
    }

private:
    static bool isTrapTab;

    void renderStat() {
        float windowWidth = ImGui::GetWindowSize().x;
        float contentWidth = 1100.0f; 

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
        
        ImGui::BeginGroup(); 
        
        ImGui::SetCursorPosX(50); 
        
        sf::Sprite slingshotSprite;
        slingshotSprite.setTexture(gs->slingshotTexture);
        slingshotSprite.setScale({1.2f, 1.2f});
        
        ImVec2 cur = ImGui::GetCursorPos();
        ImGui::SetCursorPos({cur.x, cur.y - 10.0f});
        ImGui::Image(slingshotSprite);
        
        ImGui::SameLine();
        ImGui::SetCursorPos({ImGui::GetCursorPosX(), cur.y + 10.0f}); 
        ImGui::Text("x%d", gs->inventory.Bullets); 

        ImGui::SameLine(200); 
        if (gs->status == Status::PM) ImGui::BeginDisabled();
        if (ImGui::Button("상점", {60, 40})) {
            if (const_cast<GameState*>(gs)->CanVisitShop()) {
                const_cast<GameState*>(gs)->Update();
                const_cast<GameState*>(gs)->status = Status::SHOP;
            }
        }
        if (gs->status == Status::PM) ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::Text("/");
        ImGui::SameLine();

        char sTxt[32];
        sprintf(sTxt, "재생속도(%dx)", gs->PlaybackSpeed);
        if (ImGui::Button(sTxt, {130, 40})) {
            const_cast<GameState*>(gs)->Update();
            int nextSpeed = gs->PlaybackSpeed + 1;
            if (nextSpeed > 3) {
                nextSpeed = 1;
            }
            const_cast<GameState*>(gs)->ChangePlaybackSpeed(nextSpeed);

        }
        

        ImGui::SameLine(500); 
        ImGui::Text("Day %d | %02d:%02d", gs->farm.Day, gs->farm.Hour, gs->farm.Minute);

        ImGui::SameLine(800); 
        if (ImGui::Button("인벤토리 확인", {150, 40})) {
            const_cast<GameState*>(gs)->showInv = true;
        }

        ImGui::SameLine(1080); 
        ImGui::Text("Cash: $%d", gs->Money);

        ImGui::EndGroup(); 
    }

    void renderInv() {
        if (ImGui::Button("돌아가기", {80, 80})) { 
            const_cast<GameState*>(gs)->showInv = false;
        }
        ImGui::SameLine(120);
        
        if (ImGui::Button("씨앗/함정\n변경 버튼", {120, 80})) { 
            isTrapTab = !isTrapTab; 
        }
        ImGui::SameLine(280);
        
        // 1. 씨앗 탭 렌더링
        if (!isTrapTab) {
            for (auto const& [type, count] : gs->inventory.SeedCount) { 
                if (type == SeedType::NONE) continue;
                
                ImGui::PushID((int)type);
                ImGui::BeginGroup();

                sf::Texture* tex = nullptr;
                if (type == SeedType::SEED1) tex = const_cast<sf::Texture*>(&gs->riceSeedTexture);
                else if (type == SeedType::SEED2) tex = const_cast<sf::Texture*>(&gs->potatoSeedTexture);
                else if (type == SeedType::SEED3) tex = const_cast<sf::Texture*>(&gs->carrotSeedTexture);

                ImVec2 startPos = ImGui::GetCursorPos();
                
                if (tex && tex->getSize().x > 0) {
                    sf::Sprite seedSprite(*tex);
                    float scaleX = 60.0f / tex->getSize().x;
                    float scaleY = 60.0f / tex->getSize().y;
                    seedSprite.setScale({scaleX, scaleY});
                    ImGui::Image(seedSprite);
                } else {
                    ImGui::Dummy({60.0f, 60.0f});
                }
                
                ImGui::SetCursorPos(startPos);
                
                // [선택 상태 시각화] 선택된 씨앗이면 배경을 반투명한 흰색으로 하이라이트
                bool isSelected = (gs->selectedSeed == type);
                ImVec4 btnColor = isSelected ? ImVec4(1.0f, 1.0f, 1.0f, 0.3f) : ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                
                ImGui::PushStyleColor(ImGuiCol_Button, btnColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.4f)); 
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));

                if (ImGui::Button("##seedBtn", {60, 60})) { 
                    const_cast<GameState*>(gs)->selectedSeed = type;
                    const_cast<GameState*>(gs)->selectedTrap = TrapType::NONE;
                }
                
                ImGui::PopStyleColor(3);

                ImGui::SameLine();
                ImGui::SetCursorPosY(startPos.y + 20.0f); 
                ImGui::Text("X %d", count);
                
                ImGui::EndGroup(); 
                ImGui::SameLine(0, 20); 
                ImGui::PopID();
            }
        } 
        // 2. 함정 탭 렌더링
        else {
            for (auto const& [type, count] : gs->inventory.TrapCount) { 
                if (type == TrapType::NONE) continue;
                
                ImGui::PushID((int)type + 100); 
                ImGui::BeginGroup();

                sf::Texture* tex = nullptr;
                if (type == TrapType::ANIMAL1) tex = const_cast<sf::Texture*>(&gs->cowTrapTexture);
                else if (type == TrapType::ANIMAL2) tex = const_cast<sf::Texture*>(&gs->pigTrapTexture);
                else if (type == TrapType::ANIMAL3) tex = const_cast<sf::Texture*>(&gs->horseTrapTexture);

                ImVec2 startPos = ImGui::GetCursorPos();

                if (tex && tex->getSize().x > 0) {
                    sf::Sprite trapSprite(*tex);
                    float scaleX = 60.0f / tex->getSize().x;
                    float scaleY = 60.0f / tex->getSize().y;
                    trapSprite.setScale({scaleX, scaleY});
                    ImGui::Image(trapSprite);
                } else {
                    ImGui::Dummy({60.0f, 60.0f});
                }
                
                ImGui::SetCursorPos(startPos);
                
                // [선택 상태 시각화] 선택된 함정이면 배경을 반투명한 흰색으로 하이라이트
                bool isSelected = (gs->selectedTrap == type);
                ImVec4 btnColor = isSelected ? ImVec4(1.0f, 1.0f, 1.0f, 0.3f) : ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

                ImGui::PushStyleColor(ImGuiCol_Button, btnColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.4f)); 
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));

                if (ImGui::Button("##trapBtn", {60, 60})) { 
                    const_cast<GameState*>(gs)->selectedTrap = type;
                    const_cast<GameState*>(gs)->selectedSeed = SeedType::NONE;
                }
                
                ImGui::PopStyleColor(3);

                ImGui::SameLine();
                ImGui::SetCursorPosY(startPos.y + 20.0f);
                ImGui::Text("X %d", count);
                
                ImGui::EndGroup();
                ImGui::SameLine(0, 20);
                ImGui::PopID();
            }
        }
    }
};

bool BottomUI::isTrapTab = false;
