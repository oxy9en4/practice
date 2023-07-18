#include "stdafx.h"
#include "SQuadTree.h"

std::vector<SObject*> StaticObjectList;
std::vector<SObject*> DynamicObjectList;

void SetStaticObject(SQuadTree& quadtree) {
    for (int i = 0; i < 3; ++i) {
        SObject* obj = new SStaticObject();
        obj->mName = L"StaticObj";
        obj->mName += std::to_wstring(i);
        obj->mPivot = { (float)(rand() % 800), (float)(rand() % 600) };
        obj->SetRect(obj->mPivot,
            (float)((rand() % 10) + 1.0f),
            (float)((rand() % 10) + 1.0f));
        quadtree.StaticAddObject(obj);
        StaticObjectList.push_back(obj);
    }
}


void SetDynamicObject(SQuadTree& quadtree) {
    for (int i = 0; i < 3; ++i) {
        SObject* obj = new SDynamicObject();
        obj->mName = L"DynamicObj";
        obj->mName += std::to_wstring(i);
        obj->mPivot = { (float)(rand() % 800), (float)(rand() % 600) };
        obj->SetRect(obj->mPivot,
            (float)((rand() % 10) + 1.0f),
            (float)((rand() % 10) + 1.0f));
        SPoint p = { (float)randstep(0, 800), (float)randstep(0,600) };
        obj->SetTarget(p);
        quadtree.DynamicAddObject(obj);
        DynamicObjectList.push_back(obj);
    }
}


int main()
{
    SQuadTree quadtree;
    quadtree.Run();
    SetStaticObject(quadtree);
    SetDynamicObject(quadtree);
    

}
