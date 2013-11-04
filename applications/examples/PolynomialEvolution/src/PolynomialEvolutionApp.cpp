//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "PolynomialPopulation.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PolynomialEvolutionApp : public AppNative {
public:
	void prepareSettings(Settings* settings);
	void setup();
	void mouseMove(MouseEvent event);
	void mouseDown(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void mouseUp(MouseEvent event);
	void keyDown(KeyEvent event);
	void keyUp(KeyEvent event);
	void update();
	void draw();
	void shutdown();
	
	FontSuitcase*			mSuitcase;
	UiBase*					mScene;
	UiText*					mInfoLabel;
	
	PolynomialPopulation*	mPopulation;
	PolynomialDataRef		mBest;
	
	UiPlot*					mPlotRef;
};

void PolynomialEvolutionApp::prepareSettings(Settings* settings)
{
	settings->setWindowSize( 1000, 1000 );
	settings->enableHighDensityDisplay();
}

void PolynomialEvolutionApp::setup()
{
	ci::randSeed( (unsigned int)time( NULL ) );
	
	mSuitcase = new FontSuitcase();
	
	mSuitcase->addFamily( "Heuristica",
						 getAssetPath( "Heuristica-Regular.otf" ).string(),
						 getAssetPath( "Heuristica-Italic.otf" ).string(),
						 getAssetPath( "Heuristica-Bold.otf" ).string(),
						 getAssetPath( "Heuristica-BoldItalic.otf" ).string() );
	
	mScene = new UiBase();
	mScene->setPosition( Vec2f( 0.0, 0.0 ) );
	mScene->setRelativeDimension( Vec2f( 1.0, 1.0 ) );
	
	mInfoLabel = new UiText( "", "Heuristica", 14, FontStyle::BOLD, mSuitcase );
	mInfoLabel->setRelativePosition( Vec2f( 0.5, 1.0 ) );
	mInfoLabel->setTextColor( ColorA::white() );
	mInfoLabel->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
	mScene->addChild( mInfoLabel );
	
	PolynomialDataRef tFormula(  new PolynomialData( -10.0, 10.0, true, true, ColorA( 0, 1, 0, 1 ) ) );
	tFormula->addComponent( 1.0, 2.0 );
	
	PolynomialDataRef tAssertFormulaA( new PolynomialData( -10.0, 10.0, true, false, ColorA( 1, 1, 0, 1 ) ) );
	tAssertFormulaA->addComponent( 2.0, 1.0 );
	tAssertFormulaA->addComponent( 2.0, 0.0 );
	
	PolynomialDataRef tAssertFormulaB( new PolynomialData( -10.0, 10.0, true, false, ColorA( 1, 1, 0, 1 ) ) );
	tAssertFormulaB->addComponent( 2.0, 1.0 );
	tAssertFormulaB->addComponent( -2.0, 0.0 );
	
	AssertionGroup tAssertGroup = AssertionGroup();
	
	AssertionRef tAssertA = AssertionRef( new Assertion() );
	tAssertA->setDataRhs( tAssertFormulaA );
	tAssertA->setParameterRange( -10.0, 10.0 );
	tAssertA->setType( IS_LESS );
	tAssertA->setMode( FOR_DERIVATIVE, FOR_FUNCTION );
	tAssertGroup.add( tAssertA );
	
	AssertionRef tAssertB = AssertionRef( new Assertion() );
	tAssertB->setDataRhs( tAssertFormulaB );
	tAssertB->setParameterRange( -10.0, 10.0 );
	tAssertB->setType( IS_GREATER );
	tAssertB->setMode( FOR_DERIVATIVE, FOR_FUNCTION );
	tAssertGroup.add( tAssertB );
	
	cout << tAssertGroup.getAssertionString( tFormula ) << endl;
	
	mPopulation = new PolynomialPopulation( tAssertGroup, 1000, 500, 0.1, 1.0 );
	
	{
		mPlotRef = new UiPlot( "Heuristica", mSuitcase );
		mPlotRef->addInput( tFormula );
		mPlotRef->addInput( tAssertFormulaA );
		mPlotRef->addInput( tAssertFormulaB );
		mPlotRef->setXRange( -10.0, 10.0 );
		mPlotRef->setYRange( -10.0, 10.0 );
		mPlotRef->setFillColor( ColorA( 1, 0, 0, 1 ) );
		mPlotRef->setStrokeColor( ColorA( 1, 1, 0, 1 ) );
		mPlotRef->setStrokeWeight( 1.0 );
		mPlotRef->setRelativePosition( Vec2f( 0.5, 0.5 ) );
		mPlotRef->setRelativeDimension( Vec2f( 0.9, 0.9 ) );
		mScene->addChild( mPlotRef );
	}
}

void PolynomialEvolutionApp::mouseMove(MouseEvent event)
{
	if( mScene ) {
		mScene->deepMouseMove( event );
	}
}

void PolynomialEvolutionApp::mouseDown(MouseEvent event)
{
	if( mScene ) {
		mScene->deepMouseDown( event );
	}
}

void PolynomialEvolutionApp::mouseDrag(MouseEvent event)
{
	if( mScene ) {
		mScene->deepMouseDrag( event );
	}
}

void PolynomialEvolutionApp::mouseUp(MouseEvent event)
{
	if( mScene ) {
		mScene->deepMouseUp( event );
	}
}

void PolynomialEvolutionApp::keyDown(KeyEvent event)
{
	if( mScene ) {
		mScene->deepKeyDown( event );
	}
}

void PolynomialEvolutionApp::keyUp(KeyEvent event)
{
	if( mScene ) {
		mScene->deepKeyUp( event );
	}
}

void PolynomialEvolutionApp::update()
{
	// Check if population has an update:
	if( mPopulation->hasUpdate() ) {
		// Remove previous generation from plotter:
		if( mBest ) {
			mPlotRef->removeInput( mBest );
		}
		// Get update:
		mBest = mPopulation->getUpdate();
		// Set drawing parameters:
		mBest->setDrawParameters( -10.0, 10.0, true, true, ColorA( 0, 1, 1, 1 ) );
		// Add current generation to plotter:
		mPlotRef->addInput( mBest );
	}
	// Update info label:
	mInfoLabel->setText( "FPS: " + to_string( getAverageFps() ) + "\t\tRunning Time: " + to_string( getElapsedSeconds() ) + " seconds" );
}

void PolynomialEvolutionApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	gl::enableAlphaBlending();
	gl::setViewport( toPixels( getWindowBounds() ) );
	
	if( mScene ) {
		mScene->deepDraw();
	}
}

void PolynomialEvolutionApp::shutdown()
{
	delete mPopulation;
	delete mScene;
	delete mSuitcase;
}

CINDER_APP_NATIVE( PolynomialEvolutionApp, RendererGl )
