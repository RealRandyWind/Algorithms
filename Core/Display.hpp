#pragma once

#include <Types>
#include <Drivers/DisplayDriver>
#include <Point>
#include <Iterator>
#include <Model>
#include <Styles/Scatter>

namespace Display
{
    using namespace Drivers;
    
    template<FSize Size, typename Type>
    FVoid Scatter(
            const TIterator<TPoint<Size,Type>> &Data
        )
    {
        TScatter<Size,Type> Style;
        Style.SizeData = Data.Size();
        Style.Data = Data.Data;
        FWindow Window = FWindow::Default();
        auto Driver = MDisplayDriver::Instance();
        Driver->Make(Window);
        Driver->Make(Style, Window);
        Driver->Frame(Window);
    }

    FReturn Wait(
            FSize = 0
        )
    {
        auto Driver = MDisplayDriver::Instance();
        return Driver->Wait();
    }
}