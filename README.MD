## C++ Mono Runtime Injector DLL
> Inject mono runtime instance into 64bit process :)
(this project has nothing to do with minhook its just an old name from other tests)
How To:
- Use an injector like extreme injector to inject into the game, mono-2.0-sgen.dll and MinHookTrolling.dll
Look at dllmain.cpp -> find path to the dll and set it to whatever you like
your dll must be compiled with .net framework 4.7.2
now you can run functions on objects from your dll :)
- currently doesnt work with unhollower or at least we havent figured it out

> Building
> - install mono
> - Set env variable MONO_PROJECT\ to your mono install directory (the one with the 5 folders)
> - should be able to just build and run
> - build release x64 others wont work
> 
sorry this is so scuffed rn im going to bed i havent slept in 2 days