#pragma once
#include "UIBase.hpp"

class BottomUI : public UIBase {
public:
    BottomUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        ImGui::SetNextWindowSize({1280, 100});
        ImGui::SetNextWindowPos({0, 620});

        bool isNight = (gs->state.farm.Hour >= 18 || gs->state.farm.Hour < 6);
        ImVec4 bgCol = isNight ? ImVec4(0.15f, 0.15f, 0.22f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 textCol = isNight ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgCol);
        ImGui::PushStyleColor(ImGuiCol_Text, textCol);

        ImGui::Begin("BottomBar", nullptr, flgs);

        // TODO: GameState에 bool showInv; 변수 추가
	// 인벤토리 버튼이 눌리면 showInv가 true로 바뀜
	// if (gs->showInv) 이런 식으로 if문을 바꾸면 정상 작동.
        
        if (!gs->showInv) renderStat(); else renderInv();

        ImGui::End();
        
        ImGui::PopStyleColor(2);
    }

private:
    static bool isTrapTab;

    void renderStat() {
        float windowWidth = ImGui::GetWindowSize().x;
        float contentWidth = 1100.0f; 

        // 하단 바 콘텐츠 수직 중앙 정렬 시작점 설정
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
        
        ImGui::BeginGroup(); 
        
        // 1. 총알 표시 영역 (제공된 새총 이미지 사용)
        ImGui::SetCursorPosX(50); 
        
        sf::Sprite slingshotSprite;
        slingshotSprite.setTexture(gs->slingshotTexture);
        // --- 수정된 부분: 새총 이미지 크기를 하단바에 맞춰 축소 ---
        slingshotSprite.setScale({1.2f, 1.2f});
        
        // 이미지를 살짝 위로 정렬 (글자와 맞추기 위함)
        ImVec2 cur = ImGui::GetCursorPos();
        ImGui::SetCursorPos({cur.x, cur.y - 10.0f});
        ImGui::Image(slingshotSprite);
        
        ImGui::SameLine(); 
        
        // --- 수정된 부분: 새총 이미지와 텍스트의 수직 정렬을 맞춤 ---
        ImGui::SetCursorPos({ImGui::GetCursorPosX(), cur.y + 10.0f}); 
        ImGui::Text("x%d", gs->state.inventory.Bullets); 

        // 2. 상점 및 재생속도 영역 (오프셋 수정)
        ImGui::SameLine(200); 
        if (gs->status == Status::PM) ImGui::BeginDisabled();
        if (ImGui::Button("상점", {60, 40})) {
            // TODO: 상점 UI 오픈
        }
        if (gs->status == Status::PM) ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::Text("/");
        ImGui::SameLine();

        char sTxt[32];
        sprintf(sTxt, "재생속도(%dx)", gs->PlaybackSpeed);
        if (ImGui::Button(sTxt, {100, 40})) {
            // TODO: 배속 변경 
        }

        // 3. 날짜 및 시간 영역
        ImGui::SameLine(500); 
        ImGui::Text("Day %d | %02d:%02d", gs->state.farm.Day, gs->state.farm.Hour, gs->state.farm.Minute);

        // 4. 인벤토리 확인 버튼 영역
        ImGui::SameLine(800); 
        if (ImGui::Button("인벤토리 확인", {150, 40})) {
            // TODO: showInv = true;
            const_cast<GameState*>(gs)->showInv = true;
        }

        // 5. Cash 표시 영역
        ImGui::SameLine(1080); 
        ImGui::Text("Cash: $%d", gs->state.Money);

        ImGui::EndGroup(); 
    }

    void renderInv() {
        if (ImGui::Button("Back", {80, 80})) { 
            /* TODO: [Role 3] showInv = false; */ 
            const_cast<GameState*>(gs)->showInv = false;
        }
        ImGui::SameLine(120);
        
        ImGui::BeginGroup();

        if (!isTrapTab) {
            for (auto const& [type, count] : gs->state.inventory.SeedCount) { 
                if (type == SeedType::NONE) continue;
                
                ImGui::PushID((int)type);
                if (ImGui::Button("Seed\nIMG", {60, 60})) { 
                    // TODO: 이 씨앗을 심을 아이템으로 선택 
                }
                ImGui::Text("x%d", count);
                ImGui::SameLine(0, 20);
                ImGui::PopID();
            }
        } 
        else {
            for (auto const& [type, count] : gs->state.inventory.TrapCount) { 
                if (type == TrapType::NONE) continue;
                
                ImGui::PushID((int)type + 100); 
                if (ImGui::Button("Trap\nIMG", {60, 60})) { 
                    // TODO: [Role 3] 이 함정을 설치할 아이템으로 선택 
                }
                ImGui::Text("x%d", count);
                ImGui::SameLine(0, 20);
                ImGui::PopID();
            }
        }
        
        ImGui::EndGroup();

        ImGui::SameLine(1100);
        
        if (ImGui::Button("Seed/Trap\nSwitch", {120, 80})) { 
            isTrapTab = !isTrapTab; 
        }
    }
};

bool BottomUI::isTrapTab = false;
