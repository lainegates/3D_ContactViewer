#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <osg/BlendFunc>
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
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f) );
    doorShape->setColor( osg::Vec4(0.0f, 0.0f, 1.0f, 0.9f) );

//     osg::StateSet* stateset = doorShape->getOrCreateStateSet();
//     //Alpha混合开启
//     stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
//     //取消深度测试
//     stateset->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF  );
//     stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
//     //设置渲染优先级------级别理论上来讲 比你背景的node靠后就行，没设置过的是-1. 
//     stateset->setRenderBinDetails(5, "RenderBin");


    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( doorShape.get() );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode.get() );
    return trans.release();
}


osg::MatrixTransform* createDoor2()
{
    osg::ref_ptr<osg::ShapeDrawable> doorShape1 =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f) );
    doorShape1->setColor( osg::Vec4(1.0f, 0.0f, 0.0f, 0.9f) );

//     osg::StateSet* stateset = doorShape1->getOrCreateStateSet();
//     //Alpha混合开启
//     stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
//     //取消深度测试
//     stateset->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF  );
//     stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
//     //设置渲染优先级------级别理论上来讲 比你背景的node靠后就行，没设置过的是-1. 
//     stateset->setRenderBinDetails(11, "RenderBin");
// 

    osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
    geode1->addDrawable( doorShape1.get() );

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode1.get() );
    return trans.release();
}

osg::MatrixTransform* createDoor3()
{
    osg::ref_ptr<osg::ShapeDrawable> doorShape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 2.0f, 2.0f, 2.0f) );
    doorShape->setColor( osg::Vec4(0.0f, 1.0f, 1.0f, 0.5f) );

    osg::StateSet* stateset = doorShape->getOrCreateStateSet();

//     //Alpha混合开启
//     stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
//     //取消深度测试
//     stateset->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF  );
//     stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );
//     //设置渲染优先级------级别理论上来讲 比你背景的node靠后就行，没设置过的是-1. 
//     stateset->setRenderBinDetails(5, "RenderBin");
// 
//     stateset->setMode(GL_BLEND,osg::StateAttribute::ON);  

    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();      
    blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);       
    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);        
    stateset->setAttributeAndModes( blendFunc );
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);  


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
    camera->setClearColor( osg::Vec4(1, 1, 1, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
    return camera.release();
}

void setRootNodeBlend(osg::Group* group)
{
    osg::StateSet* state = group->getOrCreateStateSet();
    osg::Material* mat = dynamic_cast<osg::Material*>(state->getAttribute(osg::StateAttribute::MATERIAL));
    if(!mat)
        mat = new osg::Material;

    mat->setAlpha(osg::Material::Face::FRONT_AND_BACK,0.5);

    state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);  
    state->setMode(GL_BLEND,osg::StateAttribute::ON);  

    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();      
    blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);       
    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);        
    state->setAttributeAndModes(blendFunc, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);     
    state->setAttributeAndModes(mat,osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);    
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
    root->addChild( createDoor3() );
    root->addChild( createDoor2() );

//     setRootNodeBlend(root);

    assert(AnimationManager::singleton()->playAnimation4Node(animDoor));


    QApplication app( argc, argv );
    osg::Camera* camera = createCamera( 50, 50, 640, 480 );

    ViewerWidget* widget = new ViewerWidget(camera, root);
    widget->setGeometry( 100, 100, 800, 600 );
    widget->show();
    return app.exec();
}
