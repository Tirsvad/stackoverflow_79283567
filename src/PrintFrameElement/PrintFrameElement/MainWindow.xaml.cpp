// file: MainWindow.xaml.cpp
#include "pch.h"

#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "winrt/base.h"                         // For winrt::com_ptr
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Printing.h>

#include <winrt/Windows.Foundation.h>           // For IInspectable
#include <winrt/Windows.Graphics.Printing.h>

#include <microsoft.ui.xaml.window.h>
//#include <windows.graphics.printing.interop.h>  // For IPrintManagerInterop

#include "winrt/impl/Microsoft.UI.Xaml.2.h"
#include "winrt/impl/Microsoft.UI.Xaml.Controls.2.h"
#include "winrt/impl/Windows.Graphics.Printing.2.h"
#include "winrt/impl/Windows.UI.Xaml.Interop.2.h"
#include "winrt/impl/Windows.UI.Xaml.Interop.0.h"

#include <debugapi.h>                           // For OutputDebugString
#include <objbase.h>                            // For CoInitializeEx
#include <combaseapi.h>                         // For CoCreateInstance
#include <winnt.h>                      
#include <winerror.h>
#include <windef.h>
#include <unknwn.h>                             // For COM pointers (IUnknown)

//#include "IPrintManagerInterop.h"     // Include your manual definition
#include <Printmanagerinterop.h>


#include <initguid.h>

// Manually define CLSID_PrintManager
//DEFINE_GUID(CLSID_PrintManager, 0x92788047, 0x3b5e, 0x41c7, 0x86, 0x2e, 0x4c, 0xd3, 0x0d, 0x45, 0xa3, 0x10);

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PrintFrameElement::implementation
{
    void MainWindow::OnNavigationViewItemInvoked(Windows::Foundation::IInspectable const&, Controls::NavigationViewItemInvokedEventArgs const& e)
    {
        auto invokedItemContainer = e.InvokedItemContainer().as<Controls::NavigationViewItem>();
        auto tag = unbox_value_or<hstring>(invokedItemContainer.Tag(), L"");
        auto type = Windows::UI::Xaml::Interop::TypeName{ tag, winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata };
        NavContent().Navigate(type);
    }
    void MainWindow::NavigateToPage(hstring const& pageName)
    {
        auto type = Windows::UI::Xaml::Interop::TypeName{ pageName, winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata };
        NavContent().Navigate(type);
    }
    void MainWindow::printButton_Click(Windows::Foundation::IInspectable const& sender, RoutedEventArgs const& e)
    {
        m_printContainer = NavContent().as<FrameworkElement>();
        printFrameworkElement(m_printContainer);
    }
    void MainWindow::printFrameworkElement(FrameworkElement const& element)
    {
        using namespace winrt::Windows::Graphics::Printing;
        using namespace Windows::Graphics::Printing;
        using namespace winrt::Microsoft::UI::Xaml::Printing;

        // Retrieve the window handle (HWND) of the current WinUI 3 window.
        // @see https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd
        auto windowNative{ this->m_inner.as<::IWindowNative>() };
        HWND hWnd{ nullptr };
        windowNative->get_WindowHandle(&hWnd);

        if (!hWnd)
        {
            OutputDebugStringW(L"Failed to retrieve the window handle of the current WinUI 3 window.");
            return;
        }

        // Initialize COM library
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        if (FAILED(hr))
        {
            OutputDebugString(L"Failed to initialize COM library.\n");
            return;
        }

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

        // Use IPrintManagerInterop to get the PrintManager instance for the current window
        //com_ptr<IPrintManagerInterop> printManagerInterop;
        //PrintManager printManager = nullptr;

        //check_hresult(printManagerInterop->GetForWindow(hWnd, __uuidof(IPrintManagerInterop), winrt::put_abi(printManager)));


        //check_hresult(::CoCreateInstance(
        //    CLSID_PrintManager,
        //    nullptr,
        //    CLSCTX_INPROC_SERVER,
        //    IID_PPV_ARGS(printManagerInterop.put())));

        //// Create a PrintManager object
        //com_ptr<IPrintManagerInterop> printManagerInterop;
        //hr = get_activation_factory(PrintManager::class_name(), printManagerInterop.put_void());
        //if (FAILED(hr))
        //{
        //    OutputDebugString(L"Failed to get activation factory for PrintManager.\n");
        //    return;
        //}

        // Get the PrintManager instance for the current window
        //auto printManager = winrt::Windows::Graphics::Printing::PrintManager::GetForCurrentView();
        //auto printManager = winrt::Windows::Graphics::Printing::PrintManagerInterop::GetForWindow(hWnd);
        //auto printManager = winrt::Windows::Graphics::Printing::PrintManagerInterop::GetForWindow(hWnd);
    }
}
