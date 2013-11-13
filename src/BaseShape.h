#ifndef BASESHAPE
#define BASESHAPE

#include <osg/Geode>
#include <osg/

class BaseShape{
public:
    BaseShape(){}
    ~BaseShape(){}

public:
    osg::Geode* getShape(){ return _geode.get();}

    void setVertices(osg::Vec3Array* points){_vertices = points ;}
    osg::Vec3Array* getVertices(){return _vertices.get();}

protected:

private:
    osg::ref_ptr<osg::Geode> _geode;
    osg::ref_ptr<osg::Vec3Array> _vertices;
};

#endif