#ifndef ANIMATIONMANAGER
#define ANIMATIONMANAGER

#include <osg/MatrixTransform>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgAnimation/StackedRotateAxisElement>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/Animation>
#include <osg/Array>

#include <set>
#include <map>
#include <utility>

class AnimationManager
{
private:
    explicit AnimationManager(){}

public:
    static AnimationManager* singleton()
    {
        if(!_animationManager)
            _animationManager = new AnimationManager;
        return _animationManager;
    }

    void setRootSenceNode(osg::Group* root);
    bool addAnimationNode(osg::MatrixTransform* node);
    bool playAnimation4Node(osg::MatrixTransform* node);

    // this is a travel animation
    bool setTranslatePath4Node( osg::MatrixTransform* node , osg::Vec3Array* vertices );

private:
    bool _generateKeyFrames4Translate(osgAnimation::Vec3LinearChannel* ch , osg::Vec3Array* vertices);

private:
    int _animationNodeCount;
    static AnimationManager* _animationManager;
    static osg::ref_ptr<osgAnimation::BasicAnimationManager> _realManager;
    static osg::ref_ptr<osg::Group> _rootScene;

    static std::set<osg::ref_ptr<osg::MatrixTransform>> _animationNodeSet;

    typedef std::pair<osg::ref_ptr<osgAnimation::Animation> 
        , osg::ref_ptr<osgAnimation::UpdateMatrixTransform>
    >   AnimationRequirement;

    typedef std::map<osg::ref_ptr<osg::MatrixTransform>, AnimationRequirement> AnimationMapType;
    static AnimationMapType AnimationManager::_animationMap;
};
#endif