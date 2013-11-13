#ifndef VIEWERWIDGET
#define VIEWERWIDGET

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include "GraphicsWindowQt.h"
#include <osgViewer/Viewer>


class ViewerWidget : public QWidget
{
public:
    ViewerWidget( osg::Camera* camera, osg::Node* scene )
        :   QWidget()
    {
        _viewer.setCamera( camera );
        _viewer.setSceneData( scene );
        _viewer.addEventHandler( new osgViewer::StatsHandler );
        _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
        _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

        osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>( camera->getGraphicsContext() );
        if ( gw )
        {
            QVBoxLayout* layout = new QVBoxLayout;
            layout->addWidget( gw->getGLWidget() );
            setLayout( layout );
        }

        connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
        _timer.start( 40 );
    }

protected:
    virtual void paintEvent( QPaintEvent* event )
    { _viewer.frame(); }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

#endif