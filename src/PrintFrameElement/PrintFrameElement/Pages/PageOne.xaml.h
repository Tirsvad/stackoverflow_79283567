#pragma once

#include "PageOne.g.h"

namespace winrt::PrintFrameElement::implementation
{
    struct PageOne : PageOneT<PageOne>
    {
        PageOne()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::PrintFrameElement::factory_implementation
{
    struct PageOne : PageOneT<PageOne, implementation::PageOne>
    {
    };
}
