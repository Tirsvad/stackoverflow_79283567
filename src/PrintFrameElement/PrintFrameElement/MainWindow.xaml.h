#pragma once

#include "MainWindow.g.h"
#include "winrt/base.h"
#include "winrt/impl/Microsoft.UI.Xaml.2.h"
#include "winrt/impl/Microsoft.UI.Xaml.Controls.2.h"
//#include "MainWindow.xaml.g.h"

namespace winrt::PrintFrameElement::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void OnNavigationViewItemInvoked(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& e);
        void NavigateToPage(hstring const& pageName);

        void printButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void printFrameworkElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);

    private:
        winrt::Microsoft::UI::Xaml::FrameworkElement m_printContainer{ nullptr };
    };
}

namespace winrt::PrintFrameElement::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
