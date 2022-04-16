#ifndef QUADTREE_HPP_INCLUDED
#define QUADTREE_HPP_INCLUDED
#include<list>
using std::list
template<typename T>

enum QuadType
{
    ROOT,
    ONE,
    TWO,
    THREE,
    FOUR
};
class QuadTreeNode
{
private:
    list<T*> objects
    double x0,y0;
    double width,height;
    QuadTreeNode* parent;
    QuadTreeNode* one;
    QuadTreeNode* two;
    QuadTreeNode* three;
    QuadTreeNode* four;
    QuadType type;
    int level;
    int max_level;

public:
    QuadTreeNode(double x0,double y0,double width,double height,int level,int max_level,QuadType type,QuadTreeNode* parent);
    ~QuadTreeNode();

    void add_object(T* object);
    list<T*> get_object();
    void del();

private:
    bool iscontain(T object);
    list<QuadTreeNode*> splash(double x0,y0,double width,double height)
};

template<typename T>
QuadTreeNode<T>::QuadTreeNode(double x0,double y0,double width,double height,int level,int max_level,QuadType type,QuadTreeNode* parent)
{
    QuadTreeNode.x0=x0;
    QuadTreeNode.y0=y0;
    QuadTreeNode.width=width;
    QuadTreeNode.height=height;
    QuadTreeNode.level=level;
    QuadTreeNode.max_level=max_level;
    QuadTreeNode.type=type;
    QuadTreeNode.parent=parent;
    QuadTreeNode.one=nullptr;
    QuadTreeNode.two=nullptr;
    QuadTreeNode.three=nullptr;
    QuadTreeNode.four=nullptr;
    QuadTreeNode.objects.clear();
}

template<typename T>
QuadTreeNode<T>::~QuadTreeNode()
{
    if(level==maxlevel)
    {
        return;
    }
    else
    {
        delete QuadTreeNode.one;
        delete QuadTreeNode.two;
        delete QuadTreeNode.three;
        delete QuadTreeNode.four;
        QuadTreeNode.parent=nullptr
    }
}

template<typename T>

#endif // QUADTREE_HPP_INCLUDED
