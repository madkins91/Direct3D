// Include the precompiled headers
#include "pch.h"
#include "Game.h"

// Use some common namespaces to simplify the code
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;


// the class definition for the core "framework" of our app
ref class App sealed : public IFrameworkView
{
	bool windowClosed;
	CGame game;
public:
	virtual void Initialize(CoreApplicationView^ AppView)
	{
		AppView->Activated += ref new TypedEventHandler
			<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

		CoreApplication::Suspending +=
			ref new EventHandler<SuspendingEventArgs^>(this, &App::Suspending);

		CoreApplication::Resuming +=
			ref new EventHandler<Object^>(this, &App::Resuming);

		windowClosed = false;
	}
	virtual void SetWindow(CoreWindow^ Window)
	{
		Window->PointerPressed += ref new TypedEventHandler
			<CoreWindow^, PointerEventArgs^>(this, &App::PointerPressed);

		Window->KeyDown += ref new TypedEventHandler
			<CoreWindow^, KeyEventArgs^>(this, &App::KeyDown);

		Window->KeyUp += ref new TypedEventHandler
			<CoreWindow^, KeyEventArgs^>(this, &App::KeyUp);

		Window->Closed += ref new TypedEventHandler
			<CoreWindow^, CoreWindowEventArgs^>(this, &App::Closed);
	}
	virtual void Load(String^ EntryPoint) 
	{

	}
	virtual void Run()
	{
		game.Initialize();
		// Obtain a pointer to the window
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();

		while (!windowClosed)
		{
			Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// Run game code here
			// ...
			// ...
			game.Update();
			game.Render();
		}
	}
	virtual void Uninitialize() {}

	void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}
	void Suspending(Object^ Sender, SuspendingEventArgs^ Args)
	{
		
	}
	void Resuming(Object^ Sender, Object^ Args)
	{

	}
	void Closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
	{
		windowClosed = true;    // time to end the endless loop
	}
	void PointerPressed(CoreWindow^ Window, PointerEventArgs^ Args)
	{
		MessageDialog dialog("Cursor X: " + Args->CurrentPoint->Position.X + " Cursor Y: " + Args->CurrentPoint->Position.Y, "Notice");
		dialog.ShowAsync();
	}

	void KeyDown(CoreWindow^ Window, KeyEventArgs^ Args)
	{
		/*MessageDialog dialog(Args->VirtualKey.ToString() + " was pressed.", "Notice");
		dialog.ShowAsync();*/
	}

	void KeyUp(CoreWindow^ Window, KeyEventArgs^ Args)
	{
		/*MessageDialog dialog(Args->VirtualKey.ToString() + " was released.", "Notice");
		dialog.ShowAsync();*/
	}
};


// the class definition that creates our core framework
ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();    // create the framework view and return it
	}
};

[MTAThread]    // define main() as a multi-threaded-apartment function

// the starting point of all programs
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());    // run the framework view source
	return 0;
}