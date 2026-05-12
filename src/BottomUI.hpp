#pragma once
#include "UIBase.hpp"

class BottomUI : public UIBase {
public:
    BottomUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        ImGui::SetNextWindowSize({1280, 100});
        ImGui::SetNextWindowPos({0, 620});

        ImGui::Begin("BottomBar", nullptr, flgs);

        // TODO: GameState에 bool showInv; 변수 추가
	// 인벤토리 버튼이 눌리면 showInv가 true로 바뀜
	// if (gs->showInv) 이런 식으로 if문을 바꾸면 정상 작동.
        bool isInv = false; // 임시 변수

        if (!isInv) renderStat(); else renderInv();

        ImGui::End();
    }

private:
    void renderStat() {
        ImGui::Text("Ammo: x%d", gs->state.inventory.Bullets); [cite: 77, 93]
        
        ImGui::SameLine(200);
        if (gs->status == Status::PM) ImGui::BeginDisabled();
        if (ImGui::Button("상점", {60, 40})) {
            // TODO: 상점 UI 오픈
        }
        if (gs->status == Status::PM) ImGui::EndDisabled();

        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Text("/");
        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);

        char sTxt[32];
        sprintf(sTxt, "재생속도(%dx)", gs->PlaybackSpeed); [cite: 63]
        if (ImGui::Button(sTxt, {100, 40})) {
            // TODO: 배속 변경 
        }

        ImGui::SameLine(520);
        ImGui::Text("Day %d | %02d:%02d", gs->state.farm.Day, gs->state.farm.Hour, gs->state.farm.Minute); [cite: 28, 98]

        ImGui::SameLine(850);
        if (ImGui::Button("인벤토리 확인", {150, 40})) { [cite: 101]
            // TODO: showInv = true;
        }

        ImGui::SameLine(1120);
        ImGui::Text("Cash: $%d", gs->state.Money); [cite: 35, 102]
    }

    void renderInv() {
        if (ImGui::Button("Back", {80, 80})) { 
            /* TODO: [Role 3] showInv = false; */ 
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
