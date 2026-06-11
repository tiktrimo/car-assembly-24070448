#ifdef _DEBUG

#include "gmock/gmock.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

#include "assemblyCar/CarAssemblyApp.h"

int main()
{
    CarAssemblyApp app;
    app.run();
    return 0;
}

#endif
