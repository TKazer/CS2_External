#pragma once
#include "OS-ImGui.h"

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui.cpp
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/9/17	11:25
****************************************************/

// OS-ImGui Draw 绘制功能
namespace OSImGui
{
    void OSImGui::Text(std::string Text, Vec2 Pos, ImColor Color, float FontSize, bool KeepCenter)
    {
        if (!KeepCenter)
        {
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
        }
        else
        {
            float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
            ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
        }
    }

    void OSImGui::StrokeText(std::string Text, Vec2 Pos, ImColor Color, float FontSize, bool KeepCenter)
    {
        this->Text(Text, Vec2(Pos.x - 1, Pos.y + 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x - 1, Pos.y - 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x + 1, Pos.y + 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Vec2(Pos.x + 1, Pos.y - 1), ImColor(0, 0, 0), FontSize, KeepCenter);
        this->Text(Text, Pos, Color, FontSize, KeepCenter);
    }

    void OSImGui::Rectangle(Vec2 Pos, Vec2 Size, ImColor Color, float Thickness, float Rounding)
    {
        ImGui::GetBackgroundDrawList()->AddRect(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, Color, Rounding, 0, Thickness);
    }

    void OSImGui::RectangleFilled(Vec2 Pos, Vec2 Size, ImColor Color, float Rounding, int Nums)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All;
        ImVec2 a = Pos.ToImVec2();
        ImVec2 b = { Pos.x + Size.x,Pos.y + Size.y };
        Rounding = ImMin<float>(Rounding, fabsf(Size.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
        Rounding = ImMin<float>(Rounding, fabsf(Size.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

        if (Rounding <= 0.0f || rounding_corners == 0)
        {
            DrawList->PathLineTo(a);
            DrawList->PathLineTo(ImVec2(b.x, a.y));
            DrawList->PathLineTo(b);
            DrawList->PathLineTo(ImVec2(a.x, b.y));
        }
        else
        {
            DrawList->PathArcTo(ImVec2(a.x + Rounding, a.y + Rounding), Rounding, IM_PI, IM_PI / 2.f * 3.f, Nums);
            DrawList->PathArcTo(ImVec2(b.x - Rounding, a.y + Rounding), Rounding, IM_PI / 2.f * 3.f, IM_PI * 2.f, Nums);
            DrawList->PathArcTo(ImVec2(b.x - Rounding, b.y - Rounding), Rounding, 0.f, IM_PI / 2.f, Nums);
            DrawList->PathArcTo(ImVec2(a.x + Rounding, b.y - Rounding), Rounding, IM_PI / 2.f, IM_PI, Nums);
        }
        DrawList->PathFillConvex(Color);
    }

    void OSImGui::Line(Vec2 From, Vec2 To, ImColor Color, float Thickness)
    {
        ImGui::GetBackgroundDrawList()->AddLine(From.ToImVec2(), To.ToImVec2(), Color, Thickness);
    }

    void OSImGui::Circle(Vec2 Center, float Radius, ImColor Color, float Thickness, int Num)
    {
        ImGui::GetBackgroundDrawList()->AddCircle(Center.ToImVec2(), Radius, Color, Num, Thickness);
    }

    void OSImGui::CircleFilled(Vec2 Center, float Radius, ImColor Color, int Num)
    {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(Center.ToImVec2(), Radius, Color, Num);
    }

    void OSImGui::ConnectPoints(std::vector<Vec2> Points, ImColor Color, float Thickness)
    {
        if (Points.size() <= 0)
            return;
        for (int i = 0; i < Points.size() - 1; i++)
        {
            Line(Points[i], Points[i + 1], Color, Thickness);
            if (i == Points.size() - 2)
                Line(Points[i + 1], Points[0], Color, Thickness);
        }
    }

    void OSImGui::Arc(ImVec2 Center, float Radius, ImColor Color, float Thickness, float Angle_begin, float Angle_end, float Nums)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        float angle = (Angle_end - Angle_begin) / Nums;
        for (int i = 0; i < Nums; i++)
        {
            float angle_ = i * angle + Angle_begin - IM_PI / 2;
            DrawList->PathLineTo({ Center.x - Radius * cos(angle_),Center.y - Radius * sin(angle_) });
        }
        DrawList->PathStroke(Color, false, Thickness);
    }

    void OSImGui::MyCheckBox(const char* str_id, bool* v)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* DrawList = ImGui::GetWindowDrawList();
        float Height = ImGui::GetFrameHeight();
        float Width = Height * 1.7f;
        float Radius = Height / 2 - 2;

        ImGui::InvisibleButton(str_id, ImVec2(Width, Height));
        if (ImGui::IsItemClicked())
            *v = !(*v);
        // 组件移动动画
        float t = *v ? 1.0f : 0.f;
        ImGuiContext& g = *GImGui;
        float AnimationSpeed = 0.08f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
        {
            float T_Animation = ImSaturate(g.LastActiveIdTimer / AnimationSpeed);
            t = *v ? (T_Animation) : (1.0f - T_Animation);
        }
        // 鼠标悬停颜色
        ImU32 Color;
        if (ImGui::IsItemHovered())
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.24f, 0.15f, 1.0f), ImVec4(0.55f, 0.85f, 0.13f, 1.000f), t));
        else
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.90f, 0.29f, 0.20f, 1.0f), ImVec4(0.60f, 0.90f, 0.18f, 1.000f), t));
        // 组件绘制
        DrawList->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + Width, p.y + Height), Color, Height);
        DrawList->AddCircleFilled(ImVec2(p.x + Radius + t * (Width - Radius * 2) + (t == 0 ? 2 : -2), p.y + Radius + 2), Radius, IM_COL32(255, 255, 255, 255), 360);
        DrawList->AddCircle(ImVec2(p.x + Radius + t * (Width - Radius * 2) + (t == 0 ? 2 : -2), p.y + Radius + 2), Radius, IM_COL32(20, 20, 20, 80), 360, 1);

        ImGui::SameLine();
        ImGui::Text(str_id);
    }

    void OSImGui::MyCheckBox2(const char* str_id, bool* v)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* DrawList = ImGui::GetWindowDrawList();
        float Height = ImGui::GetFrameHeight();
        float Width = Height * 1.7f;
        float Radius = Height / 2 - 2;

        ImGui::InvisibleButton(str_id, ImVec2(Width, Height));
        if (ImGui::IsItemClicked())
            *v = !(*v);
        // 组件移动动画
        float t = *v ? 1.0f : 0.f;
        ImGuiContext& g = *GImGui;
        float AnimationSpeed = 0.15f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
        {
            float T_Animation = ImSaturate(g.LastActiveIdTimer / AnimationSpeed);
            t = *v ? (T_Animation) : (1.0f - T_Animation);
        }
        // 鼠标悬停颜色
        ImU32 Color;
        if (ImGui::IsItemHovered())
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.08f, 0.18f, 0.21f, 1.0f), ImVec4(0.10f, 0.48f, 0.68f, 1.000f), t));
        else
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.12f, 0.22f, 0.25f, 1.0f), ImVec4(0.14f, 0.52f, 0.72f, 1.000f), t));
        // 组件绘制
        DrawList->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + Width, p.y + Height), Color, 360);
        DrawList->AddCircleFilled(ImVec2(p.x + Radius + 2 + t * (Width - (Radius + 2) * 2), p.y + Radius + 2), Radius + 2, IM_COL32(255, 255, 255, 255), 360);
        DrawList->AddCircleFilled(ImVec2(p.x + Radius + t * (Width - Radius * 2) + (t == 0 ? 2 : -2), p.y + Radius + 2), Radius, IM_COL32(230, 230, 230, 255), 360);
        if (*v)
            DrawList->AddText(ImVec2(p.x + 45, p.y + 2), ImColor{ 255,255,255,255 }, str_id);
        else
            DrawList->AddText(ImVec2(p.x + 45, p.y + 2), ImColor{ 185,185,185,255 }, str_id);

    }

    void OSImGui::MyCheckBox3(const char* str_id, bool* v)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* DrawList = ImGui::GetWindowDrawList();
        float Height = ImGui::GetFrameHeight();
        float Width = Height;
        float Left = 8;
        float Right = Left * 1.5f;
        ImGui::InvisibleButton(str_id, ImVec2(Width, Height));

        if (ImGui::IsItemClicked())
            *v = !(*v);
        // 组件移动动画
        float t = *v ? 1.0f : 0.f;
        ImGuiContext& g = *GImGui;
        float AnimationSpeed = 0.12f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
        {
            float T_Animation = ImSaturate(g.LastActiveIdTimer / AnimationSpeed);
            t = *v ? (T_Animation) : (1.0f - T_Animation);
        }
        // 鼠标悬停颜色
        ImU32 Color;
        ImU32 TickColor1, TickColor2;
        if (ImGui::IsItemHovered())
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), ImVec4(0.05f, 0.85f, 0.25f, 1.000f), t));
        else
            Color = ImGui::GetColorU32(ImLerp(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.1f, 0.9f, 0.3f, 1.000f), t));

        TickColor1 = IM_COL32(255, 255, 255, 255 * t);
        TickColor2 = IM_COL32(180, 180, 180, 255 * (1 - t));

        float Size = Width;
        float Scale = (float)(Size) / 20.0f;
        // 底色
        DrawList->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + Width, p.y + Height), Color, 5, 15);
        // 选中勾
        DrawList->AddLine(ImVec2(p.x + 3 * Scale, p.y + Size / 2 - 2 * Scale), ImVec2(p.x + Size / 2 - 1 * Scale, p.y + Size - 5 * Scale), TickColor1, 3 * Scale);
        DrawList->AddLine(ImVec2(p.x + Size - 3 * Scale - 1, p.y + 3 * Scale + 1), ImVec2(p.x + Size / 2 - 1 * Scale, p.y + Size - 5 * Scale), TickColor1, 3 * Scale);
        // 未选中勾
        DrawList->AddLine(ImVec2(p.x + 3 * Scale, p.y + Size / 2 - 2 * Scale), ImVec2(p.x + Size / 2 - 1 * Scale, p.y + Size - 5 * Scale), TickColor2, 3 * Scale);
        DrawList->AddLine(ImVec2(p.x + Size - 3 * Scale - 1, p.y + 3 * Scale + 1), ImVec2(p.x + Size / 2 - 1 * Scale, p.y + Size - 5 * Scale), TickColor2, 3 * Scale);
        ImGui::SameLine();
        ImGui::Text(str_id);
    }

    void OSImGui::MyCheckBox4(const char* str_id, bool* v)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* DrawList = ImGui::GetWindowDrawList();
        float Height = ImGui::GetFrameHeight();
        float Width = Height;
        ImGui::InvisibleButton(str_id, ImVec2(Width, Height));

        if (ImGui::IsItemClicked())
            *v = !(*v);
        // 组件动画
        float t = *v ? 1.0f : 0.f;
        ImGuiContext& g = *GImGui;
        float AnimationSpeed = 0.12f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
        {
            float T_Animation = ImSaturate(g.LastActiveIdTimer / AnimationSpeed);
            t = *v ? (T_Animation) : (1.0f - T_Animation);
        }
        // bg 0.74 0.72 0.81-> 0.69 0.77 0.76
        ImU32 BgColor;
        if (ImGui::IsItemHovered())
            BgColor = ImGui::GetColorU32(ImVec4(0.69f, 0.69f, 0.69f, 1.0f));
        else
            BgColor = ImGui::GetColorU32(ImVec4(0.74f, 0.74f, 0.74f, 1.0f));
        DrawList->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + Width, p.y + Width), BgColor);

        ImU32 FrColor;
        FrColor = ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.5f * t));
        DrawList->AddRectFilled(ImVec2(p.x + Width / 5, p.y + Width / 5), ImVec2(p.x + Width - Width / 5, p.y + Width - Width / 5), FrColor);

        ImGui::SameLine();
        ImGui::Text(str_id);
    }

    void OSImGui::ShadowRectFilled(Vec2 Pos, Vec2 Size, ImColor RectColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, float Rounding)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        ImDrawFlags Flags = (Rounding > 0.f) ? ImDrawFlags_RoundCornersMask_ : ImDrawFlags_None;
        DrawList->AddShadowRect(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, ShadowColor, ShadowThickness, ShadowOffset.ToImVec2(), Flags, Rounding);
        DrawList->AddRectFilled(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, RectColor, Rounding);
    }

    void OSImGui::ShadowCircle(Vec2 Pos, float Radius, ImColor CircleColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, int Num)
    {
        ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
        DrawList->AddShadowCircle(Pos.ToImVec2(), Radius, ShadowColor, ShadowThickness, ShadowOffset.ToImVec2(), ImDrawFlags_None, Num);
        DrawList->AddCircleFilled(Pos.ToImVec2(), Radius, CircleColor, Num);
    }

    bool OSImGui::SliderScalarEx1(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = ImGui::CalcItemWidth();

        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, (Vec2(window->DC.CursorPos) + Vec2(w, label_size.y + style.FramePadding.y * 2.0f)).ToImVec2());
        const ImRect total_bb(frame_bb.Min, (Vec2(frame_bb.Max) + Vec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f)).ToImVec2());

        const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
            return false;

        // Default format string when passing NULL
        if (format == NULL)
            format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

        const bool hovered = ImGui::ItemHoverable(frame_bb, id);
        bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
        if (!temp_input_is_active)
        {
            // Tabbing or CTRL-clicking on Slider turns it into an input box
            const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
            const bool clicked = hovered && ImGui::IsMouseClicked(0, id);
            const bool make_active = (input_requested_by_tabbing || clicked || g.NavActivateId == id);
            if (make_active && clicked)
                ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
            if (make_active && temp_input_allowed)
                if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || (g.NavActivateId == id && (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
                    temp_input_is_active = true;

            if (make_active && !temp_input_is_active)
            {
                ImGui::SetActiveID(id, window);
                ImGui::SetFocusID(id, window);
                ImGui::FocusWindow(window);
                g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
            }
        }

        if (temp_input_is_active)
        {
            // Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
            const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
            return ImGui::TempInputScalar(frame_bb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
        }

        float grab_radius = 8;

        // Draw frame
        ImRect frame_sc = frame_bb;
        float frame_height_origin = frame_sc.GetHeight();
        frame_sc.Min.y += frame_height_origin / 3;
        frame_sc.Max.y -= frame_height_origin / 3;
        const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        ImGui::RenderNavHighlight(frame_bb, id);
        window->DrawList->AddRectFilled(frame_sc.Min, frame_sc.Max, frame_col, grab_radius);

        // Slider behavior
        ImRect grab_bb;
        const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
        if (value_changed)
            ImGui::MarkItemEdited(id);

        // Render grab
        if (grab_bb.Max.x > grab_bb.Min.x)
        {
            window->DrawList->AddShadowCircle(grab_bb.GetCenter(), grab_radius, ImColor(30, 30, 30, 255), 9, { 0,0 });
            window->DrawList->AddCircleFilled(grab_bb.GetCenter(), grab_radius, ImColor(220, 220, 220, 255));
        }

        // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
        char value_buf[64];
        const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
        if (g.LogEnabled)
            ImGui::LogSetNextTextDecoration("{", "}");
        ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));


        // label
        if (label_size.x > 0.0f)
            ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);


        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
        return value_changed;
    }

}

