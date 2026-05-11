#pragma once
#include "UIBase.hpp"

class BottomUI : public UIBase {
public:
    BottomUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({1280, 100});
        ImGui::SetNextWindowPos({0, 620});

        ImGui::Begin("StatBar", nullptr, flgs);

        // 총알 
        ImGui::Text("Ammo: x%d", gs->state.inventory.Bullets);
        
        ImGui::SameLine(200);

        // 상점 및 배속 
        if (ImGui::Button("Shop / Speed", {150, 40})) {
            // TODO:  상태에 따라 상점 오픈 또는 PlaybackSpeed 조절 
        }

        ImGui::SameLine(520);

        // 날짜 및 시간
        ImGui::Text("Day %d | %02d:%02d", gs->state.farm.Day, gs->state.farm.Hour, gs->state.farm.Minute);

        ImGui::SameLine(850);

        // 인벤토리
        if (ImGui::Button("Inventory", {150, 40})) {
            // TODO: [Role 3] 인벤토리 UI 활성화 토글 [cite: 30, 44]
        }

        ImGui::SameLine(1120);

        // 돈
        ImGui::Text("Cash: $%d", gs->state.Money);

        ImGui::End();
    }
};
