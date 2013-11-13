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

#include "GraphicsWindowQt.h"
#include <assert.h>
#include "AnimationManager.h"
#include "ViewerWidget.h"



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

osg::Camera* createCamera( int x, int y, int w, int h )
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext( new osgQt::GraphicsWindowQt(traits.get()) );
    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
    return camera.release();
}


int main( int argc, char** argv )
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


    QApplication app( argc, argv );
    osg::Camera* camera = createCamera( 50, 50, 640, 480 );

    ViewerWidget* widget = new ViewerWidget(camera, root);
    widget->setGeometry( 100, 100, 800, 600 );
    widget->show();
    return app.exec();
}

