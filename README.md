C2DX_BOX2D
==========

The cocos2d-x modified chipmunk physics is complete and utter crap.  
Most notably, there isn't any continuous collision detection making  
tunneling of objects a pain in my ass to deal with. So, I've  
adopted the basterdized box2D PE and integrated it into my projects.  
Honestly though, you're better off rolling out your own custom specialized    
logic for collision detection since general physics engines are really,  
really slow and overkill. But I'm not gonna tell you what to do so everything  
here is "licensed" under the WTFPL unless it's taken from another author  
then just don't get caught if it's not cool.  
  
  
Without futher ado, the tutorials here are built using cocos2d-x v3.2 + box2D  
and MSVC2012 although I've purposefully left out the build files since YMMV.  
I must note that the box2D is aready packaged in the cocos2d-x external folder.  
If Version > 3.2 is released, I will update the guide to setting up Box2D if  
there isn't major backwards incompatibility. Otherwise, I'll be leaving  
these in code rot hell. GET IT WHILE IT'S HOT!  
  
  
SETTING UP BOX2D IN COCOS2D-X V3.2 
==================================

Use the CMakeList.txt provided here  
- Only changes are OFF for Chipmunk flag and ON for Box2D  
  
  
Use the ccConfig.h here and replace the packaged one located in  
<YOUR_C2DX_ROOT_FLDR>/cocos/base/  
or just look through and find the lines,  
  
#ifndef CC_USE_PHYSICS  
#define CC_USE_PHYSICS 1  
#endif  
  
and set to,  
#define CC_USE_PHYSICS 0  


Go through the typical project creation process of,  

`cocos new -l cpp -d ~/path/to/put/project -p org.whatever.here project_name`

Next part depend on your IDE and compiler

### Microsoft Visual Studios 2012

I. Copy the folder `<YOUR_C2DX_ROOT_FLDR>/external/Box2D` into your project's 
external folder.

II. In your MSVC2012 IDE, right click your Solution and `Add -> Exisiting Project..`
Navigate to the folder you transferred in the previous step and use the file
`Box2D/proj.win32/Box2D.vcxproj` 
Should see it listed in your Solution Explorer with the name `libcocos2d`
Right click it and `Build`

III. Right Click your main solution and `Properties -> Configuration Properties -> Linker -> Input -> Additional Dependencies`
Add `libbox2d.lib` and now the row Additional Dependencies should read 
`libbox2d.lib;%(AdditionalDependencies)`

**What this does is to tell the linker it should construct the executable with this the box2d library
Shouldn't get any LNKR errors now 

IV. In the same sidebar, you should see C/C++ -- expand it.
Click on General and add the line `$(EngineRoot)external\Box2D` to the row `Additional Include Directories`

**This lets the compiler know what it should be including when it sees the line `#include "Box2D\Box2d.h"`
Now the intellisense won't scream fuck all and give the error 'cannot open source file'

V. Now add #include "Box2D\Box2D.h" where ever you want and Box2d objects are within the namespace `BOX2D_H`
Congrats, we've ventured through hell and back and now your real suffering can begin. woOOOOooo...
