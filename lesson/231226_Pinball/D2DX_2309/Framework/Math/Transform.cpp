#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
    S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
    R = XMMatrixRotationRollPitchYaw(localRotation.x, localRotation.y, localRotation.z);
    T = XMMatrixTranslation(localPosition.x, localPosition.y, 0);

    P = XMMatrixTranslation(pivot.x, pivot.y, 0);
    IP = XMMatrixInverse(nullptr, P);

    world = IP * S * R * T * P;

    if (parent)
        world *= parent->world;

    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    XMStoreFloat2(&globalPosition, outT);
    XMStoreFloat2(&globalScale, outS);

    XMStoreFloat4x4(&matWorld, world);
    right = Vector2(matWorld._11, matWorld._12);
    up = Vector2(matWorld._21, matWorld._22);
}

void Transform::GUIRender()
{
    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        ImGui::Text(tag.c_str());

        ImGui::Checkbox("Active", &isActive);

        string temp = tag + "_Pos";
        ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);

        temp = tag + "_Rot";
        Float3 rot;
        rot.x = XMConvertToDegrees(localRotation.x);
        rot.y = XMConvertToDegrees(localRotation.y);
        rot.z = XMConvertToDegrees(localRotation.z);

        ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

        localRotation.x = XMConvertToRadians(rot.x);
        localRotation.y = XMConvertToRadians(rot.y);
        localRotation.z = XMConvertToRadians(rot.z);

        temp = tag + "_Scale";
        ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);

        temp = tag + "_Pivot";
        ImGui::DragFloat2(temp.c_str(), (float*)&pivot, 0.1f);

        if (ImGui::Button("Save"))
            Save();
        
        ImGui::SameLine();
        
        if (ImGui::Button("Load"))
            Load();

        ImGui::TreePop();
    }
}

void Transform::Save()
{
    BinaryWriter* writer = new BinaryWriter("TextData/Transforms/" + tag + ".srt");

    writer->Float(localPosition.x);
    writer->Float(localPosition.y);

    writer->Float(localRotation.x);
    writer->Float(localRotation.y);
    writer->Float(localRotation.z);

    writer->Float(localScale.x);
    writer->Float(localScale.y);

    writer->Float(pivot.x);
    writer->Float(pivot.y);

    delete writer;
}

void Transform::Load()
{
    BinaryReader* reader = new BinaryReader("TextData/Transforms/" + tag + ".srt");

    if (reader->IsFailed()) return;

    localPosition.x = reader->Float();
    localPosition.y = reader->Float();

    localRotation.x = reader->Float();
    localRotation.y = reader->Float();
    localRotation.z = reader->Float();

    localScale.x = reader->Float();
    localScale.y = reader->Float();

    pivot.x = reader->Float();
    pivot.y = reader->Float();

    delete reader;
}

bool Transform::IsActive()
{
    if (parent == nullptr)
        return isActive;

    if (isActive == false)
        return false;

    return parent->IsActive();
}
