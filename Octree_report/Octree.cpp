#include "stdafx.h"
#include "Octree.h"

void Octree::Run()
{
    mpRootNode = new Node(++iNumCounter);
    BuildTree(mpRootNode); // BuildTree is recursive func.
}

void Octree::BuildTree(Node* pParent)
{
    if (pParent->miDepth > 1) return; // Depth escape

    pParent->mpChild[0]->mBox.mbEnable = true;
    pParent->mpChild[0]->mBox;

    for (int i = 0; i < 8; ++i) {
        pParent->mpChild[i]->miIndex = ++iNumCounter;
        pParent->mpChild[i]->miDepth = pParent->miDepth + 1;
        pParent->mpChild[i]->SetParent(pParent);
        BuildTree(pParent->mpChild[i]);
    }
}

Node* Octree::CreateNode(Node* pParent, float x, float y, float z, float w, float h, float d)
{
    return nullptr;
}

Node* Octree::FindNode(Node* pNode, Object* obj)
{
    return nullptr;
}

Node* Octree::AddStaticObject(Object* obj)
{
    return nullptr;
}

Node* Octree::AddDynamicObject(Object* obj)
{
    return nullptr;
}

void Octree::PreOrder(Node* pNode)
{
}

void Octree::LevelOrder(Node* pNode)
{
}

bool Octree::Init()
{
    return false;
}

bool Octree::PreFrame()
{
    return false;
}

bool Octree::Frame()
{
    return false;
}

bool Octree::PostFrame()
{
    return false;
}

bool Octree::Render()
{
    return false;
}

bool Octree::Release()
{
    return false;
}

Octree::Octree()
{
}

Octree::~Octree()
{
}
