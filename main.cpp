#include <iostream>

#include "system.h"


using namespace std;

int main()
{
    System system;
    system.Render();

    Argument<int> pass;
    pass.Set(Key<int>(5, 0.0));
    pass.Set(Key<int>(10, 1.0));
    pass.Prepare();

    int x =0;
    while(pass.Get() != 10)
    {
        x++;
        cout<<x<<": "<<pass.Get()<<endl;
        pass.Update(0.05);

    }
    return 0;
}

