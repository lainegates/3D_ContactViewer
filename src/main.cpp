#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osgdb/ReadFile>
#include <osgViewer/Viewer>
#include <osg/io_utils>
using namespace std;
int main()
{
    osg::Node* model = osgDB::readNodeFile("cow.osg");

    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
    pat->addChild(model);

    osgViewer::Viewer viewer;
    viewer.setSceneData(pat.get());

    return viewer.run();
    cout<<"hello world!"<<endl;
}