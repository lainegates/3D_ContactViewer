#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgAnimation/StackedRotateAxisElement>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/Animation>
#include <osgga/GUIEventHandler>
#include <osgdb/ReadFile>
#include <osgViewer/Viewer>
#include <osg/io_utils>
using namespace std;

#include <assert.h>
#include "AnimationManager.h"



osg::MatrixTransform* createDoor()
{
    osg::ref_ptr<osg::ShapeDrawable> doorShape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(2.5f, 0.0f, 0.0f), 6.0f, 0.2f, 10.0f) );
    doorShape->setColor( osg::Vec4(1.0f, 1.0f, 0.8f, 1.0f) );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( doorShape.get() );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode.get() );
    return trans.release();
}


osg::MatrixTransform* createDoor2()
{
    osg::ref_ptr<osg::ShapeDrawable> doorShape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f) );
    doorShape->setColor( osg::Vec4(0.0f, 1.0f, 0.8f, 1.0f) );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( doorShape.get() );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode.get() );
    return trans.release();
}


int main()
{
    osg::MatrixTransform* animDoor = createDoor();
    osg::ref_ptr<osg::Group> root = new osg::Group;

    AnimationManager::singleton()->setRootSenceNode(root);
    assert(AnimationManager::singleton()->addAnimationNode(animDoor));
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    AnimationManager::singleton()->setTranslatePath4Node(animDoor, vertices);

    root->addChild( animDoor );
    root->addChild( createDoor2() );

    assert(AnimationManager::singleton()->playAnimation4Node(animDoor));
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    //     viewer.addEventHandler( handler.get() );
    return viewer.run();
}

