#include "AnimationManager.h"
#include <string>
#include <assert.h>
#include <algorithm>


std::set<osg::ref_ptr<osg::MatrixTransform>> AnimationManager::_animationNodeSet;

AnimationManager::AnimationMapType  AnimationManager::_animationMap;

AnimationManager* AnimationManager::_animationManager=NULL;
osg::ref_ptr<osg::Group> AnimationManager::_rootScene = NULL;
osg::ref_ptr<osgAnimation::BasicAnimationManager> AnimationManager::_realManager
    = new osgAnimation::BasicAnimationManager;

void AnimationManager::setRootSenceNode(osg::Group* root)
{
    assert(root);
    _rootScene = root;
    _rootScene->setUpdateCallback(_realManager.get());
}

bool AnimationManager::playAnimation4Node(osg::MatrixTransform* node)
{
    assert(node);

    std::set<osg::ref_ptr<osg::MatrixTransform>>::iterator it
        = std::find(_animationNodeSet.begin() , _animationNodeSet.end() , node);
    if( it != _animationNodeSet.end())
        if(_animationMap.find(node)!= _animationMap.end())
        {
            _realManager->playAnimation(_animationMap[node].first);
            return true;
        }
    printf(" animation node not found or animation way not found.\n");
    return false;
}

bool AnimationManager::addAnimationNode(osg::MatrixTransform* node)
{
    if( !_rootScene.valid())
        return false;
    _animationNodeSet.insert(node);
}

bool AnimationManager::setTranslatePath4Node( osg::MatrixTransform* node , osg::Vec3Array* vertices )
{
    // set channel
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> ch = new osgAnimation::Vec3LinearChannel;
    char name[200];
    char targetName[300];
    sprintf(name , "Node%d", _animationNodeSet.size());
    sprintf(targetName , "TargetNode%d" , _animationNodeSet.size());
    ch->setName( name );
    ch->setTargetName( targetName );
    _generateKeyFrames4Translate( ch.get(), vertices );

    // add channel to animation
    osg::ref_ptr<osgAnimation::Animation> animation = new osgAnimation::Animation;
    animation->setPlayMode( osgAnimation::Animation::LOOP );
    animation->addChannel( ch.get() );
    _realManager->registerAnimation(animation);


    // add UpdateMatrixTransform
    osg::ref_ptr<osgAnimation::UpdateMatrixTransform> updater =
        new osgAnimation::UpdateMatrixTransform(targetName);
    updater->getStackedTransforms().push_back(
        new osgAnimation::StackedTranslateElement(name, osg::Vec3(0,0,0)) );

    // add update callback
    node->setUpdateCallback(updater.get());

    _animationMap[node] = std::pair<osg::ref_ptr<osgAnimation::Animation> 
            , osg::ref_ptr<osgAnimation::UpdateMatrixTransform>>( animation , updater );
    return true;
}

bool AnimationManager::_generateKeyFrames4Translate(osgAnimation::Vec3LinearChannel* ch , osg::Vec3Array* vertices2)
{
    assert(ch );
    assert(vertices2);
    osgAnimation::Vec3KeyframeContainer* kfs = ch->getOrCreateSampler()->getOrCreateKeyframeContainer();
    kfs->clear();
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->clear();
    vertices->resize(4);
    (*vertices)[0] = osg::Vec3(10,0,0);
    (*vertices)[1] = osg::Vec3(5,5,0);
    (*vertices)[2] = osg::Vec3(0,5,5);
    (*vertices)[3] = osg::Vec3(0,5,10);

    for(int i=0 ; i<4 ; i++)
        kfs->push_back( osgAnimation::Vec3Keyframe(i , (*vertices)[i]) );

    return true;
}