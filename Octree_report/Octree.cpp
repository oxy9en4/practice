#include "stdafx.h"
#include "Octree.h"

void Octree::Run()
{
    mpRootNode = new Node(++iNumCounter);
    BuildTree(mpRootNode); // BuildTree is recursive func.
}

void Octree::BuildTree(Node* pParent)
{
    if (pParent->miDepth > 1) return; // Escape condition by Depth

    
    for (int i = 0; i < pParent->mpChild.size(); ++i) {
        Vector3 vHalf = pParent->mBox.mHalf * 0.5f;
        
        float Width = 0.0f, Height = 0.0f, Depth = 0.0f;
        if ((i % 4 == 0) % 3 != 0) Width = vHalf.x;
        if (i % 4 > 1) Height = vHalf.y;
        if (i > 3) Depth = vHalf.z;
        Vector3 fSize(Width, Height, Depth);

        Node* pNewNode = CreateNode(pParent, pParent->mBox.mPoint[0] / 2 + fSize, vHalf);
        
        pParent->mpChild.push_back(pNewNode);

        BuildTree(pParent->mpChild[i]);
    }
}

Node* Octree::CreateNode(Node* pParent, float x, float y, float z, float w, float h, float d)
{
    Node* pNode = new Node(++iNumCounter);
    pNode->SetParent(pParent);
    pNode->mBox.Set(x, y, z, w, h, d);
    return pNode;
}

Node* Octree::CreateNode(Node* pParent, Vector3 p, float w, float h, float d)
{
    Node* pNode = new Node(++iNumCounter);
    pNode->SetParent(pParent);
    pNode->mBox.Set(p, w, h, d);
    return pNode;
}

Node* Octree::CreateNode(Node* pParent, Vector3 p, Vector3 size)
{
    Node* pNode = new Node(++iNumCounter);
    pNode->SetParent(pParent);
    pNode->mBox.Set(p, size);
    return pNode;
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
