# Print FrameElement

## Issue how to print a xaml element in winui 3
How to access printer and print an xaml element. A page choose from navigation view.

MainWindow.xaml.cpp
```cpp
#include "pch.h"

#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Printing.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
//#include <winrt/Microsoft.UI.Xaml.Printing.PrintManager.h>
//#include <winrt/Windows.Graphics.Printing.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PrintingFrameworkElement::implementation
{
    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        // Do printing of the FrameworkElement here
        using namespace winrt::Microsoft::UI::Xaml;
        using namespace winrt::Microsoft::UI::Xaml::Printing;

        // Create PrintDocument
        PrintDocument printDoc = PrintDocument();

        // Create a XAML element to print
        auto content = NavContent().Content().as<FrameworkElement>();

        // FIXME: This is not working
        // Exception thrown at 0x00007FFBAD0BFB4C (KernelBase.dll) in PrintingFrameworkElement.exe: WinRT originate error - 0x80040155 : 'Interface not registered'.
        // Exception thrown at 0x00007FFBAD0BFB4C in PrintingFrameworkElement.exe: Microsoft C++ exception: winrt::hresult_error at memory location 0x000000F8A09D9DA8.
        //auto printManager = Windows::Graphics::Printing::PrintManager::GetForCurrentView();

        //// Register for PrintTaskRequested event
        //printManager.PrintTaskRequested([=](Windows::Graphics::Printing::PrintManager const&, Windows::Graphics::Printing::PrintTaskRequestedEventArgs const& args)
        //    {
        //        Windows::Graphics::Printing::PrintTask task = args.Request().CreatePrintTask(L"Print Document",
        //            [](Windows::Graphics::Printing::PrintTask const& sender, Windows::Graphics::Printing::PrintTaskSourceRequestedArgs const& e)
        //            {
        //                e.SetSource(sender.Source());
        //            });
        //    });

        // Start the print process
        //Windows::Graphics::Printing::PrintManager::ShowPrintUIAsync();


        // New approach


        printDoc.Paginate([](IInspectable const&, PaginateEventArgs const& args)
            {
                // Create custom print logic
            });

        printDoc.GetPreviewPage([](IInspectable const&, GetPreviewPageEventArgs const& args)
            {
                // Provide preview page logic
            });

        printDoc.AddPages([](IInspectable const&, AddPagesEventArgs const& args)
            {
                // Add content pages to print
            });
    }
    void MainWindow::OnNavigationViewItemInvoked(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& e)
    {
        auto invokedItemContainer = e.InvokedItemContainer().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
        auto tag = winrt::unbox_value_or<hstring>(invokedItemContainer.Tag(), L"");
        auto type = winrt::Windows::UI::Xaml::Interop::TypeName{ tag, winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata };
        NavContent().Navigate(type);
    }
    void MainWindow::NavigateToPage(hstring const& pageName)
    {
        // Find the NavigationViewItem with the specified tag
        for (auto const& item : NavControl().MenuItems())
        {
            if (auto navItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>())
            {
                if (winrt::unbox_value_or<hstring>(navItem.Tag(), L"") == pageName)
                {
                    // Set the selected item
                    NavControl().SelectedItem(navItem);
                    // Navigate to the page
                    auto type = winrt::Windows::UI::Xaml::Interop::TypeName{ pageName, winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata };
                    NavContent().Navigate(type);
                    return;
                }
            }
        }
    }
}
```

### Envoriment

- Cpp 20
- Winui 3
- Visual Studio 2022

## Issue and solution

### Get actual window handle hwnd
How to get the actual window handle hwnd of the current window in WinUI 3.
#### Solution
```cpp
// Retrieve the window handle (HWND) of the current WinUI 3 window.
// @see https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd
auto windowNative{ this->m_inner.as<::IWindowNative>() };
HWND hWnd{ nullptr };
windowNative->get_WindowHandle(&hWnd);
```

### Create an instance of IPrintManagerInterop
How to create an instance of IPrintManagerInterop in WinUI 3.

Tried to create an instance of IPrintManagerInterop in WinUI 3, but it is not working.
```cpp
// Create an instance of IPrintManagerInterop
com_ptr<IPrintManagerInterop> printManagerInterop;
auto CLSID_PrintManagerInterop = __uuidof(printManagerInterop); // GUID of IPrintManagerInterop
//hr = CoCreateInstance(CLSID_PrintManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(printManagerInterop.put()));
hr = CoCreateInstance(CLSID_PrintManagerInterop, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(printManagerInterop.put())); 
if (FAILED(hr))
{
    OutputDebugString(L"Failed to create instance of IPrintManagerInterop.\n");
    return;
}
```

### Do the printing of the FrameworkElement
How to do the printing of the FrameworkElement in WinUI 3.

TODO : Implement the printing of the FrameworkElement in WinUI 3.

## Stackoverflow

[How to access printer and print an xaml element. A page choose from navigation view.](https://stackoverflow.com/questions/79283567/xaml-element-to-print)
