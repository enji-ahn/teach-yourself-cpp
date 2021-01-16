# Teach Yourself C

C 언어 학습을 위한 프로젝트

애매하거나, 테스트 해 보고 싶은것을 구현해서 동작을 확인해 봅시다.

## Project Structure
디렉토리 구조를 다음과 같이 잡아서 진행합니다.

* /project             //Top level folder
  * /bin               //Binaries ready for deployment
    * /amd64           //AMD64 platform
       * /debug        //Debug build - duplicated in all platforms
       * /release      //Release build - duplicated in all platforms
     * /i386           //32-bit platform
  * /build             //Make and build files, IDE project files
     * /config         //Configuration files that build the binaries
     * /linux          //Linux platform
     * /macosx         //Mac OS X
     * /win            //Windows platform
  * CMakeLists.txt 
  * /tools             //External binaries
  * /doc               //Documentation
  * /lib               //External or third-party libraries
    * /platforms       //Platform-specific code for ...
       * /linux_amd64  //Linux AMD64 platform
       * /linux_i386   //Linux 32-bit platform
       * /macosx       //Mac OS X
       * /win32        //Windows 32-bit platform
       * /win64        //Windows 64-bit platform
  * /src               //Source code tree - this will contain main.cpp
    * /headers         //Header files
       * /sample_aaa
       * /sample_bbb
    * /modules         //Platform-independent modules, components or subprojects
       * /sample_aaa
       * /sample_bbb
    * /platforms       //Platform-specific code for ...
       * /linux        //Linux platform-specific code
       * /macosx
       * /win          //Windows platform-specific code
         * samples.sln
         * /sample_aaa
           * sample_aaa.vcxproj
         * /sample_bbb
  * /test              //Automated test scripts

