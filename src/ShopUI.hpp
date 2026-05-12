#pragma once
#include "UIBase.hpp"

class ShopUI : public UIBase {
public:
    ShopUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        // TODO: gs->showShop 값이 true일 때만 호출되도록 제어

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.75f, 0.35f, 0.10f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.9f, 0.5f, 0.2f, 1.0f));

        auto flgs = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
        
        ImGui::SetNextWindowSize({800, 450});
        ImGui::SetNextWindowPos({240, 100}); 

        ImGui::Begin("ShopPopup", nullptr, flgs);

        ImGui::Text("상점");
        ImGui::SameLine(680);
        if (ImGui::Button("돌아가기", {100, 30})) {
            // TODO: 상점 닫기 (gs->showShop = false;)
        }
        ImGui::Separator();

        ImGui::BeginGroup();
        renderItems();
        ImGui::EndGroup();

        ImGui::SameLine(450);

        ImGui::BeginGroup();
        renderRoulette();
        ImGui::EndGroup();

        ImGui::End();

        ImGui::PopStyleColor(2); 
    }

private:
    void renderItems() {
        ImVec2 iSz = {80, 80};

        if (ImGui::Button("Seed1\n10$", iSz)) { /* TODO: 구매 */ } ImGui::SameLine();
        if (ImGui::Button("Seed2\n20$", iSz)) { /* TODO: 구매 */ } ImGui::SameLine();
        if (ImGui::Button("Seed3\n30$", iSz)) { /* TODO: 구매 */ }
        
        ImGui::Spacing();

        if (ImGui::Button("Trap1\n100$", iSz)) { /* TODO: 구매 */ } ImGui::SameLine();
        if (ImGui::Button("Trap2\n200$", iSz)) { /* TODO: 구매 */ } ImGui::SameLine();
        if (ImGui::Button("Trap3\n300$", iSz)) { /* TODO: 구매 */ }

        ImGui::Spacing();

        if (ImGui::Button("Bullet\n50$", iSz)) { /* TODO: 구매 */ }
    }

    void renderRoulette() {
        ImGui::Button("ROULETTE\nIMG", {250, 250}); 
        
        ImGui::Spacing();
        
        // 룰렛
        if (ImGui::Button("룰렛 돌리기\n10$", {250, 50})) { 
            // TODO:  도박 실행 및 결과
        }
    }
};
