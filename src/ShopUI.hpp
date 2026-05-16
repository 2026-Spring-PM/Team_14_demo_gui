#pragma once
#include "UIBase.hpp"

class ShopUI : public UIBase {
public:
    ShopUI(const GameState* s) : UIBase(s) {}

    void Render() override {
        ImGui::SetNextWindowSize({750.0f, 500.0f});
        ImGui::SetNextWindowPos({265.0f, 110.0f});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        
        ImGui::Begin("ShopWindow", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

        ImVec2 windowPos = ImGui::GetWindowPos();

        // 1. 전체 배경
        if (gs->shopBgTexture.getSize().x > 0) {
            sf::Sprite bgSprite(gs->shopBgTexture);
            float scaleX = 750.0f / gs->shopBgTexture.getSize().x;
            float scaleY = 500.0f / gs->shopBgTexture.getSize().y;
            bgSprite.setScale({scaleX, scaleY});
            ImGui::Image(bgSprite);
        } else {
            ImGui::GetWindowDrawList()->AddRectFilled(
                windowPos, ImVec2(windowPos.x + 750.0f, windowPos.y + 500.0f), IM_COL32(204, 102, 34, 255)
            );
            ImGui::Dummy(ImVec2(750.0f, 500.0f)); 
        }

        ImGui::SetCursorPos({0.0f, 0.0f});

        // 2. 상점 타이틀
        ImGui::SetCursorPos({40.0f, 25.0f}); 
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); 
        ImGui::Text("상점");
        ImGui::PopStyleColor();

        // 3. 돌아가기 버튼 (투명)
        ImGui::SetCursorPos({590.0f, 25.0f}); 
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.1f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f)); 
        
        if (ImGui::Button("돌아가기", {120.0f, 40.0f})) {
            // TODO: 화면 닫기 또는 맵으로 돌아가는 로직 연결
        }
        ImGui::PopStyleColor(4); 

        // 4. 아이템 리스트 설정
        float startX = 30.0f;
        float startY = 80.0f;
        float btnW = 90.0f;
        float btnH = 90.0f;
        float gapX = 15.0f;
        float gapY = 35.0f; 

        auto DrawShopItem = [&](const sf::Texture& tex, const char* id, const char* priceStr, float x, float y) {
            ImGui::SetCursorPos({x, y});
            bool clicked = false;

            if (tex.getSize().x > 0) {
                sf::Sprite spr(tex);
                spr.setScale({btnW / tex.getSize().x, btnH / tex.getSize().y});
                ImGui::Image(spr);

                ImGui::SetCursorPos({x, y});
                if (ImGui::InvisibleButton(id, {btnW, btnH})) clicked = true;
            } else {
                if (ImGui::Button(id, {btnW, btnH})) clicked = true;
            }

            ImVec2 textSize = ImGui::CalcTextSize(priceStr);
            ImGui::SetCursorPos({x + (btnW - textSize.x) * 0.5f, y + btnH + 5.0f});
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
            ImGui::Text("%s", priceStr);
            ImGui::PopStyleColor();

            return clicked;
        };

        // 1열 (씨앗)
        if (DrawShopItem(gs->riceSeedTexture, "##Seed1", "10$", startX, startY)) { 
            // TODO: RiceSeed 구매 로직 연결
        }
        if (DrawShopItem(gs->potatoSeedTexture, "##Seed2", "20$", startX + btnW + gapX, startY)) { 
            // TODO: PotatoSeed 구매 로직 연결
        }
        if (DrawShopItem(gs->carrotSeedTexture, "##Seed3", "30$", startX + (btnW + gapX) * 2, startY)) { 
            // TODO: CarrotSeed 구매 로직 연결
        }

        // 2열 (함정 동물)
        float row2Y = startY + btnH + gapY;
        if (DrawShopItem(gs->cowTrapTexture, "##Trap1", "100$", startX, row2Y)) { 
            // TODO: CowTrap 구매 로직 연결
        }
        if (DrawShopItem(gs->pigTrapTexture, "##Trap2", "200$", startX + btnW + gapX, row2Y)) { 
            // TODO: PigTrap 구매 로직 연결
        }
        if (DrawShopItem(gs->horseTrapTexture, "##Trap3", "300$", startX + (btnW + gapX) * 2, row2Y)) { 
            // TODO: HorseTrap 구매 로직 연결
        }

        // 3열 (총알 - 돌)
        float row3Y = row2Y + btnH + gapY;
        if (DrawShopItem(gs->stoneTexture, "##Bullet", "50$", startX, row3Y)) { 
            // TODO: Bullet(Stone) 구매 로직 연결
        }

        // 5. 룰렛 영역
        float rouletteX = 460.0f;
        ImGui::SetCursorPos({rouletteX, startY});
        
        // 룰렛 이미지 렌더링
        if (gs->rouletteTexture.getSize().x > 0) {
            sf::Sprite rouletteSpr(gs->rouletteTexture);
            float rScaleX = 250.0f / gs->rouletteTexture.getSize().x;
            float rScaleY = 250.0f / gs->rouletteTexture.getSize().y;
            rouletteSpr.setScale({rScaleX, rScaleY});
            ImGui::Image(rouletteSpr);
        } else {
            ImGui::Button("ROULETTE\nIMG", {250.0f, 250.0f}); 
        }

        // 룰렛 돌리기 버튼 (투명 배경, 검정 글씨)
        ImGui::SetCursorPos({rouletteX, startY + 250.0f + 20.0f});
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.1f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.2f)); 
        
        if (ImGui::Button("룰렛 돌리기\n10$", {250.0f, 60.0f})) { 
            // TODO: 룰렛 동작 로직 연결
        }
        ImGui::PopStyleColor(4);

        ImGui::End();
        ImGui::PopStyleVar(2);
    }
};
